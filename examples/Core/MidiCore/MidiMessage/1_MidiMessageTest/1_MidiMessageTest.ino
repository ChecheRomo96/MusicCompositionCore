#include <MCC.h>

using namespace MCC_MidiCore;

MCC_MidiCore::MidiMessage myMessage;
void PrintBuffer()
{
    for( uint8_t i = 0; i < myMessage.Buffer().size() ; i++)
    {
      Serial.print(myMessage.Buffer()[i], HEX);
      if(i < myMessage.Buffer().size()-1){Serial.print(", ");}
      else{Serial.println(".");}
    }
}

void setup() {
    Serial.begin(115200);

    Serial.println("Channel Voice Messages: ");
      
      myMessage.NoteOff(12,0);
      Serial.print("  Note Off Message (Note:12, Channel: 0):                          ");
      PrintBuffer();
      
      myMessage.NoteOn(12,120,0);
      Serial.print("  Note On Message (Note:12, Vel:120, Channel: 0):                  ");
      PrintBuffer();
      
      myMessage.AfterTouch(12,120,0);
      Serial.print("  AfterTouch Message (Note:12, Pressure:120, Channel: 0):          ");
      PrintBuffer();
      
      myMessage.ControlChange(12,120,0);
      Serial.print("  ControlChange Message (Controller No:12, Value:120, Channel: 0): ");
      PrintBuffer();
      
      myMessage.ProgramChange(12,0);
      Serial.print("  ProgramChange Message (Program:12, Channel: 0):                  ");
      PrintBuffer();
      
      myMessage.ChannelPressure(12,0);
      Serial.print("  ChannelPressure Message (Pressure:12, Channel: 0):               ");
      PrintBuffer();
      
      myMessage.PitchBend(0,0);
      Serial.print("  PitchBend Message (Bend:0, Channel: 0):                          ");
      PrintBuffer();
      
      myMessage.PitchBend(127,0);
      Serial.print("  PitchBend Message (Bend:127, Channel: 0):                        ");
      PrintBuffer();
      
      myMessage.PitchBend(-127,0);
      Serial.print("  PitchBend Message (Bend:-127, Channel: 0):                       ");
      PrintBuffer();
      
      myMessage.PitchBend(2000,0);
      Serial.print("  PitchBend Message (Bend:2000, Channel: 0):                       ");
      PrintBuffer();
      
      myMessage.PitchBend(-2000,0);
      Serial.print("  PitchBend Message (Bend:-2000, Channel: 0):                      ");
      PrintBuffer();
      
    Serial.println();

    
    Serial.println("System Common Messages: ");
    
      myMessage.SongPositionPointer(0);
      Serial.print("  Song Position Pointer Message (Position: 0):      ");
      PrintBuffer();
      
      myMessage.SongPositionPointer(0xFF);
      Serial.print("  Song Position Pointer Message (Position: 0xFF):   ");
      PrintBuffer();
      
      myMessage.SongPositionPointer(0xAAFF);
      Serial.print("  Song Position Pointer Message (Position: 0xAAFF): ");
      PrintBuffer();
    
    Serial.println();

    
    Serial.println("System Real Time Messages: ");
    
      myMessage.ClockTick();
      Serial.print("  ClockTick Message: ");
      PrintBuffer();
      
      myMessage.Start();
      Serial.print("  Start Message:     ");
      PrintBuffer();
      
      myMessage.Continue();
      Serial.print("  Continue Message:  ");
      PrintBuffer();
      
      myMessage.Stop();
      Serial.print("  Stop Message:      ");
      PrintBuffer();
    
    Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:

}