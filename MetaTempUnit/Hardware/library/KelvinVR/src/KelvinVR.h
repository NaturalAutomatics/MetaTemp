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

#define MIN_BRIGHTNESS 0
#define MAX_BRIGHTNESS 255
#define MAX_INTENSITY 255
#define DEFAULT_BLINK_TIME 1000
#define FADE_DELAY_TIME 30
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

	void continueCooling(uint8_t intensity);
	void continueHeating(uint8_t intensity);

	void ledAction(const String &command);

	// For USB:
	void processCommand(const String &command);
	void sendStatus();

	void printHelp();

	// Main loop:
	void runFirmware(); // For Mk 1 Alpha testing
	void executeCommand(const String &command);
	void stopCommand();

protected:
	String _modelName;

	// To run commands:
	String _currentCommand;

	// LED pins
	static const uint8_t PIN_LED_GREEN = 10;
	static const uint8_t PIN_LED_RED = 11;
	static const uint8_t PIN_LED_BLUE = 9;		 // Previously ledPlus
	static const uint8_t PIN_LED_BLUE_MINUS = 8; // Previously ledMinus

	// Audio pin
	static const uint8_t PIN_BUZZER = 37;

	// Peltier control pins
	static const uint8_t PIN_PELTIER_ENABLE = 7;
	static const uint8_t PIN_PELTIER_IN1 = 6;
	static const uint8_t PIN_PELTIER_IN2 = 5;

	// Brightness
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
