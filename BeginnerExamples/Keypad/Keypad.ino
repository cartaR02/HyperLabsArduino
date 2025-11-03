#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  

const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns

// Define the symbols on the buttons of the keypad
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// Assign safe Arduino pins for rows and columns
byte rowPins[COLS] = {7, 8, 9, 10};  // Row 0 → pin 9, Row 1 → pin 8, Row 2 → pin 7, Row 3 → pin 6
byte colPins[ROWS] = {3, 4, 5, 6};  // Col 0 → pin 5, Col 1 → pin 4, Col 2 → pin 3, Col 3 → pin 2

// Initialize an instance of class Keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS ); 

void setup() {
  Serial.begin(9600);
  lcd.init();        // Initialize LCD
  lcd.backlight();   // Turn on backlight
  lcd.setCursor(0,0);
  lcd.print("Press a key:");
}

void loop() {
  char customKey = customKeypad.getKey();
  
  if (customKey) {
    lcd.clear();
    lcd.setCursor(0,0);
    Serial.println("You pressed:");
    lcd.setCursor(0,1);
    Serial.println(customKey);
  }
}
