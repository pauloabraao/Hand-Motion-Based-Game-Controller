import serial
from pynput.keyboard import Controller, Key

# Initialize serial communication with the HC-06
bluetooth_port = 'COM3'  # Replace with your HC-06 COM port
baud_rate = 9600

# Keyboard controller
keyboard = Controller()

def main():
    try:
        # Open serial port
        with serial.Serial(bluetooth_port, baud_rate, timeout=1) as ser:
            print("Connected to HC-06 Bluetooth module.")
            while True:
                # Read data from Bluetooth
                if ser.in_waiting > 0:
                    try:
                        # Attempt to decode incoming data
                        data = ser.readline().decode('utf-8', errors='ignore').strip()
                        print(f"Received: {data}")
                        
                        # Interpret and emulate keyboard actions
                        if data == "Hand Raised":
                            print("Pressing UP arrow key")
                            keyboard.press(Key.up)
                            keyboard.release(Key.up)
                        elif data == "Hand Lowered":
                            print("Pressing DOWN arrow key")
                            keyboard.press(Key.down)
                            keyboard.release(Key.down)
                        else:
                            print(f"Unrecognized data: {data}")
                    except UnicodeDecodeError as e:
                        print(f"Decoding error: {e}")
    except serial.SerialException as e:
        print(f"Serial exception: {e}")
    except KeyboardInterrupt:
        print("Program interrupted. Exiting...")

if __name__ == "__main__":
    main()
