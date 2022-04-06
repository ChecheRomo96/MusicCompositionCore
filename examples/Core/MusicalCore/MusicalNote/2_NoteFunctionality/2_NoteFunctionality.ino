#include <MCC.h>

using namespace MCC_MusicalNote;

void setup(int argc, const char * argv[])
{   
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
        Serial.println("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Printing all the notes recognized by the system
        {
        CPString::string str;
        Pitch::Letter Letter;
        Pitch::Accidental Accidental;
    
        for(uint8_t i = 0; i < Pitch::Letter::MaxIterator+1; i++)
        {
            Letter = Pitch::Letter(i);
            
            for(int8_t j = Pitch::Accidental::MinIterator; j <= Pitch::Accidental::MaxIterator; j++)
            {
                Accidental = Pitch::Accidental(j);
                
                Note myNote(i,j,3);
                str = myNote.Name();
                Serial.print(str);
                
                if(j < Pitch::Accidental::MaxIterator){ Serial.print(", "); }
                else{ Serial.println(); }
            }
        }
    }
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
        Serial.println("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Note Constructors
        {
            Note myNote;
        
            myNote.SetPitch(Pitch::C_Natural);
            myNote.SetOctave(3);
        
            Serial.print(myNote.Name());
        
            myNote = Note(Pitch::C_Natural,3);
        
            Serial.print(myNote.Name());
        
            myNote = Note(Pitch::Letter::C,Pitch::Accidental::Natural,3);
        
            Serial.print(myNote.Name());
        
        }
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
        Serial.println("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Comparing Notes
        {
            using namespace MCC_MusicalNote;
        
            SetCompareMode(CompareMode::Pitch);
        
            Note NoteA(Pitch::C_Natural,3);
            Note NoteB(Pitch::C_Natural,4);
        
            Serial.print("Comparing Pitch: ");

            if (NoteA > NoteB) { Serial.print(NoteA.Name()); Serial.print(" > "); Serial.print(NoteB.Name()); Serial.println("."); }
            else if (NoteA < NoteB) { Serial.print(NoteA.Name()); Serial.print(" < "); Serial.print(NoteB.Name()); Serial.println("."); }
            else if (NoteA == NoteB) { Serial.print(NoteA.Name()); Serial.print(" == "); Serial.print(NoteB.Name()); Serial.println("."); }
        
            SetCompareMode(CompareMode::Name);
        
            Serial.print("Comparing Name: ");

            if (NoteA > NoteB) { Serial.print(NoteA.Name()); Serial.print(" > "); Serial.print(NoteB.Name()); Serial.println("."); }
            else if (NoteA < NoteB) { Serial.print(NoteA.Name()); Serial.print(" < "); Serial.print(NoteB.Name()); Serial.println("."); }
            else if (NoteA == NoteB) { Serial.print(NoteA.Name()); Serial.print(" == "); Serial.print(NoteB.Name()); Serial.println("."); }
        
            //////////////////////////////////////////////////////////////////////////////////////////////
            std::cout<<std::endl;
            //////////////////////////////////////////////////////////////////////////////////////////////
        
            SetCompareMode(CompareMode::Pitch);
        
            NoteA.SetPitch(Pitch::C_Natural);
            NoteB.SetPitch(Pitch::D_DoubleFlat);
            NoteB.SetOctave(3);
        
            Serial.print("Comparing Pitch: ");
            NoteB.Name();
        
            if (NoteA > NoteB) { Serial.print(NoteA.Name()); Serial.print(" > "); Serial.print(NoteB.Name()); Serial.println("."); }
            else if (NoteA < NoteB) { Serial.print(NoteA.Name()); Serial.print(" < "); Serial.print(NoteB.Name()); Serial.println("."); }
            else if (NoteA == NoteB) { Serial.print(NoteA.Name()); Serial.print(" == "); Serial.print(NoteB.Name()); Serial.println("."); }
        
            SetCompareMode(CompareMode::Name);
        
            Serial.print("Comparing Name: ");

            if (NoteA > NoteB) { Serial.print(NoteA.Name()); Serial.print(" > "); Serial.print(NoteB.Name()); Serial.println("."); }
            else if (NoteA < NoteB) { Serial.print(NoteA.Name()); Serial.print(" < "); Serial.print(NoteB.Name()); Serial.println("."); }
            else if (NoteA == NoteB) { Serial.print(NoteA.Name()); Serial.print(" == "); Serial.print(NoteB.Name()); Serial.println("."); }
        }
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
        Serial.println("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Getting Note Frequencies
        {
            Note NoteA(Pitch::A_Natural, 1);
            Note NoteB(Pitch::A_Natural, 2);
            Note NoteC(Pitch::A_Natural, 3);
            Note NoteD(Pitch::A_Natural, 4);
            Note NoteE(Pitch::A_Natural, 5);

            Serial.print(NoteA.Name()); Serial.print(" - "); Serial.print(NoteA.Frequency()); Serial.println(" Hz");
            Serial.print(NoteB.Name()); Serial.print(" - "); Serial.print(NoteB.Frequency()); Serial.println(" Hz");
            Serial.print(NoteC.Name()); Serial.print(" - "); Serial.print(NoteC.Frequency()); Serial.println(" Hz");
            Serial.print(NoteD.Name()); Serial.print(" - "); Serial.print(NoteD.Frequency()); Serial.println(" Hz");
            Serial.print(NoteE.Name()); Serial.print(" - "); Serial.print(NoteE.Frequency()); Serial.println(" Hz");
        }
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
        Serial.println("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -");
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void loop()
{

}
