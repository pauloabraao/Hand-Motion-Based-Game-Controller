# Hand Motion-Based Game Controller

## Project Overview

This project introduces an innovative way to interact with games by translating hand movements into game controls. Using **Arduino**, the **MPU-6050 accelerometer and gyroscope sensor**, and **HC-06 Bluetooth module**, the controller detects hand motions and sends corresponding commands to a game via Bluetooth. On the computer side, a Python script interprets these commands to simulate keyboard inputs, creating an immersive gaming experience.

---

## Features

- Detects hand gestures using the **MPU-6050 sensor**.
- Sends commands wirelessly via **HC-06 Bluetooth module**.
- Simulates keyboard inputs using Python's **pynput** library.
- Supports two basic gestures:
  - **Hand Raised** → Simulates the **UP arrow key**.
  - **Hand Lowered** → Simulates the **DOWN arrow key**.

---

## Project Structure

```
Hand-Motion-Based-Game-Controller/
├── Arduino/
│   └── MPU-6050_HC06/
│       └── MPU-6050_HC06.ino    # Arduino sketch for sensor data processing and Bluetooth communication
├── Python/
│   └── main.py                  # Python script to interpret and map Bluetooth commands to keyboard inputs
├── README.md                    # Project documentation
```

---

## Getting Started

### Hardware Requirements

- Arduino Uno (or compatible board)
- MPU-6050 sensor module
- HC-06 Bluetooth module
- Connecting wires and breadboard
- Computer with Bluetooth capability

### Software Requirements

- Arduino IDE
- Python 3.x
- Required Python libraries:
  - `pyserial`
  - `pynput`

---

## Setup Instructions

### Arduino Setup

1. Connect the **MPU-6050 sensor** and **HC-06 Bluetooth module** to the Arduino:
   - **MPU-6050:**
     - VCC → 3.3V
     - GND → GND
     - SDA → A4
     - SCL → A5
   - **HC-06:**
     - RX → D10 (via voltage divider for 3.3V logic level)
     - TX → D11
     - VCC → 5V
     - GND → GND

2. Upload the Arduino sketch (`MPU-6050_HC06.ino`) using the Arduino IDE.

### Python Setup

1. Install the required Python libraries:
   ```bash
   pip install pyserial pynput
   ```

2. Update the `bluetooth_port` variable in `main.py` with your HC-06's COM port (check your system's device manager for the port).

3. Run the Python script:
   ```bash
   python main.py
   ```

---

## How It Works

1. **Arduino:**
   - The **MPU-6050** detects hand motion and calculates acceleration changes.
   - Gestures (like raising or lowering the hand) are identified by changes in the Y-axis acceleration.
   - Detected gestures are sent to the computer via the **HC-06 Bluetooth module**.

2. **Python Script:**
   - Receives Bluetooth commands (e.g., "UP", "DOWN").
   - Simulates corresponding keyboard inputs using the **pynput** library.

---

## Example Usage

1. Launch the Python script and ensure Bluetooth is connected.
2. Perform gestures:
   - Raise your hand to move **UP** in the game.
   - Lower your hand to move **DOWN** in the game.
3. Observe real-time control as your gestures are translated into game actions.

---

## Future Enhancements

- Add support for more gestures (e.g., left/right movement).
- Integrate support for additional games or applications.
- Use advanced sensors for more precise gesture recognition.
- Improve Bluetooth communication for faster response times.

---

## Troubleshooting

1. **No response from the Bluetooth module:**
   - Ensure the HC-06 module is powered and paired with the computer.
   - Check the COM port configuration in `main.py`.

2. **Incorrect gesture detection:**
   - Adjust the `threshold` value in the Arduino sketch to fine-tune sensitivity.

3. **Python script fails to start:**
   - Verify that the required libraries are installed.
   - Confirm the correct COM port is being used.

---

## License

This project is licensed under the MIT License. Feel free to use, modify, and distribute this code as needed.

---

Enjoy your immersive gaming experience! 🎮