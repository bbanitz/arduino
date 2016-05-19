/*
 ceci est un programe permetent la 
 crÃ©ation d'un serveur local
 initialement crÃ©Ã©
 le 18 dec 2009 par  David A. Mellis
 modifiÃ© une premiÃ¨re fois le 9 Avr 2012
 par Tom Igoe
 puis une seconde fois en fev 2016
 par Bernard Banitz dans le cadre d'un
 projet sur le telegraphe de chapes
 traduit et expliquÃ© en franÃ§ais le 23 fev 2016
 par FranÃ§ois Banitz
 la possibilitÃ© de controller des servomoteurs
 Ã  Ã©tÃ© ajoutÃ©
 */
//inclus les bibliotheques Ethernet, SPI et servo
#include <SPI.h>

#include <Servo.h>
#include <ESP8266_bb.h>
#include<SoftwareSerial.h>

ESP8266_bb wifi;
SoftwareSerial mySerial(7, 8);

int x = 1;
int y = 1;
// crÃ©Ã© l'SSID du serveur:
char ssid[] = "telegraphe (pas d'internet)";

// crÃ©Ã© l'objet "servomoteur"
Servo servoreg;
Servo servohaut;
Servo servobas;
//crÃ©e un tableau de raport caractÃ¨re/angles
String angles [38][4] = 
{{"A","135","180","90"},
{"B","112.5","157.5","112.5"},
{"C","90","135","45"},
{"D","67.5","112.5","22.5"},
{"E","135","90","180"},
{"F","112.5","67.5","157.5"},
{"G","90","45","135"},
{"H","67.5","22.5","112.5"},
{"I","135","90","90"},
{"J","135","90","90"},
{"K","112.5","67","112.5"},
{"L","90","45","45"},
{"M","67.5","157.5","22.5"},
{"N","45","90","90"},
{"O","112.5","157.5","112.5"},
{"P","90","135","135"},
{"Q","67.5","112.5","112.5"},
{"R","45","45","90"},
{"S","45","135","45"},
{"T","90","135","90"},
{"U","67.5","112.5","67.5"},
{"V","45","90","45"},
{"W","112.5","112.5","157.5"},
{"X","90","90","135"},
{"Y","67.5","67.5","22.5"},
{"Z","135","135","90"},
{"0","112.5","112.5","67.5"},
{"1","90","90","45"},
{"2","67.5","67.5","22.5"},
{"3","135","90","45"},
{"4","112.5","67.5","112.5"},
{"5","90","45","90"},
{"6","67.5","22.5","67.5"},
{"7","135","135","135"},
{"8","112.5","112.5","112.5"},
{"9","90","180","90"},
{" ","135","45","45"},
{".","90","90","90"}};

String webpage = "<html><body><h1><p align='center' style='font-size:2em'>Le Telegraphe Chappe</p></h1><br><br><form>    Message: <input id='id1' name='code'>&nbsp;<button> Go</button></form></body></html>";

void setup() {
  // met les servomoteur  au pin 9 10 et 11
   servoreg.attach(9);
   servohaut.attach(10);
   servobas.attach(11);
   Serial.begin(115200);
   mySerial.begin(115200);
   wifi.begin(&Serial,&mySerial);
}


void loop() {
  // regarde si un client se connecte
  int *connectionId;
  String reponse=wifi.readData(connectionId);
  if (reponse!="") {
    int connectionId = byte(reponse.charAt(0))-48;
    wifi.sendDebug("Id:"+String(connectionId));
    wifi.sendClient(connectionId,webpage);
    
    String message=getCode(reponse);
    if (message!="") {
      wifi.sendDebug(message);
      afficheMessage(message);
       wifi.sendClient(connectionId,"envoi message:"+message);
    }
    wifi.closeClient(connectionId);
    
  }
}
  
void afficheMessage(String code) {
      for(int x=1; x<= code.length();x++){
        for(int y=1;y <= 38;y++){
          if (code.substring(x-1,x) == angles[y][0]) {
            servoreg.write(angles[y][1].toInt());
            servohaut.write(angles[y][2].toInt());
            servobas.write(angles[y][3].toInt());
            delay(1000);
            break;
          }
        }  
      }
}


// recuperte le code de type String
  String getCode(String st) {
    //Serial.println("receive : "+st);
    int debut;
    debut=st.indexOf("GET /?code=");
    if (debut>=0) {
      debut+=11;
      int fin=st.indexOf(" HTTP/1.1");
      return st.substring(debut,fin);
      
    }  
        
   }
