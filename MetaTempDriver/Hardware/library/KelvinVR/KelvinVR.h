/*
  Main class for KelvinVR module
*/

#if defined(__AVR__)
	#include "Arduino.h"
	#include "hardware/avr/HW_AVR_defines.h"
#elif defined(__PIC32MX__)
	#include "WProgram.h"
	#include "hardware/pic32/HW_PIC32_defines.h"
#elif defined(__arm__)
	#include "Arduino.h"
	#include "hardware/arm/HW_ARM_defines.h"
#endif

class Kelvin
{
	public:
		Kelvin();
		Kelvin(modelName);
		void	begin();
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

		int _pinsOutput[] = {buzzer,greenLed, redLed,ledPlus, ledMinus};

		int _brightness = 0;    // how bright the LED is
		int _fadeAmount = 5;    // how many points to fade the LED 

		int _boadRate;
};
