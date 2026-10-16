# MCC walkthroughs

Start with `Run()` in an example's `Shared.cpp`. Each walkthrough starts with
a small musical operation: construct named inputs, compute a result, then
print it. Comments explain why the result has that spelling or value. The
remaining sections expand it into tables and comparisons.

The `START HERE` output comes from those operations. For example:

```text
START HERE: E4 + a minor third
   E4 + m3 = G4
```

The computed result is formatted for display; it is not a hard-coded answer.
These walkthroughs demonstrate public APIs. The GoogleTest suite in `tests/`
checks library correctness separately.

| Example under `examples/` | First operation |
| --- | --- |
| `Core/Version` | Read linked MCC and Foundation versions |
| `Pitch/NoteNames` | Compare C# and Db by written name and pitch class |
| `Interval/Intervals` | Transpose E4 by a minor third to G4 |
| `Tuning/Pitches` | Move A4 up an octave and calculate A5 at 880 Hz |
| `Scale/Scales` | Build E major from a formula and get degree 3: G# |
| `Chord/Chords` | Build C major from a formula and get tone 2: E |
| `Key/Keys` | Ask E minor's signature how to spell F: F# |
| `Rhythm/NoteValues` | Add a dot to a quarter: 1/4 + 1/8 = 3/8 |
| `Rhythm/Notes` | Add a dot while preserving C#4 |
| `Rhythm/Meters` | Interpret 6/8 as two dotted-quarter beats |
| `Rhythm/RhythmPatterns` | Build an eight-step tresillo from gaps 3-3-2 |

## Desktop

From the MCC repository, build the examples through the supported script:

```powershell
./scripts/build.ps1 windows_msvc_x64 -ExamplesOn -Target MCCExamples
```

Run the generated example executables in `build/windows_msvc_x64/bin/Debug/`
directly. Their walkthrough output is always enabled; no verbose test mode is
needed. Other hosts use their corresponding build preset.

## Arduino

Open the example's `.ino` sketch with its adjacent `Shared.h` and `Shared.cpp`.
Install MCC and its Foundation and CPSTL dependencies, then open the Serial
Monitor at **115200 baud**. The sketch prints the walkthrough once in `setup()`;
reset the board to repeat it.

`Desktop/main.cpp` sends each text chunk to `std::cout`; the `.ino` sends the
same chunks to `Serial.print`. All musical operations and formatting are in
`Shared.cpp`, which has no GoogleTest or desktop stream dependency. Buffer sizes
and ASCII output are kept explicit. The Keys example also demonstrates UTF-8;
its accidental glyphs depend on the monitor's font/encoding support.

To compile every sketch for the supported Arduino Uno target:

```powershell
./scripts/test-arduino.ps1 -Fqbn arduino:avr:uno
```

This checks compilation and linking. Running the sketches and inspecting the
Serial Monitor requires the board.
