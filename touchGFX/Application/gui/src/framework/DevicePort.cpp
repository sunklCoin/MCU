/*
 * DevicePort.cpp
 *
 *  Created on: 2017/09/18
 *      Author: yuhang
 */
#ifdef SIMULATOR
#include <target/simulator_remoter_messsage_gui.h>
#include <stdint.h>
#include <gui/model/ModelListener.hpp>
#else
extern "C" {
#include "remoter_message.h"
}
#endif

#ifdef SIMULATOR
#define SM_MESSAGE_QUEUE        50

ModelListener* gSM_ModelListener;
message_gui_rsp sm_message;
message_gui_rsp sm_message_queue[SM_MESSAGE_QUEUE];
int sm_message_queue_front = 0;
int sm_message_queue_rear = -1;
bool sm_message_queue_flag = false;

void SM_InitMessage() {
    memset(&sm_message, 0, sizeof(sm_message));
}

bool SM_SendMessage() {
    int queue_rear = sm_message_queue_rear + 1;
    bool queue_flag = sm_message_queue_flag;

    if (queue_rear >= SM_MESSAGE_QUEUE) {
        queue_rear = 0;
        queue_flag = true;
    }

    if (queue_flag  && queue_rear >= sm_message_queue_front) {
        return false;
    }

    sm_message_queue[queue_rear] = sm_message;
    sm_message_queue_rear = queue_rear;
    sm_message_queue_flag = queue_flag;
    return true;
}

void SM_DispatchMessage() {
    int queue_rear = sm_message_queue_rear;

    if (gSM_ModelListener != NULL) {
        if (sm_message_queue_flag) {
            while (sm_message_queue_front < SM_MESSAGE_QUEUE) {
                gSM_ModelListener->dispatchMessage(sm_message_queue[sm_message_queue_front++]);
            }
            sm_message_queue_front = 0;
            sm_message_queue_flag = false;
        }
        while (sm_message_queue_front <= queue_rear) {
            gSM_ModelListener->dispatchMessage(sm_message_queue[sm_message_queue_front++]);
        }
    }
}
#endif

void SendMessageEmpty(uint32_t msg_id) {
#ifndef SIMULATOR
    struct_remote_message msg_send;
    memset(&msg_send, 0, sizeof(msg_send));
    msg_send.task_src = TASK_GUI;
    msg_send.task_dst = TASK_GUI_SVC;
    msg_send.msg.msg_gui_req.msgid = msg_id;
    Message_Send(&msg_send);
#endif
}

/* bluetooth */
void Bluetooth_Open() {
#ifndef SIMULATOR
    SendMessageEmpty(MSG_ID_GUI_BT_OPEN_REQ);
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_BT_OPEN_RSP;
    SM_SendMessage();
#endif
}

void Bluetooth_Close() {
#ifndef SIMULATOR
    SendMessageEmpty(MSG_ID_GUI_BT_CLOSE_REQ);
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_BT_CLOSE_RSP;
    SM_SendMessage();
#endif
}

void Bluetooth_Scan_Start() {
#ifndef SIMULATOR
    SendMessageEmpty(MSG_ID_GUI_BT_SCAN_START_REQ);
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_BT_SCAN_RESULT_IND;
    strcpy_s(sm_message.data.bt.deviceName, "Test1");
    SM_SendMessage();

    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_BT_SCAN_RESULT_IND;
    sm_message.data.bt.address[0] = 0xF9;
    sm_message.data.bt.address[1] = 0xE8;
    sm_message.data.bt.address[2] = 0xD7;
    sm_message.data.bt.address[3] = 0xC6;
    sm_message.data.bt.address[4] = 0xB5;
    sm_message.data.bt.address[5] = 0xA3;
    SM_SendMessage();

    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_BT_SCAN_COMPLETE_IND;
    sm_message.data.bt.num = 0;
    SM_SendMessage();

#endif
}

void Bluetooth_Scan_Stop() {
#ifndef SIMULATOR
    SendMessageEmpty(MSG_ID_GUI_BT_SCAN_STOP_REQ);
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_BT_SCAN_COMPLETE_IND;
    sm_message.data.bt.num = 0;
    SM_SendMessage();
#endif
}

/* wifi */
void Wifi_Scan();

void Wifi_Open() {
#ifndef SIMULATOR
    SendMessageEmpty(MSG_ID_GUI_WIFI_OPEN_REQ);
#else
    /*SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_WIFI_OPEN_RSP;
    SM_SendMessage();*/
    Wifi_Scan();
#endif
}

void Wifi_Close() {
#ifndef SIMULATOR
    SendMessageEmpty(MSG_ID_GUI_WIFI_CLOSE_REQ);
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_WIFI_CLOSE_RSP;
    SM_SendMessage();
#endif
}

void Wifi_Scan() {
#ifndef SIMULATOR
    SendMessageEmpty(MSG_ID_GUI_WIFI_SCAN_REQ);
#else
    static struct_wifi_scan_list gWifi_Scan_List[3] = {
        {0, 5, 40, {0xA0, 0xB1, 0xC2, 0xD3, 0xE4, 0xF5}, {0x41, 0x62, 0x63, 0x64, 0}},
        {0, 5, 90, {0xA0, 0xB1, 0xC2, 0xD3, 0xE4, 0xF5}, {0x65, 0x6F, 0x73, 0x63, 0x76, 0x0}},
        {0, 6, 60, {0xA0, 0xB1, 0xC2, 0xD3, 0xE4, 0xF5}, {0x52, 0x45, 0x58, 0x4A, 0x57, 0}}
    };

    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_WIFI_SCAN_RSP;
    sm_message.data.wifi.scan_num = 3;
    sm_message.data.wifi.scan_list = &gWifi_Scan_List[0];
    SM_SendMessage();
#endif
}

void Wifi_Connect() {
#ifndef SIMULATOR
    SendMessageEmpty(MSG_ID_GUI_WIFI_CONNECT_REQ);
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_WIFI_CONNECT_RSP;
    SM_SendMessage();
#endif
}

void Wifi_Disconnect() {
#ifndef SIMULATOR
    SendMessageEmpty(MSG_ID_GUI_WIFI_DISCONNECT_REQ);
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_WIFI_DISCONNECT_RSP;
    SM_SendMessage();
#endif
}

/* Mic */
void Mic_StartRecord() {
#ifndef SIMULATOR
	SendMessageEmpty(MSG_ID_GUI_BT_OPEN_REQ);
#else
	SM_InitMessage();
	sm_message.msgid = MSG_ID_GUI_BT_OPEN_RSP;
	SM_SendMessage();
#endif
}

void Mic_finishRecord()
{
#ifndef SIMULATOR

#else

#endif
}

void Mic_cancelRecord()
{
#ifndef SIMULATOR

#else

#endif
}