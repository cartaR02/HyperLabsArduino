#include <Servo.h>

#define SERVO 5

Servo myservo;

void setup() 
{
  Serial.begin(9600);
  Serial.setTimeout(5);
  myservo.attach(SERVO);
}

int degrees = 0;
void loop() 
{
  // This normally takes userinput from the serial monitor to 
  int deg = Serial.parseInt();
  myservo.write(deg);
  Serial.println(deg);
}
