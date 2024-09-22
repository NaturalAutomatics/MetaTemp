/*
  KelvinVR Mk1-Alpha test module: Arduino Mega Original 2560
  Main class for KelvinVR Library

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
   | D | D | D | D | D | D | . | . | . | . | D |
   | 8 | 9 | 1 | 1 | 1 | 1 |   |   |   |   | 3 |
   |   |   | 0 | 1 | 2 | 3 |   |   |   |   | 7 |
 --+---+---+---+---+---+---+---+---+---+---+---+
   |   |   |   |   |   |               |
   |   |   |   |   |   |               |
   |   |   |   |   |   |               |
   |   |   |   |   |   |               Buzzer
   |   |   |   |   |   |
   |   |   |   |   |   +-- Not used
   |   |   |   |   |
   |   |   |   |   +-- Not used
   |   |   |   |
   |   |   |   +-- Red LED
   |   |   |
   |   |   +-- Green LED
   |   |
   |   +-- LED+ (Fading LED Blue)
   |
   +-- LED- (Fading LED Blue)

Note: Pins 9, 10, and 11 support PWM for LED brightness control



*/
#define MIN_BRIGHTNESS 0
#define MAX_BRIGHTNESS 255

#include <Arduino.h>
#include "KelvinVR.h"

Kelvin::Kelvin(const String &modelName)
{
  _modelName = modelName;
}

void Kelvin::fullPinSetup()
{
  for (int i = 0; i < sizeof(this->_pinsOutput) / sizeof(this->_pinsOutput[0]); i++)
  {
    pinMode(this->_pinsOutput[i], OUTPUT);
  }

  // Setup Peltier control pins
  pinMode(_peltierEnablePin, OUTPUT);
  pinMode(_peltierIn1Pin, OUTPUT);
  pinMode(_peltierIn2Pin, OUTPUT);

  // Initially stop the Peltier
  stopThermalControl();
}

void Kelvin::startCooling(int intensity)
{
  analogWrite(_peltierEnablePin, intensity);
  digitalWrite(_peltierIn1Pin, HIGH);
  digitalWrite(_peltierIn2Pin, LOW);
}

void Kelvin::startHeating(int intensity)
{
  analogWrite(_peltierEnablePin, intensity);
  digitalWrite(_peltierIn1Pin, LOW);
  digitalWrite(_peltierIn2Pin, HIGH);
}

void Kelvin::stopThermalControl()
{
  digitalWrite(_peltierEnablePin, LOW);
  digitalWrite(_peltierIn1Pin, LOW);
  digitalWrite(_peltierIn2Pin, LOW);
}

void Kelvin::blinkLed(int ledPin)
{
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}

void Kelvin::fadeEffect(int led)
{
  // set the brightness of pin 9:
  analogWrite(led, _brightness);

  // change the brightness for next time through the loop:
  _brightness = _brightness + _fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (_brightness <= MIN_BRIGHTNESS || _brightness >= MAX_BRIGHTNESS)
  {
    _fadeAmount = -_fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}

void Kelvin::ledOn()
{
  digitalWrite(ledPlus, HIGH);
  digitalWrite(ledMinus, LOW);
}

void Kelvin::ledOff()
{
  digitalWrite(ledPlus, LOW);
  digitalWrite(ledMinus, LOW);
}

void Kelvin::blinkFront(int delayTime)
{
  digitalWrite(ledPlus, HIGH);
  delay(delayTime);
  digitalWrite(ledPlus, LOW);
  delay(delayTime);
}
