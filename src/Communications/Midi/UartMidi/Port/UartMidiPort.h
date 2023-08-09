#ifndef MCC_UART_MIDI_PORT_H
#define MCC_UART_MIDI_PORT_H

	#include <MCC_BuildSettings.h>
	#include <Core/MidiCore/MidiCore.h>

	#include <CPVector.h>

	#if defined (MCC_UART_PORT_ENABLED)
		#include <Communications/Uart/Uart.h>
	#endif

	#include "../../MCC_Midi.h"

	namespace MusicCompositionCore::Communications::Uart
	{
		class Port;
	}

	namespace MusicCompositionCore::Communications::Midi::UartMidi
    { 	
        class Port
        {
            private:

				
				///////////////////////////////////////////////////////////////////////
				// Uart Port Pointer

					Uart::Port* _PortPointer;
				//
				///////////////////////////////////////////////////////////////////////
				// Callback vector ( Called when a midi messqge has been recieved )

					CPVector::vector<void(*)(const CPVector::vector<uint8_t>&)> _CallbackVector;

				//
				///////////////////////////////////////////////////////////////////////
				// Midi Input Decoding buffer (Initializes to 3 bytes)

					CPVector::vector<uint8_t> _MessageBuffer;
					uint8_t _BufferIndex;
				//
				///////////////////////////////////////////////////////////////////////
				// BaudRate, Polling Mode, and flags
					
					uint8_t _FlagRegister;

					// bool _PollingMode  --> Bit 0
					// bool _SOMF         --> Bit 1
					// bool _SysExFlag    --> Bit 2
				//
				///////////////////////////////////////////////////////////////////////
             
            public:

				///////////////////////////////////////////////////////////////////////
            	// Constructors

                    Port();
                    Port(const Uart::Port& Parent);
				//
				///////////////////////////////////////////////////////////////////////
                // High Level API

					const Uart::PortType& ParentType() const;
					const Uart::Port* Uart_PortPointer() const;
				//
				///////////////////////////////////////////////////////////////////////
				// Midi Port Generic API

					const CPString::string& Name() const;
					void SetName(const CPString::string& NewName);

				//
				///////////////////////////////////////////////////////////////////////
                // Midi In API

                    void AppendCallback(void(*Callback)(const CPVector::vector<uint8_t>&));
                    void DetachCallback(void(*Callback)(const CPVector::vector<uint8_t>&));

                    void SetBufferSize(uint8_t size);

					void Service();
				//
				///////////////////////////////////////////////////////////////////////
				// Midi Out API

					void Write(uint8_t Data);
					void WriteMessage(uint8_t* Data, uint8_t Len);
					void WriteMessage(const CPVector::vector<uint8_t>& Message);

					#if defined (MCC_MIDI_MESSAGE_ENABLED)
						void WriteMessage(const MCC_MidiCore::MidiMessage& Data);
					#endif

                    //////////////////////////////////////////////////////////////////
                    // Channel Voice Messages

                        void NoteOff(uint8_t Note, uint8_t Velocity = 0, uint8_t Channel = 0);
                        void NoteOn(uint8_t Note, uint8_t Velocity, uint8_t Channel = 0);
                        void AfterTouch(uint8_t Note, uint8_t Value, uint8_t Channel = 0);
                        void ControlChange(uint8_t ControlNumber, uint8_t Value, uint8_t Channel = 0);
                        void ProgramChange(uint8_t Program, uint8_t Channel = 0);
                        void ChannelPressure(uint8_t Pressure, uint8_t Channel = 0);
                        void PitchBend(uint8_t BendValue, uint8_t Channel = 0);
                        void PitchBend(uint16_t BendValue, uint8_t Channel = 0);
                        void PitchBend(int8_t BendValue, uint8_t Channel = 0);
                        void PitchBend(int16_t BendValue, uint8_t Channel = 0);

                        //////////////////////////////////////////////////////////////
                        // MCC_MidiCore::MidiNote

                            #if defined (MCC_MIDI_NOTE_ENABLED)
                                void NoteOff(const MidiCore::MidiNote& Source);
                                void NoteOn(const MidiCore::MidiNote& Source);
                            #endif
                        //
                        //////////////////////////////////////////////////////////////
                        // Mcc_MusicalNote::Note

                            #if defined (MCC_MUSICAL_NOTE_ENABLED)
                                void NoteOn(const MCC_MusicalCore::MusicalNote::Note& Source, uint8_t Vel, uint8_t Channel = 0);
                                void NoteOff(const MCC_MusicalCore::MusicalNote::Note& Source, uint8_t Vel = 0, uint8_t Channel = 0);
                            #endif
                        //
                        //////////////////////////////////////////////////////////////
                        // Mcc_MusicalNote::Pitch

                            #if defined (MCC_MUSICAL_NOTE_ENABLED)
                                void NoteOn(const MCC_MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Vel, uint8_t Channel = 0);
                                void NoteOff(const MCC_MusicalCore::MusicalNote::Pitch& Source, uint8_t Octave, uint8_t Vel = 0, uint8_t Channel = 0);
                            #endif
                        //
                        //////////////////////////////////////////////////////////////
                    //
                    //////////////////////////////////////////////////////////////////
                    // Sysytem Common Messages

                        void MTC_QuarterFrame(uint8_t MTC_ID, uint8_t Data);
                        void SongPositionPointer(uint16_t Position);
                        void SongSelect(uint8_t SongID);
                        void TuningRequest();
                    //
                    //////////////////////////////////////////////////////////////////
                    // Sysytem Real Time Messages

                        void TimingTick();
                        void Start();
                        void Stop();
                        void Continue();
                        void ActiveSensing();
                        void SystemReset();
                    //
                    //////////////////////////////////////////////////////////////////
                    // System Exclusive Messages

                        void SystemExclusive(const CPVector::vector<uint8_t>& Data);
                        void SystemExclusive(uint8_t* Data, uint8_t Length);

                        //void SysteExclusive(uint8_t ManufacturerID , uint8_t* Data, uint8_t size);
                        //void SysteExclusive(uint8_t ManufacturerID , const CPVector::vector<uint8_t>& Data);
                        //void SysteExclusive(uint32_t ManufacturerID , uint8_t* Data, uint8_t size);
                        //void SysteExclusive(uint32_t ManufacturerID , const CPVector::vector<uint8_t>& Data);
                    //
                    //////////////////////////////////////////////////////////////////

				//
				///////////////////////////////////////////////////////////////////////
                // Midi Port API

                	bool Midi_BindPort() const;
                	void Midi_UnbindPort() const;
					Midi::SystemPortHandler::PortID Midi_PortID() const;
					Midi::Port& Midi_Port() const;
	            //
				///////////////////////////////////////////////////////////////////////
			
			private:

				//////////////////////////////////////////////////////////////////////
                // Uart Port Link Helpers
					#if defined(MCC_UART_PORT_ENABLED)
						void LinkToPort(const Uart::Port& Parent);
					#endif

					void UnlinkFromPort();
				//
				///////////////////////////////////////////////////////////////////////
				// Midi In Helpers

					void InvokeCallbacks();

					void SetSysExFlag(bool State);
					const bool SysExFlag() const;

					void SetSOMF(bool State);
					const bool SOMF() const;
				//
				///////////////////////////////////////////////////////////////////////
		};
    }

#endif//MCC_UART_MIDI_PORT_H