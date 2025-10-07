/*
  Library needed: Adafruit SSD1306
  This code uses the Adafruit SSD1306 library for controlling an OLED display.
  Ensure you have installed the library before compiling.
*/

#include <Wire.h>               // Include the Wire library for I2C communication
#include <Adafruit_SSD1306.h>   // Include the Adafruit SSD1306 OLED display library

// Define constants for the display's dimensions
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Define the OLED reset pin and the I2C address for the display
#define OLED_RESET -1     // Reset pin (set to -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  // I2C address for the OLED display

// Create an instance of the display object using the defined width, height, I2C interface and reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


int PIN_VRX = A0;
int PIN_VRY = A1;
int PIN_BTN = 7;

int JOY_CENTER = 512;
int DEADZONE = 60;  
int distance = 1;  //distance increment
//Cursor
int cursorX = SCREEN_WIDTH / 2;
int cursorY = SCREEN_HEIGHT / 2;

int checkInDeadzone(int val) {
  int upperDeadzone = JOY_CENTER + DEADZONE;
  int lowerDeadzone = JOY_CENTER - DEADZONE;

  if (val > upperDeadzone) return distance;  //moves positive direction when above deadzone bound
  if (val < lowerDeadzone) return -distance; //moves negative direction when below deadzone bound
  return 0; //doesn't move when within deadzone bounds
}

void clearCanvas() {
  display.clearDisplay();

  cursorX = SCREEN_WIDTH / 2;
  cursorY = SCREEN_HEIGHT / 2;
}


void setup() {
  // Initialize I2C communication
  Wire.begin();
  pinMode(PIN_BTN, INPUT_PULLUP);

  // Initialize the OLED display with the correct voltage settings and I2C address.
  // SSD1306_SWITCHCAPVCC initializes the display with a charge pump voltage.
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  clearCanvas();

}

void loop(){
  
  if (digitalRead(PIN_BTN) == LOW) {
    clearCanvas();
    delay(200);
  }

  int xValue = analogRead(PIN_VRY);
  int yValue = analogRead(PIN_VRX);

  int xMovement = checkInDeadzone(xValue);
  int yMovement = -checkInDeadzone(yValue);

  int newCursorX = cursorX + xMovement; 
  int newCursorY = cursorY + yMovement;

  display.drawLine(cursorX, cursorY, newCursorX, newCursorY, WHITE);

  cursorX = newCursorX;
  cursorY = newCursorY;

  display.display();

}

}

