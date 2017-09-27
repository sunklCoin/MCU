/*
 * remoter_main.h
 *
 *  Created on: 2017年8月15日
 *      Author: xuke
 */

#ifndef REMOTER_MAIN_H_
#define REMOTER_MAIN_H_

#include "remoter_base.h"
#include "remoter_message.h"

#define I2C_MASTER_SLAVE_ADDR_7BIT 0x7EU

#define TASK_NAME_LENGTH	32
#define TASK_QUEUE_LENGTH	128

struct remoter_task
{
	int task_index;
	const char task_name[TASK_NAME_LENGTH];
	int stack_size;
	int priority;
	void (*task_handler)(void *pvParameters);
	TaskHandle_t handle_t;
	QueueHandle_t task_queue;
	int queue_size;
	int to_run;		// According to initialization of every module.
};

int Message_Send(struct remote_message *p_message);
int Message_Receive(struct remote_message *p_message);

extern int TouchPanel_Init(void);
extern int LCM_Init(void);
extern int Gui_Init(void);
extern int WiFi_Init(void);
extern int Bluetooth_Init(void);
extern int Zigbee_Init(void);
extern int PowerManage_Init(void);
extern int Keypad_Init(void);
extern int Audio_Init(void);
extern int Dmic_Init(void);

extern void TouchPanel_Task(void *pvParameters);
extern void Gui_Task(void *pvParameters);
extern void GuiService_Task(void *pvParameters);
extern void WiFi_Task(void *pvParameters);
extern void Bluetooth_Task(void *pvParameters);
extern void Zigbee_Task(void *pvParameters);
extern void PowerManage_Task(void *pvParameters);
extern void Keypad_Task(void *pvParameters);
extern void Audio_Task(void *pvParameters);
extern void Dmic_Task(void *pvParameters);

extern void BackLight_InitPWM(void);
extern void BOARD_InitSPIFI(void);

extern struct remoter_task remoter_tasks[];
extern struct message_bluetooth msg_bt_advertising_start;
extern struct message_bluetooth msg_bt_advertising_stop;
extern struct message_bluetooth msg_bt_scan_start;
extern struct message_bluetooth msg_bt_scan_stop;
extern struct message_bluetooth msg_bt_connect;
extern struct message_bluetooth msg_bt_disconnect;

#endif /* REMOTER_MAIN_H_ */
