/*
Tutorial used with this code: https://www.circuitbasics.com/arduino-thermistor-temperature-sensor-tutorial/

To install library needed click tools and then manage libraries.
Type in adafruit gfx
It will ask to install without dependencies, click install all

Then install library adafruit ssd1306
Click install all for that library as well

On bread board with OLED
Orient the pins to be above the screen. From left to right connect the GND pin to ground. VCC to 5V. SCL to A5. SDA to A4.

I know its a lot but follow along, read the comments.

Again add a library DHT11

This example I will use a Tempurature sensor and display a tempurature.

From the link copy the code, already copied since youre here



*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Part used for the temp sensor
#include <dht11.h>
#define DHT11PIN 4



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16


int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {

Wire.begin();
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

Serial.begin(9600);
}

void loop() {

  

  displayTemp();
  display.display();
}

void displayTemp(){
  // Delay to allow sensor to stabalize
  delay(2000);
 
  // TEMP dont worry about all this
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 
 
  // Clear the display
  display.clearDisplay();
  //Set the color - always use white despite actual display color
  display.setTextColor(WHITE);
  //Set the font size
  display.setTextSize(1);
  //Set the cursor coordinates
  // Play around with this
  
  display.setCursor(0,0);
  display.print("HyperLabs Workshop");
  display.setCursor(0,10); 
  display.print("Temperature: "); 
  display.print(T);
  display.print(" *F");
}