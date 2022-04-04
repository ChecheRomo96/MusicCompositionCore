#include <MCC.h>

using namespace MCC_MusicalNote::Pitch;


void setup()
{
	Serial.begin(115200);
	MCC::Start();
        
    CPVector::vector<MCC_MusicalNote::Note> noteVector;

    for(uint8_t i = 0; i < 20; i++)
    {
        noteVector.push_back(MCC_MusicalNote::Note(MCC_MusicalNote::PitchClass(rand()%MCC_MusicalNote::Pitch::Count), (rand()%3)+3 ));
    
        Serial.print(NoteVector[i].Name());
        if((i+1)%5 == 0){Serial.println();}
        else if(i<99){Serial.print(", ");}
    } Serial.println();
    
    SortConfiguration.Append(MCC_MusicalNote::Sorting::Note::Letter_Ascending);
    SortConfiguration.Append(MCC_MusicalNote::Sorting::Note::Accidental_Ascending);
    SortConfiguration.Append(MCC_MusicalNote::Sorting::Note::Octave_Ascending);
    
    NoteVector.Sort(SortConfiguration);
    
    
    for(uint8_t i = 0; i < 100; i++)
    {
        Serial.print(NoteVector[i].Name());
        if((i+1)%5 == 0){Serial.println();}
        else if(i<99){Serial.print(", ");}
    } Serial.println();
}

void loop()
{
	
}