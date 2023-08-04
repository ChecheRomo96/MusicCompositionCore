#include <Arduino.h>
#include <MusicCompositionCore.h>
#include "UartPortAPI.h"

void setup()
{
	MCC::Start();
	Serial.begin(115200);

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

void loop()
{

}