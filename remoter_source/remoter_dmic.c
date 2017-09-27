/*
 * remoter_dmic.c
 *
 *  Created on: 2017年9月1日
 *      Author: pangkun
 */

#include "remoter_dmic.h"

/* DMIC user callback */
void DMIC_UserCallback(DMIC_Type *base, dmic_dma_handle_t *handle, status_t status, void *userData)
{
    userData = userData;
    if (status == kStatus_DMIC_Idle)
    {
        g_Transfer_Done = true;
    }
}

void Dmic_Task(void *pvParameters)
{
    uint32_t i;
    dmic_transfer_t receiveXfer;

	PRINTF("%s: is created\n", __func__);

	while(1) {
#if 1	// xuke @ 20170926	For temp.
		vTaskSuspend(NULL);
#else
		taskENTER_CRITICAL();

		receiveXfer.dataSize = 2 * BUFFER_LENGTH;
		receiveXfer.data = g_rxBuffer;
		PRINTF("Buffer Data before transfer \r\n");
		for (i = 0; i < BUFFER_LENGTH; i++)
		{
			PRINTF("%d\r\n", g_rxBuffer[i]);
		}
		DMIC_TransferReceiveDMA(DMIC0, &g_dmicDmaHandle, &receiveXfer, APP_DMIC_CHANNEL);

		/* Wait for DMA transfer finish */
		while (g_Transfer_Done == false)
		{
		}

		PRINTF("Transfer completed\r\n");
		PRINTF("******\n");
		PRINTF("******\n");
		PRINTF("******\n");
		PRINTF("Buffer Data after transfer \r\n");
		for (i = 0; i < BUFFER_LENGTH; i++)
		{
			PRINTF("%d\r\n", g_rxBuffer[i]);
		}
		PRINTF("******---------\n");
		PRINTF("******---------\n");
		PRINTF("******---------\n");
		taskEXIT_CRITICAL();

		vTaskDelay(10000);
		/*
		 * if the parameters is null , to suspend myself.
		 * it need vTaskResume() or vTaskResumeFromISR() to resume this task
		 * */
	//vTaskSuspend(NULL);
#endif
	}
}

int Dmic_Init(void)
{
	status_t status = kStatus_Success;
    dmic_channel_config_t dmic_channel_cfg;

    /* Board pin, clock, debug console init */
    CLOCK_EnableClock(kCLOCK_InputMux);
    CLOCK_EnableClock(kCLOCK_Iocon);
    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);

    /* DMIC uses 12MHz FRO clock */
    CLOCK_AttachClk(kFRO12M_to_DMIC);

    /*12MHz divided by 5 = 2.4MHz PDM clock --> gives 48kHz sample rate */
    /*12MHz divided by 15 = 800 KHz PDM clock --> gives 16kHz sample rate */
    CLOCK_SetClkDiv(kCLOCK_DivDmicClk, 14, false);

    dmic_channel_cfg.divhfclk = kDMIC_PdmDiv1;
    dmic_channel_cfg.osr = 25U;
    dmic_channel_cfg.gainshft = 2U;
    dmic_channel_cfg.preac2coef = kDMIC_CompValueZero;
    dmic_channel_cfg.preac4coef = kDMIC_CompValueZero;
    dmic_channel_cfg.dc_cut_level = kDMIC_DcCut155;
    dmic_channel_cfg.post_dc_gain_reduce = 1;
    dmic_channel_cfg.saturate16bit = 1U;
    dmic_channel_cfg.sample_rate = kDMIC_PhyFullSpeed;
    DMIC_Init(DMIC0);

    DMIC_ConfigIO(DMIC0, kDMIC_PdmDual);
    DMIC_Use2fs(DMIC0, true);
    DMIC_SetOperationMode(DMIC0, kDMIC_OperationModeDma);
    DMIC_ConfigChannel(DMIC0, APP_DMIC_CHANNEL, kDMIC_Left, &dmic_channel_cfg);

    DMIC_FifoChannel(DMIC0, APP_DMIC_CHANNEL, FIFO_DEPTH, true, true);

    DMIC_EnableChannnel(DMIC0, APP_DMIC_CHANNEL_ENABLE);
    PRINTF("Configure DMA\r\n");

    DMA_Init(DMA0);

    DMA_EnableChannel(DMA0, APP_DMAREQ_CHANNEL);

    /* Request dma channels from DMA manager. */
    DMA_CreateHandle(&g_dmicRxDmaHandle, DMA0, APP_DMAREQ_CHANNEL);

    /* Create DMIC DMA handle. */
    DMIC_TransferCreateHandleDMA(DMIC0, &g_dmicDmaHandle, DMIC_UserCallback, NULL, &g_dmicRxDmaHandle);


    PRINTF("%s: end\n", __func__);

    return (status == kStatus_Success);
}
