#include <Keypad.h>
#include <Wire.h> 

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','#','/'}
};

byte colPins[ROWS] = {6, 5, 4, 3};  
byte rowPins[COLS] = {10, 9, 8, 7};  

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

char firstnum = '\0';
char op = '\0';
char secondnum = '\0';

void setup() {
  Serial.begin(9600);
}

void loop() {
  char customKey = customKeypad.getKey();
  
  if (customKey) {
    Serial.print("You pressed: ");
    Serial.println(customKey);

    // Store inputs in sequence
    if (firstnum == '\0' && isDigit(customKey)) {
      firstnum = customKey;
    }
    else if (op == '\0' && (customKey == '+' || customKey == '-' || customKey == '*' || customKey == '/')) {
      op = customKey;
    }
    else if (secondnum == '\0' && isDigit(customKey)) {
      secondnum = customKey;

      // Convert chars to numbers
      int a = firstnum - '0';
      int b = secondnum - '0';
      int result = 0;

      switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': if (b != 0) result = a / b; break;
      }

      Serial.print("Result = ");
      Serial.println(result);

      // Reset for next calculation
      firstnum = '\0';
      op = '\0';
      secondnum = '\0';
    }
  }
}
