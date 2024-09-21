/*
  Main class for KelvinVR Library
*/
// Ensure this library description is only included once
#ifndef KELVIN_VR_H
#define KELVIN_VR_H

#include <Arduino.h>

class Kelvin
{
public:
	Kelvin();
	Kelvin(const String &modelName);
	void begin();
	void fullPinSetup();
	void blinkLed(int ledPin);
	void fadeEffect(int led);
	void ledOn(); // Add this line
	void ledOff();
	void blinkFront(int delayTime); // Add this line if it's not already there
	int getBrightness() const { return _brightness; }

protected:
	String _modelName;

	int buzzer = 37;
	int greenLed = 10;
	int redLed = 11;
	int ledPlus = 9;
	int ledMinus = 8;

	int _pinsOutput[5];

	int _brightness = 0;
	int _fadeAmount = 5;

	int _boadRate;
};

#endif
