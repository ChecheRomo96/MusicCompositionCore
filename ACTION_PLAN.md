# MCC Reconstruction Action Plan

## Objective

Reconstruct Music Composition Core (MCC) as a portable C++17 library focused
exclusively on music theory. MCC will use Foundation for low-level reusable
infrastructure and will not contain MIDI protocol concepts.

The dependency direction is:

```text
Foundation <- MCC <- MIDILAR
```

MIDILAR will depend on both Foundation and MCC. MCC must never depend on
MIDILAR.

## Architectural decisions

- MCC contains music-theory concepts only.
- MIDI messages, note numbers, channels, velocity, clocks, devices, routing,
  parsers, ports and transports belong to MIDILAR.
- Public value types live directly in the `MCC` namespace, for example
  `MCC::Pitch`, `MCC::Note`, `MCC::Interval` and `MCC::Scale`.
- Top-level `MCC_*.h` facades detect physically available modules with
  `__has_include()` and define the same availability macros exported by CMake.
- Catalog namespaces use plural names, such as `MCC::Scales` and
  `MCC::Chords`.
- Historical MCC repositories are design and data sources, not code to copy
  without review.
- Foundation is the only required MCC dependency. CMake resolves a local
  package first and otherwise fetches the pinned Foundation tag from GitHub:
  its Release package when one exists for the preset, or its sources
  (`cmake/MCCFoundation.cmake`).
- Fundamental value types avoid dynamic allocation and support `constexpr`
  operations where practical.
- The library must remain suitable for desktop and embedded targets.

## MCC versus Foundation

Add functionality to Foundation when it:

- Has no musical meaning and would be useful to unrelated libraries, such as
  integer arithmetic, fixed-capacity containers, bit manipulation, text
  buffers or status/result types.
- Abstracts the platform, toolchain or build environment.
- Would be duplicated if MIDILAR or another library needed it independently.

Add functionality to MCC when it:

- Encodes a music-theory concept, rule, name or catalog entry.
- Depends on musical conventions such as spelling, octave numbering, tuning,
  interval quality, scale or chord structure, meter or rhythm.
- Is a musical value type or algorithm, even when implemented with generic
  Foundation building blocks.

Rules:

- MCC may depend on Foundation; Foundation must never depend on MCC.
- Generic helpers discovered while building MCC are proposed to Foundation
  first, and MCC keeps only a private detail until Foundation provides them.
- MCC does not wrap or re-export Foundation APIs under the `MCC` namespace.
- MIDI and real-time concerns belong to neither: they belong to MIDILAR.

## Phase 0 - Establish the baseline

Status: complete

- [x] Inspect the repository and identify generated artifacts.
- [x] Keep `build/` and `dist/` outside version control.
- [x] Validate the macOS ARM64 Debug build and unit tests.
- [x] Validate the installed CMake package with an isolated consumer.
- [x] Validate the AVR ATmega328P Release build.
- [x] Record the reconstruction plan in this document.
- [x] Establish `rebuild-theory-core` as the reconstruction branch.
- [x] Create the initial `0.1.0` scaffold commit and tag.

Baseline validation results:

- Three native unit tests pass.
- The package consumer resolves `MCC::MCC` and its transitive Foundation
  dependency.
- Foundation `1.0.0` is resolved for matching macOS ARM64 and AVR presets.
- The AVR static library builds successfully with C++17.

## Phase 1 - Repository and package architecture

Status: complete

Keep the Arduino-compatible public tree under `src/`, following Foundation's
facade and staged-header model:

```text
src/MCC.h         Complete library facade
src/MCC_*.h       Top-level module facades
src/MCC/*.h       Hierarchical module aggregators
src/MCC/*/        Public types, implementations and private details
data/             Canonical scale and chord definitions
tests/            Unit, property, catalog and package tests
examples/         Focused music-theory examples
tools/            Catalog generation and validation
docs/             Architecture and theory documentation
```

Actions:

- [x] Keep public headers under `src/` for direct Arduino consumption.
- [x] Preserve the installed `MCC::MCC` CMake target.
- [x] Pin RoModularBuild as a tagged submodule and delegate generic native and
  embedded presets, toolchains, lifecycle scripts, and CI actions through thin
  MCC-owned adapters.
