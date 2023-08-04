#ifndef MCC_MIDI_SYSTEM_PORTS_H
#define MCC_MIDI_SYSTEM_PORTS_H

	#include <MCC_BuildSettings.h>
	#include <CPVector.h>
	#include <CPString.h>

	namespace MusicCompositionCore::Communications::Midi
	{
		class Port;
        extern Midi::Port DummyPort;
	}

	#if defined(MCC_UART_PORT_ENABLED)
		namespace MusicCompositionCore::Communications::Uart
		{
			class Port;
			
		    #if defined(MCC_UART_IN_ENABLED)
				namespace Input{ class Port; }
		    #endif

			#if defined(MCC_UART_OUT_ENABLED)
				namespace Output { class Port; }
			#endif
		}
	#endif


	namespace MusicCompositionCore::Communications::Midi
	{
        class SystemPortHandler
        {
	        public:

		        typedef uint8_t PortID;
		    	static constexpr SystemPortHandler::PortID InvalidPortID = 0xFF;
		    	
	        private:

	        	CPVector::vector<Midi::Port> _PortVector;

	        public:

	        	SystemPortHandler();
	        	
	        	const uint8_t PortCount() const;
	        	const Midi::SystemPortHandler::PortID& GetID(const Midi::Port& Port) const;
	        	Midi::Port& Port(const Midi::SystemPortHandler::PortID& ID);

				Midi::Port& operator[](unsigned int x);
				const Midi::Port& operator[](unsigned int x) const;


				#if defined(MCC_UART_MIDI_ENABLED)

	        		bool BindPort(const UartMidi::Port& Port);
	        		void UnbindPort(const UartMidi::Port& Port);
	        		Midi::Port& GetPort(const UartMidi::Port& Port);
	        		const Midi::SystemPortHandler::PortID& GetID(const UartMidi::Port& Port) const;

		        	#if defined(MCC_UART_PORT_ENABLED)
		        		bool BindPort(const Uart::Port& Port);
		        		void UnbindPort(const Uart::Port& Port);
		        		Midi::Port& GetPort(const Uart::Port& Port);
		        		const Midi::SystemPortHandler::PortID& GetID(const Uart::Port& Port) const;

			            #if defined(MCC_UART_IN_ENABLED)
		                    bool BindPort(const Uart::Input::Port& Port);
		                    void UnbindPort(const Uart::Input::Port& Port);
							Midi::SystemPortHandler::PortID GetID(const Uart::Input::Port& Port);
		                    Midi::Port& GetPort(const Uart::Input::Port& Port);
			            #endif

			            #if defined(MCC_UART_OUT_ENABLED)
		                    bool BindPort(const Uart::Output::Port& Port);
		                    void UnbindPort(const Uart::Output::Port& Port);
							Midi::SystemPortHandler::PortID GetID(const Uart::Output::Port& Port);
		                    Midi::Port& GetPort(const Uart::Output::Port& Port);
			            #endif
		        	#endif
	            #endif

        };

        extern SystemPortHandler SystemPorts;
    
    }

#endif//MCC_MIDI_SYSTEM_PORTS_H