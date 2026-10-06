# MCC agent instructions

MCC is the music-theory library of the RoModular ecosystem. Keep it
independently buildable for desktop and embedded consumers, and preserve the
dependency direction `Foundation <- MCC <- MIDILAR`.

## Shared RoModular guidance

Before starting work, look for the shared guidance in
`../RoModularAgents`.

- If it exists and is readable, read `AGENTS.md` and `CONTRACT.md` completely.
- Read `repositories/MCC.md` for the canonical repository adapter.
- Use the relevant skill under `skills/` when the request matches one.
- If the sibling repository is unavailable, continue with the rules in this
  file and report that the shared guidance was not loaded.

Shared guidance does not expand the user's requested scope. Do not modify
Foundation, MIDILAR, RoModular, RoModularBuild, or another sibling repository
unless the user explicitly includes it.

## Repository rules

- Treat `CMakePresets.json`, its included preset files, and the scripts under
  `scripts/` as the supported build interface.
- Initialize the pinned `tools/RoModularBuild` submodule before invoking a
  workflow in a fresh checkout.
- Treat `tools/RoModularBuild` as a pinned, read-only dependency. Shared engine
  or toolchain changes belong in RoModularBuild; updating the gitlink is a
  separate, explicit dependency change.
- Preserve C++17 for CMake packages and direct source builds.
- Keep embedded code exception-free and independent of mandatory full-STL
  facilities. Operations that change a container's size may
  allocate; the library makes no real-time assumptions about the caller, and
  implementers reserve space beforehand for time-critical code. Allocation
  failure is reported through results.
- Preserve the dependency direction: MCC may consume Foundation, Foundation
  must never consume MCC, and MIDI protocol or transport concepts belong in
  MIDILAR.
- Keep musical invariants aligned with
  `docs/Topics/Specification/MusicDomain.dox` and `ACTION_PLAN.md`.
- Preserve module selection through existing `MCC_*` CMake cache options.
- Release exports contain one Release library and CMake package metadata.
  Debug is for development and testing and is not distributed.
- Examples demonstrate public APIs; they are not unit tests. Unit tests live
  under `tests/MCC/` and use GoogleTest through CTest integration.
- Keep public headers, examples, tests, version metadata, action plan, and
  Doxygen documentation synchronized with public API changes.
- Treat hardware execution separately from compile/link validation for AVR,
  STM32, PSoC, and other embedded targets.
- Preserve unrelated work and do not commit, tag, push, publish, or merge
  unless the user explicitly requests it.

## Supported entry points

Use the PowerShell equivalent on Windows when one is provided.

```text
./scripts/configure.sh <preset> [--fresh] [-- <cmake-options>]
./scripts/build.sh <preset> [--fresh] [--config <configuration>]
./scripts/test.sh <preset> [--fresh] [--config <configuration>]
./scripts/install.sh <preset>
./scripts/export.sh <preset> [--fresh] [-- <cmake-options>]
./scripts/test-package.sh <preset> [--fresh]
./scripts/docs.sh [--fresh]
```

Run the smallest relevant validation first, then broaden it according to risk.
State clearly which host, compiler, cross-compiler, and hardware checks were
not available in the current environment.
