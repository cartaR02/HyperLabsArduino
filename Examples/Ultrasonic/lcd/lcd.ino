//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <HCSR04.h>

#define TRIG 9
#define ECHO 8

#define MIN_CM 0
#define MAX_CM 15

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
UltraSonicDistanceSensor distanceSensor(TRIG, ECHO);

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
}


void loop()
{
  int cm = distanceSensor.measureDistanceCm();
  if (cm < MIN_CM || cm > MAX_CM) return;
  int xPos = map(cm, MIN_CM, MAX_CM, 0, 9);
  lcd.setCursor(xPos, 0);
  lcd.print(".");
  delay(150);
  lcd.clear();
}
