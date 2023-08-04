#include "../UartPortAPI.h"
#include <iostream>

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
