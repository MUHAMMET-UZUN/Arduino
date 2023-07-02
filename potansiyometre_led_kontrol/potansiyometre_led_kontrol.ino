#define LED 3
#define POT A0

int potVal = 0;

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(POT,INPUT);

  Serial.begin(9600);
  Serial.println("BAŞLADI");
}

void loop() {
  potVal = analogRead(POT);
  Serial.print("POT VAL: ");
  potVal= map(potVal,0,680,0,255);
  Serial.println(potVal);
  analogWrite(LED,potVal);

}
