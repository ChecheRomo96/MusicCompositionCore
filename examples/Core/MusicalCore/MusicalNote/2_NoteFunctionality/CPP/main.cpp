#include <MCC.h>

using namespace MCC_MusicalNote;

int main(int argc, const char * argv[])
{   /////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout<<std::endl<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<std::endl<<std::endl;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Printing all the notes recognized by the system
    {
        CPString::string str;
        Pitch::Letter::LetterClass Letter;
        Pitch::Accidental::AccidentalClass Accidental;
    
        for(uint8_t i = 0; i < Pitch::Letter::Count; i++)
        {
            Letter = Pitch::Letter::LetterClass(i);
            
            for(int8_t j = Pitch::Accidental::Min; j <= Pitch::Accidental::Max; j++)
            {
                Accidental = Pitch::Accidental::AccidentalClass(j);
                
                Note myNote(i,j,3);
                str = myNote.Name();
                std::cout<<str;
                
                if(j < Pitch::Accidental::Max){ std::cout<<", "; }
                else{ std::cout<<std::endl; }
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout<<std::endl<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<std::endl<<std::endl;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Note Constructors
    {
        Note myNote;
        
        myNote.SetPitch(Pitch::C_Natural);
        myNote.SetOctave(3);
        
        std::cout<<myNote.Name()<<std::endl;
        
        myNote = Note(Pitch::C_Natural,3);
        
        std::cout<<myNote.Name()<<std::endl;
        
        myNote = Note(Pitch::Letter::C,Pitch::Accidental::Natural,3);
        
        std::cout<<myNote.Name()<<std::endl;
        
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout<<std::endl<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<std::endl<<std::endl;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Comparing Notes
    {
        using namespace MCC_MusicalNote;
        
        SetCompareMode(CompareMode::Pitch);
        
        Note NoteA(Pitch::C_Natural,3);
        Note NoteB(Pitch::C_Natural,4);
        
        std::cout<<"Comparing Pitch: ";
        
        if(NoteA>NoteB){std::cout<<NoteA.Name()<<" > "<<NoteB.Name()<<"."<<std::endl;}
        else if(NoteA<NoteB){std::cout<<NoteA.Name()<<" < "<<NoteB.Name()<<"."<<std::endl;}
        else if(NoteA == NoteB){std::cout<<NoteA.Name()<<" == "<<NoteB.Name()<<"."<<std::endl;}
        
        SetCompareMode(CompareMode::Name);
        
        std::cout<<"Comparing Name: ";
        
        if(NoteA>NoteB){std::cout<<NoteA.Name()<<" > "<<NoteB.Name()<<"."<<std::endl;}
        else if(NoteA<NoteB){std::cout<<NoteA.Name()<<" < "<<NoteB.Name()<<"."<<std::endl;}
        else if(NoteA == NoteB){std::cout<<NoteA.Name()<<" == "<<NoteB.Name()<<"."<<std::endl;}
        
        //////////////////////////////////////////////////////////////////////////////////////////////
        std::cout<<std::endl;
        //////////////////////////////////////////////////////////////////////////////////////////////
        
        SetCompareMode(CompareMode::Pitch);
        
        NoteA.SetPitch(Pitch::C_Natural);
        NoteB.SetPitch(Pitch::D_DoubleFlat);
        NoteB.SetOctave(3);
        
        std::cout<<"Comparing Pitch: ";
        
        if(NoteA>NoteB){std::cout<<NoteA.Name()<<" > "<<NoteB.Name()<<"."<<std::endl;}
        else if(NoteA<NoteB){std::cout<<NoteA.Name()<<" < "<<NoteB.Name()<<"."<<std::endl;}
        else if(NoteA == NoteB){std::cout<<NoteA.Name()<<" == "<<NoteB.Name()<<"."<<std::endl;}
        
        SetCompareMode(CompareMode::Name);
        
        std::cout<<"Comparing Name: ";
        
        if(NoteA>NoteB){std::cout<<NoteA.Name()<<" > "<<NoteB.Name()<<"."<<std::endl;}
        else if(NoteA<NoteB){std::cout<<NoteA.Name()<<" < "<<NoteB.Name()<<"."<<std::endl;}
        else if(NoteA == NoteB){std::cout<<NoteA.Name()<<" == "<<NoteB.Name()<<"."<<std::endl;}
        
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout<<std::endl<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<std::endl<<std::endl;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
}
