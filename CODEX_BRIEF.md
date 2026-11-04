# VolSmoke — technical brief

Real-time volumetric tire/burnout smoke for BeamNG.drive. Two cooperating parts:

1. **BeamNG mod** (Lua + AngularJS UI): reads vehicle/camera/sun state, runs a per-wheel friction/heat model, hosts the settings UI, and streams telemetry over UDP.
2. **Native ReShade add-on** (`RealSmoke_3D.addon`, a renamed x64 Windows DLL): receives that telemetry, runs a GPU fluid simulation (compute shaders) and ray-marches the smoke into the game's frame before the UI is drawn.

License: MIT (see `mod/LICENSE`). Copyright holder: "VolSmoke contributors". Repo URL in headers is a placeholder: `https://github.com/ThugbobTrapabrickpants/VolSmoke`.

## What is in this package

| Folder | What it is | Status |
|---|---|---|
| `mod/` | Complete BeamNG mod source (Lua, UI, manifest). Ready to use as-is. | **Source of truth, keep structure** |
| `native/` | Clean-source reconstruction notes and initial project scaffold. No functional native implementation yet. | **Scaffold only** |
| `addon_decompiled/` | Ghidra C/C++ decompilation of the current add-on (`RealSmoke_3D.addon.c/.h`). Function and class names are intact (`realsmoke::...`). Not compilable as-is. | **Reference only; rewrite as real source** |
| `shaders_dxbc/` | The 20 exact compiled shaders (DXBC SM 5.0, `.cso`) extracted from the add-on. | **Embed these; do not recompile** |
| `shaders_asm/` | fxc disassembly of the same 20 shaders. Verified instruction-for-instruction identical to `shaders_dxbc/`. | Reference for editing/understanding |

The original HLSL is not available. The `.cso` files are the shaders the add-on shipped with. They are embedded in the add-on as byte arrays (13 of the 20 appear twice, byte-identical, once per graphics backend). Embed each once and share it between the D3D11 and D3D12 paths. Do not ship them as loose files.

## Data flow

```
BeamNG vehicle Lua (VE)  --queueGameEngineLua-->  GE extension  --UDP 29293 (JSON)-->  ReShade add-on (DLL)
  per-wheel friction/heat    hook                  realSmoke3DGE                         GPU sim + smoke render
                                                    ^   |                                       |
              AngularJS UI <-- bngApi.engineLua --- +   +<--- UDP 29294 heartbeat (JSON, ~1 Hz)-+
```

## Mod files (`mod/`)

| File | Role |
|---|---|
| `scripts/realsmoke3d/modScript.lua` | Registers `realSmoke3DGE` as a persistent GE extension (manual unload). |
| `lua/ge/extensions/realSmoke3DGE.lua` | Main game-engine extension / facade. BeamNG hooks: `onExtensionLoaded`, `onUpdate`, `onPreRender`, `onVehicleSpawned/Reset/Switched`, `onReset`, replay events, `onVolSmokeWheelTelemetry`. Exposes the `set*` setters the UI calls. |
| `.../realSmoke3D/networkBridge.lua` | Builds and sends the UDP packets (`env`, `vehicle`) to `127.0.0.1:29293`. |
| `.../realSmoke3D/telemetryReceiver.lua` | Receives wheel telemetry from the vehicle-side Lua, ages/validates it, tracks particle-guard state. |
| `.../realSmoke3D/uiBridge.lua` | All tunable parameters (`PARAM_SPECS`: ranges/defaults), presets, settings persistence (`settings/realSmoke3D_settings.json`), and state pushed to the UI. |
| `.../realSmoke3D/diagnostics.lua` | Heartbeat receiver on UDP 29294; version lock; ReShade/Vulkan/depth-buffer/HDR triage; particle-mod conflict scan; fault codes and messages. |
| `.../realSmoke3D/replaySystem.lua` | Replay/rewind handling (reset sequence, warm-up) so the sim stays consistent. |
| `lua/vehicle/extensions/realSmoke3DVE.lua` | Vehicle-side Lua: per-wheel friction/thermal "burnout" model; sends results to GE via `obj:queueGameEngineLua("extensions.hook('onVolSmokeWheelTelemetry', ...)")`. Also installs a guard on BeamNG's `particleFilter.nodeCollision` to suppress stock particles while 3D smoke is active. |
| `lua/common/particles.json` | Base-game particle material/definition override (used with the particle guard). |
| `ui/modules/apps/realSmoke3D/` | In-game app: `app.json` (manifest), `app.html`, `app.css`, `app.js` (AngularJS directive `realSmoke3DApp`; EN/RU strings; calls Lua through `bngApi.engineLua`). |

