#define LED 6
#define POT A0


void controlledDelay(int min, int max)
{
  int pot = analogRead(POT);
  Serial.println(pot);
  int mapped = map(pot, 0, 1023, min, max);
  delay(mapped);
}

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(POT, INPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(LED, HIGH);
  controlledDelay(5, 500);
  digitalWrite(LED, LOW);
  controlledDelay(5, 500);
}