#ifndef KelvinVR_h
#define KelvinVR_h

#include <Arduino.h>

class KelvinVR {
  public:
    KelvinVR(int enPin, int in1Pin, int in2Pin);
    void setPower(int power);

  private:
    int _enPin;
    int _in1Pin;
    int _in2Pin;
};

#endif