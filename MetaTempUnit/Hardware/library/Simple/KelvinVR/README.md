# KelvinVR Library
Arduino library for precise control of Peltier elements using L293D motor driver

![L293D Peltier Control](https://github.com/yourusername/KelvinVR/raw/main/assets/circuit_diagram.png)  
*(Include a circuit diagram Fritzing file in your repository)*

## Features
- 📶 Bidirectional control (heating/cooling) for two Peltier elements
- 🎚️ Analog PWM control (0-100% power levels)
- 🛡️ Shoot-through protection during direction changes
- 🔌 Hardware-optimized for L293D motor driver
- 📡 Simple serial command interface
- 🔥 Thermal protection framework (user-extendable)

## Installation
1. Download the latest release as ZIP
2. In Arduino IDE:  
   **Sketch → Include Library → Add .ZIP Library...**
3. Select the downloaded ZIP file
4. Restart Arduino IDE

## Hardware Setup
**L293D Connections:**
| L293D Pin | Arduino Mega Pin | Function          |
|-----------|------------------|-------------------|
| EN1       | 9 (PWM)          | Peltier 1 Enable  |
| IN1       | 8                | Peltier 1 Phase   |
| IN2       | 7                | Peltier 1 Phase   |
| EN2       | 10 (PWM)         | Peltier 2 Enable  |
| IN3       | 12               | Peltier 2 Phase   |
| IN4       | 11               | Peltier 2 Phase   |

**Power Requirements:**
- Logic voltage (VCC1): 5V from Arduino
- Motor voltage (VCC2): 7-12V external supply (match Peltier rating)
- Common ground between Arduino and power supply

## Basic Usage
```cpp
#include <KelvinVR.h>

// Initialize Peltiers (EN, IN1, IN2)
KelvinVR peltier1(9, 8, 7);  // Channel 1
KelvinVR peltier2(10, 12, 11); // Channel 2

void setup() {
  Serial.begin(9600);
  peltier1.setPower(0); // Initialize off
  peltier2.setPower(0);
}

void loop() {
  // Your control logic here
}