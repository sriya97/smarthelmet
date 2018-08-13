import processing.net.*;

import processing.serial.*;
import http.requests.*;


Serial myPort;  // Create object from Serial class
String val;      // Data received from the serial port

void setup() 
{
  frameRate(1);

  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);
}

void draw()
{
  if ( myPort.available() > 0) {  // If data is available,
    val = myPort.readStringUntil('\n');         // read it and store it in val
  }
  
  println(val);
  
  if(val!=null){
    println("Accident detected");
    GetRequest get = new GetRequest("http://localhost:8080/accident");
    get.send();
    println("Reponse Content: " + get.getContent());
    noLoop();
  }
  else{
    println("No accident");
  }  
 

}
