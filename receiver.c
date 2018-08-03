#include <VirtualWire.h>
const int ledPin = 9;
const int datain = 12;
const int stepPin = 3; 
const int dirPin = 4; 
 
void setup()
{
   // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
    vw_set_ptt_inverted(true);
    vw_set_rx_pin(datain);
    vw_setup(2000);
    pinMode(ledPin, OUTPUT);
    vw_rx_start();
}
    void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN; 
 
    if (vw_get_message(buf, &buflen))
    {
      if(buf[0]=='1')
      {  
       digitalWrite(ledPin,HIGH);
       digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 200; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(5000); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(5000);}

       
      }  
      if(buf[0]=='0')
      {
       digitalWrite(ledPin,LOW);
      }
    }
}
