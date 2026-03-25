#include <Servo.h>
#define SERVO 5
Servo myservo;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
  myservo.attach(SERVO);
}

void loop() {
  if (Serial.available() > 0) {
    int deg = Serial.parseInt();
    deg = constrain(deg, 0, 180);
    myservo.write(deg);
    Serial.println(deg);
  }
}
