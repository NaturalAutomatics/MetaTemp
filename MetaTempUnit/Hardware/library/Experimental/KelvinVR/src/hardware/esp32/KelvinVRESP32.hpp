// KelvinVRESP32.hpp
#ifndef KELVIN_VR_ESP32_HPP
#define KELVIN_VR_ESP32_HPP

#include "KelvinVRBase.hpp"

class KelvinVRESP32 : public KelvinVRBase
{
public:
    KelvinVRESP32();
    virtual ~KelvinVRESP32(); // Remove the '= default' here

    void begin() override;
    // void runThermalCycle(bool isCooling, int intensity, int durationSeconds) override;
    void update() override;
    void setThermalCycle(bool isCooling, int intensity, int durationSeconds);
    // void startCooling(int intensity);
    // void stopCooling() override;

    // Add any ESP32-specific methods here

private:
    // Add any ESP32-specific member variables here
    struct ThermalCycle
    {
        bool isCooling;
        int intensity;
        int durationSeconds;
        unsigned long startTime;
        bool isActive;
    };

    ThermalCycle thermalCycle;
};

#endif
