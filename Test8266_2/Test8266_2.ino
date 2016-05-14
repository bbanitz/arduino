#include <SoftwareSerial.h>
 
#define DEBUG true
 
SoftwareSerial printLog(10,11); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3
void setup()
{
  Serial.begin(115200);
  printLog.begin(115200); // your esp's baud rate might be different
  
 
  
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}
 
void loop()
{
  if(Serial.available()) // check if the esp is sending a message 
  {
    
    while(Serial.available())
    {
      // The esp has data so display its output to the serial window 
      char c = Serial.read(); // read the next character.
      printLog.write(c);
    } 
    
    if(Serial.find("+IPD,"))
    {
     //delay(1000);
 
     int connectionId = Serial.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
    String response = "";
    long int time = millis();
    while( (time+1000) > millis())
    {
      while(Serial.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = Serial.read(); // read the next character.
        response+=c;
      }  
    }
     printLog.println("recu :"+response);
     String webpage = "<h1>Hello</h1><h2>World!</h2><button>LED1</button>";
 
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
     
     webpage="<button>LED2</button>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
 
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,3000,DEBUG);
    }
  }
}
 
 
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    Serial.print(command); // send the read character to the Serial
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(Serial.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = Serial.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(DEBUG)
    {
      printLog.println(command);
      printLog.println(response);
    }
    
    return response;
}
