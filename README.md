# HyperLabs Arduino

Workshop resources and example code for the HyperLabs Arduino Workshop. Built with [Quarto](https://quarto.org) and published to GitHub Pages.

**Live Site:** [https://cartaR02.github.io/HyperLabsArduino/](https://cartaR02.github.io/HyperLabsArduino/)

---

## Overview

This repo provides:

- Hands-on Arduino example sketches for beginner and intermediate learners
- Organized workshop slides and video resources
- A Quarto-powered site to browse everything in one place

---

## Repository Structure

```
HyperLabsArduino/
├── _quarto.yml            # Quarto project config
├── custom.scss            # Custom theme / styling
├── index.qmd              # Home page
├── Beginner.qmd           # Beginner workshop page
├── Intermediate.qmd       # Intermediate workshop page
├── hyperlabs.png          # Logo / favicon
├── BeginnerExamples/      # Beginner Arduino sketches
│   ├── Blink/
│   ├── Buzzer/
│   ├── Coding/
│   ├── Joystick/
│   ├── Keypad/
│   ├── Motor/
│   ├── Oled/
│   ├── Potentiometer/
│   ├── Servo/
│   ├── TempSensor/
│   ├── Ultrasonic/
│   └── encoder/
├── IntermediateExamples/   # Intermediate Arduino sketches
│   ├── Bluetooth/
│   ├── IR-Remote/
│   ├── MPU6050/
│   └── RFID/
├── Others/                 # Miscellaneous examples
└── Games/                  # Fun interactive projects
```

---

## Getting Started

### 1. Install Arduino IDE

Download and install the [Arduino IDE](https://www.arduino.cc/en/software) for your operating system.

### 2. Set Up Your Board

1. Connect your Arduino (e.g., Uno) to your computer via USB
2. Open Arduino IDE > **Tools > Board** > select your board model
3. Go to **Tools > Port** > select the correct serial/USB port

### 3. Upload a Sketch

1. Open any `.ino` file from the examples folders
2. Click the **Upload** button in the Arduino IDE
3. Watch it run on your board

---

## Rendering the Quarto Site Locally

Make sure you have [Quarto installed](https://quarto.org/docs/get-started/).

**Render the site** (outputs to `_book/`):

```bash
quarto render
```

**Preview with live reload** (opens in your browser):

```bash
quarto preview
```

---

## Publishing to GitHub Pages

To publish the site to GitHub Pages, run:

```bash
quarto publish gh-pages
```

This will:

1. Render the project
2. Push the built site to the `gh-pages` branch
3. GitHub Pages will serve it automatically

> **First time?** Make sure GitHub Pages is enabled in your repo: **Settings > Pages > Source** set to `gh-pages` branch.

---

## Resources

- [Arduino IDE](https://www.arduino.cc/en/software/)
- [Arduino Language Reference](https://docs.arduino.cc/language-reference)
- [Quarto Documentation](https://quarto.org/docs/guide/)
