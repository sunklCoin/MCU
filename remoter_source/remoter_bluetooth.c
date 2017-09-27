/*
 * remoter_bluetooth.c
 *
 *  Created on: 2017年8月15日
 *      Author: xuke
 */

#include "remoter_bluetooth.h"

uint8_t background_buffer[USART_BUFFER];

static usart_rtos_handle_t handle_uart;
static uint8_t cur_msg_id = 0;

struct _usart_handle t_handle_uart;

struct rtos_usart_config usart_config = {
	.base = BLUETOOTH_USART,
	.baudrate = USART_BAUDRATE,
    .parity = kUSART_ParityDisabled,
    .stopbits = kUSART_OneStopBit,
    .buffer = background_buffer,
    .buffer_size = sizeof(background_buffer),
};

char recv_buffer_from_ic[USART_BUFFER];

struct remote_message msg_send_to_mmi = {
	.task_src = TASK_BT,
};

void Bluetooth_GpioInit(void)
{
    GPIO_Type *instanceList[] = GPIO_BASE_PTRS;
    gpio_pin_config_t pin_config[] = {
        kGPIO_DigitalOutput, 0,		// low as default.
        kGPIO_DigitalOutput, 1,		// high as default.
    };

    GPIO_PinInit(instanceList[0], BT_GPIO_WAKEUP_PORT, BT_GPIO_WAKEUP_PIN, &pin_config[0]);
	GPIO_PinInit(instanceList[0], BT_GPIO_HW_RESET_PORT, BT_GPIO_HW_RESET_PIN, &pin_config[1]);
    GPIO_PinInit(instanceList[0], BT_GPIO_SW_RESET_PORT, BT_GPIO_SW_RESET_PIN, &pin_config[1]);
}

void Bluetooth_GpioOutputWritePin(uint8_t instance, uint32_t port, uint32_t pin, uint8_t output)
{
    GPIO_Type *instanceList[] = GPIO_BASE_PTRS;

    GPIO_WritePinOutput(instanceList[instance], port, pin, output);
}

void Bluetooth_ModuleWakeup(int wakeup_enable, int delay)
{
	int enable = wakeup_enable, dly = delay;

	Bluetooth_GpioOutputWritePin(0, BT_GPIO_WAKEUP_PORT, BT_GPIO_WAKEUP_PIN, enable);
	vTaskDelay(dly);
	Bluetooth_GpioOutputWritePin(0, BT_GPIO_WAKEUP_PORT, BT_GPIO_WAKEUP_PIN, !enable);
	vTaskDelay(dly);
}

void Bluetooth_ModuleHWReset(void)
{
	int dly = 300;

	Bluetooth_GpioOutputWritePin(0, BT_GPIO_HW_RESET_PORT, BT_GPIO_HW_RESET_PIN, pdTRUE);
	vTaskDelay(dly);
	Bluetooth_GpioOutputWritePin(0, BT_GPIO_HW_RESET_PORT, BT_GPIO_HW_RESET_PIN, pdFALSE);
	vTaskDelay(dly);
	Bluetooth_GpioOutputWritePin(0, BT_GPIO_HW_RESET_PORT, BT_GPIO_HW_RESET_PIN, pdTRUE);
	vTaskDelay(dly);
}

int Bluetooth_ReceiveMessageFromMMI(void)
{
	int32_t ret = 0;
	struct remote_message msg_recv_from_mmi = {0};

    memset(&msg_recv_from_mmi, 0, sizeof(struct remote_message));
    ret = Message_Receive(&msg_recv_from_mmi);
	if (!ret)
	{
		msg_send_to_mmi.task_dst = msg_recv_from_mmi.task_src;

		/* If it's BT module message, send it. */
		if ((msg_recv_from_mmi.msg.msg_bt.msg_type == BT_CMD) || (msg_recv_from_mmi.msg.msg_bt.msg_type == BT_DATA_REQ))
		{
			PRINTF("%s, send BT message, msg_type=0x%x, param_len=%d\n", __func__,
				msg_recv_from_mmi.msg.msg_bt.msg_type, msg_recv_from_mmi.msg.msg_bt.param_len);
			Bluetooth_ModuleWakeup(pdTRUE, 300);
			ret = USART_RTOS_Send(&handle_uart, (uint8_t *)&msg_recv_from_mmi.msg.msg_bt, msg_recv_from_mmi.msg.msg_bt.param_len + 3);
			PRINTF("%s, USART_RTOS_Send done, ret=%d, msg_id=0x%x\n", __func__, ret, msg_recv_from_mmi.msg.msg_bt.msg_id);
		}
	}

	return ret;
}

