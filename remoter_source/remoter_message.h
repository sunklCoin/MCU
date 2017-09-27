/*
 * remoter_message.h
 *
 *  Created on: 2017/08/09
 *      Author: xuke
 */

#ifndef REMOTER_MESSAGE_H_
#define REMOTER_MESSAGE_H_

#include "remoter_base.h"
#include "remoter_bluetooth.h"
#include "remoter_messsage_gui.h"
#include "remoter_wifi.h"


#define MSG_QUEUE_MAX	256

#define MSG_BT_LEN	128
#define MSG_WIFI_LEN	128
#define USART_BUFFER 128

enum message_bluetooth_type {
	BT_CMD		= 0xEA,
	BT_DATA_REQ	= 0xEB,
	BT_DATA_IND	= 0XEC,
	BT_EVENT	= 0xED,
};

enum message_bluetooth_cmd_list {
	BT_CMD_Begin = 0x00,
	BT_CMD_Advertising,				// 0x01
	BT_CMD_Scan,					// 0x02
	BT_CMD_Connect,					// 0x03
	BT_CMD_Disconnect,				// 0x04
	BT_CMD_SetDeviceName,			// 0x05
	BT_CMD_Bond,					// 0x06
	BT_CMD_CentralUpdateParam,		// 0x07
	BT_CMD_PeripheralUpdateParam,	// 0x08
	BT_CMD_End,
};

enum message_bluetooth_event_list {
	BT_Event_Begin = 0x00,
	BT_Event_AdvertisingComplete,	// 0x01
	BT_Event_ScanResult,			// 0x02
	BT_Event_ScanComplete,			// 0x03
	BT_Event_Connected,				// 0x04
	BT_Event_Disconnected,			// 0x05
	BT_Event_DeviceNameComplete,	// 0x06
	BT_Event_BondComplete,			// 0x07
	BT_Event_CentralUpdateParam,	// 0x08
	BT_Event_PeripheralUpdateParam,	// 0x09		?? 0x0A
	BT_Event_End,
};

typedef struct message_bluetooth {
	uint8_t msg_type;
	uint8_t msg_id;
	uint8_t param_len;
	char params[MSG_BT_LEN];
} struct_message_bluetooth;

#if 0
typedef struct message_wifi {
	uint8_t msg;
	uint8_t len;
	char params[MSG_WIFI_LEN];
} struct_message_wifi;
#else
enum message_wifi_type {
	WIFI_OPEN		= 0x5A,
	WIFI_SCAN		= 0x5B,
	WIFI_CONNECT	= 0X5C,
	WIFI_DISC		= 0x5D,
	WIFI_CLOSE		= 0x5F,
};

typedef struct wifi_scan_info {
    int scan_num;
    struct_wifi_scan_list * pWifi_Scan_List;
} struct_wifi_scan_info;

typedef struct message_wifi {
	int msg_type;
	struct_wifi_scan_info wifi_info;
} struct_message_wifi;
#endif

typedef struct message_pm {
	uint8_t capacity;
	uint8_t batt_temperature;
	uint8_t charging_status;
} struct_message_pm;

typedef struct remote_message {
	uint16_t task_src;
	uint16_t task_dst;
	union remote_msg {
		char msg_uart_str[USART_BUFFER];
		struct_message_bluetooth msg_bt;
		struct_message_wifi msg_wifi;
		struct_message_pm msg_pm;
		struct_message_gui_req msg_gui_req;
		struct_message_gui_rsp msg_gui_rsp;
	} msg;
} struct_remote_message;

extern int Message_Send(struct_remote_message *p_message);
extern int Message_Receive(struct_remote_message *p_message);
extern int Message_Receive_NoBlock(struct_remote_message *p_message);

#endif /* REMOTER_MESSAGE_H_ */
