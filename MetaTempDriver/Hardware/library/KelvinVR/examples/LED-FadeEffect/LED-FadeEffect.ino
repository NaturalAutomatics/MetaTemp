/*
  KelvinVR Library - LED Fade Effect Example
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

*/

#include <KelvinVR.h>

// Create a Kelvin object
Kelvin kelvin("Mk1-Alpha");

// Define the LED pin
const int ledPin = 9; // Assuming ledPlus is connected to pin 9

void setup()
{
    // Initialize serial communication
    Serial.begin(9600);

    // Initialize the Kelvin object
    kelvin.fullPinSetup();

    Serial.println("KelvinVR LED Fade Effect Example");
}

void loop()
{
    // Call the fadeEffect method in a loop to create a continuous fading effect
    kelvin.fadeEffect(ledPin);

    // Print the current brightness value (optional, for debugging)
    Serial.println(kelvin.getBrightness());
}
