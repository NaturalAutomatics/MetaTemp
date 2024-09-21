/*
  Main class for KelvinVR module
*/

#ifndef KELVIN_VR_H
#define KELVIN_VR_H

#if defined(ESP32)
#include "KelvinVRESP32.hpp"
typedef KelvinVRESP32 KelvinVR;
#elif defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
#include "KelvinVRArduino.hpp"
typedef KelvinVRArduino KelvinVR;
#else
#error "Unsupported platform"
#endif

#endif

class Kelvin
{
public:
	Kelvin();
	Kelvin(modelName);
	void begin();
	void blinkLed(int ledPin);
	void ledOff();
	void fullPinSetup();

protected:
	string _modelName;

	int buzzer = 37;
	int greenLed = 10;
	int redLed = 11;
	int ledPlus = 9;
	int ledMinus = 8;

	int _pinsOutput[] = {buzzer, greenLed, redLed, ledPlus, ledMinus};

	int _brightness = 0; // how bright the LED is
	int _fadeAmount = 5; // how many points to fade the LED

	int _boadRate;
};
