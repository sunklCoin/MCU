/*
 * remoter_zigbee.c
 *
 *  Created on: 2017年8月30日
 *      Author: xuke
 */

#include "remoter_zigbee.h"

void Zigbee_Task(void *pvParameters)
{
	PRINTF("%s\n", __func__);
    while (1)
    {
        vTaskDelay(10);
    }
//	vTaskSuspend(NULL);
}

int Zigbee_Init(void)
{
	return 0;
}

