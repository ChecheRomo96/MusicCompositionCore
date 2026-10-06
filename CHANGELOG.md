# Changelog

This file records user-visible changes to Music Composition Core (MCC).
Release dates use the `YYYY-MM-DD` format.

## [Unreleased]

### Changed

- MCC requires Foundation 1.5.0 for `Foundation::Containers::BitVector`.
- Arduino sketches no longer need to include `<Foundation.h>`: every MCC
  header brings in Foundation, so including `<MCC.h>` or a single module
  header such as `<MCC_Scale.h>` is enough for the Arduino builder to find
  both libraries. The examples include only the module they demonstrate.

### Added

- **Rhythm** module (`MCC_RHYTHM`) beginning with `NoteValue`, a compact,
  allocation-free representation of whole through 256th note bases and zero
  to four augmentation dots as exact fractions of a whole note.
- `Note`, a compact written `Pitch + NoteValue`, with constructors from pitch,
  note name, natural letter, or letter + accidental, and copy-style pitch and
  value changes.
- `Meter`, a three-byte written time signature with simple, compound and
  irregular classification, exact measure duration and explicit beat
  derivation without tempo or PPQN state.
- Native and Arduino `MCC_Rhythm_NoteValues`, `MCC_Rhythm_Notes` and
  `MCC_Rhythm_Meters` examples, plus exhaustive tests for their supported
  values and construction paths.
- `RhythmPattern`, a cyclic onset/rest pattern whose step count (1 to 65535)
  is chosen and changed at runtime. Like a vector it keeps a step count and
  a byte-granular capacity (`Capacity`, `Reserve`, `Append`, `ShrinkToFit`),
  so resizing within the capacity never reallocates. The steps are a
  `Foundation::Containers::BitVector`: owned on the heap or attached from a
  caller buffer (`Attach`, `BytesFor`, `Release`) that is never reallocated;
  in-place `Parse`, `ParseIntervals`, `Rotate`, `Invert` and `Append` work
  there without allocating. Parsed from box notation (`"x..x..x...x.x..."`) or interonset
  intervals (`"3-3-4-2-4"`), with step editing, `Resize`, onset queries,
  interonset intervals, rotation, necklace equality (`IsRotationOf`),
  complement and concatenation, plus the native and Arduino
  `MCC_Rhythm_RhythmPatterns` example.

## [0.5.2] - 2026-10-01

### Fixed

- Arduino source builds now compile with the stock core's C++11 mode without
  requiring a global `-std=gnu++17` override.
- Scale and chord catalogs remain compile-time data in AVR program memory when
  the public formula parsers are exposed as runtime functions under C++11.

### Changed

- C++14 relaxed-`constexpr` operations remain `constexpr` for CMake and modern
  Arduino toolchains and become inline functions only in Arduino C++11 mode.
- Arduino example CI now exercises the core's default language flags.
- All seven example sketches were executed successfully on a physical Arduino
  Mega 2560 with the stock AVR core and its default C++11 mode.

## [0.5.1] - 2026-10-01

### Added

- Sanitizer CI job: the Debug suite under AddressSanitizer and
  UndefinedBehaviorSanitizer on Linux GCC/Clang and macOS.
- Size-budget and trivial-copyability checks for every value type, compiled
  into the library for every target, including AVR and Arm.
- clang-tidy static analysis (`.clang-tidy`, `scripts/analyze.sh`,
  `scripts/analyze.ps1`) with warnings as errors, and a CI job running it.
- `scripts/test-arduino.sh` and `scripts/test-arduino.ps1`, and an Arduino CI
  job on Linux and Windows, compiling every example sketch for the Arduino
  Uno against the pinned Foundation release.

### Fixed

- Example sketches include `<Foundation.h>` and `<MCC.h>` so the Arduino
  builder discovers both libraries; previously no sketch compiled.
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
