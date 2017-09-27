/*
 * remoter_touchpanel.c
 *
 *  Created on: 2017年8月15日
 *      Author: xuke
 */

#include "remoter_touchpanel.h"
#include "remoter_gui.h"

ft5406_handle_t touch_handle;

static void TouchPanel_ReportEvent(struct touch_event *pos_event)
{
	struct touch_event *pos = pos_event;

//	PRINTF("%s, x=%d, y=%d, press_state=%d", __func__, pos->coordinate_x, pos->coordinate_y, pos->touch_state);
#if GUI_TYPE_EMWIN
	GUI_PID_STATE pid_state;

	pid_state.x = pos->coordinate_y;	// Need to swap x & y on this board.
    pid_state.y = pos->coordinate_x;
    pid_state.Pressed = ((pos->touch_state == kTouch_Down) || (pos->touch_state == kTouch_Contact));
    pid_state.Layer = 0;

    GUI_TOUCH_StoreStateEx(&pid_state);
    WM_Exec();
#endif
}


void TouchPanel_Task(void *pvParameters)
{
	struct touch_event pos = {0};

	PRINTF("%s\n", __func__);
#if GUI_TYPE_EMWIN
    while (1)
    {
        if (kStatus_Success != FT5406_GetSingleTouch(&touch_handle, (touch_event_t *)&pos.touch_state, &pos.coordinate_x, &pos.coordinate_y))
        {
            PRINTF("%s, error reading touch controller\r\n", __func__);
        }
        else if (pos.touch_state != kTouch_Reserved)
        {
        	TouchPanel_ReportEvent(&pos);
        }

        vTaskDelay(5);
    }
#elif GUI_TYPE_TOUCHGFX
    vTaskSuspend(NULL);
#endif
}

status_t TouchPanel_I2C_Init(void)
{
    i2c_master_config_t masterConfig;

    I2C_MasterGetDefaultConfig(&masterConfig);

    /* Change the default baudrate configuration */
    masterConfig.baudRate_Bps = TP_I2C_BAUDRATE;

    /* Initialize the I2C master peripheral */
    I2C_MasterInit(TP_I2C_MASTER, &masterConfig, TP_I2C_MASTER_CLOCK_FREQUENCY);

    return kStatus_Success;
}

int TouchPanel_Init(void)
{
	status_t status = kStatus_Success;
    gpio_pin_config_t pin_config = {
        kGPIO_DigitalOutput, 0,
    };

	/* attach 12 MHz clock to FLEXCOMM2 (I2C master for touch controller) */
	CLOCK_AttachClk(TP_CLOCK_FLEXCOMM);

	/* Touch Reset line */
	CLOCK_EnableClock(TP_CLOCK_GPIO);

    /* Initialize I2C for touch panel controller */
    status = TouchPanel_I2C_Init();
    if (status != kStatus_Success)
    {
        PRINTF("I2C init failed\n");
    }
    assert(status == kStatus_Success);

    /* Enable touch panel controller */
    GPIO_PinInit(GPIO, TP_RESET_GPIO_PORT, TP_RESET_GPIO_PIN, &pin_config);
    GPIO_WritePinOutput(GPIO, TP_RESET_GPIO_PORT, TP_RESET_GPIO_PIN, 1);

    /* Initialize touch panel controller */
    status = FT5406_Init(&touch_handle, TP_I2C_MASTER);
    if (status != kStatus_Success)
    {
        PRINTF("Touch panel init failed\n");
    }
//    assert(status == kStatus_Success);

    return (status == kStatus_Success);
}
