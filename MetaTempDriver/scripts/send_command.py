import serial
import time
import argparse

def send_command(ser, command):
    ser.write((command + "\n").encode())
    time.sleep(0.1)  # Small delay to ensure command is processed
    response = ser.readline().decode().strip()
    print("Arduino response: {}".format(response))

def main():
    parser = argparse.ArgumentParser(description="Send commands to Arduino over USB")
    parser.add_argument("port", help="USB port (e.g., /dev/ttyUSB0 or COM3)")
    parser.add_argument("command", help="Command to send to Arduino")
    parser.add_argument("args", nargs="*", help="Additional arguments for the command")
    args = parser.parse_args()

    try:
        with serial.Serial(args.port, 9600, timeout=1) as ser:
            time.sleep(2)  # Wait for Arduino to reset
            
            full_command = "{} {}".format(args.command, " ".join(args.args)).strip()
            print("Sending command: {}".format(full_command))
            send_command(ser, full_command)

    except serial.SerialException as e:
        print("Error: {}".format(e))
        print("Make sure the Arduino is connected and the port is correct.")

if __name__ == "__main__":
    main()
