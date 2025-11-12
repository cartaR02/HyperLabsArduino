/*
  Simple RFID Card Reader Example
  --------------------------------
  This sketch reads an RFID tag using the RC522 module and prints its unique
  serial number to the Serial Monitor.

  It uses the RFID library from:
  https://github.com/lsongdev/Arduino-RFID-RC522/

  Connections typically:
  RC522    →   Arduino
  SDA/SS   →   D10
  SCK      →   D13
  MOSI     →   D11
  MISO     →   D12
  RST      →   D9
  3.3V     →   3.3V
  GND      →   GND
*/

#include <SPI.h>   // Include SPI communication library
#include <RFID.h>  // Include RFID library for RC522 module

#define SS_PIN 10   // Slave Select pin (SDA on the RC522)
#define RST_PIN 9   // Reset pin for RFID module

RFID rfid(SS_PIN, RST_PIN); // Create RFID object using defined pins

void setup()
{
  Serial.begin(9600);  // Start serial communication for debugging/output
  SPI.begin();         // Initialize SPI communication
  rfid.init();         // Initialize RFID module
}

void loop()
{
  // Check if a card is present near the RFID reader
  if (rfid.isCard()) {
    Serial.println("Find the card!");  // Notify that a card has been detected
    
    // If a card is detected, read its serial number
    if (rfid.readCardSerial()) {
      Serial.print("The card's number is: ");
      
      // Print each byte of the card's unique serial number in hexadecimal
      Serial.print(rfid.serNum[0], HEX);
      Serial.print(rfid.serNum[1], HEX);
      Serial.print(rfid.serNum[2], HEX);
      Serial.print(rfid.serNum[3], HEX);
      Serial.print(rfid.serNum[4], HEX);
      Serial.println(); // Move to the next line
    }

    // Tell the RFID reader to select the detected card (prepares for next read)
    rfid.selectTag(rfid.serNum);
  }

  // Put the RFID reader into a low-power idle state until the next card appears
  rfid.halt();
}
