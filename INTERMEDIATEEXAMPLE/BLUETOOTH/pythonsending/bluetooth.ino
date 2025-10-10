#include <SoftwareSerial.h>
#include <HCSR04.h>
SoftwareSerial BTSerial(10,11);
const int ledPin =  13;
const int TRIG = 9;
const int ECHO = 8;
#define MIN_DIST 0
#define MAX_DIST 40
String inputString = "";

UltraSonicDistanceSensor distanceSensor(TRIG, ECHO);
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(9600);
  BTSerial.begin(9600);

  Serial.println("Bluetooth LED Controller Ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  int cm = distanceSensor.measureDistanceCm();
  if (cm > MIN_DIST && cm < MAX_DIST){
    Serial.println("Enemyspott");
    BTSerial.write("Enemy Spotted");
  }
  while (BTSerial.available()){
    char c = BTSerial.read();
    Serial.println(c);

    if (c == '\n' || c == '\r'){
      processCommand(inputString);
      Serial.println("Clearing String");
      inputString = "";
    } else {
      Serial.println("adding to string");
      inputString += c;
    }
  }
  delay(100);
}

