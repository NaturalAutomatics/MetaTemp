/*
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
// Ensure this library description is only included once

#ifndef KELVIN_VR_H
#define KELVIN_VR_H

#include <Arduino.h>

class Kelvin
{
public:
	Kelvin();
	Kelvin(const String &modelName);
	void begin(int bitRate = 9600);
	void fullPinSetup();
	void blinkLed(int ledPin);
	void fadeEffect(int led);
	void ledOn();
	void ledOff();
	void blinkFront(int delayTime);
	int getBrightness() const { return _brightness; }

	// New methods for Peltier control
	void startCooling(int intensity = 255);
	void startHeating(int intensity = 255);
	void stopThermalControl();
	void runThermalCycle(bool isCooling, int intensity, int durationSeconds);
	void stopCooling();
	void stopHeating();

	// For USB:
	void processCommand(const String &command);
	void sendStatus();

	void printHelp();

	// Main loop:
	void runFirmware(); // For Mk 1 Alpha testing
						// void runFirmware(); // For Mk 1 Beta testing
						// void runFirmware(int boardRate);

protected:
	String _modelName;

	int buzzer = 37;
	int greenLed = 10;
	int redLed = 11;
	int ledPlus = 9; // Blue LED
	int ledMinus = 8;

	// New pins for L293D control
	int _peltierEnablePin = 7;
	int _peltierIn1Pin = 6;
	int _peltierIn2Pin = 5;

	int _pinsOutput[5];

	int _brightness = 0;
	int _fadeAmount = 5;

	int _boadRate;

	// Info to get about module:

	bool _isCooling = false;
	bool _isHeating = false;
	int _currentIntensity = 0;
	bool _ledState = false;
};

#endif
