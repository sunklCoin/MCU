/*
 * remoter_keypad.c
 *
 *  Created on: 2017年8月30日
 *      Author: xuke
 */

#include "remoter_keypad.h"
#include "fsl_gint.h"
keyboard_handle_t *button_handle;

#define DEMO_GINT0_PORT kGINT_Port0
#define KEY_SW2_GPIO_PIN 22U
#define KEY_GINT0_POL_MASK ~(1U << KEY_SW2_GPIO_PIN)
#define KEY_GINT0_ENA_MASK (1U << KEY_SW2_GPIO_PIN)
//
//void Keypad_Task(void *pvParameters)
//{
//	PRINTF("%s\n", __func__);
//
//    while (1)
//       {
//           if (kStatus_Success != AW95238_GetSingleButton(button_handle))
//           {
//               PRINTF("%s, error reading touch controller\r\n", __func__);
//           }
//           else
//           {
//        	   PRINTF("%s, waiting reading keypad controller\r\n", __func__);
//           }
//
//           vTaskDelay(5);
//       }
//
//	vTaskSuspend(NULL);
//}
//

status_t Keypad_I2C_Init(void)
{
    i2c_master_config_t masterConfig;

    I2C_MasterGetDefaultConfig(&masterConfig);

    /* Change the default baudrate configuration */
    masterConfig.baudRate_Bps = KEY_I2C_BAUDRATE;

    /* Initialize the I2C master peripheral */
    I2C_MasterInit(KEY_I2C_MASTER, &masterConfig, KEY_I2C_MASTER_CLOCK_FREQUENCY);

    button_handle = ( keyboard_handle_t * ) pvPortMalloc( sizeof( keyboard_handle_t ) );
//    button_handle->base = RMT_KEY_I2C_BASE;

    return kStatus_Success;
}

void Key_InterruptHandler()
{
	PRINTF("hello key interrupt!\n");
//	   while (1)
//	    {
	           if (kStatus_Success != AW95238_GetSingleButton(button_handle))
	           {
	               PRINTF("%s, error reading touch controller\r\n", __func__);
	           }
	           else
	           {
	        	   PRINTF("%s, waiting reading keypad controller\r\n", __func__);
	           }
	        for(int i = 0; i < 10000; i++)
	           __asm("NOP");
//	    }
}


void KEY_IRQ_Init(void)
{
	/* Initialize GINT0 */
	GINT_Init(GINT0);
	/* Setup GINT0 for edge trigger, "OR" mode */
	GINT_SetCtrl(GINT0, kGINT_CombineOr, kGINT_TrigLevel, Key_InterruptHandler);
	/* Select pins & polarity for GINT0 */
	GINT_ConfigPins(GINT0, DEMO_GINT0_PORT, KEY_GINT0_POL_MASK, KEY_GINT0_ENA_MASK);
	/* Enable callbacks for GINT0 */
	GINT_EnableCallback(GINT0);
}


int Keypad_Init(void)
{
	status_t status = kStatus_Success;
	gpio_pin_config_t pin_config = {
		kGPIO_DigitalOutput, 0,
	};

	/* attach 12 MHz clock to FLEXCOMM2 (I2C master for touch controller) */
	CLOCK_AttachClk(KEY_CLOCK_FLEXCOMM);

	/* Touch Reset line */
	CLOCK_EnableClock(KEY_CLOCK_GPIO);

	/* Initialize I2C for Keypad controller */
	status = Keypad_I2C_Init();
	if (status != kStatus_Success)
	{
		PRINTF("Keypad master I2C init failed\n");
	}
	assert(status == kStatus_Success);

	/* Enable touch panel controller */
	GPIO_PinInit(GPIO, KEY_RESET_GPIO_PORT, KEY_RESET_GPIO_PIN, &pin_config);
	GPIO_WritePinOutput(GPIO, KEY_RESET_GPIO_PORT, KEY_RESET_GPIO_PIN, 1);

	/* Initialize touch panel controller */
	status = AW95238_Init(button_handle, KEY_I2C_MASTER);
	if (status != kStatus_Success)
	{
		PRINTF("keypad ic init failed\n");
	}
	//    assert(status == kStatus_Success);

	KEY_IRQ_Init();

	return (status == kStatus_Success);
}

