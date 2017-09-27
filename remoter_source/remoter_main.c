/*
 * remoter_main.c
 *
 *  Created on: 2017/08/05
 *      Author: xuke
 */

#include "remoter_main.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/
//__attribute__ ((section(".external_mcp_flash")))
//__attribute__ ((section(".bss.$BOARD_SDRAM")))
struct remoter_task remoter_tasks[] = {
	/* index */		/* task name */			/* stack size */				/* priority */				/* task handler */	/* handle_t */	/* queue handle */	/* queue size */	/* to run */
	{TASK_GUI,		"Gui_Task",				configMINIMAL_STACK_SIZE + 900,	configMAX_PRIORITIES - 1,	Gui_Task,			NULL,			NULL,				TASK_MAX,			0},
	{TASK_GUI_SVC,	"GuiService_Task",		configMINIMAL_STACK_SIZE + 200,	configMAX_PRIORITIES - 1,	GuiService_Task,	NULL,			NULL,				TASK_MAX,			1},
	{TASK_TP,		"TouchPanel_Task",		configMINIMAL_STACK_SIZE + 100,	configMAX_PRIORITIES - 1,	TouchPanel_Task,	NULL,			NULL,				1,					0},
	{TASK_BT,		"Bluetooth_Task",		configMINIMAL_STACK_SIZE + 100,	configMAX_PRIORITIES - 2,	Bluetooth_Task,		NULL,			NULL,				1,					0},
	{TASK_WIFI,		"WiFi_Task",			configMINIMAL_STACK_SIZE + 2000,configMAX_PRIORITIES - 3,	WiFi_Task,			NULL,			NULL,				1,					0},
	{TASK_ZIGBEE,	"Zigbee_Task",			configMINIMAL_STACK_SIZE + 100,	configMAX_PRIORITIES - 3,	Zigbee_Task,		NULL,			NULL,				1,					0},
//	{TASK_KEYPAD,	"Keypad_Task",			configMINIMAL_STACK_SIZE + 100,	configMAX_PRIORITIES - 1,	Keypad_Task,		NULL,			NULL,				1,					0},
	{TASK_PM,		"PowerManage_Task",		configMINIMAL_STACK_SIZE + 100,	configMAX_PRIORITIES - 1,	PowerManage_Task,	NULL,			NULL,				1,					0},
	{TASK_AUDIO,	"Audio_Task",			configMINIMAL_STACK_SIZE + 100,	configMAX_PRIORITIES - 3,	Audio_Task,			NULL,			NULL,				1,					0},
	{TASK_DMIC,		"Dmic_Task", 			configMINIMAL_STACK_SIZE + 100,	configMAX_PRIORITIES - 3,	Dmic_Task,			NULL,			NULL,				1,					0},
};

QueueHandle_t remoter_task_queue;

int Task_Init(void)
{
	int i = 0, ret = 0;

	/* Create tasks */
	for (i=0; i<ARRAY_SIZE(remoter_tasks); ++i)
	{
		if (!remoter_tasks[i].to_run)
			continue;

		/* Create tasks. */
		ret = xTaskCreate(remoter_tasks[i].task_handler, remoter_tasks[i].task_name,
				remoter_tasks[i].stack_size, NULL, remoter_tasks[i].priority, &remoter_tasks[i].handle_t);
		if (ret != pdPASS)
			PRINTF("%s, Failed to create %s\n", __func__, remoter_tasks[i].task_name);
		else
			PRINTF("%s, %s is created\n", __func__, remoter_tasks[i].task_name);

		/* Create queues for all tasks. */
		remoter_tasks[i].task_queue = xQueueCreate(remoter_tasks[i].queue_size, sizeof(struct remote_message));
		if (remoter_tasks[i].task_queue == pdFAIL)
			PRINTF("%s, Failed to create xQueue for %s\n", __func__, remoter_tasks[i].task_name);
		else
			PRINTF("%s, xQueue for %s is created\n", __func__, remoter_tasks[i].task_name);
	}

	vTaskStartScheduler();

    return 0;
}

int Task_GetCurrentIndex(void)
{
    int i = 0, ret = 0;
    TaskHandle_t task_handle = xTaskGetCurrentTaskHandle();

    for (i=0; i<ARRAY_SIZE(remoter_tasks); ++i) {
        if (remoter_tasks[i].handle_t == task_handle) {
            ret = i;
            break;
        }
    }

    if (i == ARRAY_SIZE(remoter_tasks)) {
        i = 0;
        PRINTF("%s, failed to get current task index\n", __func__);
    }

    return ret;
}

