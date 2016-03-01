#include <ArduinoJson.h>
#include <OneWire.h>
#include <Ethernet.h>
#include <SPI.h>

int DS18S20_Pin = 7; //DS18S20 Signal pin on digital 2

//Temperature chip i/o
OneWire ds(DS18S20_Pin);  // on digital pin 2

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  server.begin();
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.println(c);
        if ( c== '\r') {
          Serial.println(commandEthernet);
          client.println(commandEthernet);
          if (commandSerial=="temp") readTemp();
           commandEthernet="";
        }
        else {
         commandEthernet+=c;
        }
      }
    }
  }     
    
  // if there's any serial available, read it:
  while (Serial.available() > 0) {
    char c=Serial.read();
    if ( c== '\r') {
      Serial.println(commandSerial);
      if (commandSerial=="temp") readTemp();
      commandSerial="";
    }
    else {
      commandSerial+=c;
    }
  }
}  

void readTemp() {
  // put your main code here, to run repeatedly:
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  for (int i=1;i<3;i++) {
    root["sensor"] = String("temperature "+String(i));
    root["value"] = getTemp();
    JsonArray& data = root.createNestedArray("data");
    data.add(getTemp(), 2);  // 6 is the number of decimals to print
    root.printTo(Serial);
    Serial.println();
  }  
}


float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      Serial.println("device not found");
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
  
}
