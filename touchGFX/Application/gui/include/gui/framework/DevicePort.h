/*
 * DevicePort.h
 *
 *  Created on: 2017/09/18
 *      Author: yuhang
 */

#ifndef DEVICEPORT_C
#define DEVICEPORT_C

/* bluetooth */
void Bluetooth_Open();
void Bluetooth_Close();
void Bluetooth_Scan_Start();
void Bluetooth_Scan_Stop();

/* wifi */
void Wifi_Open();
void Wifi_Close();
void Wifi_Scan();
void Wifi_Connect();
void Wifi_Disconnect();

 #endif /* DEVICEPORT_C */
