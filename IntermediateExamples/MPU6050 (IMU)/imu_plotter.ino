// Include the Adafruit MPU6050 library, which simplifies communication with the sensor
#include <Adafruit_MPU6050.h>

// Include the Adafruit Sensor base class — this provides a unified sensor interface
#include <Adafruit_Sensor.h>

// Include the Wire library to enable I2C communication (used by the MPU6050)
#include <Wire.h>

// Create an instance of the MPU6050 sensor class
Adafruit_MPU6050 mpu;

void setup(void) {
  // Start the serial connection so we can print sensor data to the Serial Monitor
  Serial.begin(115200);

  // Initialize communication with the MPU6050
  // This sets up the I2C communication and checks if the sensor is connected
  mpu.begin();

  // Configure the accelerometer sensitivity range
  // Options are ±2G, ±4G, ±8G, or ±16G. Higher ranges reduce sensitivity but allow for higher acceleration measurement.
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);

  // Configure the gyroscope sensitivity range
  // Options are ±250, ±500, ±1000, ±2000 degrees per second.
  // Here we choose ±250°/s for more precise readings at slower rotations.
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);

  // Set the Digital Low Pass Filter (DLPF) bandwidth.
  // This affects how much noise is filtered out from the accelerometer/gyro data.
  // Lower bandwidth (e.g. 5Hz) filters more noise but slows response time.
  // Higher bandwidth (e.g. 260Hz) gives faster response but more noise.
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Print a blank line for readability in Serial Monitor
  Serial.println("");

  // Short delay to let sensor settings stabilize before taking readings
  delay(100);
}

void loop() {

  // Declare sensor event structures to hold the current readings.
  // 'a' will store accelerometer data (in m/s^2),
  // 'g' will store gyroscope data (in rad/s),
  // 'temp' will store temperature data (in °C).
  sensors_event_t a, g, temp;

  // Get the latest sensor readings and fill the 'a', 'g', and 'temp' structures
  mpu.getEvent(&a, &g, &temp);

  // --- Print Accelerometer Data ---
  Serial.print("AccelX:");
  Serial.print(a.acceleration.x);   // X-axis acceleration
  Serial.print(",");
  Serial.print("AccelY:");
  Serial.print(a.acceleration.y);   // Y-axis acceleration
  Serial.print(",");
  Serial.print("AccelZ:");
  Serial.print(a.acceleration.z);   // Z-axis acceleration
  Serial.print(", ");

  // --- Print Gyroscope Data ---
  Serial.print("GyroX:");
  Serial.print(g.gyro.x);           // X-axis angular velocity
  Serial.print(",");
  Serial.print("GyroY:");
  Serial.print(g.gyro.y);           // Y-axis angular velocity
  Serial.print(",");
  Serial.print("GyroZ:");
  Serial.print(g.gyro.z);           // Z-axis angular velocity

  // End the current line of sensor output
  Serial.println("");

  // Wait 10 milliseconds before taking the next reading
  // (This limits the output rate to about 100 samples per second)
  delay(10);
}
