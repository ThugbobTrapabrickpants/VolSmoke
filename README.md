# VolSmoke

VolSmoke is a BeamNG.drive mod with a Lua telemetry/settings layer and a native ReShade add-on that simulates and renders volumetric tire smoke.

## Repository status

This is a community source recovery and reconstruction repository based on the latest available build. The BeamNG mod sources are present. The native add-on was recovered as a Ghidra decompilation and is being reconstructed as clean source; that decompilation is reference material, not compilable project source. Original HLSL was not recovered. The exact compiled DXBC shader programs are in `shaders_dxbc/` and their disassembly is in `shaders_asm/`. The release binary supplied for comparison is preserved in `reference/`.

The native project scaffold is intentionally not presented as a working replacement for the released add-on. Its GPU resource, simulation, rendering, and ReShade integration implementations remain to be reconstructed and validated in BeamNG/ReShade.

## Repository layout

- `mod/` — BeamNG mod source: GE and vehicle Lua, UI, manifest, and license.
- `native/` — clean-source reconstruction scaffold and protocol notes for the Windows ReShade add-on.
- `reference/` — original release add-on binary used to verify the extracted/decompiled materials.
- `addon_decompiled/` — Ghidra output kept as behavioral reference only.
- `shaders_dxbc/` — recovered compiled shader bytecode.
- `shaders_asm/` — shader disassemblies for inspection.
- `CODEX_BRIEF.md` — recovered architecture and protocol notes.

## Building and installing

The BeamNG mod can be packaged from `mod/` using BeamNG's mod packaging workflow. The native add-on does not yet have a complete build. See `native/README.md` for its reconstruction status and prerequisites. Do not expect the scaffold alone to produce a functioning replacement add-on.

For local validation, install the mod into BeamNG's mods folder and use the recovered compatible add-on build separately. A functioning native source build requires completing the reconstruction tasks documented in `native/README.md`.

## License and attribution

See `mod/LICENSE`. The project uses the collective copyright label “RealSmoke 3D contributors” rather than a personal name. Confirm the license and attribution are appropriate for every distributed asset and dependency before publishing. Repository: https://github.com/ThugbobTrapabrickpants/VolSmoke.
