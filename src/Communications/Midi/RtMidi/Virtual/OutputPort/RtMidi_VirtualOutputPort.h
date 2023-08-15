#ifndef MCC_RT_MIDI_VIRTUAL_OUT_PORT_H
#define MCC_RT_MIDI_VIRTUAL_OUT_PORT_H
	
    #include <MCC_BuildSettings.h>
    #include <RtMidi.h>
    #include <CPString.h>
    #include <Core/MidiCore/MidiCore.h>

    namespace MusicCompositionCore::Communications::Midi::RtMidi::Virtual
    {
        class OutputPort;
    }


    #include "../RtMidi_Virtual.h"

	namespace MusicCompositionCore::Communications::Midi::RtMidi::Virtual
    {
        class OutputPort
        {
            private:        
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // RtMidi API

                    RtMidiOut* _OutPort;
                    bool _PortStatus;
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                // Port Name

                    CPString::string _PortName;
                //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                

            public:

                ///////////////////////////////////////////////////////////////////////
                // Constructors and Destructor

                    OutputPort();
                    ~OutputPort();
                    OutputPort(const CPString::string& PortName);
                    OutputPort(const CPString::string& PortName, CPString::string& ClientName);
                //
                ///////////////////////////////////////////////////////////////////////
                // Midi Port Generic API

                    const CPString::string& Name() const;
                    void SetName(const CPString::string& NewName);
                //
                ///////////////////////////////////////////////////////////////////////
                // RtMidi API

                    const bool PortStatus() const;
                    void OpenPort();
                    void ClosePort();
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
                // RtMidi Port API

                    //bool RtMidi_BindPort() const;
                    //void RtMidi_UnbindPort() const;
                    //RtMidi::SystemPortHandler::PortID RtMidi_PortID() const;
                    //RtMidi::Port& RtMidi_Port() const;
                //
                ///////////////////////////////////////////////////////////////////////
                // Midi Port API

                    //bool Midi_BindPort() const;
                    //void Midi_UnbindPort() const;
                    //Midi::SystemPortHandler::PortID Midi_PortID() const;
                    //Midi::Port& Midi_Port() const;
                //
                ///////////////////////////////////////////////////////////////////////
        };
    }

#endif//MCC_RT_MIDI_VIRTUAL_OUT_PORT_H