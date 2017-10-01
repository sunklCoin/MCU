#ifndef _CONTROL_DATA_HPP_
#define _CONTROL_DATA_HPP_

#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

enum eBatteryState {
    BATTERY_NO_CHARGING = 0,
    BATTERY_CHARGING = 1
};

const int sleepScheduleArr[] = {15,30,60,120,300,600,1800};

extern "C"{
#ifndef SIMULATOR
    extern void Backlight_Adjust(uint8_t brightness);
    extern uint8_t Backlight_Get(void);
#endif
}

class ControlData {
public:
    ControlData();
    bool isBTEnable();
    void enableBTState(bool);
    bool isWifiEnable();
    void setWifiSignal(int);
    void enableWifiState(bool);
    int getWifiSignal();
    bool isCharging();
    void setBatteryState(eBatteryState state);
    void setBatteryLevel(int);
    int getBatteryLevel();
    int getBackLightLevel();
    void setBackLightLevel(int);
    void setSleepSchedule(int);
    int getSleepSchedule();
private:

};

#endif // _CONTROL_DATA_HPP_

