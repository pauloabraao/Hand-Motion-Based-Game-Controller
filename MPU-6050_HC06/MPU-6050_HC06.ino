#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SoftwareSerial.h>

// Initialize the MPU6050 sensor
Adafruit_MPU6050 mpu;

// Define SoftwareSerial pins
SoftwareSerial bluetoothSerial(10, 11); // RX, TX pins

// Thresholds for gesture detection
const float accelThreshold = 3.0;   // Acceleration change threshold (m/s^2)
const float gyroThreshold = 50.0;  // Gyroscope Z-axis threshold (°/s)
const unsigned long gestureCooldown = 300; // Minimum delay between gesture detections (ms)

// Previous sensor readings
float prevAx = 0, prevAy = 0, prevAz = 0;
float prevGz = 0;

// Timing for gesture cooldown
unsigned long lastGestureTime = 0;

// Thresholds for each axis
float xPosThreshold = 2.0;
float xNegThreshold = 2.0;
float yPosThreshold = 2.5;
float yNegThreshold = 2.5;

void setup() {
  Serial.begin(9600);
  bluetoothSerial.begin(9600);

  if (!mpu.begin()) {
    Serial.println("Failed to initialize MPU6050! Check connections.");
    while (1) delay(1000);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  // Calibration during setup
  calibrateThresholds();
}

unsigned long lastUpdate = 0;
const unsigned long interval = 50; // Sampling interval in ms

void loop() {
  unsigned long currentT = millis();
  if (currentT - lastUpdate >= interval) {
    lastUpdate = currentT;

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    unsigned long currentTime = millis();

    // Detect Y-axis gestures
    if ((a.acceleration.y > yPosThreshold || a.acceleration.y < -yNegThreshold) &&
        currentTime - lastGestureTime >= gestureCooldown) {
      if (a.acceleration.y > 0) {
        Serial.println('D');
        bluetoothSerial.println('D');
      } else {
        Serial.println('U');
        bluetoothSerial.println('U');
      }
      lastGestureTime = currentTime;
    }

    // Detect X-axis gestures
    if ((a.acceleration.x > xPosThreshold || a.acceleration.x < -xNegThreshold) &&
        currentTime - lastGestureTime >= gestureCooldown) {
      if (a.acceleration.x > 0) {
        Serial.println('R');
        bluetoothSerial.println('R');
      } else {
        Serial.println('L');
        bluetoothSerial.println('L');
      }
      lastGestureTime = currentTime;
    }
  }


  //delay(50);
}

void calibrateThresholds() {
  Serial.println("Calibrating thresholds...");
  float xMax = -1000, xMin = 1000, yMax = -1000, yMin = 1000;

  unsigned long startTime = millis();
  while (millis() - startTime < 15000) { // Collect data for 5 seconds
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    xMax = max(xMax, a.acceleration.x);
    xMin = min(xMin, a.acceleration.x);
    yMax = max(yMax, a.acceleration.y);
    yMin = min(yMin, a.acceleration.y);

    delay(50); // Sampling interval
  }

  xPosThreshold = xMax * 0.8 ; // Set thresholds as 80% of peak values
  xNegThreshold = abs(xMin) * 0.8;
  yPosThreshold = yMax * 0.8;
  yNegThreshold = abs(yMin) * 0.8;

  Serial.println("Calibration complete!");
  Serial.print("X+: "); Serial.println(xPosThreshold);
  Serial.print("X-: "); Serial.println(xNegThreshold);
  Serial.print("Y+: "); Serial.println(yPosThreshold);
  Serial.print("Y-: "); Serial.println(yNegThreshold);
}
