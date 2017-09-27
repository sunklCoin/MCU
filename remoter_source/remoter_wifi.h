/*
 * remoter_wifi.h
 *
 *  Created on: 2017年8月15日
 *      Author: xuke
 */

#ifndef REMOTER_WIFI_H_
#define REMOTER_WIFI_H_

#include "remoter_base.h"
#include "fsl_spi.h"
#include "fsl_spi_freertos.h"
#include "remoter_message.h"


//enum message_wifi_type {
//	WIFI_OPEN		= 0x5A,
//	WIFI_SCAN		= 0x5B,
//	WIFI_CONNECT	= 0X5C,
//	WIFI_DISC		= 0x5D,
//	WIFI_CLOSE		= 0x5F,
//};
//
//typedef struct wifi_scan_info {
//	int scan_num;
//	ENET_SCAN_LIST_PTR pEnet_Scan_List;
//} struct_wifi_scan_info;
//
//typedef struct message_wifi {
//	int msg_type;
//	struct_wifi_scan_info wifi_scan_list;
//} struct_message_wifi;

#endif /* REMOTER_WIFI_H_ */
