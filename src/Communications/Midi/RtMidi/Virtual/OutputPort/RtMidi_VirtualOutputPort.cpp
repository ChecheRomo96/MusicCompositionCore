#include "RtMidi_VirtualOutputPort.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Out Port

    MusicCompositionCore::Communications::Midi::RtMidi::Virtual::OutputPort::OutputPort()
    {
        _OutPort = NULL;
    }

    MusicCompositionCore::Communications::Midi::RtMidi::Virtual::OutputPort::~OutputPort()
    {
        //MusicCompositionCore::Communications::Midi::RtMidi::SystemPorts.erase(RtMidiPortArrayID()); 
    }

    MusicCompositionCore::Communications::Midi::RtMidi::Virtual::OutputPort::OutputPort(const CPString::string& PortName)
    {
        _PortStatus = 0;
        _OutPort = NULL;
        _OutPort = new RtMidiOut();
        SetName(PortName);
        //MusicCompositionCore::Communications::Midi::RtMidi::SystemPorts.push_back(MusicCompositionCore::Communications::Midi::RtMidi::RtMidiPort(this));
    }

    MusicCompositionCore::Communications::Midi::RtMidi::Virtual::OutputPort::OutputPort(const CPString::string& PortName, CPString::string& ClientName)
    {
        _PortStatus = 0;
        _OutPort = NULL;
        _OutPort = new RtMidiOut(::RtMidi::Api::UNSPECIFIED,ClientName);
        SetName(PortName);
        //MusicCompositionCore::Communications::Midi::RtMidi::SystemPorts.push_back(MusicCompositionCore::Communications::Midi::RtMidi::RtMidiPort(this));
    }

    const CPString::string& MusicCompositionCore::Communications::Midi::RtMidi::Virtual::OutputPort::Name() const
    {
        return _PortName.c_str();
    }

    const bool MusicCompositionCore::Communications::Midi::RtMidi::Virtual::OutputPort::PortStatus() const
    {
        return _PortStatus;
    }

    void MusicCompositionCore::Communications::Midi::RtMidi::Virtual::OutputPort::SetName(const CPString::string& PortName)
    {
        if(PortName == _PortName){return;}
        
        bool OpenPortFlag = 0;
        if(PortStatus())
        {
            ClosePort();
            OpenPortFlag = 1;
        }
        
        _PortName = PortName;
        
        uint8_t count = 0;
        
        bool flag = 1;
        while(flag)
        {
            flag = 0;
            for (uint i = 0; i < RtMidi::GetInputPortsAvaialble(); i++)
            {
                if(RtMidi::GetInputPortName(i) == _PortName)
                {
                    if(count == 0)
                    {
                        _PortName += "   ";
                        count++;
                        CPString::string str2(count++,10);
                        _PortName[_PortName.length()-2] = str2[0];
                        _PortName[_PortName.length()-1] = str2[1];
                        flag = 1;

                    }
                    else
                    {
                        CPString::string str2(count,10);

                        if(count < 10)
                        {
                            _PortName[_PortName.length()-2] = str2[0];
                        }
                        else if(count == 10)
                        {
                            _PortName += " ";
                            _PortName[_PortName.length()-3] = str2[0];
                            _PortName[_PortName.length()-2] = str2[1];
                            _PortName[_PortName.length()-2] = str2[2];
                        }
                        else if(count < 100)
                        {
                            _PortName[_PortName.length()-3] = str2[0];
                            _PortName[_PortName.length()-2] = str2[1];
                        }

                        count++;
                        flag = 1;
                    }
                }
            }
        }
        if(OpenPortFlag){OpenPort();}
    }

    void MusicCompositionCore::Communications::Midi::RtMidi::Virtual::OutputPort::OpenPort()
    {
        if(PortStatus())
        {
            ClosePort();
        }
        
        _OutPort->openVirtualPort(_PortName);
        _PortStatus = 1;
        
    }

    void MusicCompositionCore::Communications::Midi::RtMidi::Virtual::OutputPort::ClosePort()
    {
        _OutPort -> closePort();
        _PortStatus = 0;
    }

    void MusicCompositionCore::Communications::Midi::RtMidi::Virtual::OutputPort::Write(uint8_t data)
    {
        _OutPort -> sendMessage(&data, 1);
    }

    void MusicCompositionCore::Communications::Midi::RtMidi::Virtual::OutputPort::WriteMessage(uint8_t* data, uint8_t len)
    {
        _OutPort -> sendMessage(data,len);
    }

    void MusicCompositionCore::Communications::Midi::RtMidi::Virtual::OutputPort::WriteMessage(const CPVector::vector<uint8_t>& Data)
    {
        _OutPort -> sendMessage(&Data[0], Data.size());
    }

    #if defined (MCC_MIDI_MESSAGE_ENABLED)
        void MusicCompositionCore::Communications::Midi::RtMidi::Virtual::OutputPort::WriteMessage(const MCC_MidiCore::MidiMessage& Data)
        {
            _OutPort->sendMessage(&Data.Buffer()[0], Data.Buffer().size());
        }
    #endif

//
////////////////////////////////////////////////////////////////////////////////////////////////////
