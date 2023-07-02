#define  SARI_LED 12
#define KIRMIZI_LED 2
#define BUTON 13

void setup() {
  // put your setup code here, to run once:
  pinMode(SARI_LED, OUTPUT);
  pinMode(KIRMIZI_LED, OUTPUT);
  pinMode(BUTON, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(SARI_LED, digitalRead(BUTON));
}
