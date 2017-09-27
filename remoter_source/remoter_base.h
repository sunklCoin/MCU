/*
 * remoter_base.h
 *
 *  Created on: 2017�?�?5�?
 *      Author: xuke
 */

#ifndef REMOTER_BASE_H_
#define REMOTER_BASE_H_

/* Standard C Included Files */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* Freescale includes. */
#include "fsl_common.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_sctimer.h"
#include "fsl_i2c.h"

#include "board.h"
#include "pin_mux.h"
#include "LPC54608.h"

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#define SDRAM_BASE_ADDR 0xa0000000
#define SDRAM_SIZE_BYTES (8 * 1024 * 1024)

#if BOARD_EVAL_LPCXPRESSO54608	// Project runs on LPCXpresso54608 demo board.
/* Remoter TouchPanel HW definitions.	Begin */
#define RMT_TP_I2C_BASE				I2C2_BASE
#define RMT_TP_I2C_CLK_FREQ			12000000
#define RMT_TP_I2C_BAUDRATE			100000
#define RMT_TP_I2C_CHG_SLAVE_ADDR	0x7E	// touch panel IC
#define RMT_TP_CLOCK_FLEXCOMM		kFRO12M_to_FLEXCOMM2
#define RMT_TP_CLOCK_GPIO			kCLOCK_Gpio2
#define RMT_TP_RESET_GPIO_PORT		2		// reset pin
#define RMT_TP_RESET_GPIO_PIN		27
/* End */

/* Remoter LCM HW definitions.	Begin */
#define RMT_LCM_SPI_INDEX			SPI9
#define RMT_LCM_SPI_FLEXCOMM		kFRO12M_to_FLEXCOMM9
#define RMT_LCM_SPI_IRQ				FLEXCOMM9_IRQn
#define RMT_LCM_WR_GPIO_CLOCK		kCLOCK_Gpio3
#define RMT_LCM_RESET_GPIO_CLOCK	kCLOCK_Gpio2
#define RMT_LCM_WR_GPIO_PORT		3		// write/read signal pin
#define RMT_LCM_WR_GPIO_PIN			31
#define RMT_LCM_RESET_GPIO_PORT		2		// reset pin
#define RMT_LCM_RESET_GPIO_PIN		11
/* End */

/* Remoter Bluetooth HW definitions.	Begin */
#define RMT_BT_UART_INDEX			USART4
#define RMT_BT_UART_FLEXCOMM		kFRO12M_to_FLEXCOMM4
#define RMT_BT_UART_IRQ				FLEXCOMM4_IRQn
#define RMT_BT_UART_IRQ_HANDLER		FLEXCOMM4_IRQHandler
#define RMT_BT_UART_CLK_FREQ		CLOCK_GetFreq(kCLOCK_Flexcomm4)
#define RMT_BT_UART_BAUDRATE		9600	// 9600 is the default baud rate of QN9022 module.
#define RMT_BT_WAKEUP_GPIO_PORT		2		// wakeup pin
#define RMT_BT_WAKEUP_GPIO_PIN		17
#define RMT_BT_HW_RESET_GPIO_PORT	3		// HW reset pin
#define RMT_BT_HW_RESET_GPIO_PIN	29
#define RMT_BT_SW_RESET_GPIO_PORT	3		// SW reset pin
#define RMT_BT_SW_RESET_GPIO_PIN	27
/* End */

/* Remoter PowerManage HW definitions.	Begin */
#define RMT_PM_I2C_BASE				I2C2_BASE
#define RMT_PM_I2C_FLEXCOMM			kFRO12M_to_FLEXCOMM2
#define RMT_PM_I2C_CLK_FREQ			12000000
#define RMT_PM_I2C_BAUDRATE			100000
#define RMT_PM_I2C_CHG_SLAVE_ADDR	0x6A	// charge IC
#define RMT_PM_I2C_FG_SLAVE_ADDR	0x62	// fuel gauge IC
#define RMT_PM_ADC_BASE				ADC0
#define RMT_PM_ADC_SAMPLE_CHANNEL	4
#define RMT_PM_CLOCK_FLEXCOMM		kFRO12M_to_FLEXCOMM2
#define RMT_PM_CLOCK_GPIO			kCLOCK_Gpio0
#define RMT_PM_EN_GPIO_PORT			0		// charger enable pin
#define RMT_PM_EN_GPIO_PIN			16
/* End */
#else
/* Remoter TouchPanel HW definitions.	Begin */
#define RMT_TP_I2C_BASE				I2C2_BASE
#define RMT_TP_I2C_CLK_FREQ			12000000
#define RMT_TP_I2C_BAUDRATE			100000
#define RMT_TP_I2C_CHG_SLAVE_ADDR	0x7E	// touch panel IC
#define RMT_TP_CLOCK_FLEXCOMM		kFRO12M_to_FLEXCOMM2
#define RMT_TP_CLOCK_GPIO			kCLOCK_Gpio2
#define RMT_TP_RESET_GPIO_PORT		2		// reset pin
#define RMT_TP_RESET_GPIO_PIN		27
/* End */

