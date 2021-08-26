#ifndef MCC_USER_SETUP_H
#define MCC_USER_SETUP_H

	//////////////////////////////////////////////////////////////////
	// Hard Coded Compilation 

		//#define ARDUINO
		//#define PSOC_CREATOR
		//#define CPP
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
