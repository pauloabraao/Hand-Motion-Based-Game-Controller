#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SoftwareSerial.h>

// Initialize the MPU6050 sensor
Adafruit_MPU6050 mpu;

// Define SoftwareSerial pins
SoftwareSerial bluetoothSerial(10, 11); // RX, TX pins

// Thresholds for gesture detection
const float accelThreshold = 2.0;   // Acceleration change threshold (m/s^2)
const float gyroThreshold = 50.0;  // Gyroscope Z-axis threshold (°/s)
const unsigned long gestureCooldown = 2000; // Minimum delay between gesture detections (ms)

// Previous sensor readings
float prevAx = 0, prevAy = 0, prevAz = 0;
float prevGz = 0;

// Timing for gesture cooldown
unsigned long lastGestureTime = 0;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(9600);

  // Initialize Bluetooth Serial
  bluetoothSerial.begin(9600); // HC-06 default baud rate

  // Initialize MPU6050 sensor
  if (!mpu.begin()) {
    Serial.println("Failed to initialize MPU6050! Check connections.");
    while (1) {
      delay(1000); // Indicate failure
    }
  }

  // Configure MPU6050 ranges
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  Serial.println("MPU6050 Initialized");
}

void loop() {
  // Get sensor events
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  unsigned long currentTime = millis();

  // UP and DOWN detection using Y-axis acceleration
  if (abs(a.acceleration.y - prevAy) > accelThreshold) {
    if (currentTime - lastGestureTime >= gestureCooldown) {
      if (a.acceleration.y > prevAy) {
        Serial.println("DOWN");
        bluetoothSerial.println("DOWN");
      } else {
        Serial.println("UP");
        bluetoothSerial.println("UP");
      }
      lastGestureTime = currentTime; // Reset cooldown
    }
  }

  // RIGHT and LEFT detection using X-axis acceleration
  if (abs(a.acceleration.x - prevAx) > accelThreshold) {
    if (currentTime - lastGestureTime >= gestureCooldown) {
      if (a.acceleration.x > prevAx) {
        Serial.println("RIGHT");
        bluetoothSerial.println("RIGHT");
      } else {
        Serial.println("LEFT");
        bluetoothSerial.println("LEFT");
      }
      lastGestureTime = currentTime; // Reset cooldown
    }
  }

  // HAND TWIST detection using Z-axis gyroscope
  if (abs(g.gyro.z - prevGz) > gyroThreshold) {
    if (currentTime - lastGestureTime >= gestureCooldown) {
      Serial.println("TWIST");
      bluetoothSerial.println("TWIST");
      lastGestureTime = currentTime; // Reset cooldown
    }
  }

  // Store current sensor values for comparison in the next loop
  prevAx = a.acceleration.x;
  prevAy = a.acceleration.y;
  prevAz = a.acceleration.z;
  prevGz = g.gyro.z;

  delay(50); // Short delay for loop stability (adjustable)
}
