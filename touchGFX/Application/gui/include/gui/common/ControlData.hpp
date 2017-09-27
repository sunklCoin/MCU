#ifndef _CONTROL_DATA_HPP_
#define _CONTROL_DATA_HPP_

#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

enum eBatteryState {
    BATTERY_NO_CHARGING = 0,
    BATTERY_CHARGING = 1
};

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
private:

};

#endif // _CONTROL_DATA_HPP_

