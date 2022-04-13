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
            std::cout << myScale.Name() << ": ";


            MCC_MusicalNote::TextFormat::DefaultFormat.Octave_Disabled();
            MCC_MusicalNote::TextFormat::DefaultFormat.Accidental_Symbol();


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

            CPVector::vector<Interval> IntervalVector;

            IntervalVector.push_back(Interval(Qualities::Major, Numbers::Second));
            IntervalVector.push_back(Interval(Minor, Third));
            IntervalVector.push_back(Interval(Perfect, Fourth));
            IntervalVector.push_back(Interval(Perfect, Fifth));
            IntervalVector.push_back(Interval(Minor, Sixth));
            IntervalVector.push_back(Interval(Minor, Seventh));

            CPString::string ScaleName("Minor");
            
            Scale myScale(MCC_MusicalNote::Pitch(MCC_MusicalNote::Pitch::C_Natural), IntervalVector, ScaleName);
            std::cout << myScale.Name() << ": ";


            MCC_MusicalNote::TextFormat::DefaultFormat.Octave_Disabled();
            MCC_MusicalNote::TextFormat::DefaultFormat.Accidental_Symbol();


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


            MCC_MusicalNote::TextFormat::DefaultFormat.Octave_Disabled();
            MCC_MusicalNote::TextFormat::DefaultFormat.Accidental_Symbol();


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
            Scale myScale(MCC_MusicalNote::Pitch(MCC_MusicalNote::Pitch::C_Natural), MCC_MusicalScale::Flash::ScaleArrays::Exotic, 0);
            std::cout << myScale.Name() << ": ";


            MCC_MusicalNote::TextFormat::DefaultFormat.Octave_Disabled();
            MCC_MusicalNote::TextFormat::DefaultFormat.Accidental_Symbol();


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
    
	return 0;
}
