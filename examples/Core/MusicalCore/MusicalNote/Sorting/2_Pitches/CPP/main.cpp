#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalNote;

int main()
{
    MCC::Start();
        
    CPVector::vector<MCC_MusicalNote::Pitch> PitchVector;
    CPVector::Sorting::SortingArray<MCC_MusicalNote::Pitch> SortConfiguration;

    for(uint8_t i = 0; i < 100; i++)
    {
        PitchVector.push_back( Pitch(rand()%(MCC_MusicalNote::Pitch::MaxIterator+1)) );
        
        std::cout<< PitchVector[i].Name();
        if((i+1)%5 == 0){std::cout<<std::endl;}
        else if(i<99){std::cout<<", ";}
        
    } std::cout<<std::endl;
    
    SortConfiguration.Append(MCC_MusicalNote::Sorting::PitchClass::Letter_Ascending);
    SortConfiguration.Append(MCC_MusicalNote::Sorting::PitchClass::Accidental_Ascending);
    
    PitchVector.Sort(SortConfiguration);
    
    
    for(uint8_t i = 0; i < 100; i++)
    {
        std::cout<< PitchVector[i].Name();
        if((i+1)%5 == 0){std::cout<<std::endl;}
        else if(i<99){std::cout<<", ";}
        
    } std::cout<<std::endl;
    
	return 0;
}
