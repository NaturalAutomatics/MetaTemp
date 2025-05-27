#include "KelvinVR.h"
#include <Arduino.h>

KelvinVR::KelvinVR(int enPin, int in1Pin, int in2Pin) {
  _enPin = enPin;
  _in1Pin = in1Pin;
  _in2Pin = in2Pin;

  pinMode(_enPin, OUTPUT);
  pinMode(_in1Pin, OUTPUT);
  pinMode(_in2Pin, OUTPUT);

  analogWrite(_enPin, 0);
  digitalWrite(_in1Pin, LOW);
  digitalWrite(_in2Pin, LOW);
}

void KelvinVR::setPower(int power) {
  power = constrain(power, -100, 100);

  // Disable before changing direction
  analogWrite(_enPin, 0);

  if (power > 0) {
    digitalWrite(_in1Pin, HIGH);
    digitalWrite(_in2Pin, LOW);
  } else if (power < 0) {
    digitalWrite(_in1Pin, LOW);
    digitalWrite(_in2Pin, HIGH);
  } else {
    return;
  }

  int pwm = (abs(power) * 255) / 100;
  analogWrite(_enPin, pwm);
}