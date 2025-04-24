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

#define RADIUS 7
#define BOUNDS 3
#define POTY A0
#define POTX A1
#define RESET_TIME 5 // milliseconds

// Create an instance of the display object using the defined width, height, I2C interface and reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int X = 20;
int Y = 20;
int prevX = 20;
int prevY = 20;

int cornerX = 10;
int cornerY = 10;

void updatePosition()
{
  // get X coordinate
  int potx = analogRead(POTX);
  int x = map(potx, 0, 1023, 0, SCREEN_WIDTH);
  int poty = analogRead(POTY);
  int y = map(poty, 0, 1023, 0, SCREEN_HEIGHT);
  X = x; Y = y;
}

void drawSquare(int X, int Y, int color, int size)
{
  // draw a filled-in square, centered at (X, Y), length = width = size + 1
  // "erase" erases the area instead of filling it in
  if (size <= 0) display.drawPixel(X, Y, color);

  int x1 = X - size, x2 = X + size, y1 = Y - size, y2 = Y + size;

  for (int x = x1; x <= x2; x++)
  {
    for (int y = y1; y <= y2; y++)
    {
      display.drawPixel(x, y, color);
    }
  }

}

int inBox()
{
  return (X < cornerX && Y < cornerX);
}

void setup() {
  // Initialize I2C communication
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  delay(10);
  display.clearDisplay();
}

void loop(){
  updatePosition();
  drawSquare(X, Y, WHITE, 0);
  display.display();
  if (inBox()) display.clearDisplay();
}
