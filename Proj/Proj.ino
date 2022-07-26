#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

//Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo barrier;

int park[] = {0, 1, 2, 3, 4, 5};
int gateIn = 6;
int gateOut = 7;

int barrierPos = 90;
//bool isFree[6];
int Free;
String str,avl;
int cnt;

void setup()
{
  pinMode(park[1], INPUT);
  pinMode(park[2], INPUT);
  pinMode(park[3], INPUT);
  pinMode(park[4], INPUT);
  pinMode(park[5], INPUT);
  pinMode(gateIn, INPUT);
  pinMode(gateOut, INPUT);
  
  Serial.begin(9600);

  barrier.attach(9);
  barrier.write(barrierPos);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to MIST");
  lcd.setCursor(5, 1);
  lcd.print("Car Parking");
  delay (3000);

  //for(int id = 1; id<=5; id += 1)
  //{
  //  if (digitalRead (park[id]) == LOW) isFree[id] = false;
  //  else isFree[id] = true;
  //}

  cnt = 0;
}

void loop()
{
  avl = String(cnt);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vehicles Entered");
  lcd.setCursor(0, 1);
  lcd.print(avl);
  delay (2000);


  avl = "";
  if (digitalRead (gateOut) == LOW)
  {   
    Free = 0;
    for(int id = 1; id<=5; id += 1)
    {
      if ( digitalRead (park[id]) == HIGH )
      {
        avl = avl + String(id) + " " ;
        Free += 1;
      }
    }

    lcd.clear();
    str = "There are ";
    if (Free == 0) str = str + "no";
    else str = str + String(Free);
    lcd.setCursor(0, 0);
    lcd.print(str);
    lcd.setCursor(1, 1);
    lcd.print("slots available");
    delay (2000);
    
    if (Free == 0) delay (3000);
    else
    {
      lcd.clear();
      str = "Available slot";
      if (Free > 1) str = str + "s";
      lcd.setCursor(0, 0);
      lcd.print(str);
      lcd.setCursor(0, 1);
      lcd.print(avl);

      for(barrierPos; barrierPos>=0; barrierPos -= 1)
      {                                 
        barrier.write(barrierPos);              
        delay(20);
      }
  
      while (digitalRead (gateIn) == HIGH)
      {
        delay (5000);
        if(digitalRead (gateIn) == LOW)
        {
          cnt += 1;
          break;
        }
        if(digitalRead (gateOut) == HIGH) break;

      }
      lcd.clear();
          
      for(barrierPos; barrierPos<=90; barrierPos += 1)
      {                                 
        barrier.write(barrierPos);              
        delay(20);
      }
    }
  }

  if (digitalRead (gateIn) == LOW)
  { 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dhonnobaad!");
    lcd.setCursor(5, 1);
    lcd.print("Abar Ashben");
    delay (2000);
    
    for(barrierPos; barrierPos>=0; barrierPos -= 1)
    {                                 
      barrier.write(barrierPos);              
      delay(20);
    }

    while (digitalRead (gateOut) == HIGH)
    {
      delay (5000);
      if(digitalRead (gateIn) == HIGH) break;      
    }
    lcd.clear();
        
    for(barrierPos; barrierPos<=90; barrierPos += 1)
    {                                 
      barrier.write(barrierPos);              
      delay(20);
    }
  }
}
