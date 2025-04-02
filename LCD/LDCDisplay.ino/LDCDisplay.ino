/*
Plug the wires from the lcd to the arduino with
from LCD to ARDUINO
GND to GND
VCC to 5v
SDA to SDA or analog pins (A0 - A5)
SCL to SDA or analog pins
 
Add library LiquidCrystal I2C
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int width = 16;
const int height = 2;

// Setting up the lcd 
LiquidCrystal_I2C lcd(0x27, width, height);

void setup() {
  // put your setup code here, to run once:

  lcd.init();
  lcd.backlight();

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  lcd.print("Hyperlabs");
  lcd.setCursor(0,1);
  lcd.print("Workshop");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Time to learn");
  lcd.setCursor(0,1);
  lcd.print("Arduino");
  delay(2000);
  lcd.clear();
}
