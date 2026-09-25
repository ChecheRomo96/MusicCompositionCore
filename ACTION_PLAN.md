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
- Foundation is the only required MCC dependency.
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
- `Letter + Accidental -> PitchClass`, `PitchClass + Octave -> Pitch`;
  `MCC::Note` is reserved for pitch + rhythmic value.
- Accidentals range from -4 to +4.
- `ChromaticIndex` origin is `C-1 = 0` (`C4 = 60`).
- Errors use one canonical invalid value per type plus `IsValid()`.

Exit criteria:

- Every invariant is documented and mapped to planned tests.
- No public type has an unspecified invalid state.

## Phase 3 - Pitch primitives

Implement:

```cpp
MCC::Letter
MCC::Accidental
MCC::PitchClass
MCC::ChromaticClass
```

Required behavior:

- [ ] Preserve written spelling.
- [ ] Derive the chromatic class.
- [ ] Compare written pitch classes.
- [ ] Test enharmonic equivalence explicitly.
- [ ] Move diatonically without losing spelling.
- [ ] Support boundary accidentals safely.

Exit criteria:

- Exhaustive tests cover supported letters and accidentals.
- Enharmonic equivalence is distinct from written equality.

## Phase 4 - Pitches and tuning

Implement:

```cpp
MCC::ChromaticIndex
MCC::Pitch
MCC::Tuning
MCC::EqualTemperament
```

Required behavior:

- [ ] Combine a written pitch class with an octave.
- [ ] Calculate an unbounded absolute chromatic position.
- [ ] Transpose across octave boundaries.
- [ ] Calculate frequency from an explicit tuning.
- [ ] Support pitches outside the MIDI range.
- [ ] Verify `A4 = 440 Hz` under the standard tuning.

MCC will not expose `MidiPitch`, `MidiNote` or MIDI-number conversions.

## Phase 5 - Intervals

Implement:

```cpp
MCC::IntervalNumber
MCC::IntervalQuality
MCC::IntervalDirection
MCC::Interval
```

Required behavior:

- [ ] Preserve diatonic and chromatic distance.
- [ ] Construct intervals from number and quality.
- [ ] Calculate intervals between pitch classes and pitches.
- [ ] Support ascending, descending and compound intervals.
- [ ] Invert intervals.
- [ ] Transpose pitch classes and pitches while preserving spelling.
- [ ] Add property tests for inversion and transposition.

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
- [ ] Format pitch classes, pitches, intervals, scales and chords.
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

- [ ] Add CI for macOS, Linux and Windows native builds.
- [ ] Add AVR and Arm cross-compilation checks.
- [ ] Run installed-package consumer tests in CI.
- [ ] Add compiler-warning and static-analysis profiles.
- [ ] Add desktop sanitizer builds.
- [ ] Add compile-time and object-size checks for embedded value types.
- [ ] Validate all catalog data during CI.
- [ ] Generate and verify API documentation.

## Proposed releases

| Version | Scope |
| --- | --- |
| `0.1.0` | Build, package, test and documentation scaffold |
| `0.2.0` | Pitch classes, pitches, tuning and intervals |
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
