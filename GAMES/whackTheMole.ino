#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- OLED Configuration ---
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET    -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- Game Pinouts ---
// Index 0: Button on Pin 2 whacks LED on Pin 10, etc.
const int buttonPins[] = {2, 3, 4};
const int molePins[] = {10, 11, 12}; 

// --- Game Variables ---
long timeAllowed = 2000;    
long moleStartTime = 0;     
int activeMole = -1;        
bool waitingForHit = false; 
int score = 0; 

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); 

  // Initialize LEDs and Buttons
  for (int i = 0; i < 3; i++) {
    pinMode(molePins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP); 
  }
  
  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  // Show Start Screen
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.print("GET READY!");
  display.display();
  delay(3000);
  
  updateScoreDisplay(); 
}

void loop() {
  
  // 1. Pop up a new mole
  if (!waitingForHit) {
    activeMole = random(0, 3); 
    digitalWrite(molePins[activeMole], HIGH); 
    moleStartTime = millis(); 
    waitingForHit = true;
  }

  // 2. Check for Timeout (Fail State)
  if (waitingForHit && (millis() - moleStartTime > timeAllowed)) {
    showGameOver("TOO SLOW!"); 
  }

  // 3. Check for Button Input
  if (waitingForHit) {
    for (int i = 0; i < 3; i++) {
      
      // Since we use INPUT_PULLUP, a pressed button reads as LOW
      if (digitalRead(buttonPins[i]) == LOW) {
        
        if (i == activeMole) {
          // SUCCESS!
          digitalWrite(molePins[activeMole], LOW); 
          score++; 
          updateScoreDisplay(); 
          
          // Speed up the game
          timeAllowed = max(300, timeAllowed - 150); 
          
          waitingForHit = false;
          delay(random(500, 1500)); 
          
        } else {
          // WRONG BUTTON
          showGameOver("WRONG MOLE!");
        }
      }
    }
  }
}

// --- Display Helper Functions ---

void updateScoreDisplay() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("SCORE: ");
  display.print(score);
  
  display.setTextSize(1);
  display.setCursor(0, 40);
  display.print("Speed: ");
  display.print(timeAllowed);
  display.print(" ms");
  
  display.display();
}

void showGameOver(String reason) {
  waitingForHit = false;
  digitalWrite(molePins[activeMole], LOW); 
  
  // Update OLED to show failure
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("GAME OVER");
  
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print(reason);
  
  display.setCursor(0, 50);
  display.print("Final Score: ");
  display.print(score);
  display.display();

  // Flash LEDs to signal failure
  for (int blink = 0; blink < 3; blink++) {
    for (int i = 0; i < 3; i++) digitalWrite(molePins[i], HIGH);
    delay(250);
    for (int i = 0; i < 3; i++) digitalWrite(molePins[i], LOW);
    delay(250);
  }

  // Wait before resetting so they can read their score
  delay(3000); 

  // Reset Game Variables
  timeAllowed = 2000; 
  score = 0;
  updateScoreDisplay(); 
}