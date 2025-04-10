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
  
  // Clear the display buffer so that it's ready for new drawing commands
  display.clearDisplay();

  // Set the text color to white
  display.setTextColor(WHITE);
  
  // Set the text size (1 is the smallest size)
  display.setTextSize(1);
  
  // Set the cursor position for where to start drawing text (x=0, y=0)
  display.setCursor(0, 0);
  
  // Print the desired text to the display's buffer
  display.print("Hyperlabs Workshop!");
  
  // Note: Since there's no delay, this loop runs very fast.
  // Consider adding a delay if needed to observe the changes.
}
