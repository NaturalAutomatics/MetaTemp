// KelvinVRArduino.hpp
#ifndef KELVIN_VR_ARDUINO_HPP
#define KELVIN_VR_ARDUINO_HPP

#include "KelvinVRBase.hpp"

class KelvinVRArduino : public KelvinVRBase
{
public:
    KelvinVRArduino();
    virtual ~KelvinVRArduino() = default;

    void begin() override;
    void update() override;

    // Add any Arduino-specific methods here

private:
    // Add any Arduino-specific member variables here
    int _peltierEnablePin;
    int _peltierIn1Pin;
    int _peltierIn2Pin;
};

#endif
