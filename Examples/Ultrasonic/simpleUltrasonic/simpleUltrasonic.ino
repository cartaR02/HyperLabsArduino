#include <HCSR04.h>

#define TRIG 2
#define ECHO 3
#define LED 10

#define MIN_DIST 0
#define MAX_DIST 40

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

  if (cm > MIN_DIST && cm < MAX_DIST)
  {
    int pwmVal = map(cm, MIN_DIST, MAX_DIST, 0, 127);
    analogWrite(LED, pwmVal);
  }
  else
  {
    analogWrite(LED, 0);
  } 


  delay(50);
}