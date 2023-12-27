#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalScale;
using namespace MCC_MusicalInterval;

int main()
{
    MCC::Start();

    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalScale::Scale(const CPVector::vector<MCC_MusicalNote::Pitch> &noteTokens, CPString::string& name)

    {
        cpstd::vector<MCC_MusicalNote::Pitch> NoteVector;

        NoteVector.push_back(MCC_MusicalNote::Pitch::C_Natural);
        NoteVector.push_back(MCC_MusicalNote::Pitch::D_Natural);
        NoteVector.push_back(MCC_MusicalNote::Pitch::E_Natural);
        NoteVector.push_back(MCC_MusicalNote::Pitch::F_Natural);
        NoteVector.push_back(MCC_MusicalNote::Pitch::G_Natural);
        NoteVector.push_back(MCC_MusicalNote::Pitch::A_Natural);
        NoteVector.push_back(MCC_MusicalNote::Pitch::B_Natural);

        cpstd::string ScaleName("Major");

        Scale myScale(NoteVector, ScaleName);
        std::cout << myScale.Name() << ": ";


        MCC_MusicalNote::DefaultFormat.SetOctave_Disabled();
        MCC_MusicalNote::DefaultFormat.SetAccidental_Symbol();


        for (uint8_t i = 0; i < myScale.size(); i++)
        {
            std::cout << myScale.Note(myScale.RootOffset() + i).Name();

            if (i < myScale.size() - 1)
            {
                std::cout << ", ";
            }
            else
            {
                std::cout << "." << std::endl;
            }
        }
    }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalScale::Scale(const MCC_MusicalNote::Pitch &root, const CPVector::vector<Interval> &intervals, CPString::string& name = DefaultName);

    {
        using namespace MCC_MusicalInterval::Qualities;
        using namespace MCC_MusicalInterval::Numbers;

        cpstd::vector<Interval> IntervalVector;

        IntervalVector.push_back(Interval(Qualities::Major, Numbers::Second));
        IntervalVector.push_back(Interval(Minor, Third));
        IntervalVector.push_back(Interval(Perfect, Fourth));
        IntervalVector.push_back(Interval(Perfect, Fifth));
        IntervalVector.push_back(Interval(Minor, Sixth));
        IntervalVector.push_back(Interval(Minor, Seventh));

        cpstd::string ScaleName("Minor");

        Scale myScale(MCC_MusicalNote::Pitch(MCC_MusicalNote::Pitch::C_Natural), IntervalVector, ScaleName);
        std::cout << myScale.Name() << ": ";


        MCC_MusicalNote::DefaultFormat.SetOctave_Disabled();
        MCC_MusicalNote::DefaultFormat.SetAccidental_Symbol();


        for (uint8_t i = 0; i < myScale.size(); i++)
        {
            std::cout << myScale.Note(myScale.RootOffset() + i).Name();

            if (i < myScale.size() - 1)
            {
                std::cout << ", ";
            }
            else
            {
                std::cout << "." << std::endl;
            }
        }
    }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalScale:: Scale(const MCC_MusicalNote::Pitch& root, const Flash::Container_Mapping& source)

    {
        Scale myScale(MCC_MusicalNote::Pitch::C_Natural, MCC_MusicalScale::Flash::Scales::Dorian);
        std::cout << myScale.Name() << ": ";


        MCC_MusicalNote::DefaultFormat.SetOctave_Disabled();
        MCC_MusicalNote::DefaultFormat.SetAccidental_Symbol();


        for (uint8_t i = 0; i < myScale.size(); i++)
        {
            std::cout << myScale.Note(myScale.RootOffset() + i).Name();

            if (i < myScale.size() - 1)
            {
                std::cout << ", ";
            }
            else
            {
                std::cout << "." << std::endl;
            }
        }
    }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalScale:: Scale(const MCC_MusicalNote::Note& root, const Flash::Container_Notes& source)

    {
        Scale myScale(MCC_MusicalNote::Pitch(MCC_MusicalNote::Pitch::C_Natural), MCC_MusicalScale::Flash::Scales::Chromatic);
        std::cout << myScale.Name() << ": ";


        MCC_MusicalNote::DefaultFormat.SetOctave_Disabled();
        MCC_MusicalNote::DefaultFormat.SetAccidental_Symbol();


        for (uint8_t i = 0; i < myScale.size(); i++)
        {
            std::cout << myScale.Note(myScale.RootOffset() + i).Name();

            if (i < myScale.size() - 1)
            {
                std::cout << ", ";
            }
            else
            {
                std::cout << "." << std::endl;
            }
        }
    }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
// MusicalScale::Scale(const MCC_MusicalNote::Pitch& root, const Flash::Container* source, uint8_t ID);

    {
        Scale myScale(MCC_MusicalNote::Pitch(MCC_MusicalNote::Pitch::C_Natural), MCC_MusicalScale::Flash::ScaleArrays::Exotic, 9);
        std::cout << myScale.Name() << ": ";


        MCC_MusicalNote::DefaultFormat.SetOctave_Disabled();
        MCC_MusicalNote::DefaultFormat.SetAccidental_Symbol();


        for (uint8_t i = 0; i < myScale.size(); i++)
        {
            std::cout << myScale.Note(myScale.RootOffset() + i).Name();

            if (i < myScale.size() - 1)
            {
                std::cout << ", ";
            }
            else
            {
                std::cout << "." << std::endl;
            }
        }
    }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalScale::Scale(const MCC_MusicalNote::Pitch& root, uint8_t ID);

    {
        Scale myScale(MCC_MusicalNote::Pitch(MCC_MusicalNote::Pitch::C_Natural), 15);
        std::cout << myScale.Name() << ": ";


        MCC_MusicalNote::DefaultFormat.SetOctave_Disabled();
        MCC_MusicalNote::DefaultFormat.SetAccidental_Symbol();


        for (uint8_t i = 0; i < myScale.size(); i++)
        {
            std::cout << myScale.Note(myScale.RootOffset() + i).Name();

            if (i < myScale.size() - 1)
            {
                std::cout << ", ";
            }
            else
            {
                std::cout << "." << std::endl;
            }
        }
    }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////


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
        auto a = (i >= 0 && i < MCC_MidiProtocol::MidiNoteRange) ? i : MCC_MidiProtocol::InvalidMidiNote ;
        auto b = (octave < 0) ?  frequencyArray[pitchId] / ((( - 1 * (i-11)) / 12) + 1) : frequencyArray[pitchId] * (pow(2,octave));

        std::cout << (int16_t) myNote.NotePitch() << " - " << i << std::endl;
        std::cout << (int16_t) myNote.MidiPitch() << " - " << a << std::endl;
        std::cout << myNote.Frequency() << " - " << b << std::endl;
    }

    return 0;
}
