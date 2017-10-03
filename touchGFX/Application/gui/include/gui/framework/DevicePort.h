/*
 * DevicePort.h
 *
 *  Created on: 2017/09/18
 *      Author: yuhang
 */

#ifndef DEVICEPORT_H
#define DEVICEPORT_H

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

/* Mic */
void Mic_StartRecord();
void Mic_finishRecord();
void Mic_cancelRecord();
 #endif /* DEVICEPORT_H */
