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
 // make sure the digital pins on your Arduino match the pins below? ex: rows: 9, 7, 8, 6 cols: 5, 4, 3, 2
byte rowPins[ROWS] = {10, 9, 8, 7};   // 4 row pins
byte colPins[COLS] = {6, 5, 4, 3};    // 4 column pins

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

    // Clear calculator if 'C' is pressed
    if (customKey == 'C') {
      firstnum = '\0';
      op = '\0';
      secondnum = '\0';
      Serial.println("Calculator cleared!");
    }
    // Store first number
    else if (firstnum == '\0' && isDigit(customKey)) {
      firstnum = customKey;
    }
    // Store operator
    else if (op == '\0' && (customKey == '+' || customKey == '-' || customKey == '*' || customKey == '/')) {
      op = customKey;
    }
    // Store second number and calculate
    else if (secondnum == '\0' && isDigit(customKey)) {
      secondnum = customKey;

      // Convert chars to integers
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
