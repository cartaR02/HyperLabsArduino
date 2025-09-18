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

| Sketch / Folder | Description |
|-----------------|-------------|
| **BasicBlink/** | A simple LED blink sketch, the classic Arduino "Hello World". Great for testing that your board and IDE are working. |
| **Buzzer/** | Demonstrates use of a piezo buzzer for sound output. |
| **DCMotor/** | Controls a DC motor, showing how to drive motors from the Arduino. |
| **HelloWorldOLED/** | Example of using an OLED display with the Adafruit SSD1306 library. |
| **HelloWorldLCD/** | Demonstrates controlling a standard LCD display. |
| **Potentiometer/** | Reads values from a potentiometer and outputs them via serial. |
| **RelayModule/** | Shows how to switch devices using a relay. |
| **ServoMotor/** | Demonstrates control of a servo motor. |
| **UltrasonicSensor/** | Reads distance using an ultrasonic sensor (HC-SR04). |

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