## Network protocol

All localhost UDP, one JSON object per datagram. `protocolVersion` is `4`.

**Mod to add-on, port 29293** (add-on binds `127.0.0.1:29293` with `SO_EXCLUSIVEADDRUSE`, non-blocking, on its own thread).
- `type:"env"` (every render frame): `renderFrameId`, `resetSequence`, `replayWarmup`, `dtSim`, `dtReal`, camera (`camPos`, `camFwd`, `camUp`, `fov`, `nearClip`, `farClip`), lighting (`sunDir`, `sunCol`, `ambCol`), and all simulation/appearance tuning (`voxelSize`, `domainSize`, `quality`, `underbodyEject`, `archEject`, `vorticityStrength`, `roadDamping`, `smokeDrag`, `wakeSuction`, `slipstream*`, turbulence, fiber, opacity, ...). The exact key list is in `networkBridge.lua` (`sendEnvironmentTelemetry`); the add-on's parser is `realsmoke::ParseTelemetry` / `parseEnvironment` in the decompile.
- `type:"vehicle"`: `vehicleId`, `pos`, `vel`, `velocityValid`, `bodyValid`, `bodyCenter/Right/Forward/Up/Half` (oriented body box), `profile` (4 floats), `angVel`, `wheels[]`. See `sendVehicleTelemetry`; parser is `parseVehicle`.
- Malformed packets are rejected and logged. Values are range-checked on both sides.

**Add-on to mod, port 29294** (mod binds it): ~1 Hz JSON heartbeat, `type:"heartbeat"`, fields parsed by `diagnostics.lua`: `api`, `ver`, `frames`, `simActive`, `depthOk`, `scaled`, `scalePct`, `depthW`, `depthH`, `frameW`, `frameH`, `hdr`, `uiCaptured`.
Note: the heartbeat sender was not found in the decompile (the DLL does import `sendto`), so write it from this field list.

**Version lock:** the heartbeat `ver` must equal `EXPECTED_MOD_VERSION` in `diagnostics.lua` (currently `0.8.12.9`), else the mod shuts the pipeline down (`ERROR_VERSION_MISMATCH`). The add-on's embedded `VERSION` string is `0.8.12.9`. If you change the version, change it in the add-on, `diagnostics.lua`, and the badge text and check in `app.html` / `app.js`.

## Native add-on

**Toolchain (as shipped):** x64 MinGW-w64 GCC (MSYS2, UCRT runtime), built as a DLL and renamed `.addon`. Imports: `d3d12.dll`, `WS2_32.dll`, `USER32.dll`, `KERNEL32.dll`, UCRT. D3D11 is used through ReShade's native device pointers. Needs the ReShade add-on API headers (`reshade.hpp`). Installed as `Bin64/RealSmoke_3D.addon`, beside a ReShade build with add-on support. The mod reports `ERROR_ADDON_NOT_RESPONDING` if ReShade lacks add-on support.

**Registration (`DllMain`):** on attach, calls `ReShadeRegisterAddon`; registers these ReShade events (handler names from the decompile): `on_present`, `on_draw`, `on_draw_indexed`, `realsmoke::on_depth_bind`, `on_init_resource`, `on_destroy_resource`, `on_init_resource_view`, `on_destroy_resource_view`, `on_reset_d3d12_command_list` (x3), `on_init_d3d12_pipeline`, `on_destroy_d3d12_pipeline`, `on_bind_d3d12_pipeline`, `realsmoke::on_dispatch`, `on_destroy_device`, `on_destroy_swapchain`. Detach unregisters them. Check the decompile for which ReShade event each registration id maps to when rebuilding.

