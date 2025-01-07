import serial
import time
from pynput.keyboard import Controller, Key

# Initialize serial communication with the HC-06
bluetooth_port = 'COM5'  # Replace with your HC-06 COM port
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
                        if data == 'UP':
                            print("Pressing UP arrow key") 
                            keyboard.press(Key.up)
                            keyboard.release(Key.up)
                        
                        elif data == 'DOWN':
                            print("Pressing DOWN arrow key")
                            keyboard.press(Key.down)
                            keyboard.release(Key.down)
                        
                        elif data == 'LEFT':
                            print("Pressing LEFT arrow key")
                            keyboard.press(Key.left)
                            time.sleep(0.2)
                            keyboard.release(Key.left)
                        elif data == 'RIGHT':
                            print("Pressing RIGHT arrow key")
                            keyboard.press(Key.right)
                            time.sleep(0.2)
                            keyboard.release(Key.right)

                        elif data == 'TWIST':
                            print("Pressing TWIST arrow key")
                            keyboard.press(Key.backspace)
                            keyboard.release(Key.backspace)
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
