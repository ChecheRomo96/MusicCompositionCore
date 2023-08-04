#ifndef UART_PORT_API
#define UART_PORT_API

	#include <CPVector.h>

	extern CPVector::vector<uint8_t> Buffer;

	uint8_t UART_BytesAvailable();
	uint8_t UART_ReadByte();
	void UART_MidiMessageCallback(const CPVector::vector<uint8_t>& Message);
	
#endif//UART_PORT_API