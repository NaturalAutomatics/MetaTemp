#ifndef KELVIN_VR_BASE_H
#define KELVIN_VR_BASE_H

class KelvinVRBase
{
public:
    virtual void begin() = 0;
    virtual void update() = 0;
    // Add other common functions here
    virtual ~KelvinVRBase() {}
};

#endif
