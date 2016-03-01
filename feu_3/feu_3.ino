#include <LCD4Bit_mod.h> 
//create object to control an LCD.  
//number of lines in display=1
LCD4Bit_mod lcd = LCD4Bit_mod(2); 
int rouge=0;
int jaune=1;
int vert=2;

int feu1=1;
int feu2=11;
char *texteCouleur[3];


void setup() {
  texteCouleur[0]="rouge ";
  texteCouleur[1]="orange";
  texteCouleur[2]="vert  ";
  // Toutes les sortie en output, feux eteints:
  initFeu(feu1);
  initFeu(feu2);
  lcd.init();
  //optionally, now set up our application-specific display settings, overriding whatever the lcd did in lcd.init()
  //lcd.commandWrite(0x0F);//cursor on, display on, blink on.  (nasty!)
   lcd.clear();
  lcd.printIn("Feu 1 : rouge");
  lcd.cursorTo(2, 0);
  lcd.printIn("Feu 2 : rouge");
  allume(feu1,rouge);
  allume(feu2,rouge);
  delay(1000);
 
}

void initFeu(int feu) {
  for (int i=0;i<3;i++) {
    pinMode(feu+i,OUTPUT);
  }  
}  

void allume(int feu,int couleur) {
  if (feu==feu1) lcd.cursorTo(1,8); else lcd.cursorTo(2,8);
  lcd.printIn(texteCouleur[couleur]);
   for (int i=0;i<3;i++) {
     if (i==couleur) digitalWrite(feu+i,LOW);
     else digitalWrite(feu+i,HIGH);
     //digitalWrite(feu+i,i==couleur?LOW:HIGH);
     
   } 
}  

void loop() {
  // put your main code here, to run repeatedly:
  //allume(feu1,rouge);
  
  allume(feu2,vert);
  delay(5000);
  allume(feu2,jaune);
  delay(5000);
  allume(feu2,rouge);
  delay(5000);
  allume(feu1,vert);
  delay(5000);
  allume(feu1,jaune);
  delay(5000);
  allume(feu1,rouge);
  delay(5000);
  
}
