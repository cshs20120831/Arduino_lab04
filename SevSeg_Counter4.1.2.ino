#include "SevSeg.h"
SevSeg sevseg;
float Analogin;
void setup() 
{
  byte numDigits = 4;
  byte digitPins[] = {7,3,4,8};
  byte segmentPins[] = {6,5,10,12,13,2,9,11};
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default. Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins,segmentPins);
  sevseg.setBrightness(90);
}

void loop() 
{
  static unsigned long timer = millis();
  static int minute=59;
  static int hour=23;
  static int Pin10;
  Pin10 = digitalRead (A0); // Reset
  
  if(millis()>=timer)
  {
    if (minute == 60) 
    { 
      if( ++minute>=60)
      {
      minute=0;
      if( ++ hour >=24)
        hour=0;
      }
    } // overflow
    
    if (Pin10 == LOW) 
     {
      minute = 0;
      hour = 0;
     }    
    timer +=100;
   
     sevseg.setNumber(hour * 100 + minute, 4);
   }
 
  for(int i=0;i<10;i++)
      sevseg.refreshDisplay();

}
