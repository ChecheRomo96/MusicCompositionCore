#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalNote;
using namespace MCC_MusicalNote::Pitch;

int main()
{
    MCC::Start();
        
    CPVector::vector<MCC_MusicalNote::Note> NoteVector;
    CPVector::Sorting::SortingArray<MCC_MusicalNote::Note> SortConfiguration;

    for(uint8_t i = 0; i < 100; i++)
    {
        NoteVector.push_back( MCC_MusicalNote::Note(PitchClass(rand()%(MCC_MusicalNote::Pitch::MaxIterator+1), rand() % 4 ) );
        
        std::cout<<NoteVector[i].Name();
        if((i+1)%5 == 0){std::cout<<std::endl;}
        else if(i<99){std::cout<<", ";}
        
    } std::cout<<std::endl;
    
    SortConfiguration.Append(MCC_MusicalNote::Sorting::Note::Letter_Ascending);
    SortConfiguration.Append(MCC_MusicalNote::Sorting::Note::Accidental_Ascending);
    SortConfiguration.Append(MCC_MusicalNote::Sorting::Note::Octave_Ascending);
    
    NoteVector.Sort(SortConfiguration);
    
    
    for(uint8_t i = 0; i < 100; i++)
    {
        std::cout<<NoteVector[i].Name();
        if((i+1)%5 == 0){std::cout<<std::endl;}
        else if(i<99){std::cout<<", ";}
        
    } std::cout<<std::endl;
    
	return 0;
}
