#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

//Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo barrier;
int barrierPos = 90;

void setup()
{
  pinMode(13,OUTPUT);
  pinMode(2,INPUT);
  Serial.begin(9600);

  barrier.attach(9);
  barrier.write(barrierPos);
}
void loop()
{
  if (digitalRead(2)== LOW)
  {
    lcd.setCursor(1, 1);
    lcd.print("slots available");
    delay (2000);
  }
  else 
  {
    lcd.setCursor(1, 1);
    lcd.print("slots not available");
    delay (2000);
  }
}
