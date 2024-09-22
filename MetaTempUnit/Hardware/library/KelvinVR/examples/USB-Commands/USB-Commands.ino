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

#include "Kelvin.h"

Kelvin kelvin("Mk1-Alpha");

void setup()
{
    Serial.begin(9600);
    kelvin.begin();
    kelvin.fullPinSetup();
}

void loop()
{
    if (Serial.available())
    {
        String command = Serial.readStringUntil('\n');
        command.trim();

        if (command.startsWith("COOL"))
        {
            int intensity = 255;
            if (command.length() > 5)
            {
                intensity = command.substring(5).toInt();
            }
            kelvin.startCooling(intensity);
            Serial.println("Cooling started");
        }
        else if (command.startsWith("HEAT"))
        {
            int intensity = 255;
            if (command.length() > 5)
            {
                intensity = command.substring(5).toInt();
            }
            kelvin.startHeating(intensity);
            Serial.println("Heating started");
        }
        else if (command == "STOP")
        {
            kelvin.stopThermalControl();
            Serial.println("Thermal control stopped");
        }
        else if (command.startsWith("CYCLE"))
        {
            String params[4];
            int paramCount = 0;
            int lastIndex = 0;
            for (int i = 0; i < command.length(); i++)
            {
                if (command.charAt(i) == ' ' || i == command.length() - 1)
                {
                    params[paramCount++] = command.substring(lastIndex, i == command.length() - 1 ? i + 1 : i);
                    lastIndex = i + 1;
                }
            }
            if (paramCount == 4)
            {
                bool isCooling = params[1] == "COOL";
                int intensity = params[2].toInt();
                int duration = params[3].toInt();
                kelvin.runThermalCycle(isCooling, intensity, duration);
                Serial.println("Thermal cycle started");
            }
        }
        else if (command == "STOPCOOL")
        {
            kelvin.stopCooling();
            Serial.println("Cooling stopped");
        }
        else if (command == "STOPHEAT")
        {
            kelvin.stopHeating();
            Serial.println("Heating stopped");
        }
        else if (command == "LED ON")
        {
            kelvin.ledOn();
            Serial.println("LED turned on");
        }
        else if (command == "LED OFF")
        {
            kelvin.ledOff();
            Serial.println("LED turned off");
        }
        else if (command.startsWith("LED BLINK"))
        {
            int delay = 1000;
            if (command.length() > 10)
            {
                delay = command.substring(10).toInt();
            }
            kelvin.blinkFront(delay);
            Serial.println("LED blinking");
        }
        else if (command == "LED FADE")
        {
            kelvin.fadeEffect(kelvin.getBrightness());
            Serial.println("LED fading");
        }
        else
        {
            Serial.println("Unknown command");
        }
    }
}
