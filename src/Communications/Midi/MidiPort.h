#ifndef MCC_MIDI_PORT_H
#define MCC_MIDI_PORT_H

	#include <MCC_BuildSettings.h>

	namespace MusicCompositionCore
	{
		namespace Communications
		{
			namespace Midi
			{
				typedef uint8_t PortType;
				typedef uint8_t PortID;

				static constexpr PortID InvalidID = 0xFF;

				namespace PortTypes
				{
					static constexpr Midi::PortType InvalidType = 0;
					static constexpr Midi::PortType Uart = 1;
					static constexpr Midi::PortType RtMidi = 2;
				}
			}
		}
	}

	#if defined (MCC_UART_MIDI_ENABLED)
		#include "UartMidi/UartMidi.h"
	#endif

	#include<CPString.h>
	#include<CPVector.h>

	namespace MusicCompositionCore
	{
		namespace Communications
		{
			namespace Midi
			{
				namespace Uart
				{
					class MidiPort;
				}
				
				class Port
				{
					private:

						void* _PortPointer;
						PortType _PortType;

					public:

						Port();


						#if defined (MCC_UART_MIDI_ENABLED)
							Port(const Uart::MidiPort& Parent);
						#endif
						

						///////////////////////////////////////////////////////////////////////
	                    // High Level API

							void LinkToPort(const Uart::MidiPort& Parent);
							void UnlinkFromPort();

							const PortType& ParentType() const;
							const void* ParentPointer() const;
						//
						///////////////////////////////////////////////////////////////////////
						// Midi Port Generic API

							const CPString::string& Name() const;
							void SetName(const CPString::string& NewName);
						//
						///////////////////////////////////////////////////////////////////////
	                    // Midi In API

	                        void AppendCallback(void(*Callback)(CPVector::vector<uint8_t>&));
	                        void DetachCallback(void(*Callback)(CPVector::vector<uint8_t>&));

	                        void SetBufferSize(uint8_t size);

							void Service();
						//
						///////////////////////////////////////////////////////////////////////


				};

				extern CPVector::vector<Port> SystemPorts;

                bool BindPort(const Uart::MidiPort& PortPointer); 
                void ReleasePort(const Uart::MidiPort& PortPointer); 
                PortID GetSystemPortID(const Uart::MidiPort& Port);
			}
		}
	}

#endif//MCC_MIDI_PORT_H
