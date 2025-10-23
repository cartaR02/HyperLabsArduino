#include <SoftwareSerial.h>
SoftwareSerial myBluetooth(10, 11); // 10 is arduino RX that goes to bluetooth TX
                                    // 11 is arduino TX that goes to bluetooth RX
const int ledPin = 7;

void setup() {
  // For the USB Serial Monitor (for debugging)
  Serial.begin(9600); 
  Serial.println("Arduino is ready.");

  pinMode(ledPin, OUTPUT);
  
  // Start the Bluetooth serial port
  myBluetooth.begin(9600); 
  myBluetooth.println("Bluetooth connected. Send '1' for ON, '0' for OFF.");
}

void loop() {
  
  // Check if data has arrived from Bluetooth
  if (myBluetooth.available()) {
    
    // Read the incoming byte (as a character)
    char command = myBluetooth.read();
    
    // (Good for debugging) Print the command to the USB Serial Monitor
    Serial.print("Command received: ");
    Serial.println(command);

    // --- This is the new logic ---
    // Check what the command is
    if (command == '1') {
      digitalWrite(ledPin, HIGH); // Turn the LED on
      myBluetooth.println("LED is ON");
    } else if (command == '0') {
      digitalWrite(ledPin, LOW);  // Turn the LED off
      myBluetooth.println("LED is OFF");
    }
    // ----------------------------
  }
  
  // (Optional) You can also check for data from the USB serial
  // and send it to Bluetooth
  if (Serial.available()) {
    char data = Serial.read();
    myBluetooth.write(data);
  }
}

