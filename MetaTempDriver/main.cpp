/*

  __  __      _      _____                    
 |  \/  | ___| |_ __|_   _|__ _ __ ___  _ __  
| |\/| |/ _ \ __/ _ \| |/ _ \ '_ ` _ \| '_ \ 
| |  | |  __/ ||  __/| |  __/ | | | | | |_) |
|_|  |_|\___|\__\___||_|\___|_| |_| |_| .__/ 
                                      |_|    
 ____       _                
|  _ \ _ __(_)_   _____ _ __ 
| | | | '__| \ \ / / _ \ '__|
| |_| | |  | |\ V /  __/ |   
|____/|_|  |_| \_/ \___|_|   
                             

                             

September 13th 2024 By Alex Noyanov
*/


#include <C:\Users\Alex\Documents\Work\OpenVR-git\openvr\headers\openvr.h>

class ObjectTemperatureController
{
public:
    ObjectTemperatureController(vr::IVRSystem* vrSystem, vr::ETrackedControllerRole handType)
        : m_vrSystem(vrSystem), m_handType(handType)
    {
        vr::EVRInputError err = vr::VRInput()->GetActionHandle("/actions/main/in/GrabObject", &m_grabActionHandle);
        if (err != vr::VRInputError_None)
        {
            // Handle error
        }

        vr::VRInput()->GetActionSetHandle("/actions/main", &m_actionSetHandle);
        vr::VRInput()->GetActionHandle("/actions/main/in/GrabObject", &m_grabActionHandle);
    }

    void Update()
    {
        vr::VRActiveActionSet_t activeActionSet = { m_actionSetHandle };
        vr::VRInput()->UpdateActionState(&activeActionSet, sizeof(activeActionSet), &m_actionStateData);

        vr::InputDigitalActionData_t grabData = m_actionStateData.rActiveOrigin == vr::VRActiveActionSet_t::k_ulInvalidActionHandle ? vr::InputDigitalActionData_t{} : m_actionStateData.digitalActionData[m_grabActionHandle];

        if (grabData.bState && !m_isGrabbing)
        {
            m_isGrabbing = true;
            m_grabbedObject = GetObjectInHand();
            // Do something with the grabbed object, like get its temperature
        }
        else if (!grabData.bState && m_isGrabbing)
        {
            m_isGrabbing = false;
            m_grabbedObject = nullptr;
        }
    }

private:
    vr::IVRSystem* m_vrSystem;
    vr::ETrackedControllerRole m_handType;
    vr::VRActionHandle_t m_grabActionHandle;
    vr::VRActionSetHandle_t m_actionSetHandle;
    vr::VRActiveActionSet_t m_actionStateData = {};
    bool m_isGrabbing = false;
    vr::TrackedDeviceIndex_t m_grabbedObject = vr::k_unTrackedDeviceIndexInvalid;

    vr::TrackedDeviceIndex_t GetObjectInHand()
    {
        vr::VRActiveActionSet_t activeActionSet = { m_actionSetHandle };
        vr::VRInput()->UpdateActionState(&activeActionSet, sizeof(activeActionSet), &m_actionStateData);

        vr::InputOriginInfo_t originInfo;
        if (m_actionStateData.activeOrigin != vr::VRActiveActionSet_t::k_ulInvalidActionHandle)
        {
            vr::VRInput()->GetOriginTrackedDeviceInfo(m_actionStateData.activeOrigin, &originInfo, sizeof(originInfo));
            return originInfo.trackedDeviceIndex;
        }

        return vr::k_unTrackedDeviceIndexInvalid;
    }
};
