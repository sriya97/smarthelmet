include <VirtualWire.h>
const int ledPin = 7;

const int gasInt = A0; // GAS sensor output pin 
int vibr_Pin = 3;

char *data;

#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);


void setup() {
  pinMode(ledPin,OUTPUT);

  pinMode(vibr_Pin, INPUT);

  pinMode(gasInt, INPUT); // Setting the gas sensor input
  
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(12);
  vw_setup(2000);
 mySerial.begin(9600);
  Serial.begin(9600);// put your setup code here, to run once:

}


void loop() {
  alcohol();
  accident();

}

void alcohol()
{

  Serial.println(analogRead(A0));
  if (analogRead(A0) < 600){
    
    data="1";

    digitalWrite(ledPin,HIGH);
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
   
  }

  else{

    data="0";

    digitalWrite(ledPin,LOW);
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
   
  }
}

void accident()
{
  long measurement =TP_init();
  delay(50);
 // Serial.print("measurment = ");
  Serial.println(measurement);
  if (measurement > 1000){
    SendMessage();
  }
  else{
    Serial.println(measurement); 
  }
}

long TP_init(){
  delay(10);
  long measurement=pulseIn (vibr_Pin, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}

void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919265196069\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
