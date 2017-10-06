#include <gui/common/ControlData.hpp>

bool glb_BtState = false;
bool glb_Wifistate = false;
int glb_wifiSignal = 0;
int glb_BatteryState = 0;
int glb_BatteryLevel = 0;
int glb_currBacklight = 0;
int glb_currSleepSchedule = 0;


ControlData::ControlData()
{
#ifndef SIMULATOR
    glb_currBacklight = Backlight_Get();
#else
    glb_currBacklight = 100;
#endif
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

int ControlData::getBackLightLevel()
{
    return glb_currBacklight;
}


void ControlData::setBackLightLevel(int value)
{
    glb_currBacklight = value;
#ifndef SIMULATOR
    Backlight_Adjust(value);
#endif
}

void ControlData::setSleepSchedule(int value)
{
    glb_currSleepSchedule = value;
#ifndef SIMULATOR

#endif
}

int ControlData::getSleepSchedule()
{
    return glb_currSleepSchedule;
}


void ControlData::gotoSleep()
{
#ifndef SIMULATOR
    LCD_Sleep();
#endif
    isSleep = true;
}

void ControlData::wakeupLcd()
{
#ifndef SIMULATOR
    LCD_Awake();
#endif
    isSleep = false;
}

bool ControlData::isSleepState()
{
    return isSleep;
}
