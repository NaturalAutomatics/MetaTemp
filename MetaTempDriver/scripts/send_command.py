"""
This module provides functionality to send commands to an Arduino over USB.
It includes a command-line interface for easy interaction.
"""

import time
import argparse
import serial


def send_command(ser, command):
    """
    Send a command to the Arduino and read the response.

    Args:
    ser (serial.Serial): The serial connection to the Arduino.
    command (str): The command to send.

    Returns:
    str: The response from the Arduino.
    """
    ser.write(f"{command}\n".encode())
    time.sleep(0.1)  # Small delay to ensure command is processed
    response = ser.readline().decode().strip()
    print(f"Arduino response: {response}")


def main():
    """
    Main function to parse command-line arguments and send commands to the Arduino.
    """
    parser = argparse.ArgumentParser(
        description="Send commands to Arduino over USB"
    )
    parser.add_argument("port", help="USB port (e.g., /dev/ttyUSB0 or COM3)")
    parser.add_argument("command", help="Command to send to Arduino")
    parser.add_argument(
        "args", nargs="*", help="Additional arguments for the command"
    )
    args = parser.parse_args()

    try:
        with serial.Serial(args.port, 9600, timeout=1) as ser:
            time.sleep(2)  # Wait for Arduino to reset
            full_command = f"{args.command} {' '.join(args.args)}".strip()
            print(f"Sending command: {full_command}")
            send_command(ser, full_command)

    except serial.SerialException as e:
        print(f"Error: {e}")
        print("Make sure the Arduino is connected and the port is correct.")


if __name__ == "__main__":
    main()
