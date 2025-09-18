# HyperLabs Arduino Workshop

Welcome to **HyperLabs Arduino**!  
This repository supports the HyperLabs Arduino Workshop. It contains example sketches and supporting files to help beginners get started with Arduino components and basic programming.

---

## Table of Contents

- [Overview](#overview)  
- [Repository Structure](#repository-structure)  
- [Getting Started](#getting-started)  
- [Examples](#examples)  
- [Contributing](#contributing)  
- [License](#license)  

---

## Overview

The goal of this workshop/repo is to provide:

- Hands-on example code to demonstrate how to use Arduino hardware & sensors  
- A clean starting point for students/new users to learn how to install, configure, and upload sketches  
- Organized code and resources so learning is straightforward  

---

## Repository Structure

Here’s a breakdown of the folders / files in this repo and what each is for:

HyperLabsArduino/
│
├── Examples/ ← Contains sketch(es) / sample Arduino projects
├── Others/ ← Miscellaneous files or extra resources
├── .gitattributes ← Git config for handling file endings, etc.
├── .DS_Store ← macOS system file (can be ignored)
└── README.md ← This document


## Examples

The `Examples/` folder contains Arduino sketches demonstrating various components:

| Sketch | Purpose / What You’ll Learn | Components Needed | Notes |
|--------|------------------------------|-------------------|-------|
| **BlinkLED** | The classic "Hello World" of Arduino: makes an LED blink on and off. Teaches `digitalWrite()` and `delay()`. | LED, resistor (220–330Ω), jumper wires | Connect LED (through resistor) to a digital pin (e.g. 13) and ground. |
| **ButtonInput** | Shows how to read a button press as a digital input. Introduces pull-up/pull-down resistors. | Pushbutton, resistor (if not using internal pull-up) | Connect one side of button to input pin, the other to 5V/GND. Use `pinMode(pin, INPUT_PULLUP)` if needed. |
| **PotentiometerAnalog** | Reads analog values using `analogRead()` and maps them to control output (like brightness or servo angle). | Potentiometer | Connect pot ends to 5V and GND, wiper to an analog input (A0–A5). |
| **LEDFadePWM** | Demonstrates PWM output with `analogWrite()`. Fades LED brightness smoothly. | LED, resistor | Use a PWM-enabled digital pin (marked with `~` on most boards). |
| **ServoControl** | Controls a servo motor using the `Servo` library. | Servo motor, external power (if needed) | Connect signal wire to a digital pin, power servo with 5V/GND. Don’t overload Arduino’s 5V pin. |
| **UltrasonicDistance** | Uses an HC-SR04 ultrasonic sensor to measure distance. Introduces timing and calculations. | Ultrasonic sensor (HC-SR04), jumper wires | Connect Trigger and Echo pins to digital pins. Power with 5V/GND. |
| **RelaySwitch** | Demonstrates using a relay to switch larger loads with Arduino control. | Relay module, external device/load | Connect relay input pin to Arduino digital output. Use proper external wiring for high-voltage devices. |
| **OLEDDisplay** | Displays text/graphics on an OLED screen using the Adafruit SSD1306 library. | OLED display, jumper wires | Connect via I2C (SDA/SCL) or SPI depending on display. Install required libraries in Arduino IDE. |

Each folder contains a `.ino` sketch file that can be opened directly in the Arduino IDE.

  
- **Others/**: Additional resources or “extras” that are relevant but not part of the main examples — maybe diagrams, notes, or parts not yet formalized into full sketches.  
- **.gitattributes**: Git configuration file.  
- **.DS_Store**: MacOS file system artifact; not used by code.

---

## Getting Started

To use this repo:

1. **Install Arduino IDE**  
   If you haven’t already: download and install the [Arduino IDE](https://www.arduino.cc/en/software) for your operating system.

2. **Set up your Arduino board**  
   - Connect your board (e.g. Arduino Uno) to your computer via USB.  
   - Open Arduino IDE → go to **Tools → Board** → select your board model.  
   - Go to **Tools → Port** → select the correct serial/USB port.

3. **Clone or Download the Repository**  
   ```bash
   git clone https://github.com/cartaR02/HyperLabsArduino.git
Or download the ZIP.

Open and Upload an Example Sketch

Open Arduino IDE → File → Open → navigate to a sketch inside the Examples/ folder.

Verify (compile) → Upload to your connected board. 
