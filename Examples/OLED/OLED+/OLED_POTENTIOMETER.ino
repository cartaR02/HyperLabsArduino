/*
Tutorial used with this code: https://www.circuitbasics.com/arduino-thermistor-temperature-sensor-tutorial/

To install library needed click Tools -> Manage Libraries.
Type in "Adafruit GFX" and click "Install All" to install its dependencies.
Then install the "Adafruit SSD1306" library similarly.

For the OLED on your breadboard:
- Orient the pins so they’re at the top of the screen.
- From left to right: Connect the GND pin to ground, VCC to 5V, SCL to A5, and SDA to A4.

Also, add the DHT11 library if you need to measure temperature.
This example uses a servo and a potentiometer to display a position value on the OLED.
*/

#include <SPI.h>               // Needed for SPI communication (might be used by some OLED libraries)
#include <Wire.h>              // I2C library for communication with the OLED display
#include <Adafruit_GFX.h>      // Core graphics library for displays
#include <Adafruit_SSD1306.h>  // Library for the SSD1306 OLED display
#include <Servo.h>             // Library to control servo motors

// Define the analog pin for the potentiometer
#define POT A0

// Define the OLED display dimensions in pixels
#define SCREEN_WIDTH 128       // OLED display width, in pixels
#define SCREEN_HEIGHT 64       // OLED display height, in pixels

// Create a Servo object to control the servo motor
Servo myServo;

// OLED display configuration:
// The OLED uses I2C. On the Arduino UNO, SDA is A4 and SCL is A5.
#define OLED_RESET     -1      // Reset pin for the OLED (set to -1 if sharing the Arduino reset pin)
#define SCREEN_ADDRESS 0x3C    // OLED I2C address (0x3C for 128x32, 0x3D for 128x64 displays)

// Create the OLED display object with the defined dimensions and reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Begin I2C communication for the OLED display
  Wire.begin();

  // Initialize the OLED display with the proper voltage settings and I2C address
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

  // Initialize serial communication at 9600 baud for debugging purposes
  Serial.begin(9600);
  
  // Attach the servo motor to digital pin 5
  myServo.attach(5);
}

void loop() {
  // Read the analog value from the potentiometer (value between 0 and 1023)
  int pot = analogRead(POT);
  
  // Map the potentiometer value (0-1023) to servo degrees (0-180)
  int degrees = map(pot, 0, 1023, 0, 180);
  
  // Write the mapped angle to the servo motor
  myServo.write(degrees);
  
  // Display update:
  // First, push any previous content to the OLED, then clear the display for new information.
  display.display();
  display.clearDisplay();

  // Set text parameters for the OLED:
  display.setTextColor(WHITE);  // OLEDs use "white" for text regardless of the display color
  display.setTextSize(1);         // Set the font size to 1 (small text)

  // Set the cursor to the top-left corner of the display (x=0, y=0) and print the potentiometer value
  display.setCursor(0, 0);
  display.print("Pot: ");
  display.print(degrees);
  
  // Move the cursor down by 10 pixels (to a new line) to print the servo state
  display.setCursor(0, 10);
  display.println("Servo rotating: ");
  
  // Display the servo rotation direction based on the mapped degrees value:
  // When the degrees value is less than 90, we consider it a clockwise rotation.
  // When it is more than 90, it is a counterclockwise rotation.
  // Exactly 90 degrees implies a "stopped" or neutral position.
  if (degrees < 90) {
    display.print("Clockwise");
  } else if (degrees > 90) {
    display.print("Counterclockwise");
  } else {
    display.print("Stopped");
  }
  
  // Pause for 100 milliseconds to allow the display to update and servo to adjust position
  delay(100);
}
