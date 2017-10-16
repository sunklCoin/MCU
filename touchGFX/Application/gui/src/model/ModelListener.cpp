/*
 * ModelListener.cpp
 *
 *  Created on: 2017/9/15
 *      Author: yuhang
 */
#include <gui/model/ModelListener.hpp>
#include <gui/common/ControlData.hpp>
#include <gui/framework/DevicePort.h>
#ifndef SIMULATOR
#include <fsl_debug_console.h>
#endif
///#include <remoter_powermanage.h>
#include <gui/framework/DevicePort.h>


void ModelListener::dispatchMessage(message_gui_rsp &message) {
    Unicode::UnicodeChar strParam[61] = {0};
    memset(strParam, 0, sizeof(strParam));
    bool status = false;

#ifndef SIMULATOR
    PRINTF("%s | msgid=%0x\n", __func__, message.msgid);
#endif // !SIMULATOR
    switch (message.msgid) {
        /* bluetooth */
        case MSG_ID_GUI_BT_OPEN_RSP:
            Bluetooth_SetState(bt_state_advertised);
            onBluetoothStateChange(true);
            model->mControlData.enableBTState(true);
            updateStatusBar(StatusBar::utBluetooth);
            //Bluetooth_RedoAction(bt_action_open);
            break;
        case MSG_ID_GUI_BT_CLOSE_RSP:
            Bluetooth_SetState(bt_state_idle);
            onBluetoothStateChange(false);
            model->mControlData.enableBTState(false);
            updateStatusBar(StatusBar::utBluetooth);
            //Bluetooth_RedoAction(bt_action_close);
            break;
        case MSG_ID_GUI_BT_SCAN_RESULT_IND:
            Unicode::strncpy(strParam, message.data.bt.deviceName, BT_DEVICENAME_LEN);
            onBluetoothScanResult(strParam, message.data.bt.address);
            break;
        case MSG_ID_GUI_BT_SCAN_COMPLETE_IND:
            Bluetooth_SetState(bt_state_advertised);
            onBluetoothScanComplete(message.data.bt.num);
            //Bluetooth_RedoAction(bt_action_scan);
            break;
        case MSG_ID_GUI_BT_CONNECT_RSP:
            Bluetooth_SetState(bt_state_advertised);
            onBluetoothConnected(message.result == 0x00, message.data.bt.address);
            break;
        case MSG_ID_GUI_BT_DISCONNECT_RSP:
            Bluetooth_SetState(bt_state_advertised);
            onBluetoothDisonnected(message.data.bt.reason, message.data.bt.address);
            break;
        case MSG_ID_GUI_BT_BOND_RSP:
            Bluetooth_SetState(bt_state_advertised);
            onBluetoothBonded(message.result == 0x00, message.data.bt.bonded, message.data.bt.address);
            break;
        case MSG_ID_GUI_BT_CENTRAL_UPDATE_PARAM_RSP:
            Bluetooth_SetState(bt_state_advertised);
            onBluetoothCentralUpdateParam(message.result == 0x00);
            break;
        case MSG_ID_GUI_BT_PERIPHERAL_UPDATE_PARAM_RSP:
            Bluetooth_SetState(bt_state_advertised);
            onBluetoothPeripheralUpdateParam(message.result == 0x00);
            break;
        /* pm */
        case MSG_ID_GUI_PM_REFRESH_IND:
            if (message.data.pm.charging_status == 1 /*CHG_IN_PROGRESS*/)
                model->mControlData.setBatteryState(BATTERY_CHARGING);
            else
                model->mControlData.setBatteryState(BATTERY_NO_CHARGING);
            model->mControlData.setBatteryLevel(message.data.pm.level);
            updateStatusBar(StatusBar::utBattery);
            break;
        /* wifi */
        case MSG_ID_GUI_WIFI_OPEN_RSP:
            Wifi_SetState(wifi_state_idle);
            status = message.result == 0;
            model->mControlData.enableWifiState(status);
            onWifiOpened(status);
            // go to scan
        case MSG_ID_GUI_WIFI_SCAN_RSP:
            Wifi_SetState(wifi_state_idle);
            Wifi_SetScanList(message.data.wifi.scan_list, message.data.wifi.scan_num);
            for (int i = 0; i < message.data.wifi.scan_num; i++) {
                memset(strParam, 0, sizeof(strParam));
                Unicode::strncpy(strParam, (char*) message.data.wifi.scan_list[i].ssid, message.data.wifi.scan_list[i].ssid_len);
                strParam[message.data.wifi.scan_list[i].ssid_len] = '\0';
                onWifiScanResult(strParam, message.data.wifi.scan_list[i].bssid, 
                    message.data.wifi.scan_list[i].rssi, 
                    message.data.wifi.scan_list[i].security_enabled != 0);
            }
            onWifiScanCompleted(message.data.wifi.scan_num);
            break;
        case MSG_ID_GUI_WIFI_CLOSE_RSP:
            Wifi_SetState(wifi_state_closed);
            status = message.result == 0;
            model->mControlData.enableWifiState(!status);
            onWifiClosed(status);
            break;
        case MSG_ID_GUI_WIFI_CONNECT_RSP:
            Wifi_SetState(wifi_state_idle);
            status = message.result == 0;
            onWifiConnected(status);
            break;
        case MSG_ID_GUI_WIFI_DISCONNECT_RSP:
            Wifi_SetState(wifi_state_idle);
            status = message.result == 0;
            onWifiDisonnected(status);
            break;
        case MSG_ID_GUI_WIFI_MIC_TRANSFER_CHANNLE_RSP:
            status = message.result == -1;
            onTransferConnectState(!status);
            break;
        /* keypad */
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

/* Bluetooth */
void ModelListener::onBluetoothStateChange(bool state)
{
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__); 
#endif // !SIMULATOR
}

//void ModelListener::onBluetoothScanResult(touchgfx::Unicode::UnicodeChar* strDeviceName, touchgfx::Unicode::UnicodeChar* strAddress)
void ModelListener::onBluetoothScanResult(touchgfx::Unicode::UnicodeChar* strName, uint8_t address[]) {
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

void ModelListener::onBluetoothConnected(bool status, uint8_t address[]) {
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

void ModelListener::onBluetoothDisonnected(int reason, uint8_t address[]) {
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

void ModelListener::onBluetoothBonded(bool status, int bonded, uint8_t address[]) {
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

void ModelListener::onBluetoothCentralUpdateParam(bool status) {
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

void ModelListener::onBluetoothPeripheralUpdateParam(bool status) {
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

/* Wifi */
void ModelListener::onWifiOpened(bool status) {
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

void ModelListener::onWifiClosed(bool status) {
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

void ModelListener::onWifiScanResult(touchgfx::Unicode::UnicodeChar* strName, uint8_t address[], int rssi, bool needPwd) {
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

void ModelListener::onWifiScanCompleted(int num) {
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

void ModelListener::onWifiConnected(bool status) {
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

void ModelListener::onWifiDisonnected(bool status) {
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

void ModelListener::onTransferConnectState(bool reason)
{
#ifndef SIMULATOR
    PRINTF("%s | \n", __func__);
#endif // !SIMULATOR
}

