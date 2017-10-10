/*
 * DevicePort.cpp
 *
 *  Created on: 2017/09/18
 *      Author: yuhang
 */
#ifdef SIMULATOR
#include <stdint.h>
#include <gui/model/ModelListener.hpp>
#endif
#include <gui/framework/DevicePort.h>
#include <string.h>


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
#else
void InitMessage(struct_remote_message& msg_send, uint32_t msg_id) {
    memset(&msg_send, 0, sizeof(msg_send));
    msg_send.task_src = TASK_GUI;
    msg_send.task_dst = TASK_GUI_SVC;
    msg_send.msg.msg_gui_req.msgid = msg_id;
}

void SendMessageEmpty(uint32_t msg_id) {
    struct_remote_message msg_send;
    memset(&msg_send, 0, sizeof(msg_send));
    msg_send.task_src = TASK_GUI;
    msg_send.task_dst = TASK_GUI_SVC;
    msg_send.msg.msg_gui_req.msgid = msg_id;
    Message_Send(&msg_send);
}
#endif

/* bluetooth */
enum_bluetooth_state bluetooth_state = bt_state_idle;
enum_bluetooth_action bluetooth_action = bt_action_none;

void Bluetooth_Open();
void Bluetooth_Close();

void Bluetooth_SetState(enum_bluetooth_state state) {
    bluetooth_state = state;
}

void Bluetooth_SetAction(enum_bluetooth_action action) {
    bluetooth_action = action;
}

void Bluetooth_RedoAction(enum_bluetooth_action action) {
    if (bluetooth_action != action) {
        switch (bluetooth_action) {
            case bt_action_open:
                Bluetooth_Open();
                break;
            case bt_action_scan:
                ///Bluetooth_Scan_Start();
                break;
            case bt_action_close:
                Bluetooth_Close();
                break;
        }
    }
    bluetooth_action = bt_action_none;
}

void Bluetooth_Open() {
    if (bluetooth_state != bt_state_idle) {
        Bluetooth_SetAction(bt_action_open);
        return;
    }

#ifndef SIMULATOR
    SendMessageEmpty(MSG_ID_GUI_BT_OPEN_REQ);
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_BT_OPEN_RSP;
    SM_SendMessage();
#endif

    Bluetooth_SetState(bt_state_advertising);
}

void Bluetooth_Close() {
    if (bluetooth_state != bt_state_advertised) {
        Bluetooth_SetAction(bt_action_close);
        return;
    }

#ifndef SIMULATOR
    SendMessageEmpty(MSG_ID_GUI_BT_CLOSE_REQ);
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_BT_CLOSE_RSP;
    SM_SendMessage();
#endif

    Bluetooth_SetState(bt_state_closeadvertising);
}

void Bluetooth_Scan_Start() {
    if (bluetooth_state != bt_state_advertised) {
        Bluetooth_SetAction(bt_action_scan);
        return;
    }

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

    Bluetooth_SetState(bt_state_scaning);
}

void Bluetooth_Scan_Stop() {
#if 0
    if (bluetooth_state != bt_state_scaning) return;

#ifndef SIMULATOR
    SendMessageEmpty(MSG_ID_GUI_BT_SCAN_STOP_REQ);
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_BT_SCAN_COMPLETE_IND;
    sm_message.data.bt.num = 0;
    SM_SendMessage();
#endif

    Bluetooth_SetState(bt_state_stopscaning);
#endif
}

void Bluetooth_Connect(uint8_t address[]) {
    if (bluetooth_state != bt_state_advertised) return;

#ifndef SIMULATOR
    struct_remote_message msg_send;
    InitMessage(msg_send, MSG_ID_GUI_BT_CONNECT_REQ);
    memcpy(msg_send.msg.msg_gui_req.para.bt.address, address, BT_MACADDRESS_LEN);
    Message_Send(&msg_send);
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_BT_CONNECT_RSP;
    SM_SendMessage();
#endif
}

void Bluetooth_Disconnect(uint8_t address[]) {
    if (bluetooth_state != bt_state_advertised) return;

#ifndef SIMULATOR
    struct_remote_message msg_send;
    InitMessage(msg_send, MSG_ID_GUI_BT_DISCONNECT_RSP);
    memcpy(msg_send.msg.msg_gui_req.para.bt.address, address, BT_MACADDRESS_LEN);
    Message_Send(&msg_send);
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_BT_DISCONNECT_REQ;
    SM_SendMessage();
#endif
}

void Bluetooth_Bond(uint8_t address[]) {
    if (bluetooth_state != bt_state_advertised) return;

#ifndef SIMULATOR
    struct_remote_message msg_send;
    InitMessage(msg_send, MSG_ID_GUI_BT_BOND_REQ);
    memcpy(msg_send.msg.msg_gui_req.para.bt.address, address, BT_MACADDRESS_LEN);
    Message_Send(&msg_send);
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_BT_BOND_RSP;
    SM_SendMessage();
#endif
}

