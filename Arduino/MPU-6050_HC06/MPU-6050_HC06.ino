#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SoftwareSerial.h>

// Initialize the MPU6050 sensor
Adafruit_MPU6050 mpu;

// Define SoftwareSerial pins
SoftwareSerial bluetoothSerial(10, 11); // RX, TX pins

float prev_ax = 0, prev_ay = 0, prev_az = 0;
float threshold = 2.0; // Acceleration change threshold for gesture detection

void setup() {
  // Initialize Serial for debugging
  Serial.begin(9600);

  // Initialize Bluetooth Serial
  bluetoothSerial.begin(9600); // HC-06 default baud rate
  Serial.println("Bluetooth Module initialized!");

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // Configure MPU6050 ranges
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  Serial.println("MPU6050 Initialized and configured.");
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Gesture detection logic
  if (abs(a.acceleration.y - prev_ay) > threshold) {
    if (a.acceleration.y > prev_ay) {
      Serial.println("Hand Raised");
      bluetoothSerial.println("UP"); // Send "UP" to Bluetooth
    } else {
      Serial.println("Hand Lowered");
      bluetoothSerial.println("DOWN"); // Send "DOWN" to Bluetooth
    }
  }

  // Store current acceleration for comparison in the next loop
  prev_ax = a.acceleration.x;
  prev_ay = a.acceleration.y;
  prev_az = a.acceleration.z;

  delay(200); // Adjust for gesture timing
}
