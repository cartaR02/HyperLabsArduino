// Take value from petentiometer and send it into the piezzo buzzer

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(9, OUTPUT);
}

int currentValue = 0;
void loop() {
  // put your main code here, to run repeatedly:
int readValue = analogRead(A0) * 3;

delay(10);
tone(9, readValue);
Serial.println(readValue);
}