/* wifi */
struct_wifi_scan* m_scan_list = NULL;
uint16_t m_scan_num = 0;

enum_wifi_state m_wifi_state = wifi_state_closed;

void Wifi_SetState(enum_wifi_state state) {
    m_wifi_state = state;
}

void Wifi_SetScanList(struct_wifi_scan* scan_list, uint16_t scan_num) {
    m_scan_list = scan_list;
    m_scan_num = scan_num;
}

struct_wifi_scan* FindScanListEntry(uint8_t address[]) {
    for (int i = 0; i < m_scan_num; i++) {
        if (memcmp(m_scan_list[i].bssid, address, BT_MACADDRESS_LEN) == 0) {
            return &m_scan_list[i];
        }
    }
    return NULL;
}


void Wifi_Scan();

void Wifi_Open() {
    if (m_wifi_state != wifi_state_closed) {
        return;
    }

#ifndef SIMULATOR
    SendMessageEmpty(MSG_ID_GUI_WIFI_OPEN_REQ);
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_WIFI_OPEN_RSP;
    SM_SendMessage();
#endif

    Wifi_SetState(wifi_state_opening);
}

void Wifi_Close() {
    if (m_wifi_state != wifi_state_idle) {
        return;
    }

#ifndef SIMULATOR
    SendMessageEmpty(MSG_ID_GUI_WIFI_CLOSE_REQ);
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_WIFI_CLOSE_RSP;
    SM_SendMessage();
#endif

    //Wifi_SetState(wifi_state_closing);
    Wifi_SetState(wifi_state_closed);
}

void Wifi_Scan() {
    if (m_wifi_state != wifi_state_idle && m_wifi_state != wifi_state_closed) {
        return;
    }

#ifndef SIMULATOR
    SendMessageEmpty(MSG_ID_GUI_WIFI_SCAN_REQ);
#else
    static struct_wifi_scan gWifi_Scan_List[3] = {
        {0, 5, 40, 1, 0, 0, 0, {0xA0, 0xB1, 0xC2, 0xD3, 0xE4, 0xF5}, {0x41, 0x62, 0x63, 0x64, 0}, 0, 0, 0, 0},
        {0, 5, 90, 1, 0, 0, 0, {0xA0, 0xB1, 0xC2, 0xD3, 0xE4, 0xF5}, {0x65, 0x6F, 0x73, 0x63, 0x76, 0x0}, 0, 0, 0, 0},
        {0, 6, 60, 0, 0, 0, 0, {0xA0, 0xB1, 0xC2, 0xD3, 0xE4, 0xF5}, {0x52, 0x45, 0x58, 0x4A, 0x57, 0}, 0, 0, 0, 0}
    };

    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_WIFI_SCAN_RSP;
    sm_message.data.wifi.scan_num = 3;
    sm_message.data.wifi.scan_list = &gWifi_Scan_List[0];
    SM_SendMessage();
#endif

    Wifi_SetState(wifi_state_scaning);
}

bool Wifi_Connect(uint8_t address[], char password[]) {
    if (m_wifi_state != wifi_state_idle) {
        return false;
    }

#ifndef SIMULATOR
    struct_wifi_scan* entry = FindScanListEntry(address);
    if (entry != NULL) {
        struct_remote_message msg_send;
        InitMessage(msg_send, MSG_ID_GUI_WIFI_CONNECT_REQ);
        msg_send.msg.msg_gui_req.para.wifi.enet_info = entry;
        memcpy(msg_send.msg.msg_gui_req.para.wifi.password, password, sizeof(msg_send.msg.msg_gui_req.para.wifi.password)-1);
        Message_Send(&msg_send);
        return true;
    }
    return false;
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_WIFI_CONNECT_RSP;
    SM_SendMessage();
	return true;
#endif

    Wifi_SetState(wifi_state_connecting);
}

void Wifi_Disconnect() {
    if (m_wifi_state != wifi_state_idle) {
        return;
    }

#ifndef SIMULATOR
    SendMessageEmpty(MSG_ID_GUI_WIFI_DISCONNECT_REQ);
#else
    SM_InitMessage();
    sm_message.msgid = MSG_ID_GUI_WIFI_DISCONNECT_RSP;
    SM_SendMessage();
#endif

    Wifi_SetState(wifi_state_disconnecting);
}

#ifndef SIMULATOR
extern "C"{
void Dmic_StartRecord();
void Dmic_FinishRecord();
void Dmic_CancelRecord();
}
#endif
/* Mic */
void Mic_StartRecord() {
#ifndef SIMULATOR
    Dmic_StartRecord();
#else

#endif
}

void Mic_FinishRecord()
{
#ifndef SIMULATOR
    Dmic_FinishRecord();
#else

#endif
}

void Mic_CancelRecord()
{
#ifndef SIMULATOR
    Dmic_CancelRecord(); 
#else

#endif
}