/*Remoter Keyboard HW definitions.	Begin*/
#define RMT_KEY_I2C_BASE			I2C6_BASE
#define RMT_KEY_I2C_CLK_FREQ			12000000
#define RMT_KEY_I2C_BAUDRATE			100000
#define RMT_KEY_I2C_CHG_SLAVE_ADDR	0x5B	// KEY IC
#define RMT_KEY_CLOCK_FLEXCOMM		kFRO12M_to_FLEXCOMM6
#define RMT_KEY_CLOCK_GPIO			kCLOCK_Gpio3
#define RMT_KEY_RESET_GPIO_PORT		3		// reset pin
#define RMT_KEY_RESET_GPIO_PIN		11
/*End*/

/* Remoter LCM HW definitions.	Begin */
#define RMT_LCM_SPI_INDEX			SPI9
#define RMT_LCM_SPI_FLEXCOMM		kFRO12M_to_FLEXCOMM9
#define RMT_LCM_SPI_IRQ				FLEXCOMM9_IRQn
#define RMT_LCM_WR_GPIO_CLOCK		kCLOCK_Gpio3
#define RMT_LCM_RESET_GPIO_CLOCK	kCLOCK_Gpio4
#define RMT_LCM_WR_GPIO_PORT		3		// write/read signal pin
#define RMT_LCM_WR_GPIO_PIN			3
#define RMT_LCM_RESET_GPIO_PORT		4		// reset pin
#define RMT_LCM_RESET_GPIO_PIN		16
/* End */

/* Remoter Bluetooth HW definitions.	Begin */
#define RMT_BT_UART_INDEX			USART8
#define RMT_BT_UART_FLEXCOMM		kFRO12M_to_FLEXCOMM8
#define RMT_BT_UART_IRQ				FLEXCOMM8_IRQn
#define RMT_BT_UART_IRQ_HANDLER		FLEXCOMM8_IRQHandler
#define RMT_BT_UART_CLK_FREQ		CLOCK_GetFreq(kCLOCK_Flexcomm8)
#define RMT_BT_UART_BAUDRATE		9600	// 9600 is the default baud rate of QN9022 module.
#define RMT_BT_WAKEUP_GPIO_PORT		3		// wakeup pin, connects to module internal GPIO0_3.
#define RMT_BT_WAKEUP_GPIO_PIN		14
#define RMT_BT_HW_RESET_GPIO_PORT	3		// HW reset pin
#define RMT_BT_HW_RESET_GPIO_PIN	29
#define RMT_BT_SW_RESET_GPIO_PORT	3		// SW reset pin, connects to module internal GPIO2_4.
#define RMT_BT_SW_RESET_GPIO_PIN	27
/* End */

/* Remoter PowerManage HW definitions.	Begin */
#define RMT_PM_I2C_BASE				I2C6_BASE
#define RMT_PM_I2C_FLEXCOMM			kFRO12M_to_FLEXCOMM6
#define RMT_PM_I2C_CLK_FREQ			12000000
#define RMT_PM_I2C_BAUDRATE			100000
#define RMT_PM_I2C_CHG_SLAVE_ADDR	0x6A	// charge IC
#define RMT_PM_I2C_FG_SLAVE_ADDR	0x62	// fuel gauge IC
#define RMT_PM_ADC_BASE				ADC0
#define RMT_PM_ADC_SAMPLE_CHANNEL	4
#define RMT_PM_CLOCK_FLEXCOMM		kFRO12M_to_FLEXCOMM2
#define RMT_PM_CLOCK_GPIO			kCLOCK_Gpio0
#define RMT_PM_EN_GPIO_PORT			0		// charger enable pin
#define RMT_PM_EN_GPIO_PIN			16
/* End */
#endif

enum task_index
{
	TASK_GUI = 0,
	TASK_GUI_SVC,
	TASK_TP,
	TASK_BT,
	TASK_WIFI,
	TASK_ZIGBEE,
//	TASK_KEYPAD,
	TASK_PM,
	TASK_AUDIO,
	TASK_DMIC,
	TASK_MAX
};

typedef struct touch_event {
	  int coordinate_x;
	  int coordinate_y;
	  int touch_state;
} struct_touch_event;

#endif /* REMOTER_BASE_H_ */
