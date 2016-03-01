#include <ArduinoJson.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Ethernet.h>
#include <SPI.h>



/*-----( Declare Constants )-----*/
#define ONE_WIRE_BUS 7 /*-(Connect to Pin 7 )-*/

/*-----( Declare objects )-----*/
/* Set up a oneWire instance to communicate with any OneWire device*/
OneWire ourWire(ONE_WIRE_BUS);
DallasTemperature sensors(&ourWire);

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

String commandSerial,commandEthernet;
EthernetClient client;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  sensors.begin();
  server.begin();
}

void loop() {
  client = server.available();
  if (client) {
    //Serial.println("new client");
    if (client.connected()) {
      if (client.available()) {
        char c = client.read();
        //Serial.println(c);
        if ( c== '\r') {
          Serial.println(commandEthernet);
          client.println(commandEthernet);
          if (getCommand(commandEthernet)=="/temp") {
            
            readTemp(false);
          }
          commandEthernet="";
          client.stop();
        }
        else {
         commandEthernet+=c;
        }
      }
    }
  }     
    
  // if there's any serial available, read it:
  if (Serial.available() > 0) {
    char c=Serial.read();
    if ( c== '\r') {
      Serial.println(commandSerial);
      if (commandSerial=="temp") readTemp(true);
      commandSerial="";
    }
    else {
      commandSerial+=c;
    }
  }
}  

void readTemp(boolean serial) {
  // put your main code here, to run repeatedly:
  Serial.println("ok");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  sensors.requestTemperatures();
  for (int i=0;i<4;i++) {
    root["sensor"] = String("temperature "+String(i));
    root["value"] = sensors.getTempCByIndex(i);
    if (serial) {
      root.printTo(Serial);
      Serial.println();
    } 
    else {
      root.printTo(client);
      client.println(); 
    }
  }  
}


String getCommand(String line) {
  if (line.startsWith("GET ")) {
    int index=line.indexOf(" HTTP/1.1");
    String command=line.substring(4,index);
    Serial.println(command);
    return command;
  }
  return "";
}