int Task_GetIndex(int task_index)
{
    int i = 0, ret = 0;

    for (i=0; i<ARRAY_SIZE(remoter_tasks); ++i) {
        if (remoter_tasks[i].task_index == task_index) {
            ret = i;
            return ret;
        }
    }

    PRINTF("%s, failed to get current task index\n", __func__);
    return ret;
}

int Message_Send(struct_remote_message *p_message)
{
	int ret = 0;
	struct remote_message *p_msg = p_message;
    int index = Task_GetIndex(p_msg->task_dst);

    vTaskResume(remoter_tasks[index].handle_t);
    xQueueSend(remoter_tasks[index].task_queue, p_msg, portMAX_DELAY);

	return ret;
}

inline int Message_Receive(struct_remote_message *p_message)
{
	int ret = 0, task_index = 0;
	struct remote_message *p_msg = p_message;

	task_index = Task_GetCurrentIndex();
	xQueueReceive(remoter_tasks[task_index].task_queue, p_msg, portMAX_DELAY);

	return ret;
}

inline int Message_Receive_NoBlock(struct_remote_message *p_message)
{
	int ret = 0, task_index = 0;
	struct remote_message *p_msg = p_message;

	task_index = Task_GetCurrentIndex();
	ret = xQueueReceive(remoter_tasks[task_index].task_queue, p_msg, (TickType_t) 0);

	return ret;
}

int Task_Manage(void)
{
//	int i = 0;
	int ret = 0;
//	struct remoter_message queue_message = {0};
//	QueueHandle_t task_queue = NULL;

	Task_Init();
#if 0
	vTaskSuspend(remoter_tasks[TASK_GUI].task_handler);
	vTaskSuspend(remoter_tasks[TASK_TP].task_handler);
	vTaskSuspend(remoter_tasks[TASK_BT_TX].task_handler);
	vTaskSuspend(remoter_tasks[TASK_BT_RX].task_handler);
	vTaskSuspend(remoter_tasks[TASK_WIFI].task_handler);
	vTaskSuspend(remoter_tasks[TASK_ZIGBEE].task_handler);
	vTaskSuspend(remoter_tasks[TASK_KEYPAD].task_handler);
	vTaskSuspend(remoter_tasks[TASK_PM].task_handler);
	vTaskSuspend(remoter_tasks[TASK_AUDIO].task_handler);

	/* Create a main queue to dispatch messages for all tasks. */
	remoter_task_queue = xQueueCreate(TASK_QUEUE_LENGTH, sizeof(struct remote_message));
	if (remoter_task_queue == pdFAIL)
	{
		PRINTF("%s, Failed to create main queue\n", __func__);
		return -1;
	}
#endif

    while (1);

    return ret;
}

int Uart_Debug_Init(void)
{
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    return 0;
}

/* Init board hardware. */
int Board_Init(void)
{
	PRINTF("%s\n", __func__);

	BOARD_InitBootPins();
    BOARD_BootClock180M();
    BOARD_InitSDRAM();
#if !GUI_RESOURCE_ONLY_INTERNAL_FLASH
    BOARD_InitSPIFI();
#endif
//    Board_LED_Init();
    Keypad_Init();
	Uart_Debug_Init();

	remoter_tasks[TASK_TP].to_run = TouchPanel_Init();
	remoter_tasks[TASK_GUI].to_run = LCM_Init();
	remoter_tasks[TASK_GUI].to_run &= Gui_Init();
	remoter_tasks[TASK_BT].to_run = Bluetooth_Init();
//	remoter_tasks[TASK_KEYPAD].to_run = Keypad_Init();
	remoter_tasks[TASK_WIFI].to_run = WiFi_Init();
	remoter_tasks[TASK_PM].to_run = PowerManage_Init();
	remoter_tasks[TASK_DMIC].to_run = Dmic_Init();

    BOARD_InitDebugConsole();

    /* Set the back light PWM. */
//	BackLight_InitPWM();

    return 0;
}

int main(void)
{
	int ret = 0;

	Board_Init();
	ret = Task_Manage();

    return ret;
}
