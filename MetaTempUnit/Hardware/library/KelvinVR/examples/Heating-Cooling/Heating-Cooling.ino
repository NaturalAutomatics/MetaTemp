/*
  KelvinVR Library - Peltier Control Example
  This sketch demonstrates the use of the cooling and heating methods
  to control a Peltier module using the L293D driver.

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

Kelvin kelvin("Mk1-Alpha");

const int coolingDuration = 10000; // 10 seconds
const int heatingDuration = 10000; // 10 seconds
const int idleDuration = 5000;     // 5 seconds

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    kelvin.fullPinSetup();

    Serial.println("KelvinVR Peltier Control Example");
    Serial.println("================================");
}

void loop()
{
    // Cooling cycle
    Serial.println("Starting cooling cycle...");
    kelvin.startCooling(200); // Start cooling at about 78% intensity
    kelvin.ledOn();           // Turn on LED to indicate active cooling
    for (int i = 0; i < coolingDuration / 1000; i++)
    {
        Serial.print("Cooling: ");
        Serial.print(i + 1);
        Serial.println(" seconds");
        delay(1000);
    }
    kelvin.ledOff(); // Turn off LED

    // Idle cycle
    Serial.println("Stopping thermal control (Idle)...");
    kelvin.stopThermalControl();
    for (int i = 0; i < idleDuration / 1000; i++)
    {
        Serial.print("Idle: ");
        Serial.print(i + 1);
        Serial.println(" seconds");
        delay(1000);
    }

    // Heating cycle
    Serial.println("Starting heating cycle...");
    kelvin.startHeating(200); // Start heating at about 78% intensity
    kelvin.ledOn();           // Turn on LED to indicate active heating
    for (int i = 0; i < heatingDuration / 1000; i++)
    {
        Serial.print("Heating: ");
        Serial.print(i + 1);
        Serial.println(" seconds");
        delay(1000);
    }
    kelvin.ledOff(); // Turn off LED

    // Idle cycle
    Serial.println("Stopping thermal control (Idle)...");
    kelvin.stopThermalControl();
    for (int i = 0; i < idleDuration / 1000; i++)
    {
        Serial.print("Idle: ");
        Serial.print(i + 1);
        Serial.println(" seconds");
        delay(1000);
    }

    Serial.println("Cycle complete. Restarting...");
    Serial.println();
}
