// Common practice to declare pins as const and change them here

const int trigPin = 7;
const int echoPin = 6;
const int buzzerPin = 9;

float duration,distance;


void setup() {
  // put your setup code here, to run once:
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(buzzerPin, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  distance = getDistance();
  
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
  if (distance < 30){
    int buzzerNoise = map(distance, 0, 30, 2000, 500);
    tone(buzzerPin, buzzerNoise);
  } else {
    noTone(buzzerPin);
  }
}

int getDistance(){
  // Calculations for the distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return(duration*.0343)/2;
}
