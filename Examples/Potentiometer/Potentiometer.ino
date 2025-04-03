const int potPin = A0;  // Potentiometer connected to analog pin A0
const int ledPin = 9;   // LED connected to digital pin 9

void setup() {
    pinMode(ledPin, OUTPUT);  // Set LED pin as an output
    Serial.begin(9600);       // Initialize serial communication
}

void loop() {
    int potValue = analogRead(potPin); // Read potentiometer value (0-1023)
    Serial.println(potValue); // Print value to serial monitor

    if (potValue > 500) {
        digitalWrite(ledPin, HIGH); // Turn on LED
    } else {
        digitalWrite(ledPin, LOW);  // Turn off LED
    }

    delay(100); // Small delay for stability
}
