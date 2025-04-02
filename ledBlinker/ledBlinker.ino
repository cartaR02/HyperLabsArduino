#define LED_PIN 13

void setup() { // setup runs once on startup

  pinMode(LED_PIN, OUTPUT); // set pin connected to the LED as output
  Serial.begin(9600);       // start USB communication, so we can print

}

void loop() { // loop runs over and over again
  
  digitalWrite(13, HIGH);   // turn the LED on
  Serial.println("LED on"); // print that it's on
  delay(1000);              // wait 1 second

  digitalWrite(13, LOW);     // turn the LED off
  Serial.println("LED off"); // print that it's off
  delay(1000);               // wait 1 second

}
