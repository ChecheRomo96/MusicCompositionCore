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

void UART_MidiMessageCallback(const CPVector::vector<uint8_t>& Message)
{
	std::cout << "Midi Message Callback -> ";

	for (uint8_t i = 0; i < Message.size(); i++)
	{
		std::cout << (uint32_t)Message[i];
		if (i < Message.size()-1) { std::cout << ", "; }
		else { std::cout << "."; }
	} std::cout << std::endl;
}



int main()
{
	MCC::Start();

	// Crate an Uart::Input Port, and retrieve the data on the input buffer

	MCC_Communications::Uart::Input::Port Port;
	Port.SetName("Uart Input Port");
	Port.HLAPI_Link(UART_BytesAvailable, UART_ReadByte);

	std::cout << Port.Name() << " :" << std::endl;
	
	Buffer.resize(3);
	Buffer[0] = 0x90;	Buffer[1] = 60;	Buffer[2] = 100;

	while (Port.BytesAvailable())
	{
		std::cout << (uint16_t)Port.ReadByte();
		if (Buffer.size() >= 1) {std::cout << ", "; }
		else { std::cout << "."; }
	}  std::cout << std::endl << std::endl;


	// Crate an Uart::Input Port, bind it to the Uart::SystemPorts, and retrieve the data on the input buffer
	MCC_Communications::Uart::Input::Port Port2("Uart Port", UART_BytesAvailable, UART_ReadByte);

	std::cout << Port2.Name() << " :" << std::endl;

	if (Port2.Uart_BindPort())
	{
		Buffer.resize(3);
		Buffer[0] = 0x90;	Buffer[1] = 60;	Buffer[2] = 100;


		while (Port2.Uart_Port().BytesAvailable())
		{
			std::cout << (uint16_t)Port2.Uart_Port().ReadByte();
			if (Buffer.size() >= 1) { std::cout << ", "; }
			else { std::cout << "."; }
		}  std::cout << std::endl << std::endl;
	}

	#if defined(MCC_UART_MIDI_ENABLED)
	// Crate an Uart::Input Port, bind it to the Midi::UartMidi::SystemPorts, and retrieve the data on the input buffer
	MCC_Communications::Uart::Input::Port Port3("UartMidi Port", UART_BytesAvailable, UART_ReadByte);

	std::cout << Port3.Name() << " :" << std::endl;

	if (Port3.UartMidi_BindPort())
	{
		Port3.UartMidi_Port().AppendCallback(UART_MidiMessageCallback);

		Buffer.resize(3);
		Buffer[0] = 0x90;	Buffer[1] = 60;	Buffer[2] = 100;


		Port3.UartMidi_Port().Service();
	} std::cout<<std::endl;


	// Crate an Uart::Input Port, bind it to the Midi::SystemPorts, and retrieve the data on the input buffer
	MCC_Communications::Uart::Input::Port Port4("Midi Port", UART_BytesAvailable, UART_ReadByte);

	std::cout << Port4.Name() << " :" << std::endl;

	if (Port4.Midi_BindPort())
	{
		Port4.Midi_Port().AppendCallback(UART_MidiMessageCallback);

		Buffer.resize(3);
		Buffer[0] = 0x90;	Buffer[1] = 60;	Buffer[2] = 100;


		Port4.Midi_Port().Service();
	}
	#endif
}
