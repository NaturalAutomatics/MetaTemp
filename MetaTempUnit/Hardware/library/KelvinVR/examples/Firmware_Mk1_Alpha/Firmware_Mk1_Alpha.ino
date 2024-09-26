/*
  KelvinVR Library - Firmware for Mk1 Alpha

    Platfor: Arduino Mega 2560

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
Run command: HELP
*/

#include "KelvinVR.h"

Kelvin kelvin("Mk1-Alpha"); // Create a Kelvin object with a model name

void setup()
{
    kelvin.begin(); // Initialize the Kelvin with default settings
}

void loop()
{
    kelvin.runFirmware(); // Running firmware for Mk 1 Alpha Unit
}
