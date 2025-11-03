

#include <DHT11.h>

DHT11 mySensor(2);

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly.

int temp = mySensor.readTemperature();

int humidity = mySensor.readHumidity();

Serial.print("t:");
Serial.print(temp);
Serial.print(" h: ");
Serial.print(humidity);
Serial.println();




}
