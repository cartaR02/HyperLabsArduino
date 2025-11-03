const int potPin = A0;   // Potentiometer connected to analog pin A0
const int buzzerPin = 9; // Piezo buzzer connected to digital pin 9

void setup() {
    pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as an output
    Serial.begin(9600);          // Initialize serial communication
}

void loop() {
    int potValue = analogRead(potPin); // Read potentiometer value (0-1023)
    Serial.println(potValue); // Print value to Serial Monitor for debugging

    int frequency = map(potValue, 0, 1023, 100, 2000); // Map pot value to a frequency range

    tone(buzzerPin, frequency); // Play the mapped frequency

    delay(100); // Small delay for stability
}
