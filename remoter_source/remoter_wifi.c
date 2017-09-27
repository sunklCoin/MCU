/*
 * remoter_wifi.c
 *
 *  Created on: 2017�?�?5�?
 *      Author: xuke
 */

#include "remoter_wifi.h"

#include "FreeRTOS_CLI.h"
#include "main.h"
#include "throughput.h"
#include "task.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SHELL_TASK 0
#define DUMP_WIFI_SCAN_LIST 1
#define LOGD(format,...) PRINTF("[%s][%d]: "format, __func__,__LINE__, ##__VA_ARGS__)

/*!
 * @brief Data structure and callback function for slave SPI communication.
 */
struct remote_message msg_to_mmi = {
	.task_src = TASK_WIFI,
};

extern A_UINT32 concurrent_connect_flag;
extern A_UINT16 ap_channel_hint;
extern A_UINT8 ssid_str_concurrent[MAX_SSID_LENGTH];

/*******************************************************************************
 * Code
 ******************************************************************************/
static void Board_Hw_Init(void);
static void Create_WiFi_Tasks(void);
static int WiFi_Open(void);
static int WiFi_Close(void);
static int WiFi_Scan(void);
static int WiFi_Connect(void);
static int WiFi_Disconnect(void);
static int WiFi_ReceiveMessageFromMMI(void);
static int WiFi_SendMessageToMMI(void);
static int WiFi_Scan_Dump(ENET_SCAN_LIST enet_scan_list, int16_t num_scan);

static void Board_Hw_Init(void)
{
	/* Borad UART4 Init */
	CLOCK_AttachClk(kFRO12M_to_FLEXCOMM4);
}

static void Create_WiFi_Tasks(void)
{
	if (xTaskCreate(wmiconfig_Task1, "wmiconfig1", 5*1024, NULL, configMAX_PRIORITIES - 4, NULL) !=
		pdPASS)
	{
		LOGD("Failed to create wmiconfig2 task");
	}
	if (xTaskCreate(wmiconfig_Task2, "wmiconfig2", 5*1024, NULL, configMAX_PRIORITIES - 2, NULL) !=
		pdPASS)
	{
		LOGD("Failed to create wmiconfig2 task");
	}

	Creat_WiFi_Shell_Tasks();
}

static int WiFi_Scan_Dump(ENET_SCAN_LIST enet_scan_list, int16_t num_scan)
{
	int i;
	A_UINT8 temp_ssid[33];

	LOGD("Scan result count:%d\n",num_scan);

	for (i = 0;i<num_scan;i++)
	{
		memcpy(temp_ssid,enet_scan_list.scan_info_list[i].ssid,enet_scan_list.scan_info_list[i].ssid_len);

		temp_ssid[enet_scan_list.scan_info_list[i].ssid_len] = '\0';

		if (enet_scan_list.scan_info_list[i].ssid_len == 0)
		{
		   printf("ssid = SSID Not available\n");
		}
		else {
#if ENABLE_SCC_MODE
		  if((concurrent_connect_flag == 0x0F) && (strcmp((char const *)ssid_str_concurrent, (char const *)temp_ssid) == 0))
		  {
			ap_channel_hint = enet_scan_list.scan_info_list[i].channel;
			printf("scan res ch : %d \n", ap_channel_hint);
			return A_OK;
		  }
		  else if((concurrent_connect_flag == 0x0F))
		  {
			 return A_OK;
		  }
		  else
#endif
		 {
		   printf ("ssid = %s\n",temp_ssid);

		printf ("bssid = %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",enet_scan_list.scan_info_list[i].bssid[0],enet_scan_list.scan_info_list[i].bssid[1],enet_scan_list.scan_info_list[i].bssid[2],enet_scan_list.scan_info_list[i].bssid[3],enet_scan_list.scan_info_list[i].bssid[4],enet_scan_list.scan_info_list[i].bssid[5]);
		printf ("channel = %d\n",enet_scan_list.scan_info_list[i].channel);

		printf("indicator = %d\n",enet_scan_list.scan_info_list[i].rssi);

		printf("security = ");

		if(enet_scan_list.scan_info_list[i].security_enabled){
			if(enet_scan_list.scan_info_list[i].rsn_auth || enet_scan_list.scan_info_list[i].rsn_cipher){
				printf("\n\r");
				printf("RSN/WPA2= ");
			}

			if(enet_scan_list.scan_info_list[i].rsn_auth){
				printf(" {");
				if(enet_scan_list.scan_info_list[i].rsn_auth & SECURITY_AUTH_1X){
					printf("802.1X ");
				}

				if(enet_scan_list.scan_info_list[i].rsn_auth & SECURITY_AUTH_PSK){
					printf("PSK ");
				}
				printf("}");
			}

			if(enet_scan_list.scan_info_list[i].rsn_cipher){
				printf(" {");
				/* AP security can support multiple options hence
				 * we check each one separately. Note rsn == wpa2 */
				if(enet_scan_list.scan_info_list[i].rsn_cipher & ATH_CIPHER_TYPE_WEP){
					printf("WEP ");
				}

				if(enet_scan_list.scan_info_list[i].rsn_cipher & ATH_CIPHER_TYPE_TKIP){
					printf("TKIP ");
				}

				if(enet_scan_list.scan_info_list[i].rsn_cipher & ATH_CIPHER_TYPE_CCMP){
					printf("AES ");
				}
				printf("}");
			}

			if(enet_scan_list.scan_info_list[i].wpa_auth || enet_scan_list.scan_info_list[i].wpa_cipher){
				printf("\n\r");
				printf("WPA= ");
			}

			if(enet_scan_list.scan_info_list[i].wpa_auth){
				printf(" {");
				if(enet_scan_list.scan_info_list[i].wpa_auth & SECURITY_AUTH_1X){
					printf("802.1X ");
				}

				if(enet_scan_list.scan_info_list[i].wpa_auth & SECURITY_AUTH_PSK){
					printf("PSK ");
				}
				printf("}");
			}

			if(enet_scan_list.scan_info_list[i].wpa_cipher){
				printf(" {");
				if(enet_scan_list.scan_info_list[i].wpa_cipher & ATH_CIPHER_TYPE_WEP){
					printf("WEP ");
				}

				if(enet_scan_list.scan_info_list[i].wpa_cipher & ATH_CIPHER_TYPE_TKIP){
					printf("TKIP ");
				}

				if(enet_scan_list.scan_info_list[i].wpa_cipher & ATH_CIPHER_TYPE_CCMP){
					printf("AES ");
				}
				printf("}");
			}
			/* it may be old-fashioned WEP this is identified by
			 * absent wpa and rsn ciphers */
			if(enet_scan_list.scan_info_list[i].rsn_cipher == 0 &&
				enet_scan_list.scan_info_list[i].wpa_cipher == 0){
				printf("WEP ");
			}
		}else{
			printf("NONE! ");
		}
		  }
		}
	if(i!= enet_scan_list.num_scan_entries-1)
	{
			 printf("\n ");
			 printf("\n \r");
	}
	else
	{
			 printf("\nshell> ");
	}
	}
}

