#ifndef KELVIN_VR_ESP32_H
#define KELVIN_VR_ESP32_H

#include "KelvinVRBase.hpp"

class KelvinVRESP32 : public KelvinVRBase
{
public:
    void runThermalCycle(bool isCooling, int intensity, int durationSeconds) override;
    void begin() override;
    void update() override;
    // Implement other functions
};

#endif
