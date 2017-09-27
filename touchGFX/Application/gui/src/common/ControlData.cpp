#include <gui/common/ControlData.hpp>

bool glb_BtState = false;
bool glb_Wifistate = false;
int  glb_wifiSignal = 0;
int glb_BatteryState = 0;
int glb_BatteryLevel = 0;



ControlData::ControlData()
{

}

bool ControlData::isBTEnable()
{
    return glb_BtState;
}


void ControlData::enableBTState(bool state)
{
    glb_BtState = state;
}

//
bool ControlData::isWifiEnable()
{
    return glb_Wifistate;
}

void ControlData::setWifiSignal(int signalLevel)
{
    glb_wifiSignal = signalLevel;
}

void ControlData::enableWifiState(bool state)
{
    glb_Wifistate = state;
}

int ControlData::getWifiSignal()
{
    return glb_wifiSignal;
}

bool ControlData::isCharging()
{
    return (glb_BatteryState == BATTERY_CHARGING);
}

void ControlData::setBatteryState(eBatteryState state)
{
    glb_BatteryState = state; 
}

void ControlData::setBatteryLevel(int level)
{
    glb_BatteryLevel = level;
}

int ControlData::getBatteryLevel()
{
    return glb_BatteryLevel;
}