static int WiFi_Open(void)
{
	return WiFi_Scan();
}

static int WiFi_Scan(void)
{
	int ret;
	int i;
	int16_t num_scan;
	ENET_SCAN_LIST enet_scan_list;

	ret = wmi_set_scan_param(&enet_scan_list, &num_scan);
//	WiFi_Scan_Dump(enet_scan_list, num_scan);

	msg_to_mmi.msg.msg_wifi.wifi_info.scan_num = num_scan;
	if (msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List != NULL)
		free(msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List);
	msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List = (struct_wifi_scan_list *) malloc(sizeof(struct_wifi_scan_list) * num_scan);
	for (i = 0; i < num_scan; i++) {
		msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List[i].ssid_len = enet_scan_list.scan_info_list[i].ssid_len;
		msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List[i].channel = enet_scan_list.scan_info_list[i].channel;
		msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List[i].rssi = enet_scan_list.scan_info_list[i].rssi;
		memcpy(msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List[i].ssid, enet_scan_list.scan_info_list[i].ssid,
				enet_scan_list.scan_info_list[i].ssid_len);
		msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List[i].ssid[enet_scan_list.scan_info_list[i].ssid_len] = '\0';

		memcpy(msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List[i].bssid, enet_scan_list.scan_info_list[i].bssid,
				sizeof(enet_scan_list.scan_info_list[i].bssid) / enet_scan_list.scan_info_list[i].bssid[0]);
#if DUMP_WIFI_SCAN_LIST
		LOGD("-----------------------WIFI SCAN LIST DUMP---------------------------------\n");
		LOGD("AP Index: [%d/%d]\n", i+1, num_scan);
		LOGD("AP Name: %s\n", msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List[i].ssid);
		LOGD("AP MAC Address: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n", msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List[i].bssid[0],
				msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List[i].bssid[1], msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List[i].bssid[2],
				msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List[i].bssid[3], msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List[i].bssid[4],
				msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List[i].bssid[5]);
		LOGD("AP Indicator: %d\n", msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List[i].rssi);
		LOGD("AP Channel: %d\n", msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List[i].channel);
#endif
	}
        msg_to_mmi.msg.msg_wifi.msg_type = WIFI_SCAN;
	return ret;
}

static int WiFi_ReceiveMessageFromMMI(void)
{
	int32_t ret = 0;
	struct_remote_message msg_recv_from_mmi = {0};

	memset(&msg_recv_from_mmi, 0, sizeof(struct_remote_message));
	ret = Message_Receive(&msg_recv_from_mmi);
	if (!ret)
	{
		msg_to_mmi.task_dst = msg_recv_from_mmi.task_src;

		/* If it's WiFi module message, send it. */
		switch (msg_recv_from_mmi.msg.msg_wifi.msg_type) {
		case WIFI_OPEN:
			WiFi_Open();
			break;
		case WIFI_SCAN:
			WiFi_Scan();
			break;
		}
	}

	return ret;
}

static int WiFi_SendMessageToMMI(void)
{
	int32_t ret = 0;
	struct_message_wifi msg_bt_recv_from_ic = {0};

	Message_Send(&msg_to_mmi);
	/*if (msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List != NULL)
		free(msg_to_mmi.msg.msg_wifi.wifi_info.pWifi_Scan_List);*/

	return ret;
}

void WiFi_Task(void *pvParameters)
{
	int ret;
	LOGD("%s\n", __func__);

#if !SHELL_TASK
	HVAC_initialize_networking();
#endif
	WiFi_Scan();

	do {
		ret = WiFi_ReceiveMessageFromMMI();
		PRINTF("%s, WiFi_ReceiveMessageFromMMI done, ret=%d\n", __func__);

		ret = WiFi_SendMessageToMMI();
		PRINTF("%s, WiFi_SendMessageToMMI done, ret=%d\n", __func__, ret);
	} while (kStatus_Success == ret);

	vTaskSuspend(NULL);
}

int WiFi_Init(void)
{
    int ret = 1;
    LOGD("WiFi_Init Begin\r\n");
    Board_Hw_Init();

#if SHELL_TASK
    Create_WiFi_Tasks();
#endif

    return ret;
}
