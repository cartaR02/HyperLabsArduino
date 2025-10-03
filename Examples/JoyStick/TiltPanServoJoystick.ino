#include <Servo.h>   // Include the Servo library

// --- Pin definitions ---
#define SERVO 5       // Pin for servo controlling X-axis
#define SERVOY 6      // Pin for servo controlling Y-axis
#define PINVRX A0     // Joystick X-axis analog input
#define PINVRY A1     // Joystick Y-axis analog input
#define PINBTN 7      // Joystick button (not used yet)

Servo myservoX;       // Servo object for X-axis
Servo myservoY;       // Servo object for Y-axis

void setup() 
{
  Serial.begin(9600);     // Start serial monitor at 9600 baud
  Serial.setTimeout(5);   // Timeout for serial input (not really needed here)

  // Attach servo objects to their pins
  myservoX.attach(SERVO); 
  myservoY.attach(SERVOY);
}

int degrees = 0; // (Unused variable, can be removed)

void loop() 
{
  // Read joystick values (NOTE: variable names are swapped!)
  // You're reading VRY into vrx and VRX into vry.
  int vrx = analogRead(PINVRY); 
  int vry = analogRead(PINVRX);

  // Convert joystick range (0–1023) into servo range (0–180 degrees)
  int mappedX = map(vrx, 0, 1023, 0, 180);
  int mappedY = map(vry, 0, 1023, 0, 180);

  // Send the mapped values to the servos
  myservoX.write(mappedX);
  myservoY.write(mappedY);

  delay(100); // Small delay (makes movement less jittery, but reduces responsiveness)

  // Print values for debugging
  Serial.println(mappedX);
  Serial.println(mappedY);
}