- [x] Define module macros from facades when Arduino discovers their headers.
- [x] Export the same module macros through CMake targets.
- [x] Apply the C++ standard at target scope.
- [x] Allow tests to use an installed GoogleTest before downloading it.
- [x] Add Foundation compatibility checks to the installed package.
- [x] Define rules for adding functionality to MCC versus Foundation.

Exit criteria:

- Build-tree and installed-package consumers compile successfully.
- macOS and AVR validation remain green.
- No public MCC header references MIDILAR or MIDI.
- CMake and Arduino expose the same module-availability macros.

## Phase 2 - Music-domain specification

Status: complete (`docs/Topics/Specification/MusicDomain.dox`)

Document and approve the invariants that all later modules will use:

- [x] Octave convention and middle-C definition.
- [x] Written equality versus enharmonic equivalence.
- [x] Diatonic, chromatic and absolute ordering.
- [x] Supported accidental range.
- [x] Absolute chromatic-coordinate origin and representation.
- [x] Directed, simple and compound interval semantics.
- [x] Error-handling policy without exceptions.
- [x] Embedded memory and object-size constraints.
- [x] Text formatting and caller-provided buffer policy.

Decisions:

- Scientific pitch notation: middle C is `C4`, `A4 = 440 Hz`.
- `Letter + Accidental -> NoteName`, `NoteName + Octave -> Pitch`;
  `MCC::Note` is reserved for pitch + rhythmic value.
- Accidentals range from -4 to +4.
- `ChromaticIndex` origin is `C-1 = 0` (`C4 = 60`).
- Errors use one canonical invalid value per type plus `IsValid()`.
- Terminology (revised after Phase 4): `NoteName` is the spelled letter +
  accidental (`C#` != `Db`) and `PitchClass` is the integer class 0-11
  (`C#` and `Db` are both 1), matching standard music-theory usage.

Exit criteria:

- Every invariant is documented and mapped to planned tests.
- No public type has an unspecified invalid state.

## Phase 3 - Pitch primitives

Status: complete (`src/MCC/Pitch/`, module macro `MCC_PITCH`)

Implement:

```cpp
MCC::Letter
MCC::Accidental
MCC::NoteName
MCC::PitchClass
```

Required behavior:

- [x] Preserve written spelling.
- [x] Derive the pitch class.
- [x] Compare written note names.
- [x] Test enharmonic equivalence explicitly.
- [x] Move diatonically without losing spelling.
- [x] Support boundary accidentals safely.

Exit criteria:

- Exhaustive tests cover supported letters and accidentals.
- Enharmonic equivalence is distinct from written equality.

Decisions:

- `Letter` is an `enum class` with free queries `DiatonicIndex()`,
  `NaturalSemitone()` and `MoveLetter()`; non-enumerator casts are rejected by
  `NoteName`.
- `NoteName::MovedDiatonically()` moves the letter and keeps the written
  accidental; `NoteName::Altered()` keeps the letter and changes the
  accidental, returning the invalid value outside `[-4, +4]`.
- `PitchClass` construction checks its input; `Transposed()` reduces
  modulo 12.
- Invalid values sort after every valid value.
- Floored modulo arithmetic uses `Foundation::Math::FloorMod`, added in
  Foundation `1.1.0`; MCC now requires Foundation 1.1 or newer.

## Phase 4 - Pitches and tuning

Status: complete (`src/MCC/Pitch/`, `src/MCC/Tuning/`, module macro
`MCC_TUNING`)

Implement:

```cpp
MCC::ChromaticIndex
MCC::Pitch
MCC::Tuning
MCC::EqualTemperament
```

Required behavior:

- [x] Combine a written note name with an octave.
- [x] Calculate an unbounded absolute chromatic position.
- [x] Transpose across octave boundaries.
- [x] Calculate frequency from an explicit tuning.
- [x] Support pitches outside the MIDI range.
- [x] Verify `A4 = 440 Hz` under the standard tuning.

MCC will not expose `MidiPitch`, `MidiNote` or MIDI-number conversions.

Decisions:

- `ChromaticIndex` is a 16-bit value type with one invalid value; valid
  indices are exactly the writable pitch range `[-1528, 1551]`.
