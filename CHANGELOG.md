# Changelog

This file records user-visible changes to Music Composition Core (MCC).
Release dates use the `YYYY-MM-DD` format.

## [Unreleased]

### Added

- **Scale** module (`MCC_SCALE`): `ScalePattern` built from degree formulas,
  `Scale` with spelling-preserving degrees and explicit enharmonic
  membership, and the `Scales` catalog of 36 reviewed scales with stable
  identifiers, families and aliases, read through `Scales::Find()`.
- The catalog lives in program memory on AVR through Foundation's
  `FOUNDATION_FLASH`.
- `MCC_Scale_Scales` example and the SPEC-SCL invariants.

### Changed

- MCC requires Foundation `1.4.0` or a newer `1.x` release.

### Fixed

- Legacy scale data: Byzantine, Hirajoshi, Major Blues, Japanese and Arabic
  (see `Scale.dox`).

## [0.2.0] - 2026-09-30

### Added

- **Pitch** module (`MCC_PITCH`): `Letter`, `Accidental` (-4 to +4),
  spelled `NoteName` (`C#` != `Db`), integer `PitchClass` (0-11),
  `ChromaticIndex` (`C-1 = 0`, `C4 = 60`) and `Pitch` (middle C is `C4`),
  with written equality, explicit enharmonic equivalence, diatonic movement,
  alteration, octave movement and pitch-height ordering.
- **Tuning** module (`MCC_TUNING`): `Tuning` and `EqualTemperament`, with
  `constexpr` frequencies from an explicit reference (`A4 = 440 Hz`) and no
  math-library dependency.
- **Interval** module (`MCC_INTERVAL`): `Interval` with quality, number and
  direction, simple and compound intervals, inversion, `IntervalBetween()`
  and spelling-preserving transposition of note names and pitches.
- The music-domain specification in
  `docs/Topics/Specification/MusicDomain.dox`.
- Native (macOS, Linux, Windows), AVR and Arm CI, installed-package consumer
  tests and warning-free Doxygen publication.

### Changed

- MCC requires Foundation `1.2.0` or a newer `1.x` release and resolves it
  from a local package or the pinned GitHub release
  (`cmake/MCCFoundation.cmake`).
- Generic presets, toolchains, lifecycle scripts and CI actions come from
  the pinned RoModularBuild `v0.4.0` submodule through thin MCC adapters.

## [0.1.0]

### Added

- Build, package, test and documentation scaffold.