**Main classes (namespace `realsmoke`):** `NetworkReceiver` (UDP thread, snapshots), `D3D11ResourceManager` / `D3D12ResourceManager` (textures, grids, root signatures, descriptors), `SimulationDispatcher` / `D3D12SimulationDispatcher` (fluid sim), `SmokeRenderer` / `D3D12SmokeRenderer` (ray-march + composite), `D3D12DepthCapture` and `BeamNGShadowHook` (scene depth/colour capture, sun shadow probe), `GpuProfiler` (GPU timing/diagnostics logs). Two parallel code paths exist, one per API (D3D11 and D3D12), with the same algorithm.

**Frame pipeline (from log strings):** capture scene depth/colour before BeamNG's CEF UI, then if telemetry shows tyre emission (otherwise the sim sleeps at zero GPU cost): velocity advection, curl, vorticity force, divergence, pressure solve (Jacobi, 5 dispatches x 2 iterations), projection, density injection and advection (limited MacCormack, forward + reverse pass), density-brick build (empty-space skipping), then render smoke at reduced resolution, bilateral upsample, composite, and redraw the UI over it.

## Shader map (role inferred from names, logs and cbuffer layouts; check the asm)

| Shader | Role |
|---|---|
| `CS_VA` | velocity advection |
| `CS_CALC_VORTICITY`, `CS_VORTICITY` | curl; vorticity-confinement force |
| `CS_DIV` | divergence (tiled) |
| `CS_PRESSURE_X2` | Jacobi pressure solve, two iterations per dispatch |
| `CS_PROJECT` | pressure projection (tiled) |
| `CS_I` | emission / density injection |
| `CS_A`, `CS_A_FORWARD`, `CS_A_REVERSE` | density advection; MacCormack forward and reverse passes (the last two differ by one operand sign) |
| `CS_DENSITY_BRICKS` | builds coarse density bricks for ray-march skipping |
| `CS_ShadowProbe`, `CS_ShadowProbeFinalize` | samples the game's sun shadow data into a mask |
| `CS_DIAGNOSTICS` | occupancy/readback telemetry for profiling |
| `PS_S` | main volumetric smoke ray-march pixel shader |
| `PS_BilateralUpsample` | depth-aware upsample of the low-res smoke |
| `PS_UI` | re-composites the captured UI over the smoke |
| `VS_Q`, `PS_A`, `PS_D` | fullscreen-quad vertex shader and small copy/debug pixel shaders |

Compute shaders use 8x8x8 thread groups, except `CS_ShadowProbe` (8x8x1) and `CS_ShadowProbeFinalize` (1x1x1). The constant-buffer layouts are in the asm headers (e.g. `CBSim` in `CS_DIV.asm`); the add-on's CPU-side structs must match them byte for byte.

## Rebuild guidance

- Treat `addon_decompiled/` as a behavioural reference: re-create idiomatic C++ with the same class split, the same UDP protocol and the same shader inputs. Do not paste decompiler output.
- Keep wire compatibility with `mod/` exactly (ports, JSON keys, `protocolVersion`), or change both sides together.
- Keep compute dispatch dimensions, constant-buffer layouts, resource formats and binding slots identical to what the shaders declare.
- Keep log prefixes such as `[SIM PIPELINE OK]`, `[NETWORK ERROR]`, `[GPU PERF]`; they are useful for debugging.
- Pending tasks: (1) project scaffolding (CMake, MinGW-w64 or MSVC, ReShade headers); (2) `NetworkReceiver` and telemetry parsing; (3) heartbeat sender; (4) D3D11 path; (5) D3D12 path; (6) shader embedding from `shaders_dxbc/`; (7) an install script that copies the add-on to `Bin64/` and the mod to BeamNG's mods folder.
