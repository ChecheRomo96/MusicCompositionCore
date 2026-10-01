# Music Composition Core (MCC)

MCC is a portable C++17 library for music-composition primitives. This
repository is a clean reconstruction of earlier Music Composition Core
experiments and uses Foundation as its low-level dependency.

Clone MCC with its pinned build infrastructure:

```bash
git clone --recurse-submodules https://github.com/ChecheRomo96/MusicCompositionCore.git
```

For an existing checkout:

```bash
git submodule update --init --recursive
```

It contains music theory only: no MIDI concepts. Available modules:

- **Pitch**: `Letter`, `Accidental`, `NoteName` (spelled, `C#` != `Db`),
  `PitchClass` (0-11), `ChromaticIndex` and `Pitch` (middle C is `C4`).
- **Interval**: `Interval` with quality, number and direction, inversion,
  `IntervalBetween()` and spelling-preserving transposition
  (`E4 + M3 = G#4`).
- **Tuning**: `Tuning` and `EqualTemperament` frequencies (`A4 = 440 Hz`).
- **Scale**: `ScalePattern`, `Scale` and the `Scales` catalog of 36 reviewed
  scales, stored in program memory on AVR (`E` major spells `G#`).
- **Core**: version information.

The rules every type follows are in
`docs/Topics/Specification/MusicDomain.dox`, and the roadmap is in
`ACTION_PLAN.md`. The API documentation is published to the `docs` branch.

## Dependency

MCC consumes the CMake target `Foundation::Foundation` from Foundation
`1.4.0` or a newer `1.x` release. Configuring MCC resolves it in this order
(see `cmake/MCCFoundation.cmake`):

1. A `Foundation::Foundation` target already defined by a parent project.
2. `-DMCC_FOUNDATION_PREFIX=<prefix>` or the `MCC_FOUNDATION_PREFIX`
   environment variable.
3. A sibling export in `../Foundation/dist/<preset>`.
4. Normal `find_package(Foundation)` rules (`Foundation_DIR`,
   `CMAKE_PREFIX_PATH`).
5. With `MCC_FETCH_FOUNDATION=ON` (the default), the GitHub Release package
   for tag `v1.4.0` and the preset, verified against its SHA-256; for presets
   without a Release package (AVR, Arm), the Foundation sources at that tag
   are cloned and built with MCC's toolchain.

Downloads are kept in `build/<preset>/_deps/` and reused. No setup is needed
on a fresh machine:

```bash
./scripts/configure.sh macos_arm64 --fresh
```

To develop both libraries together, export Foundation next to MCC or build
your working copy directly:

```bash
./scripts/configure.sh macos_arm64 --fresh -- \
  -DFETCHCONTENT_SOURCE_DIR_FOUNDATION=../Foundation
```

Use `-DMCC_FETCH_FOUNDATION=OFF` to forbid network access. MCC rejects
Foundation packages recorded for a different platform preset.

## Build and test

Public MCC presets and scripts remain the supported interface. Their generic
configure, build, test, install, clean, native preset, and cross-toolchain
implementation comes from the pinned `tools/RoModularBuild` submodule; MCC
retains its module options, Foundation resolution, packaging, examples,
documentation, and release policy.

```bash
./scripts/build.sh macos_arm64 --config Debug
./scripts/test.sh macos_arm64 --config Debug
./scripts/test.sh macos_arm64 --config Release
```

On Windows PowerShell:

```powershell
./scripts/build.ps1 windows_msvc_x64 -Configuration Debug
./scripts/test.ps1 windows_msvc_x64 -Configuration Debug
```

Tests use GoogleTest through CMake FetchContent and link only the public
`MCC::MCC` target.

Validate the installed package from an isolated downstream project:

```bash
./scripts/test-package.sh macos_arm64 --fresh
```

```powershell
./scripts/test-package.ps1 windows_msvc_x64 -Fresh
```

This smoke test exports MCC, resolves it with `find_package(MCC)`, links only
`MCC::MCC`, and calls a Foundation API. It catches regressions in both package
discovery and the transitive Foundation dependency.

## Export

```bash
./scripts/export.sh macos_arm64 --fresh
./scripts/export.sh atmega328p_avrgcc_avr5 --fresh
```

Each export contains one Release MCC library, public headers, and a relocatable
CMake package. When Foundation came from a package, it remains a separate
dependency and must be discoverable when a downstream project calls
`find_package(MCC CONFIG REQUIRED)`; when it was built from sources, it is
installed next to MCC.

## Examples and documentation

```bash
./scripts/export.sh macos_arm64 --fresh --examples-on
MCC_FOUNDATION_PREFIX=../Foundation/dist/macos_arm64 \
  ./scripts/docs.sh --fresh
```

The generated documentation starts at
`build/documentation/docs/html/index.html`.

## Arduino

Install both Foundation and MCC as Arduino libraries, then include:

```cpp
#include <MCC.h>
```

## License

Copyright (c) 2026 José Manuel Romo. All rights reserved.

MCC is currently proprietary. No permission is granted for external use,
compilation, modification, redistribution, integration, or commercial use
without prior written authorization. See [LICENSE](LICENSE).
