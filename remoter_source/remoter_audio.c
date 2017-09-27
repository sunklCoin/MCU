/*
 * remoter_audio.c
 *
 *  Created on: 2017年8月30日
 *      Author: xuke
 */

#include "remoter_audio.h"

void Audio_Task(void *pvParameters)
{
	PRINTF("%s\n", __func__);
    while (1)
    {
        vTaskDelay(10);
    }
//	vTaskSuspend(NULL);
}

int Audio_Init(void)
{
	return 0;
}

