#define IN1 6
#define IN2 5

int serialReadInt()
{
  if (!Serial.available()) return -1;
  return Serial.parseInt();
}

void setMotorSpeed(int spd)
{
  int zeroPin;
  int signalPin;

  // determine which pins to apply signal to
  if (spd > 0)
  {
    // case 1: spd is positive, rotate one direction
    zeroPin = IN1;
    signalPin = IN2;
  }
  else
  {
    // case 2: spd is negative, rotate the other direction
    zeroPin = IN2;
    signalPin = IN1;
    spd = -spd;
  }


  // apply pwm signal
  digitalWrite(zeroPin, LOW);
  analogWrite(signalPin, spd);

}

void setup()
{
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(115200);
  Serial.setTimeout(10);

}

void loop()
{
  int dataIn = serialReadInt();

  if (dataIn != -1)
  {
    setMotorSpeed(dataIn);
  }
 
  delay(100);

}