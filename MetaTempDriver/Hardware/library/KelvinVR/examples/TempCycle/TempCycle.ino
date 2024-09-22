/*
  KelvinVR Library - Peltier Control Example
  This sketch demonstrates the use of the cooling and heating Cycle

  This example demonstrates how to use the KelvinVR library to
  control a Peltier module using the L293D driver.

      Arduino Mega 2560
    ___________________
   |  ___________  USB |
   | |           |     |
   | |           |     |
   | |           |     |
   | |           |     |
   | |___________|     |
   |                   |
   |                   |
   |                   |
   |                   |
   |                   |
   |                   |
   |                   |
 --+---+---+---+---+---+---+---+---+---+---+---+
   | D | D | D | D | D | D | D | . | . | . | D |
   | 5 | 6 | 7 | 8 | 9 | 1 | 1 |   |   |   | 3 |
   |   |   |   |   |   | 0 | 1 |   |   |   | 7 |
 --+---+---+---+---+---+---+---+---+---+---+---+
     |   |   |   |   |   |   |               |
     |   |   |   |   |   |   |               |
     |   |   |   |   |   |   |               |
     |   |   |   |   |   |   |               Buzzer
     |   |   |   |   |   |   |
     |   |   |   |   |   |   +-- Red LED
     |   |   |   |   |   |
     |   |   |   |   |   +-- Green LED
     |   |   |   |   |
     |   |   |   |   +-- LED+ (Fading LED)
     |   |   |   |
     |   |   |   +-- LED-
     |   |   |
     |   |   +-- L293D Enable (Peltier)
     |   |
     |   +-- L293D Input 1 (Peltier)
     |
     +-- L293D Input 2 (Peltier)

Note: Pins 5, 6, 9, 10, and 11 support PWM for LED brightness and motor control

*/

#include <KelvinVR.h>

KelvinVR kelvin;

void setup()
{
    Serial.begin(9600);
    kelvin.begin();
}

void loop()
{
    // Run a cooling cycle at 78% intensity for 30 seconds
    kelvin.runThermalCycle(true, 200, 30);

    delay(5000); // Wait for 5 seconds

    // Run a heating cycle at 50% intensity for 20 seconds
    kelvin.runThermalCycle(false, 128, 20);

    delay(10000); // Wait for 10 seconds before repeating
}
