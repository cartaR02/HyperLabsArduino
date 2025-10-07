/*
  Pan-Tilt Joystick Control
  --------------------------
  This program controls a two-servo pan-tilt mount using a joystick.

  Hardware needed:
  - 2x Servos mounted on a tilt-pan bracket (one for X-axis, one for Y-axis)
  - 1x Joystick module with X (A0), Y (A1), and button (pin 7)

  How it works:
  - The joystick X-axis controls the horizontal servo (pan).
  - The joystick Y-axis controls the vertical servo (tilt).
  - The joystick values (0–1023) are mapped to servo angles (0–180).
  - Optional: the joystick button can be used to reset servos to center (90°, 90°).
*/

#include <Servo.h>

// --- Pin definitions ---
#define SERVO 5       // Pin for X-axis servo (pan)
#define SERVOY 6      // Pin for Y-axis servo (tilt)
#define PINVRX A0     // Joystick X-axis analog input
#define PINVRY A1     // Joystick Y-axis analog input
#define PINBTN 7      // Joystick button input (not used yet)

Servo myservoX;       // Servo object for X-axis (pan)
Servo myservoY;       // Servo object for Y-axis (tilt)

void setup() 
{
  Serial.begin(9600);     // Start serial monitor at 9600 baud
  Serial.setTimeout(5);   // Timeout for serial input (not really needed)

  // Attach servo objects to their pins
  myservoX.attach(SERVO); 
  myservoY.attach(SERVOY);

  pinMode(PINBTN, INPUT_PULLUP); // Setup joystick button
}

void loop() 
{
  // Read joystick values
  int vrx = analogRead(PINVRX); 
  int vry = analogRead(PINVRY);

  // Convert joystick range (0–1023) into servo range (0–180 degrees)
  int mappedX = map(vrx, 0, 1023, 0, 180);
  int mappedY = map(vry, 0, 1023, 0, 180);

  // Send mapped values to servos
  myservoX.write(mappedX);
  myservoY.write(mappedY);

  // Optional: reset to center if button pressed
  if (digitalRead(PINBTN) == LOW) {
    myservoX.write(90);
    myservoY.write(90);
  }

  delay(15); // Small delay for smoother movement

  // Print values for debugging
  Serial.print("X: ");
  Serial.print(mappedX);
  Serial.print(" | Y: ");
  Serial.println(mappedY);
}
