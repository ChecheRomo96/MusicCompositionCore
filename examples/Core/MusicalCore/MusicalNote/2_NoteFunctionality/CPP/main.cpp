#include <MCC.h>

using namespace MCC_MusicalNote;

int main(int argc, const char * argv[])
{   /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
        std::cout<<std::endl<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<std::endl<<std::endl;
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
                std::cout<<str;
                
                if(j < Pitch::Accidental::MaxIterator){ std::cout<<", "; }
                else{ std::cout<<std::endl; }
            }
        }
    }
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
        std::cout<<std::endl<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<std::endl<<std::endl;
    //
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
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
        std::cout<<std::endl<<"- - - - - - - - - - - - - - - - - - - - - - - - - - - - -"<<std::endl<<std::endl;
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Comparing Notes
        {
            using namespace MCC_MusicalNote;
        
            SetCompareMode(CompareMode::Pitch);
        
            Note NoteA(Pitch::C_Natural,3);
            Note NoteB(Pitch::C_Natural,4);
        
            std::cout<<"Comparing Pitch: ";

            if (NoteA > NoteB) { std::cout << NoteA.Name() << " > "; std::cout << NoteB.Name() << "." << std::endl; }
            else if (NoteA < NoteB) { std::cout << NoteA.Name() << " < "; std::cout << NoteB.Name() << "." << std::endl; }
            else if (NoteA == NoteB) { std::cout << NoteA.Name() << " == "; std::cout << NoteB.Name() << "." << std::endl; }
        
            SetCompareMode(CompareMode::Name);
        
            std::cout<<"Comparing Name: ";

            if (NoteA > NoteB) { std::cout << NoteA.Name() << " > "; std::cout << NoteB.Name() << "." << std::endl; }
            else if (NoteA < NoteB) { std::cout << NoteA.Name() << " < "; std::cout << NoteB.Name() << "." << std::endl; }
            else if (NoteA == NoteB) { std::cout << NoteA.Name() << " == "; std::cout << NoteB.Name() << "." << std::endl; }
        
            //////////////////////////////////////////////////////////////////////////////////////////////
            std::cout<<std::endl;
            //////////////////////////////////////////////////////////////////////////////////////////////
        
            SetCompareMode(CompareMode::Pitch);
        
            NoteA.SetPitch(Pitch::C_Natural);
            NoteB.SetPitch(Pitch::D_DoubleFlat);
            NoteB.SetOctave(3);
        
            std::cout<<"Comparing Pitch: ";
            NoteB.Name();
        
            if (NoteA > NoteB){ std::cout << NoteA.Name() << " > "; std::cout<< NoteB.Name() << "." << std::endl; }
            else if(NoteA<NoteB) { std::cout << NoteA.Name() << " < "; std::cout << NoteB.Name() << "." << std::endl; }
            else if(NoteA == NoteB) { std::cout << NoteA.Name() << " == "; std::cout << NoteB.Name() << "." << std::endl; }
        
            SetCompareMode(CompareMode::Name);
        
            std::cout<<"Comparing Name: ";

            if (NoteA > NoteB) { std::cout << NoteA.Name() << " > "; std::cout << NoteB.Name() << "." << std::endl; }
            else if (NoteA < NoteB) { std::cout << NoteA.Name() << " < "; std::cout << NoteB.Name() << "." << std::endl; }
            else if (NoteA == NoteB) { std::cout << NoteA.Name() << " == "; std::cout << NoteB.Name() << "." << std::endl; }
        }
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
        std::cout << std::endl << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl << std::endl;
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Getting Note Frequencies
        {
            Note NoteA(Pitch::A_Natural, 1);
            Note NoteB(Pitch::A_Natural, 2);
            Note NoteC(Pitch::A_Natural, 3);
            Note NoteD(Pitch::A_Natural, 4);
            Note NoteE(Pitch::A_Natural, 5);

            std::cout << NoteA.Name() << " - " << NoteA.Frequency() << " Hz" << std::endl;
            std::cout << NoteB.Name() << " - " << NoteB.Frequency() << " Hz" << std::endl;
            std::cout << NoteC.Name() << " - " << NoteC.Frequency() << " Hz" << std::endl;
            std::cout << NoteD.Name() << " - " << NoteD.Frequency() << " Hz" << std::endl;
            std::cout << NoteE.Name() << " - " << NoteE.Frequency() << " Hz" << std::endl;
        }
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
        std::cout << std::endl << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl << std::endl;
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
}
