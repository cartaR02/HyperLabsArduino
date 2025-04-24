// Rotary Encoder Inputs
#define CLK 2
#define DT 3

int counter = 0;
int currentStateCLK;
int lastStateCLK;

const int LEDs[] = {4, 5, 6, 7, 8, 9, 10, 11, 12};
const int numLEDs = 9;

String currentDir = "";

void setup() {
  // Set encoder pins as inputs
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);

  // set LED pins as outputs
  for (int i = 0; i < numLEDs; i++) pinMode(LEDs[i], INPUT);

  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);

  // Call updateEncoder() when a change is seen on CLK pin
  attachInterrupt(digitalPinToInterrupt(CLK), updateEncoder, CHANGE);
}

void updateLEDs(int pos)
{

  for (int i = 0; i < numLEDs; i++)
  {
    if (i == pos) digitalWrite(LEDs[i], HIGH);
    else digitalWrite(LEDs[i], LOW);
  }
  
}

void updateEncoder() {
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {

    if (digitalRead(DT) != currentStateCLK) counter--;
    else counter++;

    if (counter < 0) counter = numLEDs - 1;
    if (counter > numLEDs - 1) counter = 0;
    
    Serial.println(counter);
    updateLEDs(counter);
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;
}

void loop() {
}