- `Pitch` is 3 bytes: a `NoteName` plus a signed 8-bit octave.
- Transposition in this phase preserves spelling: `MovedDiatonically()`
  (octave changes between `B` and `C`), `Altered()` and `MovedByOctaves()`.
  Transposing by semitones needs an interval to choose the spelling and
  belongs to Phase 5.
- `MCC::IsLowerThan()` implements pitch-height order (SPEC-ORD-6);
  `operator<` stays written order.
- Tuning lives in its own `MCC_TUNING` module because it is the only module
  that uses `float`; it requires `MCC_PITCH`.
- `Tuning` is a value (reference pitch + frequency) and `EqualTemperament`
  holds one; there are no virtual functions.
- Frequencies use a table of the twelve semitone ratios plus exact octave
  doublings, with no `pow()` or math library, and are `constexpr`.
  Frequencies above the `float` range (after `B123` under `A4 = 440 Hz`)
  return `0`.
- Every integer input of the pitch API is `int32_t`, so behavior is the same
  where `int` is 16 bits (AVR).
- Octave and floored-division arithmetic use `Foundation::Math::FloorDiv`,
  added in Foundation `1.2.0`.

## Phase 5 - Intervals

Status: complete (`src/MCC/Interval/`, module macro `MCC_INTERVAL`)

Implement:

```cpp
MCC::IntervalNumber
MCC::IntervalQuality
MCC::IntervalDirection
MCC::Interval
```

Required behavior:

- [x] Preserve diatonic and chromatic distance.
- [x] Construct intervals from number and quality.
- [x] Calculate intervals between note names and pitches.
- [x] Support ascending, descending and compound intervals.
- [x] Invert intervals.
- [x] Transpose note names and pitches while preserving spelling.
- [x] Add property tests for inversion and transposition.

Decisions:

- `Interval` stores signed diatonic steps and signed semitones (4 bytes).
  Direction follows the steps, or the semitones for a unison, so no
  diminished unison can exist; number and quality are derived.
- Valid intervals span at most the writable pitch range (1791 steps, 3079
  semitones) and need at most four augmentations or diminutions; so the
  interval between extreme spellings such as `Cbbbb` and `C####` is invalid.
- `Interval(quality, number, direction)` builds an interval; a perfect
  unison ignores the direction. `Interval::FromSteps()` builds one from raw
  counts.
- `IntervalBetween(Pitch, Pitch)` is directed; `IntervalBetween(NoteName,
  NoteName)` is the simple ascending interval to the next occurrence of the
  target letter.
- `pitch + interval`, `pitch - interval`, `noteName + interval` and
  `noteName - interval` transpose preserving spelling; an accidental outside
  `[-4, +4]` or an octave outside `[-128, 127]` makes the result invalid.
- `Inverted()` inverts the simple part and keeps the direction; an
  augmented octave inverts to the opposite-direction augmented unison
  (clarified in SPEC-INT-6).
- `operator==` is written equality (`A4 != d5`); `IsEnharmonic()` compares
  signed semitones.

## Phase 6 - Scales and scale catalog

Implement:

```cpp
MCC::ScaleDegree
MCC::ScalePattern
MCC::Scale
MCC::Scales
```

Actions:

- [ ] Inventory every historical `.Scale` and `.ScaleArray` definition.
- [ ] Compare definitions across the historical repositories.
- [ ] Separate canonical names from aliases.
- [ ] Store reviewed definitions as canonical data files.
- [ ] Generate static C++ catalog data for desktop and embedded builds.
- [ ] Preserve the provenance of every migrated definition.
- [ ] Validate identifiers, aliases, degrees, ordering and duplicates.
- [ ] Test scale generation from every supported root.
- [ ] Test enharmonic spelling under an explicit policy or key context.

Initial catalog families:

- Diatonic and modal scales.
- Major and minor variants.
- Pentatonic and blues scales.
- Symmetric scales.
- Reviewed exotic scales.

## Phase 7 - Chords and chord catalog

Implement:

```cpp
MCC::ChordPattern
MCC::ChordInversion
MCC::Chord
MCC::Chords
```

Actions:

