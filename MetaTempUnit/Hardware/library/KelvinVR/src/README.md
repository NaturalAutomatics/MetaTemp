# KelvinVR Library

KelvinVR is a library for Arduino that provides thermal control and LED manipulation functionalities. It's designed for use with the KelvinVR Mk1-Alpha hardware.

## Installation

[Provide instructions on how to install the library]

## Usage

Include the library in your Arduino sketch:

```cpp
#include <KelvinVR.h>

Kelvin kelvin("Mk1-Alpha");

void setup() {
  kelvin.begin();
}

void loop() {
  // Your code here
  kelvin.runFirmware();
}
```

## Methods

### Initialization
- `begin(int baudRate = 115200)`: Initializes the KelvinVR system. Default baud rate is 115200 if not specified.

### Thermal Control
- `startCooling(int intensity)`: Starts cooling at the specified intensity (0-255).
- `startHeating(int intensity)`: Starts heating at the specified intensity (0-255).
- `stopThermalControl()`: Stops all thermal control operations.
- `stopCooling()`: Stops the cooling operation.
- `stopHeating()`: Stops the heating operation.
- `runThermalCycle(bool isCooling, int intensity, int duration)`: Runs a thermal cycle with specified parameters.

### LED Control
- `ledOn()`: Turns on the LED.
- `ledOff()`: Turns off the LED.
- `blinkFront(int delay)`: Makes the LED blink with the specified delay.
- `fadeEffect(int ledPin)`: Applies a fade effect to the specified LED.

### System Information
- `sendStatus()`: Sends the current status of the system.
- `printHelp()`: Prints help information about available commands.

### Command Processing
- `processCommand(const String &command)`: Processes incoming commands. Supported commands include:
  - `COOL intensity`
  - `HEAT intensity`
  - `STOP`
  - `CYCLE COOL/HEAT intensity duration`
  - `STATUS`
  - `STOPCOOL`
  - `STOPHEAT`
  - `HELP`
  - `LED ON`
  - `LED OFF`
  - `LED BLINK delay`
  - `LED FADE BLUE/GREEN/RED`


## Example
```cpp 
#include <KelvinVR.h>

Kelvin kelvin;

void setup() {
  kelvin.begin(115200);  // Initialize with 115200 baud rate
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    if (command.length() > 0) {
      kelvin.processCommand(command);
    }
  }
}
```


## Notes
The default baud rate for serial communication is 9600.

Intensity values for heating and cooling range from 0 to 255.

Always ensure proper power supply and connections before operating thermal control functions.

## License
Include license information here

## Contributing
Provide information on how to contribute to the project

## Support
Provide contact information or links for support