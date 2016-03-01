
int rouge=0;
int jaune=1;
int vert=2;
int feu1=1;
int feu2=11;

void setup() {
  // Toutes les sortie en output, feux eteints:
  initFeu(feu1);
  initFeu(feu2);
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
   for (int i=0;i<3;i++) {
 //    if (i==couleur) digitalWrite(feu+i,LOW);
  //   else digitalWrite(feu+i,HIGH);
     digitalWrite(feu+i,i==couleur?LOW:HIGH);
   } 
}  

void loop() {
  // put your main code here, to run repeatedly:
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
