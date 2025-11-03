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
  while (!Serial.available());
  int deg = Serial.parseInt();
  myservo.write(deg);
  Serial.println(deg);
}