# Changelog

This file records user-visible changes to Music Composition Core (MCC).
Release dates use the `YYYY-MM-DD` format.

## [Unreleased]

### Added

- Sanitizer CI job: the Debug suite under AddressSanitizer and
  UndefinedBehaviorSanitizer on Linux GCC/Clang and macOS.
- Size-budget and trivial-copyability checks for every value type, compiled
  into the library for every target, including AVR and Arm.
- clang-tidy static analysis (`.clang-tidy`, `scripts/analyze.sh`,
  `scripts/analyze.ps1`) with warnings as errors, and a CI job running it.

### Fixed

- Two implementation-defined narrowing conversions in `Pitch` and
  `KeySignature` found by clang-tidy.

### Changed

- MCC and its tests build with Foundation's warning set as errors when
  testing is enabled.

## [0.5.0] - 2026-10-01

### Added

- **Key** module (`MCC_KEY`): `KeySignature` and `Key` in the seven diatonic
  modes, `Key::FromSignature()`, and `Key::Spell()` for pitch classes and
  chromatic indices in the key's context.
- **Notation** module (`MCC_NOTATION`): allocation-free `Format` and `Parse`
  for note names, pitches and intervals, plus formatting of catalog scales,
  chord symbols and keys, with ASCII or Unicode accidentals and explicit
  naturals, encoded as ASCII/UTF-8 (`char`), UTF-16 (`char16_t`) or UTF-32
  (`char32_t`) according to the buffer type, or sent code point by code
  point to a callback without a buffer. Parsing reads the same encodings and
  symbols, either letter case, `x` double sharps and signed intervals.
- `MCC_Key_Keys` example and the SPEC-KEY invariants.

## [0.4.0] - 2026-10-01

### Added

- **Chord** module (`MCC_CHORD`): `ChordPattern` built from chord formulas up
  to the thirteenth, `Chord` with spelling-preserving tones, explicit
  enharmonic membership and close-position inversions, and the `Chords`
  catalog of 28 reviewed chords with symbols and aliases in program memory.
- `Chords::FromScale()`, which lists every catalog chord written in a scale
  (the historical chord pool).
- `MCC_Chord_Chords` example and the SPEC-CHD invariants.

### Changed

- `NaturalSemitone()` and interval quality computation derive the major-scale
  semitones arithmetically, so AVR builds no longer copy a lookup table into
  RAM.

### Fixed

- Legacy chord data: Diminished, Minor Sixth, Half Diminished Seventh and
  Diminished Seventh (see `Chord.dox`).

## [0.3.0] - 2026-10-01

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
