#include <iostream>
#include <CPString.h>
#include <CPVector.h>
#include <MCC.h>

int main()
{
    std::cout << "This project uses CPString version: " << CPSTRING_VERSION << std::endl;
    std::cout << "This project uses CPVector version: " << CPVECTOR_VERSION << std::endl;
    std::cout << "This project uses MCC version: " << MCC_VERSION << std::endl;
    std::cout << std::endl;

    std::cout << "Checking MCC compile congif:" << std::endl;
    
    std::cout << std::endl;

    #if defined(MCC_CORE_ENABLED)
        
        std::cout << "MCC::Core Enabled..."<< std::endl;

        #if defined(MCC_UTILITY_CORE_ENABLED)
            std::cout << "MCC::Core::UtilityCore Enabled..." << std::endl;

            #if defined(MCC_ACCUMULATOR_ENABLED)
                std::cout << "MCC::Core::UtilityCore::Accumulator Enabled..." << std::endl;
            #endif

        #endif
    
        std::cout << std::endl;
    
        #if defined(MCC_MUSICAL_CORE_ENABLED)
            std::cout << "MCC::Core::MusicalCore Enabled..." << std::endl;
    
        #if defined(MCC_MUSICAL_NOTE_ENABLED)
            std::cout << "MCC::Core::MusicalCore::MusicalNote Enabled..." << std::endl;
        #endif
    
        #endif
    #endif



	return 0;
}
