// --- Include the required libraries ---
#include <Wire.h>                 // For I2C communication (SDA/SCL)
#include <Adafruit_MPU6050.h>     // Library for the MPU6050 IMU
#include <Adafruit_Sensor.h>      // Unified sensor event definitions
#include <Adafruit_GFX.h>         // Graphics library (basic shapes/text)
#include <Adafruit_SSD1306.h>     // OLED display driver library

// --- Define display dimensions ---
#define SCREEN_WIDTH 128          // OLED display width in pixels
#define SCREEN_HEIGHT 64          // OLED display height in pixels

// --- Create a display object ---
// Parameters: width, height, I2C bus, reset pin (-1 = none)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- Create an IMU object ---
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);           // Start serial monitor for debugging
  Wire.begin();                   // Initialize I2C communication
  Wire.setClock(400000);          // Use fast I2C speed (400 kHz) for quicker updates

  // ---- Initialize the MPU6050 IMU ----
  if (!mpu.begin(0x68)) {         // Try to start the sensor at address 0x68
    Serial.println(F("MPU6050 not found"));
    while (1) {}                  // Halt the program if the sensor isn’t detected
  }

  // Set accelerometer range and bandwidth (optional fine-tuning)
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);  // ±4g range (sensitivity)
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);    // Basic internal filtering to reduce noise

  // ---- Initialize the OLED display ----
  // Use the I2C address found by the scanner (usually 0x3C)
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Change to 0x3D if needed
    Serial.println(F("SSD1306 init failed"));
    while (1) {}               // Halt if display fails to initialize
  }

  // Clear any old data on the screen
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);  // White text on black background
  display.setTextSize(1);               // Small text font
  display.setCursor(16, 26);            // Move cursor to roughly the center
  display.println(F("IMU Bubble Level"));  // Display a title
  display.display();                    // Update OLED with the title text
  delay(600);                           // Pause for 0.6 seconds so it’s readable
}

void loop() {
  // Create sensor event structures for accelerometer, gyro, and temperature
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);   // Read all 3 sensor events from the IMU

  // Extract linear acceleration values (in m/s^2) for each axis
  float ax = a.acceleration.x;
  float ay = a.acceleration.y;
  float az = a.acceleration.z;

  // --- Calculate tilt angles from acceleration only ---
  // pitch: forward/backward tilt  (rotation around Y-axis)
  float pitch_deg = atan2(-ax, sqrt(ay*ay + az*az)) * 57.2958; // convert radians → degrees
  // roll: left/right tilt (rotation around X-axis)
  float roll_deg  = atan2( ay,  az ) * 57.2958;                // convert radians → degrees

  // --- Constrain tilt angles so the bubble stays on screen ---
  int roll_c  = (roll_deg  < -30) ? -30 : (roll_deg  > 30 ? 30 : (int)roll_deg);
  int pitch_c = (pitch_deg < -30) ? -30 : (pitch_deg > 30 ? 30 : (int)pitch_deg);

  // --- Map the angles to OLED pixel coordinates ---
  // Roll controls horizontal (x) position
  int x = map(-roll_c,  -30, 30, 10, SCREEN_WIDTH  - 10);
  // Pitch controls vertical (y) position (inverted so tilt-up moves bubble up)
  int y = map(-pitch_c, -30, 30, SCREEN_HEIGHT - 10, 10);

  // --- Draw the user interface ---
  display.clearDisplay();                         // Clear the screen each frame

  // Draw a border around the screen
  display.drawRect(1, 1, SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2, SSD1306_WHITE);

  // Draw crosshair lines through the center
  display.drawLine(SCREEN_WIDTH / 2, 1, SCREEN_WIDTH / 2, SCREEN_HEIGHT - 2, SSD1306_WHITE); // vertical line
  display.drawLine(1, SCREEN_HEIGHT / 2, SCREEN_WIDTH - 2, SCREEN_HEIGHT / 2, SSD1306_WHITE); // horizontal line

  // Draw the bubble (circle) at the mapped coordinates
  display.fillCircle(x, y, 5, SSD1306_WHITE);

  // Push all the drawings to the OLED
  display.display();

  // Small delay to control refresh rate (~100 frames/sec)
  delay(10);
}
