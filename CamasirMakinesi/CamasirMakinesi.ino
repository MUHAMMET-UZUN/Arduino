#include<LiquidCrystal.h>
#define YELLOW_LED 12
#define RED_LED 2
#define LED 3
#define POT A0
#define BUTON 13

LiquidCrystal lcd(8, 7, 6, 5, 4, 3);
int potVal = 0;
int mod = 0;
int temperature = 40;
int tempMod;
int countdown = 3;

void setup() {
  tempMod = mod;

  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(POT, INPUT);

  lcd.begin(16, 2);

  //Serial.begin(9600);

}

void loop() {

  lcd.clear();
  lcd.home();
  lcd.print("Mode Select:");

  delay(2000);
  AvailableFeedback();

  while (!digitalRead(BUTON)) {
    potVal = analogRead(POT);
    potVal = map(potVal, 0, 1023, 0, 255);
    lcd.setCursor(0, 1);
    if (potVal < 85) {
      mod = 0;
      ClearAndGoRow2();
      lcd.print("Sentetic");
    }
    else if (potVal < 170) {
      mod = 1;
      ClearAndGoRow2();
      lcd.print("Cotton");
    }
    else if (potVal < 255) {
      mod = 2;
      ClearAndGoRow2();
      lcd.print("Sensitive");
    }
  }

  lcd.clear();
  lcd.home();
  lcd.print("Temperature:");
  delay(500);

  while (!digitalRead(BUTON)) {
    potVal = analogRead(POT);
    potVal = map(potVal, 0, 1023, 0, 255);
    lcd.setCursor(0, 1);
    if (potVal < 85) {
      temperature = 30;
      ClearAndGoRow2();
      lcd.print("30 Degree");
    }
    else if (potVal < 175) {
      temperature = 40;
      ClearAndGoRow2();
      lcd.print("40 Degree");
    }
    else if (potVal < 255) {
      temperature = 60;
      ClearAndGoRow2();
      lcd.print("60 Degree");
    }
  }



  switch (mod)
  {
    case 0:
      SenteticProgram();
      break;
    case 1:
      CottonProgram();
      break;
    case 2:
      SensitiveProgram();
      break;
    default:
      lcd.clear();
      lcd.print("MODE ERROR!");
      delay(3000);
      break;
  }


}


void SenteticProgram()
{
  int i;
  int washTime = 20;
  BusyFeedback();
  delay(1000);

  while (washTime > 0)
  {
    for (i = 0; i < 4; i++)
    {
      countdown = 3;
      if (ButtonCheck()) ChangeProsess();
      if (mod == -1) break;
      lcd.clear();
      lcd.home();
      lcd.print("Sentetic Wash");
      lcd.setCursor(i, 1);
      lcd.print(".");
      lcd.setCursor(5, 1);
      lcd.print(washTime);
      lcd.setCursor(9, 1);
      lcd.print("Temp:");
      lcd.print(temperature);
      delay(1000);
      washTime--;
    }
    if (mod == -1) break;
  }
  if (mod != -1)
    DoneProgress();
  else
    CancelProgress();
}

void CottonProgram()
{
  int i;
  int washTime = 20;
  BusyFeedback();
  delay(1000);

  while (washTime > 0)
  {
    for (i = 0; i < 4; i++)
    {
      countdown = 3;
      if (ButtonCheck()) ChangeProsess();
      if (mod == -1) break;
      lcd.clear();
      lcd.home();
      lcd.print("Cotton Wash");
      lcd.setCursor(i, 1);
      lcd.print(".");
      lcd.setCursor(5, 1);
      lcd.print(washTime);
      lcd.setCursor(9, 1);
      lcd.print("Temp:");
      lcd.print(temperature);
      delay(1000);
      washTime--;
    }
    if (mod == -1) break;
  }
  if (mod != -1)
    DoneProgress();
  else
    CancelProgress();
}


void SensitiveProgram()
{
  int i;
  int washTime = 20;
  BusyFeedback();
  delay(1000);

  while (washTime > 0)
  {
    for (i = 0; i < 4; i++)
    {
      countdown = 3;
      if (ButtonCheck()) ChangeProsess();
      if (mod == -1) break;
      lcd.clear();
      lcd.home();
      lcd.print("Sensitive Wash");
      lcd.setCursor(i, 1);
      lcd.print(".");
      lcd.setCursor(5, 1);
      lcd.print(washTime);
      lcd.setCursor(9, 1);
      lcd.print("Temp:");
      lcd.print(temperature);
      delay(1000);
      washTime--;
    }
    if (mod == -1) break;
  }
  if (mod == -1)
    CancelProgress();
  else
    DoneProgress();
}


void CancelProgress()
{
  lcd.clear();
  lcd.home();
  lcd.setCursor(5, 0);
  lcd.print("WASH");
  lcd.setCursor(2, 1);
  lcd.print("CANCELED!");
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  delay(2000);
}

void ChangeProsess()
{
  while (ButtonCheck())
  {
    delay(100);
    lcd.clear();
    lcd.home();
    lcd.print(countdown);
    if (countdown <= 0)
    {
      mod = -1;
      break;
    }
    countdown--;
    delay(1000);
  }
}

bool ButtonCheck()
{
  return digitalRead(BUTON);
}
void BusyFeedback()
{
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, HIGH);
}
void AvailableFeedback()
{
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(RED_LED, LOW);
}
void InProgressFeedback()
{
  digitalWrite(RED_LED, HIGH);
  delay(500);
  digitalWrite(RED_LED, LOW);
  delay(500);
}
void DoneProgress()
{
  lcd.clear();
  lcd.home();
  lcd.setCursor(5, 0);
  lcd.print("WASH");
  lcd.setCursor(3, 1);
  lcd.print("COMPLETED!");
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  while (!ButtonCheck())
  {
    ChangingFeedback();
  }
}
void ChangingFeedback()
{
  digitalWrite(YELLOW_LED, HIGH);
  delay(500);
  digitalWrite(YELLOW_LED, LOW);
  delay(500);
}

void ClearAndGoRow2()
{
  if (tempMod != mod)
  {
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    tempMod = mod;
  }
}
