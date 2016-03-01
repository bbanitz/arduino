int F1_R = 2;
int F1_J = 3;
int F1_V = 4;
int F2_R = 5;
int F2_J = 6;
int F2_V = 7;
void setup() {
pinMode(F1_R, OUTPUT);
pinMode(F1_J, OUTPUT);
pinMode(F1_V, OUTPUT);
pinMode(F2_R, OUTPUT);
pinMode(F2_J, OUTPUT);
pinMode(F2_V, OUTPUT);
digitalWrite(F1_R, HIGH);
digitalWrite(F1_J, HIGH);
digitalWrite(F1_V, HIGH);
digitalWrite(F2_R, HIGH);
digitalWrite(F2_J, HIGH);
digitalWrite(F2_V, HIGH);
}

void loop() {
digitalWrite(F1_J, HIGH);
digitalWrite(F1_V, HIGH);
digitalWrite(F2_R, HIGH);
digitalWrite(F1_R, LOW);
digitalWrite(F2_V, LOW);
delay(3000);
digitalWrite(F2_V, HIGH);
digitalWrite(F2_J, LOW);
delay(1000);
digitalWrite(F2_J, HIGH);
digitalWrite(F2_R, LOW);
digitalWrite(F1_R, HIGH);
digitalWrite(F1_V, LOW);
delay(3000);
digitalWrite(F1_V, HIGH);
digitalWrite(F1_J, LOW);
delay(1000);
}
