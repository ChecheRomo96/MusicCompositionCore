#ifndef MCC_UART_MIDI_SYSTEM_PORTS_H
#define MCC_UART_MIDI_SYSTEM_PORTS_H

	#include <MCC_BuildSettings.h>
	#include <CPVector.h>
	#include <CPString.h>

	namespace MusicCompositionCore::Communications::Midi::UartMidi
	{
		class Port;
        extern UartMidi::Port DummyPort;
	}

	#if defined(MCC_UART_PORT_ENABLED)
		namespace MusicCompositionCore::Communications::Uart
		{
			class Port;

		    #if defined(MCC_UART_IN_ENABLED)
				namespace Input{ class Port; }
		    #endif
		}
	#endif


	namespace MusicCompositionCore::Communications::Midi::UartMidi
	{
        class SystemPortHandler
        {
	        public:

		        typedef uint8_t PortID;
		    	static constexpr SystemPortHandler::PortID InvalidPortID = 0xFF;
		    	
	        private:

	        	CPVector::vector<UartMidi::Port> _PortVector;

	        public:

	        	SystemPortHandler();
	        	
	        	const uint8_t PortCount() const;
	        	const UartMidi::SystemPortHandler::PortID& GetID(const UartMidi::Port& Port) const;
	        	UartMidi::Port& Port(const UartMidi::SystemPortHandler::PortID& ID);

				UartMidi::Port& operator[](unsigned int x);
				const UartMidi::Port& operator[](unsigned int x) const;


	        	#if defined(MCC_UART_PORT_ENABLED)
	        		bool BindPort(const Uart::Port& Port);
	        		void UnbindPort(const Uart::Port& Port);
	        		UartMidi::Port& GetPort(const Uart::Port& Port);
	        		const UartMidi::SystemPortHandler::PortID& GetID(const Uart::Port& Port) const;

		            #if defined(MCC_UART_IN_ENABLED)
	                    bool BindPort(const Uart::Input::Port& Port);
	                    void UnbindPort(const Uart::Input::Port& Port);
	                    UartMidi::Port& GetPort(const Uart::Input::Port& Port);
						const UartMidi::SystemPortHandler::PortID GetID(const Uart::Input::Port& Port) const;
		            #endif

		            #if defined(MCC_UART_OUT_ENABLED)
	                    bool BindPort(const Uart::Output::Port& Port);
	                    void UnbindPort(const Uart::Output::Port& Port);
	                    UartMidi::Port& GetPort(const Uart::Output::Port& Port);
						const UartMidi::SystemPortHandler::PortID GetID(const Uart::Output::Port& Port) const;
		            #endif
	        	#endif

        };

        extern SystemPortHandler SystemPorts;
    
    }

#endif//MCC_UART_MIDI_SYSTEM_PORTS_H