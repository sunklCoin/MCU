/*
 * DevicePort.h
 *
 *  Created on: 2017/09/18
 *      Author: yuhang
 */
#ifndef DEVICEPORT_H
#define DEVICEPORT_H

#ifdef SIMULATOR
#include <target/simulator_remoter_messsage_gui.h>
#else
extern "C" {
#include "remoter_message.h"
}
#endif

/* bluetooth */
typedef enum bluetooth_state {
    bt_state_idle = 0,
    bt_state_advertising,
    bt_state_advertised,
    bt_state_scaning,
    bt_state_stopscaning,
    bt_state_closeadvertising
} enum_bluetooth_state;

typedef enum bluetooth_action {
    bt_action_none = 0,
    bt_action_open,
    bt_action_scan,
    bt_action_close
} enum_bluetooth_action;


extern void Bluetooth_SetState(enum_bluetooth_state state);
extern void Bluetooth_RedoAction(enum_bluetooth_action action);

extern void Bluetooth_Open();
extern void Bluetooth_Close();
extern void Bluetooth_Scan_Start();
extern void Bluetooth_Scan_Stop();
extern void Bluetooth_Connect(uint8_t address[]);
extern void Bluetooth_Disconnect(uint8_t address[]);
extern void Bluetooth_Bond(uint8_t address[]);

/* wifi */
typedef enum wifi_state {
    wifi_state_closed = 0,
    wifi_state_opening,
    wifi_state_idle,
    wifi_state_scaning,
    wifi_state_connecting,
    wifi_state_disconnecting,
    wifi_state_closing,
} enum_wifi_state;

void Wifi_SetState(enum_wifi_state state);

extern void Wifi_Open();
extern void Wifi_Close();
extern void Wifi_Scan();
extern void Wifi_SetScanList(struct_wifi_scan* scan_list, uint16_t scan_num) ;
extern bool Wifi_Connect(uint8_t address[], char password[]);
extern void Wifi_Disconnect();

/* Mic */
extern void Mic_StartRecord();
extern void Mic_FinishRecord();
extern void Mic_CancelRecord();
 #endif /* DEVICEPORT_H */
