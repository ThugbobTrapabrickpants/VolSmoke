# Shader binaries extracted from the latest RealSmoke_3D.addon

Each `.cso` is the exact compiled DXBC (shader model 5.0) embedded in the addon, named after the matching file in `shaders_asm/`.
The "copies" column is how many times that identical blob appears in the addon (13 shaders appear twice, byte-identical).

| shader | bytes | copies in addon | sha256 (first 16) |
|---|---|---|---|
| CS_A | 45344 | 2 | `1c9bfaa085cf94b4` |
| CS_A_FORWARD | 35864 | 2 | `53847fa7208163e6` |
| CS_A_REVERSE | 35868 | 2 | `e5bbb4dc064b431e` |
| CS_CALC_VORTICITY | 36056 | 2 | `10b05c6a94b43724` |
| CS_DENSITY_BRICKS | 2748 | 2 | `57e943b4fd8793b4` |
| CS_DIAGNOSTICS | 3116 | 1 | `d91ef10db752cd22` |
| CS_DIV | 11976 | 2 | `de21b50827f470a5` |
| CS_I | 14844 | 2 | `089298a52a7f2df2` |
| CS_PRESSURE_X2 | 13092 | 2 | `147a51b4375c4301` |
| CS_PROJECT | 24656 | 2 | `a82bed7d95654b5f` |
| CS_ShadowProbe | 2844 | 1 | `f54cde357ef26eaa` |
| CS_ShadowProbeFinalize | 2392 | 1 | `6768ba25f1eff2a8` |
| CS_VA | 49948 | 2 | `6abd7f4147a8218d` |
| CS_VORTICITY | 27216 | 2 | `855c899404d0d2a3` |
| PS_A | 736 | 1 | `e68feafdbf1da05e` |
| PS_BilateralUpsample | 8776 | 1 | `ab9ae6449a36e845` |
| PS_D | 748 | 1 | `4aafce88e54c2641` |
| PS_S | 170776 | 2 | `a8488214385efae1` |
| PS_UI | 4612 | 1 | `aee563717812d609` |
| VS_Q | 736 | 2 | `a174a158a51b830a` |