- [ ] Inventory every historical `.Chord` and `.ChordArray` definition.
- [ ] Normalize names, symbols and aliases.
- [ ] Migrate triads, sevenths, extensions and suspended chords.
- [ ] Generate static catalog data.
- [ ] Validate interval patterns and duplicate definitions.
- [ ] Generate chord pitches from a root and inversion.
- [ ] Add basic recognition tests for unordered pitch collections.

## Phase 8 - Keys and notation

Implement:

```cpp
MCC::KeySignature
MCC::Key
MCC::NotationOptions
MCC::Notation
```

Actions:

- [ ] Model tonic, mode and key signature separately from a scale.
- [ ] Resolve degree spelling from the key context.
- [ ] Format note names, pitches, intervals, scales and chords.
- [ ] Support ASCII output and optional Unicode symbols.
- [ ] Support caller-provided fixed buffers for embedded builds.
- [ ] Avoid mandatory `std::string` allocation in the core API.

## Phase 9 - Musical rhythm

Implement theory and composition concepts only:

```cpp
MCC::NoteValue
MCC::Note
MCC::Meter
MCC::Tuplet
MCC::RhythmPattern
MCC::EuclideanPattern
```

Actions:

- [ ] Represent note values and dotted values exactly.
- [ ] Combine a pitch with a note value into `MCC::Note`.
- [ ] Represent simple and compound meter.
- [ ] Represent tuplets independently of runtime timing.
- [ ] Migrate and verify the historical Euclidean-rhythm algorithm.
- [ ] Keep clocks, scheduling, callbacks and PPQN execution outside MCC.

## Phase 10 - Required MIDILAR integration

MIDILAR will consume MCC as a required public dependency:

```cmake
find_package(Foundation CONFIG REQUIRED)
find_package(MCC CONFIG REQUIRED)

target_link_libraries(MIDILAR
    PUBLIC
        Foundation::Foundation
        MCC::MCC)
```

MIDILAR owns:

- MIDI note numbers, channels and velocity.
- MIDI messages and parsers.
- MIDI Clock, PPQN execution and MTC.
- Control Change, NRPN and SysEx.
- UART, USB and desktop MIDI transports.
- Devices, routing, callbacks and real-time processing.
- Conversion between `MCC::Pitch` and MIDI note numbers.

Integration actions:

- [ ] Export MCC as a transitive MIDILAR package dependency.
- [ ] Move or recreate historical MIDI functionality in MIDILAR.
- [ ] Implement checked conversions for values inside the MIDI range.
- [ ] Test rejection of pitches outside the MIDI range.
- [ ] Test scale, chord and rhythm integration without adding MIDI to MCC.

## Phase 11 - Quality and release readiness

Status: in progress (`.github/workflows/`)

- [x] Add CI for macOS, Linux and Windows native builds.
- [x] Add AVR and Arm cross-compilation checks.
- [x] Run installed-package consumer tests in CI.
- [ ] Add compiler-warning and static-analysis profiles.
- [ ] Add desktop sanitizer builds.
- [ ] Add compile-time and object-size checks for embedded value types.
- [ ] Validate all catalog data during CI.
- [x] Generate and verify API documentation.

## Proposed releases

| Version | Scope |
| --- | --- |
| `0.1.0` | Build, package, test and documentation scaffold |
| `0.2.0` | Note names, pitches, tuning and intervals |
| `0.3.0` | Scales and reviewed scale catalog |
| `0.4.0` | Chords, keys and notation |
| `0.5.0` | Rhythm and compositional patterns |
| `0.9.0` | Required MIDILAR integration validated |
| `1.0.0` | Stable documented API on supported targets |

## Definition of done for MCC 1.0

- MCC contains no MIDI terminology or protocol functionality.
- Foundation is MCC's only external library dependency.
- MIDILAR consumes MCC as a required dependency.
- Public types have documented invariants and invalid-state policies.
- Fundamental value types do not allocate dynamically.
- Desktop, AVR and Arm builds are validated.
- Scale and chord catalogs are reviewed, generated and automatically tested.
- The installed package works from an isolated consumer project.
- Musical behavior is covered by example-based and property-based tests.
- Historical implementation details do not leak into the public API.
