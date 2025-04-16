#include <Buzzer.h>
#include <HCSR04.h>

#define TRIG 2
#define ECHO 3
#define BUZZER 10

#define DIST_MIN 5
#define DIST_MAX 40
#define NOTE_MIN 20
#define NOTE_MAX 180

Buzzer buzzer(BUZZER);
UltraSonicDistanceSensor distanceSensor(TRIG, ECHO); // initialize sensor

void setup() 
{
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
}

int noteDuration = 80;

int notes[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 0, NOTE_C7, NOTE_E7, 0, NOTE_G7, 0,
  NOTE_G6, 0, NOTE_C7, 0, NOTE_G6, 0, NOTE_E6, 0, NOTE_A6, 0,
  NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0, NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0,
  NOTE_F7, NOTE_G7, 0, NOTE_E7, 0, NOTE_C7, NOTE_D7, NOTE_B6, 0,
  NOTE_C7, 0, NOTE_G6, 0, NOTE_E6, 0, NOTE_A6, 0,
  NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0, NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0,
  NOTE_F7, NOTE_G7, 0, NOTE_E7, 0, NOTE_C7, NOTE_D7, NOTE_B6, 0
};

float durationScalars[] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 3,
  1, 3, 1, 2, 1, 2, 1, 2, 1, 1,
  1, 1, 1, 1, 1, 1.25, 1.25, 1.25, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 2,
  1, 2, 1, 2, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1.25, 1.25, 1.25, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 2
};

int newNoteDuration()
{
  int cm = distanceSensor.measureDistanceCm();
  if (cm < DIST_MIN || cm > DIST_MAX) return -1;
  return map(cm, DIST_MIN, DIST_MAX, NOTE_MIN, NOTE_MAX);

}

void loop() {
  buzzer.begin(100);

  int numNotes = sizeof(notes) / sizeof(notes[0]);
  for (int i = 0; i < numNotes; i++) {
    noteDuration = newNoteDuration();
    Serial.println(noteDuration);

    while (noteDuration == -1) noteDuration = newNoteDuration(); // wait until you move your hand back 

    buzzer.sound(notes[i], (int)(noteDuration * durationScalars[i]));
  }

  buzzer.end(10);
}
