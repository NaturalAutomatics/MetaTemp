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

#define DEFAULT_BAUD_RATE 115200

#include <Arduino.h>

class Kelvin
{

public:
	Kelvin();
	Kelvin(const String &modelName);
	void begin(unsigned long bitRate = DEFAULT_BAUD_RATE);
	void fullPinSetup();
	void blinkLed(int ledPin);
	void fadeEffect(uint8_t led);
	void ledOn();
	void ledOff();
	void blinkFront(int delayTime);
	uint8_t getBrightness() const { return _brightness; }

	// New methods for Peltier control
	void startCooling(uint8_t intensity = 255);
	void startHeating(uint8_t intensity = 255);
	void stopThermalControl();
	void runThermalCycle(bool isCooling, uint8_t intensity, int durationSeconds);
	void stopCooling();
	void stopHeating();

	void ledAction(const String &command);

	// For USB:
	void processCommand(const String &command);
	void sendStatus();

	void printHelp();

	// Main loop:
	void runFirmware(); // For Mk 1 Alpha testing

protected:
	String _modelName;

	static const uint8_t buzzer = 37;
	static const uint8_t greenLed = 10;
	static const uint8_t redLed = 11;
	static const uint8_t ledPlus = 9; // Blue LED
	static const uint8_t ledMinus = 8;

	// New pins for L293D control
	static const uint8_t _peltierEnablePin = 7;
	static const uint8_t _peltierIn1Pin = 6;
	static const uint8_t _peltierIn2Pin = 5;

	// int _pinsOutput[5];

	uint8_t _brightness = 0;
	uint8_t _fadeAmount = 5;

	// Info to get about module:

	bool _isCooling = false;
	bool _isHeating = false;
	int _currentIntensity = 0;
	bool _ledState = false;

	bool _cycleInProgress = false;
};

#endif
