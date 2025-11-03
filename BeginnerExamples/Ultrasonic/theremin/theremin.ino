#define TRIG 9
#define ECHO 8
#define BUZZER 10

#define MIN_PITCH 200
#define MAX_PITCH 1000
#define MIN_DIST 1
#define MAX_DIST 50

#include <HCSR04.h>

UltraSonicDistanceSensor sensor(TRIG, ECHO);

void setup()
{
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop()
{
  int cm = sensor.measureDistanceCm();
  Serial.println(cm);
  if (cm < MIN_DIST || cm > MAX_DIST) 
  {
    tone(BUZZER, 0, 10);
  }
  else
  {
    unsigned int pitch = map(cm, MIN_DIST, MAX_DIST, MIN_PITCH, MAX_PITCH);
    tone(BUZZER, pitch, 10);
  }
  delay(10);

}