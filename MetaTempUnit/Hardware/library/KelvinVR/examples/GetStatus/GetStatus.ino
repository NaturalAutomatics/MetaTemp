/*
  KelvinVR Library - Get Status via USB

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
        kelvin.processCommand(command);
    }

    // Optionally, you can periodically send the status
    // static unsigned long lastStatusTime = 0;
    // if (millis() - lastStatusTime > 5000) // Send status every 5 seconds
    // {
    //     kelvin.sendStatus();
    //     lastStatusTime = millis();
    // }
}
