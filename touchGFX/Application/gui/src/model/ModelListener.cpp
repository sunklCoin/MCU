/*
 * ModelListener.cpp
 *
 *  Created on: 2017/9/15
 *      Author: yuhang
 */
#include <gui/model/ModelListener.hpp>
#include <gui/common/ControlData.hpp>
#ifndef SIMULATOR
#include <fsl_debug_console.h>
#endif
///#include <remoter_powermanage.h>

void ModelListener::dispatchMessage(message_gui_rsp &message) {
    Unicode::UnicodeChar strParam1[61] = {0};
    Unicode::UnicodeChar strParam2[21] = {0};
    memset(strParam1, 0, sizeof(strParam1));
    memset(strParam2, 0, sizeof(strParam2));

#ifndef SIMULATOR
    PRINTF("%s | msgid=%0x\n", __func__, message.msgid);
#endif // !SIMULATOR
    switch (message.msgid) {
        case MSG_ID_GUI_BT_OPEN_RSP:
            onBluetoothStateChange(true);
            model->mControlData.enableBTState(true);
            updateStatusBar(StatusBar::utBluetooth);
            break;
        case MSG_ID_GUI_BT_CLOSE_RSP:
            onBluetoothStateChange(false);
            model->mControlData.enableBTState(false);
            updateStatusBar(StatusBar::utBluetooth);
            break;
        case MSG_ID_GUI_BT_SCAN_RESULT_IND:
            Unicode::strncpy(strParam1, message.data.bt.deviceName, BT_DEVICENAME_LEN);
            Unicode::snprintf(strParam2, 18, "%02X:%02X:%02X:%02X:%02X:%02X", message.data.bt.address[0], message.data.bt.address[1],
                message.data.bt.address[2], message.data.bt.address[3], message.data.bt.address[4], message.data.bt.address[5]);
            onBluetoothScanResult(strParam1, strParam2);
            break;
        case MSG_ID_GUI_BT_SCAN_COMPLETE_IND:
            onBluetoothScanComplete(message.data.bt.num);
            break;
        case MSG_ID_GUI_PM_REFRESH_IND:
            if (message.data.pm.charging_status == 1 /*CHG_IN_PROGRESS*/)
                model->mControlData.setBatteryState(BATTERY_CHARGING);
            else
                model->mControlData.setBatteryState(BATTERY_NO_CHARGING);
            model->mControlData.setBatteryLevel(message.data.pm.level);
            updateStatusBar(StatusBar::utBattery);
            break;
        case MSG_ID_GUI_WIFI_SCAN_RSP:
            for (int i = 0; i < message.data.wifi.scan_num; i++) {
                Unicode::strncpy(strParam1, (char*) message.data.wifi.scan_list[i].ssid, 32);
                onWifiScanResult(strParam1, message.data.wifi.scan_list[i].bssid, message.data.wifi.scan_list[i].rssi);
            }
            onWifiScanCompleted(message.data.wifi.scan_num);
            break;
        case MSG_ID_GUI_KEYPAD_INPUT_IND:
            handleKeyEvent(message.data.key.key_code);
            break;
    }
}

void ModelListener::handleKeyEvent(uint8_t key) {
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

void ModelListener::onBluetoothStateChange(bool state)
{
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__); 
#endif // !SIMULATOR
}

void ModelListener::onBluetoothScanResult(touchgfx::Unicode::UnicodeChar* strDeviceName, touchgfx::Unicode::UnicodeChar* strAddress)
{
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

void ModelListener::onBluetoothScanComplete(int num)
{
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

void ModelListener::onWifiScanResult(touchgfx::Unicode::UnicodeChar* strName, uint8_t address[], int rssi) {
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

void ModelListener::onWifiScanCompleted(int num) {
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

