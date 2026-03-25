// Download library
#include <HCSR04.h>

#define TRIG 9
#define ECHO 8

UltraSonicDistanceSensor distanceSensor(TRIG, ECHO); // initialize sensor

void setup () 
{
  Serial.begin(9600);
}

void loop () 
{
  // get distance from the sensor and print it
  int cm = distanceSensor.measureDistanceCm();
  Serial.println(cm);

  delay(50);
}
