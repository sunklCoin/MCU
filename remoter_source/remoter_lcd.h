/*
 * remoter_lcd.h
 *
 *  Created on: 2017年8月15日
 *      Author: xuke
 */

#ifndef REMOTER_LCD_H_
#define REMOTER_LCD_H_

#include "remoter_base.h"
#include "remoter_gui.h"
#include "fsl_lcdc.h"
#include "fsl_i2c.h"
#include "fsl_spi.h"
#include "fsl_spi_freertos.h"

#define LCM_WR_GPIO_CLOCK		RMT_LCM_WR_GPIO_CLOCK
#define LCM_RESET_GPIO_CLOCK	RMT_LCM_RESET_GPIO_CLOCK
#define LCM_SPI_INDEX		RMT_LCM_SPI_INDEX
#define LCM_SPI_FLEXCOMM	RMT_LCM_SPI_FLEXCOMM
#define LCM_SPI_IRQ			RMT_LCM_SPI_IRQ
#define LCM_WR_GPIO_PORT	RMT_LCM_WR_GPIO_PORT
#define LCM_WR_GPIO_PIN		RMT_LCM_WR_GPIO_PIN
#define LCM_RESET_GPIO_PORT		RMT_LCM_RESET_GPIO_PORT
#define LCM_RESET_GPIO_PIN		RMT_LCM_RESET_GPIO_PIN

#define APP_LCD LCD
#define APP_LCD_IRQHandler LCD_IRQHandler
#define APP_LCD_IRQn LCD_IRQn

#define LCD_SPI_SSEL kSPI_Ssel0
#define TRANSFER_SIZE (4)          /*! Transfer size */
#define TRANSFER_BAUDRATE (500000U) /*! Transfer baudrate - 500k */
#define SPI_NVIC_PRIO 2

#define LCD_WIDTH 240
#define LCD_HEIGHT 320
#define LCD_BITS_PER_PIXEL 16

#define LCD_PANEL_CLK 7000000
#define LCD_PPL LCD_WIDTH
#define LCD_HSW 2
#define LCD_HFP 8
#define LCD_HBP 8
#define LCD_LPP LCD_HEIGHT
#define LCD_VSW 4
#define LCD_VFP 8
#define LCD_VBP 4
#define LCD_POL_FLAGS kLCDC_InvertVsyncPolarity | kLCDC_InvertHsyncPolarity
#define LCD_INPUT_CLK_FREQ CLOCK_GetFreq(kCLOCK_LCD)

#define LCD_LOGO_WIDTH 150
#define LCD_LOGO_HEIGHT 150
#define LCD_LOGO_START_X ((LCD_WIDTH - LCD_LOGO_WIDTH)>>1)
#define LCD_LOGO_START_Y ((LCD_HEIGHT - LCD_LOGO_HEIGHT)>>1)

#endif /* REMOTER_LCD_H_ */
