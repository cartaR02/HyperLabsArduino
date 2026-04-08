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
bool gameStarted = false; 

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
  showStartScreen();
}

void loop() {
  
  // 0. Wait for a button press to start the game
  if (!gameStarted) {
    for (int i = 0; i < 3; i++) {
      if (digitalRead(buttonPins[i]) == LOW) {
        
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(10, 20);
        display.print("GET READY!");
        display.display();
        
        // Wait for player to release the button
        while (digitalRead(buttonPins[0]) == LOW || 
               digitalRead(buttonPins[1]) == LOW || 
               digitalRead(buttonPins[2]) == LOW) {
          delay(10);
        }
        
        delay(1500); 
        
        gameStarted = true;
        updateScoreDisplay();
        break;
      }
    }
    return; 
  }

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

void showStartScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 10);
  display.print("WHACK-A-MOLE");
  
  display.setCursor(0, 40);
  display.print("Press any button...");
  display.display();
}

void showGameOver(String reason) {
  waitingForHit = false;
  digitalWrite(molePins[activeMole], LOW); 
  
  // Update OLED to show failure
  display.clearDisplay();
  
  // Title
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("GAME OVER");
  
  // Reason for losing
  display.setTextSize(1);
  display.setCursor(0, 20); // Moved up slightly to make room
  display.print(reason);
  
  // Final Score
  display.setCursor(0, 35); // Moved up slightly
  display.print("Final Score: ");
  display.print(score);

  // Final Speed (NEW)
  display.setCursor(0, 50); // Added new line at the bottom
  display.print("Final Speed: ");
  display.print(timeAllowed);
  display.print("ms");
  
  display.display();

  // Flash LEDs to signal failure
  for (int blink = 0; blink < 3; blink++) {
    for (int i = 0; i < 3; i++) digitalWrite(molePins[i], HIGH);
    delay(250);
    for (int i = 0; i < 3; i++) digitalWrite(molePins[i], LOW);
    delay(250);
  }

  // Wait before resetting so they can read their score and speed
  delay(3500); 

  // Reset Game Variables
  timeAllowed = 2000; 
  score = 0;
  gameStarted = false; 
  showStartScreen(); 
}
