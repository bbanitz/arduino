int bouton=11;
int led=12;
void setup() { //setup (faire au début)
pinMode(led,OUTPUT);//mettre "led" en sortie
} //fin du setup
void loop() { //loop (recomencer à l'infini:)
    if (digitalRead(bouton)){ //si bouton pressé faire:
      tone(led,5); //commencer buzz
} //fin du "si"
else { //sinon faire:
    noTone(led); //arreter buzz
} //fin du "sinon"
} //fin du loop
