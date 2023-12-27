#if defined(ARDUINO)
    #include <Aunit.h>
    #include <aunit/contrib/gtest.h>
#endif

#if __has_include(<gtest/gtest.h>)
    #include <gtest/gtest.h>
#endif

#include <MCC.h>


    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the default constructor of the CPString class.
    //! The purpose of this test is to verify that the default constructor correctly
    //! initializes an empty string with a size of zero.\n\n
    //! The test is expected to pass if the assertion holds true, demonstrating that
    //! the default constructor effectively creates an empty string with a size of zero.

        TEST(MCC_MusicalNote, PitchTest) {
            MCC_MusicalNote::Note myNote(MCC_MusicalNote::Pitch::C_QuadrupleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::C_QuadrupleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::C_QuadrupleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::C_TripleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::C_TripleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::C_TripleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::C_DoubleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::C_DoubleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::C_DoubleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::C_Flat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::C_Flat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::C_Flat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::C_Natural, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::C_Natural);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::C_Natural, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::C_Sharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::C_Sharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::C_Sharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::C_DoubleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::C_DoubleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::C_DoubleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::C_TripleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::C_TripleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::C_TripleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::C_QuadrupleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::C_QuadrupleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::C_QuadrupleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::D_QuadrupleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::D_QuadrupleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::D_QuadrupleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::D_TripleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::D_TripleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::D_TripleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::D_DoubleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::D_DoubleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::D_DoubleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::D_Flat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::D_Flat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::D_Flat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::D_Natural, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::D_Natural);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::D_Natural, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::D_Sharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::D_Sharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::D_Sharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::D_DoubleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::D_DoubleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::D_DoubleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::D_TripleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::D_TripleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::D_TripleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::D_QuadrupleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::D_QuadrupleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::D_QuadrupleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::E_QuadrupleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::E_QuadrupleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::E_QuadrupleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::E_TripleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::E_TripleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::E_TripleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::E_DoubleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::E_DoubleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::E_DoubleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::E_Flat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::E_Flat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::E_Flat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::E_Natural, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::E_Natural);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::E_Natural, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::E_Sharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::E_Sharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::E_Sharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::E_DoubleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::E_DoubleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::E_DoubleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::E_TripleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::E_TripleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::E_TripleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::E_QuadrupleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::E_QuadrupleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::E_QuadrupleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::F_QuadrupleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::F_QuadrupleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::F_QuadrupleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::F_TripleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::F_TripleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::F_TripleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::F_DoubleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::F_DoubleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::F_DoubleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::F_Flat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::F_Flat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::F_Flat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::F_Natural, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::F_Natural);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::F_Natural, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::F_Sharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::F_Sharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::F_Sharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::F_DoubleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::F_DoubleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::F_DoubleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::F_TripleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::F_TripleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::F_TripleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::F_QuadrupleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::F_QuadrupleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::F_QuadrupleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::G_QuadrupleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::G_QuadrupleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::G_QuadrupleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::G_TripleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::G_TripleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::G_TripleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::G_DoubleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::G_DoubleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::G_DoubleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::G_Flat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::G_Flat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::G_Flat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::G_Natural, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::G_Natural);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::G_Natural, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::G_Sharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::G_Sharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::G_Sharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::G_DoubleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::G_DoubleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::G_DoubleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::G_TripleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::G_TripleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::G_TripleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::G_QuadrupleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::G_QuadrupleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::G_QuadrupleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::A_QuadrupleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::A_QuadrupleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::A_QuadrupleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::A_TripleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::A_TripleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::A_TripleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::A_DoubleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::A_DoubleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::A_DoubleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::A_Flat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::A_Flat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::A_Flat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::A_Natural, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::A_Natural);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::A_Natural, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::A_Sharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::A_Sharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::A_Sharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::A_DoubleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::A_DoubleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::A_DoubleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::A_TripleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::A_TripleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::A_TripleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::A_QuadrupleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::A_QuadrupleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::A_QuadrupleSharp, 1);
            
            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::B_QuadrupleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::B_QuadrupleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::B_QuadrupleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::B_TripleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::B_TripleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::B_TripleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::B_DoubleFlat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::B_DoubleFlat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::B_DoubleFlat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::B_Flat, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::B_Flat);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::B_Flat, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::B_Natural, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::B_Natural);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::B_Natural, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::B_Sharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::B_Sharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::B_Sharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::B_DoubleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::B_DoubleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::B_DoubleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::B_TripleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::B_TripleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::B_TripleSharp, 1);

            myNote = MCC_MusicalNote::Note(MCC_MusicalNote::Pitch::B_QuadrupleSharp, 3);
            ASSERT_EQ(myNote.GetPitch().GetType(), MCC_MusicalNote::Pitch::B_QuadrupleSharp);
            ASSERT_EQ(myNote.GetPitch() == MCC_MusicalNote::Pitch::B_QuadrupleSharp, 1);

        }
    //
    //////////////////////////////////////////////////////////////////////////////////
    //! @test
    //! This test case assesses the default constructor of the CPString class.
    //! The purpose of this test is to verify that the default constructor correctly
    //! initializes an empty string with a size of zero.\n\n
    //! The test is expected to pass if the assertion holds true, demonstrating that
    //! the default constructor effectively creates an empty string with a size of zero.

        TEST(MCC_MusicalNote, NoteMethods) {
            MCC::Start();

            MCC_MusicalNote::Pitch pitchArray[12] = {
                MCC_MusicalNote::Pitch::C_Natural,
                MCC_MusicalNote::Pitch::C_Sharp,
                MCC_MusicalNote::Pitch::D_Natural,
                MCC_MusicalNote::Pitch::D_Sharp,
                MCC_MusicalNote::Pitch::E_Natural,
                MCC_MusicalNote::Pitch::F_Natural,
                MCC_MusicalNote::Pitch::F_Sharp,
                MCC_MusicalNote::Pitch::G_Natural,
                MCC_MusicalNote::Pitch::G_Sharp,
                MCC_MusicalNote::Pitch::A_Natural,
                MCC_MusicalNote::Pitch::A_Sharp,
                MCC_MusicalNote::Pitch::B_Natural
            };

            double frequencyArray[12] = {
                16.35, // C0
                17.32, // C#0
                18.35, // D0
                19.45, // D#0
                20.60, // E0
                21.83, // F0
                23.12, // F#0
                24.50, // G0
                25.96, // G#0
                27.50, // A0
                29.14, // A#0
                30.87  // B0
            };

            MCC_MusicalNote::Note myNote;

            for (int16_t i = -12; i <= MCC_MidiProtocol::MidiNoteRange + 12; i++) {
                auto pitchId = i % 12;
                while (pitchId < 0) { pitchId += 12; }

                auto octave = (i < 0) ? ((i - 11) / 12) : (i / 12);

                myNote = MCC_MusicalNote::Note(pitchArray[pitchId], octave);
                auto a = (i >= 0 && i < MCC_MidiProtocol::MidiNoteRange) ? i : MCC_MidiProtocol::InvalidMidiNote;
                auto b = (octave < 0) ? frequencyArray[pitchId] / (((-1 * (i - 11)) / 12) + 1) : frequencyArray[pitchId] * (pow(2, octave));

                myNote = MCC_MusicalNote::Note(pitchArray[pitchId], octave);
                ASSERT_EQ(myNote.NotePitch(), i);
                ASSERT_EQ(myNote.MidiPitch(), a);
                EXPECT_NEAR(myNote.Frequency(), b, myNote.Frequency() * 0.01);
            }

        }
    //