#include <MCC.h>
#include <math.h>
#include <CPVector.h>

CPVector::vector<uint8_t> Buffer;

uint8_t UART_BytesAvailable()
{
	return Buffer.size();
}

uint8_t UART_ReadByte()
{
	return Buffer.pop_first();
}

void UART_Write( uint8_t Data )
{
	std::cout <<"0x" << std::hex << (uint16_t)Data << ", ";
}

void UART_MidiMessageCallback(const CPVector::vector<uint8_t>& Message)
{
	std::cout << "Midi Message Callback -> ";

	for (uint8_t i = 0; i < Message.size(); i++)
	{
		std::cout << "0x" << (uint32_t)Message[i];
		if (i < Message.size()-1) { std::cout << ", "; }
		else { std::cout << "."; }
	} std::cout << std::endl;
}

int main()
{
	MCC::Start();

	// Crate an Uart::Duplex Port, and retrieve the data on the input buffer
	MCC_Communications::Uart::Duplex::Port Port;
	Port.SetName("Uart Duplex Port");
	Port.HLAPI_Link(UART_BytesAvailable, UART_ReadByte, UART_Write);

	std::cout << Port.Name() << " :" << std::endl;
	
	Buffer.resize(3);
	Buffer[0] = 0x90;	Buffer[1] = 60;	Buffer[2] = 100;

	std::cout<<"  Writing to Port : ";
	Port.WriteBuffer(Buffer);
	std::cout << std::endl;

	std::cout<<"  Reading from Port : ";
	while (Port.BytesAvailable())
	{
		std::cout << "0x" << (uint16_t)Port.ReadByte();
		if (Buffer.size() >= 1) {std::cout << ", "; }
		else { std::cout << "."; }
	}  std::cout << std::endl << std::endl;

	// Crate an Uart::Duplex Port, bind it to the Uart::SystemPorts, and retrieve the data on the input buffer
	MCC_Communications::Uart::Duplex::Port Port2("Uart Port", UART_BytesAvailable, UART_ReadByte, UART_Write);


	if (Port2.Uart_BindPort())
	{

		std::cout << Port2.Uart_Port().Name() << " :" << std::endl;

		Buffer.resize(3);
		Buffer[0] = 0x90;	Buffer[1] = 60;	Buffer[2] = 100;

		std::cout<<"  Writing to Port : ";
		Port2.Uart_Port().WriteBuffer(Buffer);
		std::cout << std::endl;

		std::cout<<"  Reading from Port : ";
		while (Port2.Uart_Port().BytesAvailable())
		{
			std::cout << "0x" << (uint16_t)Port2.Uart_Port().ReadByte();
			if (Buffer.size() >= 1) {std::cout << ", "; }
			else { std::cout << "."; }
		}  std::cout << std::endl << std::endl;
	}

	#if defined(MCC_UART_MIDI_ENABLED)
	
		// Crate an Uart::Duplex Port, bind it to the Midi::UartMidi::SystemPorts, and retrieve the data on the input buffer
		MCC_Communications::Uart::Duplex::Port Port3("UartMidi Port", UART_BytesAvailable, UART_ReadByte, UART_Write);

		if (Port3.UartMidi_BindPort())
		{
			std::cout << Port3.UartMidi_Port().Name() << " :" << std::endl;

			Port3.UartMidi_Port().AppendCallback(UART_MidiMessageCallback);

			Buffer.resize(3);
			Buffer[0] = 0x90;	Buffer[1] = 60;	Buffer[2] = 100;

			std::cout<<"  Writing to Port : ";
			Port3.UartMidi_Port().WriteMessage(Buffer);

			Port3.UartMidi_Port().NoteOn(60, 100);

			MCC_MidiCore::MidiMessage myMessage;
			myMessage.NoteOff(60);
			Port3.UartMidi_Port().WriteMessage(myMessage);
			
			std::cout << std::endl;

			std::cout<<"  Reading from Port : ";
			Port3.UartMidi_Port().Service();
		} std::cout<<std::endl;


		// Crate an Uart::Duplex Port, bind it to the Midi::SystemPorts, and retrieve the data on the input buffer
		MCC_Communications::Uart::Duplex::Port Port4("Midi Port", UART_BytesAvailable, UART_ReadByte, UART_Write);

		if (Port4.Midi_BindPort())
		{
			std::cout << Port4.Midi_Port().Name() << " :" << std::endl;

			Port4.Midi_Port().AppendCallback(UART_MidiMessageCallback);

			Buffer.resize(3);
			Buffer[0] = 0x90;	Buffer[1] = 60;	Buffer[2] = 100;

			std::cout << "  Writing to Port : ";
			Port4.Midi_Port().WriteMessage(Buffer);

			Port4.Midi_Port().NoteOn(60, 100);

			MCC_MidiCore::MidiMessage myMessage;
			myMessage.NoteOff(60);
			Port4.Midi_Port().WriteMessage(myMessage);

			std::cout << std::endl;

			std::cout << "  Reading from Port : ";
			Port4.Midi_Port().Service();
		} std::cout << std::endl;

	#endif
}
