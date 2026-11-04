# Native add-on reconstruction

This directory is the clean-source home for the Windows ReShade add-on. The original C++ source and original HLSL were not recovered. The only native implementation reference is `../addon_decompiled/RealSmoke_3D.addon.c/.h`; those files contain Ghidra artifacts and must not be treated as compilable C++ source.

The original release binary is now preserved at `../reference/RealSmoke_3D.addon` (SHA-256: `C2FFFCBE45C5BFB10D0800A01AF396C0619CA284DDB95EFDEB6695A1CA8FB50E`). It provides the exact artifact to re-inspect and compare against the decompilation, but it does not restore source-level information.

## Recovered facts

- The shipped module is an x64 Windows ReShade add-on renamed to `.addon`.
- It receives localhost UDP telemetry on port 29293 and sends a heartbeat on port 29294 (the heartbeat sender was not recovered).
- The wire protocol version is 4. The BeamNG Lua implementation is in `../mod/lua/ge/extensions/realSmoke3D/networkBridge.lua` and diagnostics are in `../mod/lua/ge/extensions/realSmoke3D/diagnostics.lua`.
- The binary contains D3D11 and D3D12 rendering/simulation paths and uses the 20 recovered DXBC shaders in `../shaders_dxbc/`.
- The add-on version in the recovered build is 0.8.12.9.

## Reconstruction order

1. Set up a Windows x64 toolchain and obtain the ReShade add-on API headers matching the intended ReShade release.
2. Implement strict JSON parsing and versioned UDP receive/snapshot handling; document all field ranges against the Lua sender.
3. Implement the heartbeat sender and make its fields match `diagnostics.lua`.
4. Add shader embedding from the recovered `.cso` files and validate constant buffers, resource formats, register slots, and dispatch dimensions against `shaders_asm/`.
5. Rebuild a minimal D3D11 path, then D3D12 resource management, scene depth/color capture, simulation dispatch, and compositing.
6. Test in BeamNG with supported ReShade builds, both graphics APIs, UI overlays, resets, replay, device loss, and telemetry timeouts.

The current recovered materials are not enough to claim behavioral equivalence or a working native replacement. Keep the known-good released binary separate until a reconstructed build passes runtime validation.