int Bluetooth_SendMessageToMMI(void)
{
	int32_t ret = 0, i = 0;
    size_t len = 0;
	struct message_bluetooth msg_bt_recv_from_ic = {0};
	uint8_t msg_buffer = 0;

	ret = USART_RTOS_Receive(&handle_uart, &msg_buffer, 1, &len);
	PRINTF("%s, ret=%d, msg_buffer=0x%x\n", __func__, ret, msg_buffer);

	/* ASCII string. */
	if ((msg_buffer >= ' ') && (msg_buffer <= '~'))
	{
		recv_buffer_from_ic[i++] = msg_buffer;
		do
		{
			ret = USART_RTOS_Receive(&handle_uart, &msg_buffer, 1, &len);
			recv_buffer_from_ic[i] = msg_buffer;
			PRINTF("%s, ret=%d, len=%d, msg_buffer=0x%x\n", __func__, ret, len, msg_buffer);
		} while (msg_buffer && (++i < USART_BUFFER));

		if (i >= USART_BUFFER)
		{
			recv_buffer_from_ic[USART_BUFFER] = 0;
			PRINTF("%s, recv_buffer_from_ic is overflow, set 0 to the end\n", __func__);
		}
		else
			PRINTF("%s, recv_buffer_from_ic=%s\n", __func__, recv_buffer_from_ic);

		strncpy(msg_send_to_mmi.msg.msg_uart_str, recv_buffer_from_ic, strlen(recv_buffer_from_ic));
	}
	else if ((msg_buffer == BT_DATA_REQ) || (msg_buffer == BT_EVENT)
			|| (msg_buffer == BT_CMD) || (msg_buffer == BT_DATA_REQ)	// Test only.
			)
	{
		memset(&msg_bt_recv_from_ic, 0, sizeof(struct message_bluetooth));

		msg_bt_recv_from_ic.msg_type = msg_buffer;
		PRINTF("%s, ret=%d, len=%d, msg_type=0x%x\n", __func__, ret, len, msg_bt_recv_from_ic.msg_type);

		ret = USART_RTOS_Receive(&handle_uart, &msg_buffer, 1, &len);
		msg_bt_recv_from_ic.msg_id = msg_buffer;
		cur_msg_id = msg_bt_recv_from_ic.msg_id;
		PRINTF("%s, ret=%d, len=%d, msg_id=0x%x\n", __func__, ret, len, msg_bt_recv_from_ic.msg_id);

		ret = USART_RTOS_Receive(&handle_uart, &msg_buffer, 1, &len);
		msg_bt_recv_from_ic.param_len = msg_buffer;
		PRINTF("%s, ret=%d, len=%d, param_len=0x%x\n", __func__, ret, len, msg_bt_recv_from_ic.param_len);

		if (msg_bt_recv_from_ic.param_len)
		{
			do
			{
				ret = USART_RTOS_Receive(&handle_uart, &msg_buffer, 1, &len);
				msg_bt_recv_from_ic.params[i] = msg_buffer;
				PRINTF("%s, ret=%d, len=%d, params[%d]=0x%x\n", __func__, ret, len, i, msg_bt_recv_from_ic.params[i]);
			} while (++i < msg_bt_recv_from_ic.param_len);
		}

		msg_send_to_mmi.msg.msg_bt = msg_bt_recv_from_ic;
	}
	else
		PRINTF("%s, invalid messages, msg_buffer=0x%x\n", __func__, msg_buffer);

	Message_Send(&msg_send_to_mmi);

	return ret;
}

void Bluetooth_Task(void *pvParameters)
{
    int ret = 0;

    PRINTF("%s\n", __func__);

	Bluetooth_ModuleHWReset();

    do {
        // vTaskSuspend(NULL); // Wait for messages.
        ret = Bluetooth_ReceiveMessageFromMMI();
        PRINTF("%s, Bluetooth_ReceiveMessageFromMMI done, ret=%d\n", __func__);

        do {
            ret = Bluetooth_SendMessageToMMI();
            PRINTF("%s, Bluetooth_SendMessageToMMI done, ret=%d\n", __func__, ret);
        } while (kStatus_Success == ret && cur_msg_id == BT_Event_ScanResult);
    } while (kStatus_Success == ret);

    USART_RTOS_Deinit(&handle_uart);
    vTaskSuspend(NULL);
}

int Bluetooth_Init(void)
{
	status_t status = kStatus_Success;

	CLOCK_AttachClk(BLUETOOTH_FLEXCOMM_CLOCK);

    NVIC_SetPriority(BLUETOOTH_USART_IRQn, USART_NVIC_PRIO);

    usart_config.srcclk = BLUETOOTH_USART_CLK_FREQ;

    if (0 > USART_RTOS_Init(&handle_uart, &t_handle_uart, &usart_config))
    {
        vTaskSuspend(NULL);
    }

    Bluetooth_GpioInit();

    return (status == kStatus_Success);
}
