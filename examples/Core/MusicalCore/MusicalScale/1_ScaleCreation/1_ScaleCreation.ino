#include <MCC.h>

using namespace MCC_MusicalScale;
using namespace MCC_MusicalInterval;

void setup()
{
  Serial.begin(115200);
    MCC::Start();
    
    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalScale::Scale(const CPVector::vector<MCC_MusicalNote::Pitch> &noteTokens, CPString::string& name)
       
        {
            CPVector::vector<MCC_MusicalNote::Pitch> NoteVector;

            NoteVector.push_back(MCC_MusicalNote::Pitch::C_Natural);
            NoteVector.push_back(MCC_MusicalNote::Pitch::D_Natural);
            NoteVector.push_back(MCC_MusicalNote::Pitch::E_Natural);
            NoteVector.push_back(MCC_MusicalNote::Pitch::F_Natural);
            NoteVector.push_back(MCC_MusicalNote::Pitch::G_Natural);
            NoteVector.push_back(MCC_MusicalNote::Pitch::A_Natural);
            NoteVector.push_back(MCC_MusicalNote::Pitch::B_Natural);

            CPString::string ScaleName("Major");
            
            Scale myScale(NoteVector, ScaleName);
            Serial.print(myScale.Name());
            Serial.print(": ");


            MCC_MusicalNote::TextFormat::DefaultFormat.Octave_Disabled();
            MCC_MusicalNote::TextFormat::DefaultFormat.Accidental_Symbol();


            for (uint8_t i = 0; i < myScale.size(); i++)
            {
                Serial.print(myScale.Note(myScale.RootOffset() + i).Name());

                if (i < myScale.size() - 1)
                {
                    Serial.print(", ");
                }
                else
                {
                    Serial.println(".");
                }
            }
        }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalScale::Scale(const MCC_MusicalNote::Pitch &root, const CPVector::vector<Interval> &intervals, CPString::string& name = DefaultName);

        {
            using namespace MCC_MusicalInterval::Qualities;
            using namespace MCC_MusicalInterval::Numbers;

            CPVector::vector<Interval> IntervalVector;

            IntervalVector.push_back(Interval(Qualities::Major, Numbers::Second));
            IntervalVector.push_back(Interval(Minor, Third));
            IntervalVector.push_back(Interval(Perfect, Fourth));
            IntervalVector.push_back(Interval(Perfect, Fifth));
            IntervalVector.push_back(Interval(Minor, Sixth));
            IntervalVector.push_back(Interval(Minor, Seventh));

            CPString::string ScaleName("Minor");
            
            Scale myScale(MCC_MusicalNote::Pitch(MCC_MusicalNote::Pitch::C_Natural), IntervalVector, ScaleName);
            Serial.print(myScale.Name());
            Serial.print(": ");


            MCC_MusicalNote::TextFormat::DefaultFormat.Octave_Disabled();
            MCC_MusicalNote::TextFormat::DefaultFormat.Accidental_Symbol();


            for (uint8_t i = 0; i < myScale.size(); i++)
            {
                Serial.print(myScale.Note(myScale.RootOffset() + i).Name());

                if (i < myScale.size() - 1)
                {
                    Serial.print(", ");
                }
                else
                {
                    Serial.println(".");
                }
            }
        }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalScale:: Scale(const MCC_MusicalNote::Pitch& root, const Flash::Container_Mapping& source)
       
        {
            Scale myScale(MCC_MusicalNote::Pitch::C_Natural, MCC_MusicalScale::Flash::Scales::Dorian);
            Serial.print(myScale.Name());
            Serial.print(": ");


            MCC_MusicalNote::TextFormat::DefaultFormat.Octave_Disabled();
            MCC_MusicalNote::TextFormat::DefaultFormat.Accidental_Symbol();


            for (uint8_t i = 0; i < myScale.size(); i++)
            {
                Serial.print(myScale.Note(myScale.RootOffset() + i).Name());

                if (i < myScale.size() - 1)
                {
                    Serial.print(", ");
                }
                else
                {
                    Serial.println(".");
                }
            }
        }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalScale:: Scale(const MCC_MusicalNote::Note& root, const Flash::Container_Notes& source)

        {
            Scale myScale(MCC_MusicalNote::Pitch(MCC_MusicalNote::Pitch::C_Natural), MCC_MusicalScale::Flash::Scales::Chromatic);
            Serial.print(myScale.Name());
            Serial.print(": ");


            MCC_MusicalNote::TextFormat::DefaultFormat.Octave_Disabled();
            MCC_MusicalNote::TextFormat::DefaultFormat.Accidental_Symbol();


            for (uint8_t i = 0; i < myScale.size(); i++)
            {
                Serial.print(myScale.Note(myScale.RootOffset() + i).Name());

                if (i < myScale.size() - 1)
                {
                    Serial.print(", ");
                }
                else
                {
                    Serial.println(".");
                }
            }
        }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalScale:: Scale(const MCC_MusicalNote::Note& root, const Flash::Container_Notes& source)

        {
            Scale myScale(MCC_MusicalNote::Pitch(MCC_MusicalNote::Pitch::C_Natural), MCC_MusicalScale::Flash::ScaleArrays::Exotic, 9);
            Serial.print(myScale.Name());
            Serial.print(": ");


            MCC_MusicalNote::TextFormat::DefaultFormat.Octave_Disabled();
            MCC_MusicalNote::TextFormat::DefaultFormat.Accidental_Symbol();


            for (uint8_t i = 0; i < myScale.size(); i++)
            {
                Serial.print(myScale.Note(myScale.RootOffset() + i).Name());

                if (i < myScale.size() - 1)
                {
                    Serial.print(", ");
                }
                else
                {
                    Serial.println(".");
                }
            }
        }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
    // MusicalScale:: Scale(const MCC_MusicalNote::Note& root, uint8_t ID)

        {
            Scale myScale(MCC_MusicalNote::Pitch(MCC_MusicalNote::Pitch::C_Natural), 15);
            Serial.print(myScale.Name());
            Serial.print(": ");


            MCC_MusicalNote::TextFormat::DefaultFormat.Octave_Disabled();
            MCC_MusicalNote::TextFormat::DefaultFormat.Accidental_Symbol();


            for (uint8_t i = 0; i < myScale.size(); i++)
            {
                Serial.print(myScale.Note(myScale.RootOffset() + i).Name());

                if (i < myScale.size() - 1)
                {
                    Serial.print(", ");
                }
                else
                {
                    Serial.println(".");
                }
            }
        }
    //
    ///////////////////////////////////////////////////////////////////////////////////////////
}

void loop()
{

}