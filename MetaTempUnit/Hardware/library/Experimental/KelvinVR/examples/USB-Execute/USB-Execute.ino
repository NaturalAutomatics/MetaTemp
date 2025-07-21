/*
  KelvinVR Library - USB Commands
  This sketch demonstrates the use of the fadeEffect method
  to create a smooth fading effect on an LED.

      Arduino Uno
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
 --+---+---+---+---+---+--
   | D | D | D | D | D |
   | 1 | 1 | 1 | 9 | 8 |
   | 3 | 2 | 1 |   |   |
 --+---+---+---+---+---+--
     |   |   |   |   |
     |   |   |   |   |
     |   |   |   |   |
     |   |   |   |   Ground
     |   |   |   |
     |   |   |   LED+ (Fading LED)
     |   |   |
     |   |   Red LED
     |   |
     |   Green LED
     |
     Buzzer

Note: Pin 9 is used for PWM to control LED brightness

==== ALL USB COMMANDS LIST: =====
Start Cooling: Command: "COOL intensity" Example: "COOL 200" (to start cooling at intensity 200) Default: "COOL" (will use default intensity of 255)

Start Heating: Command: "HEAT intensity" Example: "HEAT 180" (to start heating at intensity 180) Default: "HEAT" (will use default intensity of 255)

Stop Thermal Control: Command: "STOP"

Run Thermal Cycle: Command: "CYCLE cooling/heating intensity duration" Example: "CYCLE COOL 200 30" (to run a cooling cycle at intensity 200 for 30 seconds) Example: "CYCLE HEAT 180 45" (to run a heating cycle at intensity 180 for 45 seconds)

Stop Cooling: Command: "STOPCOOL"

Stop Heating: Command: "STOPHEAT"

LED Control: Command: "LED ON" (to turn the LED on) Command: "LED OFF" (to turn the LED off) Command: "LED BLINK delay" (to blink the LED with a specific delay) Command: "LED FADE" (to create a fade effect)
*/

#include "KelvinVR.h"

Kelvin kelvin("Mk1-Alpha"); // Create a Kelvin object with a model name

void setup()
{
    Serial.begin(9600); // Initialize serial communication at 9600 baud
    kelvin.begin();     // Initialize the Kelvin object
}

void loop()
{
    if (Serial.available())
    {
        String command = Serial.readStringUntil('\n'); // Read the incoming command
        command.trim();                                // Remove any leading or trailing whitespace

        if (command.length() > 0)
        {

            kelvin.processCommand(command); // Process the command using the Kelvin object
        }
    }

    // You can add any other continuous operations here if needed
}
