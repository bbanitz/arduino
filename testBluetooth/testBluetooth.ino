int led=13;
void setup()
{
  
  Serial.begin(9600);
  Serial.setTimeout(100);
  pinMode(led,OUTPUT);
  pinMode(12,OUTPUT);
  
}

void loop() {
  char value[3];
  char c=Serial.read();
  if (c=='h') Serial.println("Hello");
  if (c=='0') digitalWrite(led,LOW);
  if (c=='1') digitalWrite(led,HIGH);
  if (c==0) {
    if (Serial.readBytes(value,3)==3) {
      //int intValue=(value[0]-48)*100+(value[1]-48)*10+value[2]-48;
      analogWrite(11,atoi(value));     
    }
  }
  float temperature=(5.0 * analogRead(1) * 100.0) / 1024;
  //String tempStr=floatToString(temperature);
  
  Serial.print(temperature);
  Serial.write(10);
}
