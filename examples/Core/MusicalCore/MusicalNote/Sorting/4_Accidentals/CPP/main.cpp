#include <iostream>
#include <MCC.h>

using namespace MCC_MusicalNote;

int main()
{
    MCC::Start();
        
    CPVector::vector<MCC_MusicalNote::Pitch::Accidental> NoteVector;
    CPVector::Sorting::SortingArray<MCC_MusicalNote::Pitch::Accidental> SortConfiguration;

    for(uint8_t i = 0; i < 100; i++)
    {
        NoteVector.push_back( Pitch::Accidental( Pitch::Accidental::MinIterator + (rand()%(Pitch::Accidental::MaxIterator-Pitch::Accidental::MinIterator+1))  ));
        
        std::cout<<NoteVector[i].Name();
        if((i+1)%5 == 0){std::cout<<std::endl;}
        else if(i<99){std::cout<<", ";}
        
    } std::cout<<std::endl;
    
    SortConfiguration.Append(Sorting::Accidental::Ascending);
    
    NoteVector.Sort(SortConfiguration);
    
    
    for(uint8_t i = 0; i < 100; i++)
    {
        std::cout<<NoteVector[i].Name();
        if((i+1)%5 == 0){std::cout<<std::endl;}
        else if(i<99){std::cout<<", ";}
        
    } std::cout<<std::endl;
    
	return 0;
}
