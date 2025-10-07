/* ===================== REACTION GAME =====================
  
  DESCRIPTION:
  This is a two-player reaction speed game using an OLED display and three buttons.
  When the screen flashes white, the first player to press their button wins!

  HOW TO PLAY:
  1. Connect all components (see wiring below).
  2. Turn on the Arduino — the OLED will say "Press Start Button!"
  3. Press the Start button to begin.
  4. Wait... after a random delay, the screen will flash white.
  5. The first player to press their button (Left or Right) after the flash wins!
  6. The OLED will display the winner before returning to the start screen.

  WHAT YOU'LL NEED:
  - Arduino Uno (or compatible board)
  - 0.96" or 1.3" I2C OLED display (SSD1306)
  - 3 push buttons:
      • Left Player button (D2 → button → GND)
      • Right Player button (D3 → button → GND)
      • Start button (D4 → button → GND)
  - Breadboard and jumper wires

  LIBRARIES REQUIRED:
  - Adafruit GFX Library
  - Adafruit SSD1306 Library

  CONNECTION SUMMARY:
  OLED → Arduino
  ----------------
  VCC → 5V (or 3.3V, depending on display)
  GND → GND
  SDA → A4
  SCL → A5
*/

#include <Wire.h>                 
#include <Adafruit_GFX.h>         
#include <Adafruit_SSD1306.h>     

// ================== OLED DISPLAY CONFIGURATION ==================
#define SCREEN_WIDTH 128        // OLED display width, in pixels
#define SCREEN_HEIGHT 64        // OLED display height, in pixels
#define OLED_RESET -1           // Reset pin (not used here)
#define SCREEN_ADDRESS 0x3C     // I2C address for most 128x64 OLEDs
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ================== BUTTON PINS ==================
// Each button connects one side to a digital pin, and the other side to GND.
const int buttonL = 2;          // Left player button
const int buttonR = 3;          // Right player button
const int buttonStart = 4;      // Start button

// ================== SETUP FUNCTION ==================
void setup() {
  Serial.begin(9600); // Start the serial monitor for debugging output

  // Initialize the OLED display
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // Configure button pins as inputs with internal pull-up resistors.
  // This means the pins read HIGH when not pressed, and LOW when pressed.
  pinMode(buttonR, INPUT_PULLUP);
  pinMode(buttonL, INPUT_PULLUP);
  pinMode(buttonStart, INPUT_PULLUP);
}

// ================== MAIN LOOP ==================
void loop() {
  // Check if the Start button is pressed
  int start = digitalRead(buttonStart);
  if (start == LOW) {
    // If pressed, start the game
    enterGame();
  }

  // Display start screen message
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println("Press\nStart\nButton!");
  display.display();

  delay(10); // Small delay to prevent flicker
}

// ================== HELPER FUNCTIONS ==================

// Displays a message on the OLED with a given text size and delay time
void writeMessage(String message, int size, int delay_time) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(size);
  display.println(message);
  display.display();
  delay(delay_time);
}

// Fills the screen completely white (used for the reaction flash)
void displayStart() {
  display.fillScreen(WHITE);
  display.display(); 
}

// ================== GAME LOGIC ==================
void enterGame() {
  // Display instructions for players
  writeMessage("Click the button when the screen flashes white", 1, 3000);
  
  // Wait a random amount of time between 1 and 10 seconds
  int random_start = random(1000, 10000);
  delay(random_start);

  // Flash the screen white to signal "GO!"
  displayStart();

  // Wait for either player to press their button first
  while (true) {
    if (digitalRead(buttonL) == LOW) {
      // Left player pressed first
      Serial.println("LEFT");
      writeMessage("LEFT\nWINS", 4, 2000);
      break;
    } else if (digitalRead(buttonR) == LOW) {
      // Right player pressed first
      Serial.println("RIGHT");
      writeMessage("RIGHT\nWINS", 4, 2000);
      break;
    }
  }
}
