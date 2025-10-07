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


int PIN_VRX = A0;   // Joystick X-axis connected to analog pin A0
int PIN_VRY = A1;   // Joystick Y-axis connected to analog pin A1
int PIN_BTN = 7;    // Joystick button connected to digital pin 7

int JOY_CENTER = 512;  // Joystick center calibration
int DEADZONE = 60;  // Joystick wiggle range to ignore (prevents jitter)
int distance = 1;  //distance increment
//Cursor
int cursorX = SCREEN_WIDTH / 2;  // Start cursor at screen center (X)
int cursorY = SCREEN_HEIGHT / 2;  // Start cursor at screen center (Y)

/*
  checkInDeadzone():
  Reads joystick analog value and determines if movement
  should occur in positive, negative, or no direction.
*/
int checkInDeadzone(int val) {
  int upperDeadzone = JOY_CENTER + DEADZONE; // Sets the upper limit of the deadzone
  int lowerDeadzone = JOY_CENTER - DEADZONE; // Sets the lower limit of the deadzone

  if (val > upperDeadzone) return distance;  //moves positive direction when above deadzone bound
  if (val < lowerDeadzone) return -distance; //moves negative direction when below deadzone bound
  return 0; //doesn't move when within deadzone bounds
}

/*
  clearCanvas():
  Clears the OLED display and re-centers the cursor.
*/
void clearCanvas() {
  display.clearDisplay();

  cursorX = SCREEN_WIDTH / 2;
  cursorY = SCREEN_HEIGHT / 2;
}


void setup() {
  
  Wire.begin();  // Initialize I2C communication
  pinMode(PIN_BTN, INPUT_PULLUP); // Joystick button uses internal pull-up resistor

  // Initialize the OLED display with the correct voltage settings and I2C address.
  // SSD1306_SWITCHCAPVCC initializes the display with a charge pump voltage.
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  clearCanvas();  // Start with a blank screen

}

void loop(){
  
  if (digitalRead(PIN_BTN) == LOW) { // Button pressed (active = low)
    clearCanvas(); 
    delay(200); // Short delay
  }

  int xValue = analogRead(PIN_VRY); // Y-axis on joystick controls X movement
  int yValue = analogRead(PIN_VRX); // X-axis on joystick controls Y movement

  int xMovement = checkInDeadzone(xValue); // Horizontal movement
  int yMovement = -checkInDeadzone(yValue); // Vertical movement (inverted)

  int newCursorX = cursorX + xMovement; // Computes new end point for drawLine(); (X)
  int newCursorY = cursorY + yMovement; // Computes new end point for drawLine(); (X)

  display.drawLine(cursorX, cursorY, newCursorX, newCursorY, WHITE);

  cursorX = newCursorX; // Update end point of the new line to be starting point of the next line (X)
  cursorY = newCursorY; // Update end point of the new line to be starting point of the next line (X)

  display.display(); // Refresh the display

}

}

