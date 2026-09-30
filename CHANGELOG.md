# Changelog

This file records user-visible changes to Music Composition Core (MCC).
Release dates use the `YYYY-MM-DD` format.

## [0.2.0] - Unreleased

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
