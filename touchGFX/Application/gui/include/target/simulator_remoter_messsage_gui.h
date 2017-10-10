/*
 * remoter_messsage_gui.h
 *
 *  Created on: 2017/9/5
 *      Author: yuhang
 */

#ifndef REMOTER_MESSAGE_GUI_H_
#define REMOTER_MESSAGE_GUI_H_
#include <stdint.h>
#define RM_MSG_BASE                     (0x0400)
#define MSG_RESULT_GUI_OK               0
#define MSG_RESULT_GUI_ERR           1

typedef enum {
    MSG_ID_GUI_BT_BEGIN = RM_MSG_BASE,
    MSG_ID_GUI_BT_OPEN_REQ,
    MSG_ID_GUI_BT_OPEN_RSP,
    MSG_ID_GUI_BT_CLOSE_REQ,
    MSG_ID_GUI_BT_CLOSE_RSP,
    MSG_ID_GUI_BT_SCAN_START_REQ,
    MSG_ID_GUI_BT_SCAN_STOP_REQ,
    MSG_ID_GUI_BT_SCAN_RESULT_IND,
    MSG_ID_GUI_BT_SCAN_COMPLETE_IND,
    MSG_ID_GUI_BT_CONNECT_REQ,
    MSG_ID_GUI_BT_CONNECT_RSP,
    MSG_ID_GUI_BT_DISCONNECT_REQ,
    MSG_ID_GUI_BT_DISCONNECT_RSP,
    MSG_ID_GUI_BT_SET_DEVICENAME_REQ,
    MSG_ID_GUI_BT_SET_DEVICENAME_RSP,
    MSG_ID_GUI_BT_BOND_REQ,
    MSG_ID_GUI_BT_BOND_RSP,
    MSG_ID_GUI_BT_CENTRAL_UPDATE_PARAM_REQ,
    MSG_ID_GUI_BT_CENTRAL_UPDATE_PARAM_RSP,
    MSG_ID_GUI_BT_PERIPHERAL_UPDATE_PARAM_REQ,
    MSG_ID_GUI_BT_PERIPHERAL_UPDATE_PARAM_RSP,
    MSG_ID_GUI_BT_END,
    MSG_ID_GUI_WIFI_BEGIN,
    MSG_ID_GUI_WIFI_OPEN_REQ,
    MSG_ID_GUI_WIFI_OPEN_RSP,
    MSG_ID_GUI_WIFI_CLOSE_REQ,
    MSG_ID_GUI_WIFI_CLOSE_RSP,
    MSG_ID_GUI_WIFI_SCAN_REQ,
    MSG_ID_GUI_WIFI_SCAN_RSP,
    MSG_ID_GUI_WIFI_CONNECT_REQ,
    MSG_ID_GUI_WIFI_CONNECT_RSP,
    MSG_ID_GUI_WIFI_DISCONNECT_REQ,
    MSG_ID_GUI_WIFI_DISCONNECT_RSP,
    MSG_ID_GUI_WIFI_END,
    MSG_ID_GUI_PM_BEGIN,
    MSG_ID_GUI_PM_REFRESH_IND,
    MSG_ID_GUI_PM_END,
    MSG_ID_GUI_KEYPAD_BEGIN,
    MSG_ID_GUI_KEYPAD_INPUT_IND,
    MSG_ID_GUI_KEYPAD_END,
} remote_msg_id;


#define BT_DEVICENAME_LEN       (60)
#define BT_MACADDRESS_LEN       (6)

/* bluetooth */
typedef struct gui_para_bt_req {
    char deviceName[BT_DEVICENAME_LEN];
    uint8_t address[BT_MACADDRESS_LEN];
} struct_gui_para_bt_req;

typedef struct gui_data_bt_rsp {
    char deviceName[BT_DEVICENAME_LEN];
    uint8_t address_type;
    uint8_t address[BT_MACADDRESS_LEN];
    uint8_t num;
    uint8_t reason;
    uint8_t bonded;
} struct_gui_data_bt_rsp;

/* powermanager */
typedef struct gui_data_pm_rsp {
    uint8_t level;
    uint8_t battery_temp;
    uint8_t charging_status;
} struct_gui_data_pm_rsp;

typedef struct gui_data_key_rsp {
    uint8_t key_type;
    uint8_t key_code;
} struct_gui_data_key_rsp;

/* wifi */
#if 0
typedef struct wifi_scan_list {
    uint8_t channel;	/* wifi ap channel */
    uint8_t ssid_len;
    uint8_t rssi;		/* wifi ap indicator */
    uint8_t bssid[6];	/* wifi ap mac address */
    uint8_t ssid[32];	/* wifi ap name */
} struct_wifi_scan;
#else
typedef struct wifi_scan_list {
    uint8_t channel;
    uint8_t ssid_len;
    uint8_t rssi;
    uint8_t security_enabled;
    uint16_t beacon_period;
    uint8_t preamble;
    uint8_t bss_type;
    uint8_t bssid[6];
    uint8_t ssid[32];
    uint8_t rsn_cipher;
    uint8_t rsn_auth;
    uint8_t wpa_cipher;
    uint8_t wpa_auth;
} struct_wifi_scan;
#endif

typedef struct gui_para_wifi_req {
    struct_wifi_scan* enet_info;
    char password[64];
} struct_gui_para_wifi_req;

typedef struct gui_data_wifi_rsp {
    uint8_t scan_num;
    struct_wifi_scan * scan_list;
} struct_gui_data_wifi_rsp;

typedef struct message_gui_req {
    uint32_t msgid;
    union gui_data_req {
    	struct_gui_para_bt_req bt;
        struct_gui_para_wifi_req wifi;
    } para;
} struct_message_gui_req;

typedef struct message_gui_rsp {
    uint32_t msgid;
    uint8_t result;
    union gui_data_rsp {
        struct_gui_data_bt_rsp bt;
        struct_gui_data_pm_rsp pm;
        struct_gui_data_wifi_rsp wifi;
        struct_gui_data_key_rsp key;
    } data;
} struct_message_gui_rsp;

#endif /* REMOTER_MESSAGE_GUI_H_ */
