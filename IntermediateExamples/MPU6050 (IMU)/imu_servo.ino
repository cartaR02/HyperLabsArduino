#include <Wire.h>                    // I2C bus support
#include <Adafruit_MPU6050.h>        // MPU6050 helper library
#include <Adafruit_Sensor.h>         // Adafruit sensor base types
#include <Servo.h>                   // UNO’s standard servo library

Adafruit_MPU6050 mpu;                // Create a global MPU6050 object
Servo servo;                         // Create a global Servo object

const int SERVO_PIN = 9;             // UNO digital pin for servo signal    // 180 / PI for radians → degrees

void setup() {
  Serial.begin(115200);              // Start serial for debugging (optional)
  Wire.begin();                      // Initialize I2C (A4=SDA, A5=SCL on UNO)

  if (!mpu.begin(0x68)) {            // Try to start the MPU6050 at I2C addr 0x68
    while (1) {                      // If not found, halt here and print a message
      Serial.println(F("MPU6050 not found"));
      delay(1000);
    }
  }

  // Optional but helpful sensor config (keeps code basic—no smoothing)
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G); // Set accel ±4g range
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);   // Low-pass bandwidth

  servo.attach(SERVO_PIN);            // Attach the servo signal to D9
  servo.write(90);                    // Center the servo at startup (approx 90°)
}

void loop() {
  sensors_event_t accel, gyro, temp;  // Structs to hold sensor readings
  mpu.getEvent(&accel, &gyro, &temp); // Read a single set of accel/gyro/temp

  // Read accelerometer components in m/s^2
  float ax = accel.acceleration.x;    // Accel X
  float ay = accel.acceleration.y;    // Accel Y
  float az = accel.acceleration.z;    // Accel Z

  // Compute "pitch" (front/back tilt) from accelerometer only
  // Using a standard formula that avoids needing smoothing
  float pitch = atan2(-ax, sqrt(ay*ay + az*az)) * RAD_TO_DEG; // degrees

  // Map pitch angle to a servo angle
  // Here we assume pitch in [-90, +90] maps to servo [0, 180]
  // Constrain first so extreme tilts don’t exceed limits
  float pitchClamped = constrain(pitch, -90.0, 90.0); // keep within expected range
  int servoAngle = map((int)pitchClamped, -90, 90, 0, 180); // linear mapping

  servo.write(servoAngle);            // Command the servo immediately (no smoothing)

  // Optional debug output so you can see numbers in Serial Monitor
  // Serial.print("pitch: "); Serial.print(pitch);
  // Serial.print("  angle: "); Serial.println(servoAngle);

  delay(10);                          // Small delay to reduce bus spam (not smoothing)
}
