#ifndef MCC_USER_SETUP_H
#define MCC_USER_SETUP_H

        //////////////////////////////////////////////////////////////////
        // Compilation Setup

                #ifndef MCC_CORE_ENABLED
                    #define MCC_CORE_ENABLED
                #endif

                #ifndef MCC_UTILITY_CORE_ENABLED
                    #define MCC_UTILITY_CORE_ENABLED
                #endif

                #ifndef MCC_MUSICAL_CORE_ENABLED
                    #define MCC_MUSICAL_CORE_ENABLED
                #endif

                #ifndef MCC_MIDI_CORE_ENABLED
                    #define MCC_MIDI_CORE_ENABLED
                #endif
        //              
        //////////////////////////////////////////////////////////////////
        // Debug 
                
                //#define DEBUG
        //              
        //////////////////////////////////////////////////////////////////
        // Default Midi Ports
        
                #define MIDI_CLIENT_NAME "MCC"
                
                #define MIDI_PORT_1_ENABLED
                #define MIDI_PORT_1_DUPLEX
                //#define MIDI_PORT_1_SEND_ONLY
                //#define MIDI_PORT_1_RECIEVE_ONLY              
                        #define MIDI_PORT_1_NAME "MidiPort 1"
        
                //#define MIDI_PORT_2_ENABLED
                #define MIDI_PORT_2_DUPLEX
                //#define MIDI_PORT_2_SEND_ONLY
                //#define MIDI_PORT_2_RECIEVE_ONLY
                        #define MIDI_PORT_2_NAME "MidiPort 2" 

                //#define MIDI_PORT_3_ENABLED
                #define MIDI_PORT_3_DUPLEX
                //#define MIDI_PORT_3_SEND_ONLY
                //#define MIDI_PORT_3_RECIEVE_ONLY
                        #define MIDI_PORT_3_NAME "MidiPort 3" 

                //#define MIDI_PORT_4_ENABLED
                #define MIDI_PORT_4_DUPLEX
                //#define MIDI_PORT_4_SEND_ONLY
                //#define MIDI_PORT_4_RECIEVE_ONLY
                        #define MIDI_PORT_4_NAME "MidiPort 4" 
                


#endif//MCC_USER_SETUP
