Welcome to **HyperLabs Arduino**!  
This repository supports the HyperLabs Arduino Workshop. It contains example sketches and supporting files to help beginners get started with Arduino components and basic programming.

---

## Table of Contents

- [Overview](#overview)
- [Repository Structure](#repository-structure)
- [Getting Started](#getting-started)
- [Examples](#examples)
- [Slides](#slides)
- [Videos and Guides](#Videos-and-guides)

---

## Overview

The goal of this workshop/repo is to provide:

- Hands-on example code to demonstrate how to use Arduino hardware & sensors
- A clean starting point for students/new users to learn how to install, configure, and upload sketches
- Organized code and resources so learning is straightforward
- [Github Repo](https://github.com/cartaR02/HyperLabsArduino)

---

## Repository Structure

- **Examples/** → Contains Arduino sketches / sample projects
- **Others/** → Miscellaneous files or extra resources
- **.gitattributes** → Git config for handling file endings, etc.
- **.DS_Store** → macOS system file (can be ignored)
- **README.md**

---

## Slides

- [Arduino Slides 1 09/18/2025](https://www.canva.com/design/DAGzPY7RSnw/Yf6TqiRTzH-27oPtMXnemw/view?utm_content=DAGzPY7RSnw&utm_campaign=designshare&utm_medium=link2&utm_source=uniquelinks&utlId=h0fe4a98ba1)

---

## Videos and Guides

Here are some helpful videos and documentation to get started with Arduino:

- **[Arduino IDE](https://www.arduino.cc/en/software/)** - Offical Arduino IDE best for programming Arduino
- **[Arduino Language Reference](https://docs.arduino.cc/language-reference)** – Official Arduino docs covering all functions, syntax, and examples.
- **[Mark Rober Arduino Tutorial](https://www.youtube.com/watch?v=yi29dbPnu28)** – Fun and practical Arduino introduction by Mark Rober.
- **[What is Arduino](https://www.youtube.com/watch?v=tiGw9PQbvrg&t=402s)** – Quick overview of Arduino boards and projects.
- **[Arduino in 100 Seconds](https://www.youtube.com/watch?v=1ENiVwk8idM)** – Concise, beginner-friendly explanation of Arduino basics.

---

## Examples

The `Examples/` folder contains Arduino sketches demonstrating various components:

| Sensor                | What it is / What it does                                                                       | Possible Projects                                                        | Code                                                                                                                                    |
| --------------------- | ----------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------ | --------------------------------------------------------------------------------------------------------------------------------------- |
| **LED**               | Light-emitting diode; turns on/off to emit light.                                               | - Blink LED<br>- Blink with potentiometer<br>- LED patterns              | [Open Blink.ino](https://github.com/cartaR02/HyperLabsArduino/blob/main/Examples/Blink/Blink.ino)                                       |
| **Potentiometer**     | Variable resistor; outputs analog voltage depending on knob position.                           | - Read analog value<br>- Control LED brightness<br>- Control servo angle | [Open Potentiometer.ino](https://github.com/cartaR02/HyperLabsArduino/blob/main/Examples/Potentiometer/Potentiometer.ino)               |
| **Piezo Buzzer**      | Produces sound when voltage is applied; can play tones or melodies.                             | - Play a tone<br>- Simple melody<br>- Alarm signal                       | [Open Buzzer.ino](https://github.com/cartaR02/HyperLabsArduino/blob/main/Examples/Buzzer/Buzzer.ino)                                    |
| **DC Motor**          | Converts electrical energy to rotational motion; speed/direction controlled via PWM and driver. | - Motor forward/back<br>- PWM speed control<br>- Simple robot drive      | [Open Motor.ino](https://github.com/cartaR02/HyperLabsArduino/blob/main/Examples/Motor/Motor.ino)                                       |
| **Servo Motor**       | Motor that moves to a specific angle; controlled by PWM signal.                                 | - Sweep servo<br>- Control via potentiometer<br>- Interactive project    | [Open Servo.ino](https://github.com/cartaR02/HyperLabsArduino/blob/main/Examples/Servo/Servo.ino)                                       |
| **Ultrasonic Sensor** | Measures distance by sending sound pulses and measuring echo time.                              | - Measure distance<br>- Obstacle detection<br>- Parking aid              | [Open Ultrasonic.ino](https://github.com/cartaR02/HyperLabsArduino/blob/main/Examples/Ultrasonic/simpleUltrasonic/simpleUltrasonic.ino) |
| **OLED Display**      | Small screen that shows text/graphics via I2C or SPI.                                           | - Show text<br>- Display sensor readings<br>- Simple game or graphics    | [Open OLED.ino](https://github.com/cartaR02/HyperLabsArduino/blob/main/Examples/OLED/SIMPLE_OLED/SIMPLE_OLED.ino)                       |

Oled Commands
🔹 Display Control

display.begin(vccstate, i2caddr) – initialize display.

display.display() – refresh the screen with whatever is in the buffer.

display.clearDisplay() – clear the display buffer.

display.dim(true/false) – dim or undim the display.

display.invertDisplay(true/false) – invert pixels (white ↔ black).

🔹 Text Functions

display.setCursor(x, y) – set text position.

display.setTextColor(color) – set text color (usually WHITE, sometimes BLACK for inverse).

display.setTextColor(color, background) – set text color and background.

display.setTextSize(n) – set text size multiplier.

display.cp437(true/false) – use full 256-char font instead of ASCII.

display.write(char) – write a single character.

display.print("text") / display.println("text") – print text like Serial.

🔹 Drawing Shapes

(from Adafruit GFX, inherited by SSD1306)

display.drawPixel(x, y, color) – draw a single pixel.

display.drawLine(x0, y0, x1, y1, color) – draw a line.

display.drawRect(x, y, w, h, color) – draw rectangle outline.

display.fillRect(x, y, w, h, color) – filled rectangle.

display.drawCircle(x, y, r, color) – circle outline.

display.fillCircle(x, y, r, color) – filled circle.

display.drawRoundRect(x, y, w, h, r, color) – rounded rectangle outline.

display.fillRoundRect(x, y, w, h, r, color) – filled rounded rectangle.

display.drawTriangle(x0, y0, x1, y1, x2, y2, color) – triangle outline.

display.fillTriangle(x0, y0, x1, y1, x2, y2, color) – filled triangle.

🔹 Bitmaps & Images

display.drawBitmap(x, y, bitmap, w, h, color) – draw a monochrome bitmap from an array.

display.drawXBitmap(x, y, bitmap, w, h, color) – draw XBM image format.

🔹 Screen Size Info

display.width() – returns display width.

display.height() – returns display height.

Each folder contains a `.ino` sketch file that can be opened directly in the Arduino IDE.

---

## Getting Started

To use this repo:

1. **Install Arduino IDE**  
   If you haven’t already: download and install the [Arduino IDE](https://www.arduino.cc/en/software) for your operating system.

2. **Set up your Arduino board**
   - Connect your board (e.g., Arduino Uno) to your computer via USB.
   - Open Arduino IDE → go to **Tools → Board** → select your board model.
   - Go to **Tools → Port** → select the correct serial/USB port.
