#include <SoftwareSerial.h>
#include <HCSR04.h> // Include the HCSR04 library

SoftwareSerial myBluetooth(10, 11); // 10 is arduino RX that goes to bluetooth TX
                                    // 11 is arduino TX that goes to bluetooth RX

// Define pins for the ultrasonic sensor
const int trigPin = 9;
const int echoPin = 8;
const int maxDist = 30;
const int minDist = 5;

// Initialize the library object
// (trig pin, echo pin)
UltraSonicDistanceSensor distanceSensor(trigPin, echoPin); 

void setup() {
  // Set up the ultrasonic sensor pins
  // No pinMode setup is needed; the library handles it.
  Serial.begin(9600);
  // Start the Bluetooth serial port
  myBluetooth.begin(9600); 
  myBluetooth.println("Bluetooth connected. Sending distance data...");
}

void loop() {
  
  // --- This is the ultrasonic sensor logic ---
  
  // Get the distance in centimeters (cm) from the library
  // The .dist() method handles all the pulsing and timing
  int distance = distanceSensor.measureDistanceCm();
  myBluetooth.println(distance);
  if(distance > minDist && distance < maxDist) {
    myBluetooth.print("SOMEONE IS COMING");
  }
  
  // Wait 500ms before sending the next reading
  delay(500); 
}

