/*
  Arduino Function and Array Demo
  --------------------------------
  Demonstrates:
    - Reusable functions
    - Arrays
    - Loops
    - Serial input/output
    - Calculating averages (useful for sensor data)
    
  No hardware needed — works in Serial Monitor.
*/

const int NUM_READINGS = 10;
float tempReadings[NUM_READINGS]; // pretend this is sensor data

// --- Function Declarations ---

// Function to simulate taking a temperature reading (returns random float)
float getTemperature() {
  return random(200, 310) / 10.0; // random 20.0–31.0 °C
}

// Function to print a formatted reading
void printSensorReading(String name, float value, String units) {
  Serial.print(name);
  Serial.print(": ");
  Serial.print(value, 2);
  Serial.print(" ");
  Serial.println(units);
}

// Function to calculate average of an array
float average(float arr[], int size) {
  float total = 0;
  for (int i = 0; i < size; i++) {
    total += arr[i];
  }
  return total / size;
}

// Function to ask user for input
String getInput(String prompt) {
  Serial.println(prompt);
  while (Serial.available() == 0) {
    // wait for input
  }
  String input = Serial.readStringUntil('\n');
  input.trim();
  return input;
}

// Typewriter-style text printing (for fun)
void typeText(String text, int speed) {
  for (int i = 0; i < text.length(); i++) {
    Serial.print(text[i]);
    delay(speed);
  }
  Serial.println();
}

// --- Setup runs once ---
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0)); // seed random generator with analog noise
  
  typeText("=== Arduino Average and Functions Demo ===", 40);
  delay(500);

  // Get user name just for personalization
  String name = getInput("Enter your name:");
  Serial.print("Welcome, "); Serial.println(name);
  Serial.println();

  Serial.println("Simulating 10 temperature readings...\n");
  
  // Take 10 fake readings
  for (int i = 0; i < NUM_READINGS; i++) {
    tempReadings[i] = getTemperature();
    printSensorReading("Temperature", tempReadings[i], "°C");
    delay(300);
  }

  // Compute and print the average
  float avgTemp = average(tempReadings, NUM_READINGS);
  Serial.println();
  Serial.print("Average temperature: ");
  Serial.print(avgTemp, 2);
  Serial.println(" °C");
  
  // Add some logic to interpret the result
  if (avgTemp > 28) {
    Serial.println("It's pretty warm overall!");
  } else if (avgTemp < 22) {
    Serial.println("Fairly cool readings!");
  } else {
    Serial.println("Temperature is moderate.");
  }

  Serial.println("\nSetup complete. Loop will repeat every 10 seconds.");
  Serial.println();
}

// --- Loop runs forever ---
void loop() {
  delay(10000); // wait 10 seconds before running again

  Serial.println("\nTaking new readings...\n");
  for (int i = 0; i < NUM_READINGS; i++) {
    tempReadings[i] = getTemperature();
    printSensorReading("Temperature", tempReadings[i], "°C");
    delay(300);
  }

  float avgTemp = average(tempReadings, NUM_READINGS);
  Serial.print("\nNew average temperature: ");
  Serial.print(avgTemp, 2);
  Serial.println(" °C");
}
