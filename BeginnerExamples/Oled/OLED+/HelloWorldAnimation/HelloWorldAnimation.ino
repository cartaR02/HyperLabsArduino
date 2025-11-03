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
  Serial.begin(9600);
  // Initialize the OLED display with the correct voltage settings and I2C address.
  // SSD1306_SWITCHCAPVCC initializes the display with a charge pump voltage.
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  
  
  display.clearDisplay();
  // Set the text color to white
  display.setTextColor(WHITE);
  
  // Set the text size (1 is the smallest size)
  display.setTextSize(1);
  
  // Set the cursor position for where to start drawing text (x=0, y=0)
  display.setCursor(0, 0);
  display.print("Helo");
  /*
  
for (int i = 0; i < myString.length(); i++) {
  display.clearDisplay();
  display.display();
  
  // Clear the display buffer so that it's ready for new drawing commands
  
  
  // Clear the display buffer so that it's ready for new drawing commands
  delay(100);
  
   
}*/

}

char alternatingAlphabet[] = {
    'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e', 'F', 'f', 'G', 'g',
    'H', 'h', 'I', 'i', 'J', 'j', 'K', 'k', 'L', 'l', 'M', 'm', 'N', 'n',
    'O', 'o', 'P', 'p', 'Q', 'q', 'R', 'r', 'S', 's', 'T', 't', 'U', 'u',
    'V', 'v', 'W', 'w', 'X', 'x', 'Y', 'y', 'Z', 'z', ' ', ',', '!'
  };
  int alphabetLength = sizeof(alternatingAlphabet) / sizeof(alternatingAlphabet[0]);
  String myString = "Hello World!";
  
int delayTime = 15;
void loop(){
  String currentString = "";
  for (int i = 0; i < myString.length(); i++) {
  
  display.clearDisplay();
  display.print(currentString);
  char currentChar = myString.charAt(i);
    // Print the current character; this appends it at the current cursor position
  for (int j = 0; j < alphabetLength; j++ ){
    display.clearDisplay();
    display.setCursor(0,0);
    char foundChar = alternatingAlphabet[j];
    delay(delayTime);
    display.print(currentString);
    display.print(foundChar);
    display.display();
    if (foundChar == currentChar){
      currentString += foundChar;
      Serial.println(currentString);
      break;
    }
  }
    
  }
  delay(2000)
  display.clearDisplay();
  display.setCursor(0,0);
  delayTime -= 1;
}
