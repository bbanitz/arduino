#include "ESP8266_bb.h"
#define DEBUG true
 

void ESP8266_bb::begin(Stream *serial, Stream *serialDebug){
	this->serial = serial;
	this->serialDebug = serialDebug;
  this->serialDebug->println("INIT");
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
  this->serialDebug->println("FIN INIT");
}
							 
ESP8266_bb::ESP8266_bb(){
  
  //Serial.begin(115200);
  //printLog.begin(115200); // your esp's baud rate might be different
  
 }
void ESP8266_bb::sendDebug(String message) {
	this->serialDebug->println(message);
}

void ESP8266_bb::sendClient(int connectionId, String message) {
  String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=message.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(message,1000,DEBUG);
    	
}


void ESP8266_bb::closeClient(int id) {
	String closeCommand = "AT+CIPCLOSE="; 
    closeCommand+=String(id); // append connection id
    closeCommand+="\r\n";
     
    sendData(closeCommand,3000,DEBUG);
}

String ESP8266_bb::readData(int *connectionId){
  //this->serialDebug->println("debut");
  String response = "";
  if(this->serial->available()) // check if the esp is sending a message 
  {
    //delay(100);
    while(this->serial->available())
    {
      // The esp has data so display its output to the serial window 
      char c = this->serial->read(); // read the next character.
     
    } 
    
    if(this->serial->find("+IPD,"))
    {
     /*
	 delay(10);
     int connectionId = this->serial->read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
    */
    long int time = millis();
    while( (time+1000) > millis())
    {
      while(this->serial->available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = this->serial->read(); // read the next character.
        response+=c;
      }  
    }
	
	int Id = byte(response.charAt(0))-48;
	connectionId=&Id;
	 //this->serialDebug->println(connectionId); 
     if (DEBUG) this->serialDebug->println(" recu :"+response);
	 //*id=connectionId;
	 }
  }
  return response;
}
 
 
String ESP8266_bb::sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    this->serial->print(command); // send the read character to the Serial
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(this->serial->available())
      {
             
        char c = this->serial->read(); // read the next character.
        response+=c;
      }  
    }
    
    if(DEBUG)
    {
      this->serialDebug->println("command :"+command);
      this->serialDebug->println("response :"+response);
    }
    
    return response;
}
