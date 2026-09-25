# Music Composition Core (MCC)

MCC is a portable C++17 library for music-composition primitives. This
repository is a clean reconstruction of earlier Music Composition Core
experiments and uses Foundation as its low-level dependency.

The initial `0.1.0` scaffold intentionally exposes only build/version
information. Legacy notes, pitches, intervals, scales, MIDI representations,
and utilities will be reviewed and migrated as independently tested modules.

## Dependency

MCC consumes the exported CMake target `Foundation::Foundation`. Export a
Foundation package for the same preset before configuring MCC:

```bash
cd ../Foundation
./scripts/export.sh macos_arm64 --fresh

cd ../MCC
./scripts/configure.sh macos_arm64 --fresh
```

Sibling repositories are discovered automatically through
`../Foundation/dist/<preset>`. Otherwise configure the dependency explicitly:

```bash
./scripts/configure.sh macos_arm64 --fresh -- \
  -DMCC_FOUNDATION_PREFIX=/path/to/Foundation/package
```

The prefix can also be supplied through the `MCC_FOUNDATION_PREFIX`
environment variable. MCC rejects Foundation packages recorded for a different
platform preset.

## Build and test

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
CMake package. Foundation remains a separate dependency and must be discoverable
when a downstream project calls `find_package(MCC CONFIG REQUIRED)`.

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
