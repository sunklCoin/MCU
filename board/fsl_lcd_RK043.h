#ifndef _FSL_RK043_H_
#define _FSL_RK043_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* SDRAM Address Base */
#define SDRAM_BASE      0xA0000000

#define APP_LCD LCD
#define LCD_PANEL_CLK 7000000
#define LCD_PPL 240
#define LCD_HSW 2
#define LCD_HFP 8
#define LCD_HBP 8
#define LCD_LPP 320
#define LCD_VSW 4
#define LCD_VFP 8
#define LCD_VBP 4
#define LCD_POL_FLAGS kLCDC_InvertVsyncPolarity | kLCDC_InvertHsyncPolarity
#define LCD_INPUT_CLK_FREQ CLOCK_GetFreq(kCLOCK_LCD)
#define LCD_WIDTH 240
#define LCD_HEIGHT 320
#define LCD_BITS_PER_PIXEL 16
#define IMG_HEIGHT 320
#define IMG_WIDTH 240
#define APP_LCD_IRQHandler LCD_IRQHandler
#define APP_LCD_IRQn LCD_IRQn
#define EXAMPLE_I2C_MASTER_BASE (I2C2_BASE)
#define I2C_MASTER_CLOCK_FREQUENCY (12000000)
#define APP_PIXEL_PER_BYTE 8

void LCD_Init_BL_PWM(void);
status_t LCD_RK043_Init(void);
#endif
