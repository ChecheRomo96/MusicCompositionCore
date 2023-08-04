#include <MCC.h>
#include <math.h>
#include <CPVector.h>

CPVector::vector<uint8_t> Buffer;


void UART_Write( uint8_t Data )
{
	std::cout <<"0x" << std::hex << (uint16_t)Data << ", ";
}

int main()
{
	MCC::Start();

	// Crate an Uart::Input Port, and retrieve the data on the input buffer
	MCC_Communications::Uart::Output::Port Port;
	Port.SetName("Uart Output Port");
	Port.HLAPI_Link(UART_Write);

	std::cout << Port.Name() << " :" << std::endl;

	Buffer.resize(3);
	Buffer[0] = 0x90;	Buffer[1] = 60;	Buffer[2] = 100;

	Port.WriteBuffer(Buffer);
	std::cout << std::endl << std::endl;

	// Crate an Uart::Input Port, bind it to the Uart::SystemPorts, and retrieve the data on the input buffer
	MCC_Communications::Uart::Output::Port Port2("Uart Port", UART_Write);


	if (Port2.Uart_BindPort())
	{
		std::cout << Port2.Uart_Port().Name() << " :" << std::endl;
		Port2.Uart_Port().WriteBuffer(Buffer);
		std::cout << std::endl << std::endl;
	}

	#if defined(MCC_UART_MIDI_ENABLED)
	// Crate an Uart::Input Port, bind it to the Midi::UartMidi::SystemPorts, and retrieve the data on the input buffer
		
		MCC_Communications::Uart::Output::Port Port3("UartMidi Port", UART_Write);

		if(Port3.UartMidi_BindPort())
		{
			std::cout << Port3.UartMidi_Port().Name() << " :" << std::endl;
			Port3.UartMidi_Port().WriteMessage(Buffer);
			std::cout << std::endl;

			//Port3.UartMidi_Port().NoteOn(60, 100);

			MCC_MidiCore::MidiMessage myMessage;
			myMessage.NoteOff(60);
			Port3.UartMidi_Port().WriteMessage(myMessage);

			std::cout << std::endl << std::endl;
		}
		

		// Crate an Uart::Input Port, bind it to the Midi::SystemPorts, and retrieve the data on the input buffer
		MCC_Communications::Uart::Output::Port Port4("Midi Port", UART_Write);


		if (Port4.Midi_BindPort())
		{
			std::cout << Port4.Midi_Port().Name() << " :" << std::endl;
			Port4.Midi_Port().WriteMessage(Buffer);
			std::cout << std::endl;

			Port4.Midi_Port().NoteOn(60, 100);

			MCC_MidiCore::MidiMessage myMessage;
			myMessage.NoteOff(60);
			Port4.Midi_Port().WriteMessage(myMessage);

			std::cout << std::endl << std::endl;
		}
	#endif

}
