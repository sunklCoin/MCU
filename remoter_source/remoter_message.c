/*
 * remoter_message.c
 *
 *  Created on: 2017年8月30日
 *      Author: xuke
 */

#include "remoter_message.h"

/* Bluetoot module messages.	Begin */
struct message_bluetooth msg_bt_advertising_start = {
	.msg_type = BT_CMD,
	.msg_id = BT_CMD_Advertising,
	.param_len = 5,
	.params = {0x01, 0x03, 0x00, 0x64, 0x00},
};

struct message_bluetooth msg_bt_advertising_stop = {
	.msg_type = BT_CMD,
	.msg_id = BT_CMD_Advertising,
	.param_len = 5,
	.params = {0x00, 0x00, 0x00, 0x00, 0x00},
};

struct message_bluetooth msg_bt_scan_start = {
	.msg_type = BT_CMD,
	.msg_id = BT_CMD_Scan,
	.param_len = 1,
	.params = {0x01},
};

struct message_bluetooth msg_bt_scan_stop = {
	.msg_type = BT_CMD,
	.msg_id = BT_CMD_Scan,
	.param_len = 1,
	.params = {0x00},
};

struct message_bluetooth msg_bt_connect = {
	.msg_type = BT_CMD,
	.msg_id = BT_CMD_Connect,
	.param_len = 6,
	.params = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66},
};

struct message_bluetooth msg_bt_disconnect = {
	.msg_type = BT_CMD,
	.msg_id = BT_CMD_Disconnect,
	.param_len = 6,
	.params = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66},
};
/* Bluetoot module messages.	Begin */
