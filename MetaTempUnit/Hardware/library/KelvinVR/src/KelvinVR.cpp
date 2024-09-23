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

void Kelvin::begin()
{
  Serial.begin(9600);
  fullPinSetup();
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

  // Set info:
  _isCooling = true;
  _currentIntensity = intensity;
}

void Kelvin::startHeating(int intensity)
{
  analogWrite(_peltierEnablePin, intensity);
  digitalWrite(_peltierIn1Pin, LOW);
  digitalWrite(_peltierIn2Pin, HIGH);

  // Set info:
  _isCooling = false;
  _currentIntensity = intensity;
}

void Kelvin::stopCooling()
{
  digitalWrite(_peltierEnablePin, LOW);
  digitalWrite(_peltierIn1Pin, LOW);
  digitalWrite(_peltierIn2Pin, LOW);
}

void Kelvin::stopHeating()
{
  digitalWrite(_peltierEnablePin, LOW);
  digitalWrite(_peltierIn1Pin, LOW);
  digitalWrite(_peltierIn2Pin, LOW);
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
  _ledState = true;
}

void Kelvin::ledOff()
{
  digitalWrite(ledPlus, LOW);
  digitalWrite(ledMinus, LOW);
  _fadeAmount = -_fadeAmount;
}

void Kelvin::blinkFront(int delayTime)
{
  digitalWrite(ledPlus, HIGH);
  delay(delayTime);
  digitalWrite(ledPlus, LOW);
  delay(delayTime);
}

void Kelvin::runThermalCycle(bool isCooling, int intensity, int durationSeconds)
{
  if (isCooling)
  {
    Serial.println("Starting cooling cycle...");
    startCooling(intensity);
  }
  else
  {
    Serial.println("Starting heating cycle...");
    startHeating(intensity);
  }

  ledOn(); // Turn on LED to indicate active cycle

  for (int i = 0; i < durationSeconds; i++)
  {
    Serial.print(isCooling ? "Cooling: " : "Heating: ");
    Serial.print(i + 1);
    Serial.println(" seconds");
    delay(1000);
  }

  ledOff(); // Turn off LED

  if (isCooling)
  {
    stopCooling();
  }
  else
  {
    stopHeating();
  }

  Serial.println("Thermal cycle completed.");
}

void Kelvin::sendStatus()
{
  Serial.println("KelvinVR Status:");
  Serial.println("----------------");
  Serial.print("Model: ");
  Serial.println(_modelName);
  Serial.print("Thermal State: ");
  if (_isCooling)
  {
    Serial.println("Cooling");
  }
  else if (_isHeating)
  {
    Serial.println("Heating");
  }
  else
  {
    Serial.println("Idle");
  }
  Serial.print("Current Intensity: ");
  Serial.println(_currentIntensity);
  Serial.print("LED State: ");
  Serial.println(_ledState ? "ON" : "OFF");
  Serial.println("----------------");
}

void Kelvin::processCommand(const String &command)
{
  if (command.startsWith("COOL"))
  {
    int intensity = 255;
    if (command.length() > 5)
    {
      intensity = command.substring(5).toInt();
    }
    startCooling(intensity);
    Serial.println("Cooling started");
  }
  else if (command.startsWith("HEAT"))
  {
    int intensity = 255;
    if (command.length() > 5)
    {
      intensity = command.substring(5).toInt();
    }
    startHeating(intensity);
    Serial.println("Heating started");
  }
  else if (command == "STOP")
  {
    stopThermalControl();
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
      runThermalCycle(isCooling, intensity, duration);
      Serial.println("Thermal cycle started");
    }
  }

  else if (command == "STATUS")
  {
    sendStatus();
  }

  else if (command == "STOPCOOL")
  {
    stopCooling();
    Serial.println("Cooling stopped");
  }
  else if (command == "STOPHEAT")
  {
    stopHeating();
    Serial.println("Heating stopped");
  }
  else if (command == "LED ON")
  {
    ledOn();
    Serial.println("LED turned on");
  }
  else if (command == "LED OFF")
  {
    ledOff();
    Serial.println("LED turned off");
  }
  else if (command.startsWith("LED BLINK"))
  {
    int delay = 1000;
    if (command.length() > 10)
    {
      delay = command.substring(10).toInt();
    }
    blinkFront(delay);
    Serial.println("LED blinking");
  }
  else if (command == "LED FADE BLUE")
  {
    fadeEffect(ledPlus);
    Serial.println("LED fading BLUE");
  }
  else if (command == "LED FADE GREEN")
  {
    fadeEffect(greenLed);
    Serial.println("LED fading GREEN");
  }
  else if (command == "LED FADE RED")
  {
    fadeEffect(redLed);
    Serial.println("LED fading GREEN");
  }
  else
  {
    Serial.println("Unknown command");
  }
}
