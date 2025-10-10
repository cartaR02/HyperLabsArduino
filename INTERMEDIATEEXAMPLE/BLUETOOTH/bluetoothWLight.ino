#include <SoftwareSerial.h>   // Include library to create a serial connection on other pins

// Create a Bluetooth serial object using digital pins 10 (RX) and 11 (TX)
SoftwareSerial BTSerial(10, 11);

// Define which Arduino pin the LED is connected to
const int ledPin = 13;

// String variable to collect characters sent over Bluetooth until a full command is received
String inputString = "";

void setup() {
  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // Make sure LED starts off

  // Initialize the built-in USB serial monitor
  Serial.begin(9600);

  // Initialize the Bluetooth serial connection (HC-05)
  BTSerial.begin(9600);

  // Print a startup message to the Serial Monitor
  Serial.println("Bluetooth LED Controller Ready");
}

void loop() {
  // Continuously check for any data sent from the Bluetooth module
  while (BTSerial.available()) {
    // Read one character from Bluetooth
    char c = BTSerial.read();
    Serial.println(c);  // For debugging: show the received character in Serial Monitor

    // Check if the character is a newline or carriage return → end of command
    if (c == '\n' || c == '\r') {
      // Process the command stored in inputString
      processCommand(inputString);
      Serial.println("Clearing String");  // Debug info
      inputString = "";                   // Reset the string for the next command
    } else {
      // Add the character to the ongoing command string
      Serial.println("adding to string"); // Debug info
      inputString += c;
    }
  }
}

// Function that runs when a full command ("on" or "off") is received
void processCommand(String cmd) {
  cmd.trim();      // Remove any leading/trailing spaces or line breaks
  cmd.toLowerCase();  // Convert to lowercase for case-insensitive matching

  // If command is "on", turn the LED on
  if (cmd == "on") {
    digitalWrite(ledPin, HIGH);
    BTSerial.println("LED turned on ");  // Send confirmation back over Bluetooth
    Serial.println("LED turned on ");    // Print confirmation to Serial Monitor
  } 
  // If command is "off", turn the LED off
  else if (cmd == "off") {
    digitalWrite(ledPin, LOW);
    BTSerial.println("LED turned off");  // Send confirmation back over Bluetooth
    Serial.println("LED turned off");    // Print confirmation to Serial Monitor
  }
}
