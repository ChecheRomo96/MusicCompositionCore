#include <MCC.h>

using namespace MCC_MusicalNote;
using namespace MCC_MusicalNote::Pitch;

void setup()
{
    Serial.begin(115200);
    MCC::Start();
        
    CPVector::vector<MCC_MusicalNote::Note> NoteVector;
    CPVector::Sorting::SortingArray<MCC_MusicalNote::Pitch> SortConfiguration;

    for(uint8_t i = 0; i < 40; i++)
    {
        NoteVector.push_back( Pitch(rand()%(MCC_MusicalNote::Pitch::MaxIterator+1)) );
    
        Serial.print(NoteVector[i].Name());
        if((i+1)%5 == 0){Serial.println();}
        else if(i<99){Serial.print(", ");}
    } Serial.println();
    
    SortConfiguration.Append(MCC_MusicalNote::Sorting::Note::Letter_Ascending);
    SortConfiguration.Append(MCC_MusicalNote::Sorting::Note::Accidental_Ascending);
    SortConfiguration.Append(MCC_MusicalNote::Sorting::Note::Octave_Ascending);
    
    NoteVector.Sort(SortConfiguration);
    
    for(uint8_t i = 0; i < NoteVector.size(); i++)
    {
        Serial.print(NoteVector[i].Name());
        if((i+1)%5 == 0){Serial.println();}
        else if(i<99){Serial.print(", ");}
    } Serial.println();

    MCC_MusicalNote::Sort
}

void loop()
{
    
}