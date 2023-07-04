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
        
        std::cout << "MCC::Core Enabled..."<< std::endl<< std::endl;

        #if defined(MCC_UTILITY_CORE_ENABLED)
            std::cout << "  MCC::Core::UtilityCore Enabled..." << std::endl;

            #if defined(MCC_ACCUMULATOR_ENABLED)
                std::cout << "    MCC::Core::UtilityCore::Accumulator Enabled..." << std::endl;
            #endif

        #endif
    
        std::cout << std::endl;
    
        #if defined(MCC_MUSICAL_CORE_ENABLED)
            std::cout << "  MCC::Core::MusicalCore Enabled..." << std::endl;
    
            #if defined(MCC_MUSICAL_NOTE_ENABLED)
                std::cout << "    MCC::Core::MusicalCore::MusicalNote Enabled..." << std::endl;
            #endif
    
        #endif
    #endif

    std::cout << std::endl;

    #if defined(MCC_COMMUNICATIONS_ENABLED)
        std::cout << "MCC::Communications Enabled..." << std::endl<< std::endl;

        #if defined(MCC_MIDI_PORT_ENABLED)
            std::cout << "  MCC::Communications::Midi Enabled..." << std::endl;

            #if defined(MCC_UART_MIDI_ENABLED)
                std::cout << "    MCC::Communications::Midi::Uart Enabled..." << std::endl;

                #if defined(MCC_COMPILE_UART_MIDI_IN)
                    std::cout << "      MCC::Communications::Midi::Uart::InputPort Enabled..." << std::endl;
                #endif

                #if defined(MCC_COMPILE_UART_MIDI_OUT)
                    std::cout << "      MCC::Communications::Midi::Uart::OutputPort Enabled..." << std::endl;
                #endif
            #endif

            #if defined(MCC_RTMIDI_ENABLED)
                std::cout << "    MCC::Communications::Midi::RtMidi Enabled..." << std::endl;
                
            #endif



        #endif

    #endif


    #if defined(MCC_BUILD_EXAMPLES)
        std::cout << "Examples Built. Find them on the \"BuildDirectory/Examples\" Directory" << std::endl;
    #endif


	return 0;
}
