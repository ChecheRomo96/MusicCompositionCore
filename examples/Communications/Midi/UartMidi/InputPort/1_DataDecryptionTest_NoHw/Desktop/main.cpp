#include <MCC.h>
#include <math.h>

CPVector::vector<uint8_t> MessageQueue; // FIFO pile used to simulate incoming data

uint8_t Available()
{
    return MessageQueue.size();
}

uint8_t Read()
{
    if(Available())
    {
        uint8_t Data = MessageQueue[0];
        MessageQueue.erase((uint8_t)0);
        return Data;
    }
    return  0;;
}

void Callback(CPVector::vector<uint8_t>& message)
{
    MCC_MusicalScale::Scale myScale;

    std::cout<<(uint)message[0]<<" - ";

    switch (message[0]&0xF0) 
    {
        case MCC_MidiCore::Protocol::ChannelVoice::NoteOff:
            std::cout<<"Note Off - "<<myScale.Note(message[1]).Name()<<" - ";
            break;

        case MCC_MidiCore::Protocol::ChannelVoice::NoteOn:
            std::cout<<"Note On - "<<myScale.Note(message[1]).Name()<<" - ";
            break;

        case MCC_MidiCore::Protocol::ChannelVoice::ControlChange:
            std::cout<<"Control Change ";
            break;

        case MCC_MidiCore::Protocol::ChannelVoice::ChannelPressure:
            std::cout<<"Channel Pressure ";
            break;

        case MCC_MidiCore::Protocol::ChannelVoice::PitchBend:
            std::cout<<"Pitch Bend ";
            break;

        case MCC_MidiCore::Protocol::ChannelVoice::AfterTouch:
            std::cout<<"After Touch ";
            break;

        case 0xF0: // System Messages
            switch(message[0])
            {
                case MCC_MidiCore::Protocol::System::RealTime::TimingTick:
                    std::cout<<"Timing Tick ";
                    break;

                case MCC_MidiCore::Protocol::System::RealTime::Start:
                    std::cout<<"Start Song ";
                    break;

                case MCC_MidiCore::Protocol::System::RealTime::Stop:
                    std::cout<<"Stop Song ";
                    break;

                case MCC_MidiCore::Protocol::System::RealTime::Continue:
                    std::cout<<"Continue Song ";
                    break;

                case MCC_MidiCore::Protocol::System::Common::SongPositionPointer:
                    std::cout<<"Song Position Pointer ->  ";// <<((uint)message[1]<<8)|(uint)message[2]<<" ";
                    break;

                case MCC_MidiCore::Protocol::System::Common::MTC_QuarterFrame:
                    std::cout<<"MTC Quarte Frame ";
                    break;

                case MCC_MidiCore::Protocol::System::Common::SongSelect:
                    std::cout<<"Song Select ";
                    break;
                    
                case MCC_MidiCore::Protocol::System::RealTime::ActiveSensing:
                    std::cout<<"Active Sensing ";
                    break;
            }
            break;
    }
    std::cout<<"Message Recieved.\n";
}

int main()
{
	MCC::Start();

    MessageQueue.resize(6);

    MessageQueue[0] = MCC_MidiCore::Protocol::ChannelVoice::NoteOn;
    MessageQueue[1] = 0x45;
    MessageQueue[2] = 0x40;

    MessageQueue[3] = MCC_MidiCore::Protocol::ChannelVoice::NoteOff;
    MessageQueue[4] = 0x45;
    MessageQueue[5] = 0x00;

    MCC_Communications::Midi::Uart::InputPort MidiIn(Available,Read);
    MidiIn.AppendCallback(Callback);
    
    MidiIn.Initialize();
    MidiIn.SetBaudRate(MCC_Communications::Midi::Uart::SpecBaudRate);
    
    if(MidiIn.EnablePort())
    {
        std::cout<<"Port succesfully binded to system ports."<<std::endl;
    }
    else
    {
        std::cout<<"Error, Could not bind to system ports."<<std::endl;
        return 1;
    }
    
    auto UartPortID = MidiIn.UartMidiPortID();
    
    if(UartPortID != MCC_Communications::Midi::Uart::InvalidPortID)
    {
        MCC_Communications::Midi::Uart::SystemPorts[UartPortID].Service();
    }
    
    
    MessageQueue.resize(6);

    MessageQueue[0] = MCC_MidiCore::Protocol::ChannelVoice::NoteOn;
    MessageQueue[1] = 0x45;
    MessageQueue[2] = 0x40;

    MessageQueue[3] = MCC_MidiCore::Protocol::ChannelVoice::NoteOff;
    MessageQueue[4] = 0x45;
    MessageQueue[5] = 0x00;
    
    auto MidiPortID = MidiIn.MidiPortID();
    
    if(MidiPortID != MCC_Communications::Midi::InvalidID)
    {
        MCC_Communications::Midi::SystemPorts[MidiPortID].Service();
    }
    

    return 0;
}

