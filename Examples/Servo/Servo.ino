#include <Servo.h>

#define POT A0
#define SERVO 5

Servo myservo;

void setup() 
{
  myservo.attach(SERVO);                       // attaches the servo on pin 9 to the servo object
}

void loop() 
{
  int pot = analogRead(POT);                   // reads the value of the potentiometer (value between 0 and 1023)
  int degrees = map(pot, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(degrees);                      // sets the servo velocity according to the scaled value
}