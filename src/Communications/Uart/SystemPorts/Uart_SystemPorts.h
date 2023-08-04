#ifndef MCC_UART_SYSTEM_PORTS_H
#define MCC_UART_SYSTEM_PORTS_H

	#include <MCC_BuildSettings.h>
	#include <CPVector.h>
	#include <CPString.h>

	namespace MusicCompositionCore::Communications::Uart
	{
		class Port;
        extern Port DummyPort;
	}
	
	#if defined(MCC_UART_IN_ENABLED)
		namespace MusicCompositionCore::Communications::Uart::Input
		{
			class Port;
		}
	#endif

	#if defined(MCC_UART_IN_ENABLED)
		namespace MusicCompositionCore::Communications::Uart::Output
		{
			class Port;
		}
	#endif

	namespace MusicCompositionCore::Communications::Uart
	{
        class SystemPortHandler
        {
	        public:
		        typedef uint8_t PortID;
		    	static constexpr SystemPortHandler::PortID InvalidPortID = 0xFF;
		    	
	        private:

	        	CPVector::vector<Uart::Port> _PortVector;

	        public:

	        	SystemPortHandler();
	        	
	        	const uint8_t PortCount() const;
	        	const Uart::SystemPortHandler::PortID& GetID(const Uart::Port& Port) const;
	        	Uart::Port& Port(const Uart::SystemPortHandler::PortID& ID);

				Uart::Port& operator[](unsigned int x);
				const Uart::Port& operator[](unsigned int x) const;


	        	#if defined(MCC_UART_IN_ENABLED)
	        		bool BindPort(const Uart::Input::Port& Port);
	        		void UnbindPort(const Uart::Input::Port& Port);
	        		Uart::Port& GetPort(const Uart::Input::Port& Port);
	        		const Uart::SystemPortHandler::PortID& GetID(const Uart::Input::Port& Port) const;
	        	#endif

	        	#if defined(MCC_UART_OUT_ENABLED)
	        		bool BindPort(const Uart::Output::Port& Port);
	        		void UnbindPort(const Uart::Output::Port& Port);
	        		Uart::Port& GetPort(const Uart::Output::Port& Port);
	        		const Uart::SystemPortHandler::PortID& GetID(const Uart::Output::Port& Port) const;
	        	#endif


        };

        extern SystemPortHandler SystemPorts;
    
    }

#endif//MCC_UART_SYSTEM_PORTS_H