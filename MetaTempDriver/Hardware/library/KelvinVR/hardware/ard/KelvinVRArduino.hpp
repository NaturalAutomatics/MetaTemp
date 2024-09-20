#ifndef KELVIN_VR_ARDUINO_H
#define KELVIN_VR_ARDUINO_H

#include "../KelvinVRBase.hpp"

class KelvinVRArduino : public KelvinVRBase
{
public:
    void begin() override;
    void update() override;
    // Implement other functions
};

#endif
