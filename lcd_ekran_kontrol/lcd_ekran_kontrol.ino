#include<LiquidCrystal.h>

LiquidCrystal lcd(8, 7, 6, 5, 4, 3);


byte desen[8] = {B00000,
                 B01010,
                 B00100,
                 B01010,
                 B00000,
                 B10001,
                 B01110
                };

void setup()
{
  pinMode(A1,OUTPUT);
  analogWrite(A1,14);
  lcd.begin(16, 2);
  Serial.begin(9600);

  //lcd.command(B00111000);  // 8-bit, 2 satır, 5x7 karakter
  //lcd.command(B00001100);  // Ekran açık, imleç kapalı
}

void loop()
{
  Serial.println(A0);
  DesenCiz();
}

void DesenCiz()
{
  int i;
  byte desen1[8] = {B11111,
                    B11111,
                    B11111,
                    B11111,
                    B11111,
                    B11110,
                    B11100,
                    B11000
                   };
  byte desen2[8] = {B11111,
                    B11111,
                    B11111,
                    B11111,
                    B11111,
                    B01111,
                    B00111,
                    B00011
                   };
  byte desen3[8] = {B11000,
                    B11100,
                    B11110,
                    B11111,
                    B11111,
                    B11111,
                    B11111,
                    B11111
                   };
  byte desen4[8] = {B00011,
                    B00111,
                    B01111,
                    B11111,
                    B11111,
                    B11111,
                    B11111,
                    B11111
                   };
  lcd.createChar(1, desen1);
  lcd.createChar(2, desen2);
  lcd.createChar(3, desen3);
  lcd.createChar(4, desen4);

  while (1)
  {
    lcd.home();
    delay(1000);
    for (i = 0; i < 8; i++)
    {
      lcd.write(byte(1));
      lcd.write(byte(2));
    }
    lcd.setCursor(0, 1);
    delay(1000);
    for (i = 0; i < 8; i++)
    {
      lcd.write(byte(3));
      lcd.write(byte(4));
    }
  }
}

void KayanYazi(char*yazi)
{
  lcd.print(yazi);

  while (true)
  {
    lcd.scrollDisplayLeft();
    delay(125);
  }
}

void Bomba(int countdown = 5)
{
  while (countdown > 0)
  {
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print(countdown);
    lcd.display();
    delay(500);
    lcd.noDisplay();
    delay(500);
    countdown--;
  }
  lcd.display();
  lcd.home();
  lcd.setCursor(6, 0);
  lcd.print("BOM!");
  delay(5000);
}
