#include <IRremote.h>   // Include the IRremote library

const int RECEIVE_PIN = 7;   // IR receiver signal pin
const int LED_PIN = 11;      // LED pin

IRrecv irrecv(RECEIVE_PIN);  // IR receiver object
decode_results results;      // Store decoded IR data

// 👉 Replace these with your actual button codes
unsigned long UP_BUTTON = 0xFF18E7;     // Make sure the remote button code matches the ones for YOUR remote
unsigned long DOWN_BUTTON = 0xFF4AB5;   // ^Same thing here!!

unsigned long lastCode = 0;

void setup() {
  Serial.begin(9600);       // Open Serial Monitor at 9600 baud
  irrecv.enableIRIn();      // Start IR receiver
  pinMode(LED_PIN, OUTPUT); // LED pin as output
}

void loop() {
  if (irrecv.decode(&results)) {              // If we got an IR signal
    unsigned long value = results.value;


    // Turn LED ON if UP button is pressed
    if (value == UP_BUTTON) {
      digitalWrite(LED_PIN, HIGH);
    }
    // Turn LED OFF if DOWN button is pressed
    else if (value == DOWN_BUTTON) {
      digitalWrite(LED_PIN, LOW);
    }

   
    irrecv.resume();  // Ready to receive the next code
  }
}
