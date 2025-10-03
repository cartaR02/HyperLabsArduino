#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins
int PIN_VRX = A0;   // Joystick X
int PIN_VRY = A1;   // Joystick Y
int PIN_BTN = 7;    // Joystick button 

// Joystick Setup
int JOY_CENTER = 512;   // adjust if your center isn't ~512
int DEADZONE  = 60;     // ignore tiny wiggles
int MAX_STEP  = 1;      // pixels per frame

// Cursor
int x = SCREEN_WIDTH / 2;
int y = SCREEN_HEIGHT / 2;

int stepFrom(int val) {
  if (val > JOY_CENTER + DEADZONE) return 1;   
  if (val < JOY_CENTER - DEADZONE) return -1;  
  return 0;                                    
}

void clearCanvas() {
  display.clearDisplay();
  display.display();
  // keep cursor centered when clearing
  x = SCREEN_WIDTH / 2;
  y = SCREEN_HEIGHT / 2;
}

void setup() {
  pinMode(PIN_BTN, INPUT_PULLUP);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  clearCanvas();
}

void loop() {
  // Clear on click (button is LOW when pressed)
  if (digitalRead(PIN_BTN) == LOW) {
    clearCanvas();
    delay(200); 
  }

  int vrx = analogRead(PIN_VRY);
  int vry = analogRead(PIN_VRX);

  int dx = stepFrom(vrx);
  int dy = -stepFrom(vry);

  if (dx != 0 || dy != 0) {
    int oldX = x, oldY = y;
    x += dx; y += dy;
    display.drawLine(oldX, oldY, x, y, SSD1306_WHITE);
    display.display();
  }
}

