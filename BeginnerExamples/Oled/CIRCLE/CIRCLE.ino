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
#define POT A0

// Create an instance of the display object using the defined width, height, I2C interface and reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int circleX = 3, circleY = 3; // stores the position of the circle
int Xdirection = 2, Ydirection = 1; // positive or negative

void updateCirclePos()
{
  if (circleX > SCREEN_WIDTH - RADIUS - BOUNDS) 
  {
    Xdirection *= -1; // reverse direction
    circleX = SCREEN_WIDTH - RADIUS - BOUNDS;
  }
  if (circleX < RADIUS + 3)
  {
    Xdirection *= -1;
    circleX = RADIUS + 3;
  }

  // exact same code for X, but for Y
  if (circleY > SCREEN_HEIGHT - RADIUS - BOUNDS) 
  {
  Ydirection *= -1; // reverse direction
    circleY = SCREEN_HEIGHT - RADIUS - BOUNDS;
  }
  if (circleY < RADIUS + BOUNDS)
  {
  Ydirection *= -1;
    circleY = RADIUS + BOUNDS;
  }

  circleX += Xdirection;
  circleY += Ydirection;
}

int sign(int x)
{
  if (x < 0) return -1;
  else return 1;
}

void setCircleSpeed()
{
  int pot = analogRead(POT);
  int speeds = map(pot, 0, 1023, 0, 5);
  Xdirection = sign(Xdirection) * 2 * speeds;
  Ydirection = sign(Ydirection) * speeds;
}

void setup() {
  // Initialize I2C communication
  Wire.begin();

  // Initialize the OLED display with the correct voltage settings and I2C address.
  // SSD1306_SWITCHCAPVCC initializes the display with a charge pump voltage.
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
}

void loop(){
  // Refresh the display to show any changes (if there are any previous buffer content)
  display.display();
  display.clearDisplay();

  display.drawCircle(circleX, circleY, RADIUS, WHITE);
  updateCirclePos();
  setCircleSpeed();

  delay(10);

  
}
