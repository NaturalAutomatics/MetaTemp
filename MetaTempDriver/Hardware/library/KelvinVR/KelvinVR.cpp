/*
  KelvinVR Mk1-Alpha test module: Arduino Mega Original 2560

  Front LED connection:

  RGLed inside:

  Motor Shield connections:


*/

#include "KelvinVR.h"

Kelvin::Kelvin(string modelName)
{ 
	_modelName = modelName;
}

void Kelvin:: fullPinSetup(){
  for(int i = 0; i < sizeof(pinsOutput); i++){
    pinMode(pinsOutput[i],OUTPUT);
  }
}

void Kelvin:: blinkLed(int ledPin){
  digitalWrite(ledPin,HIGH);
  delay(1000);
  digitalWrite(ledPin,LOW);
  delay(1000);
}

void Kelvin:: fadeEffect(int led) {
   // set the brightness of pin 9:
  analogWrite(led, brightness);

  // change the brightness for next time through the loop:
  _brightness = _brightness + _fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (_brightness <= 0 || _brightness >= 255) {
    _fadeAmount = -_fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}

void Kelvin:: ledOn(){
  digitalWrite(ledPlus,HIGH);
  digitalWrite(ledMinus,LOW);
}

void Kelvin:: ledOff() {
  digitalWrite(ledPlus,LOW);
}

void Kelvin:: blinkFront(int delayTime){
  digitalWrite(ledPlus,HIGH);
  delay(delayTime);
  digitalWrite(ledPlus,LOW);
  delay(delayTime);
}

