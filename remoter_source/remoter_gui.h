/*
 * remoter_gui.h
 *
 *  Created on: 2017年8月15日
 *      Author: xuke
 */

#ifndef REMOTER_GUI_H_
#define REMOTER_GUI_H_

#include "remoter_base.h"
#include "fsl_touch_ft5406.h"

#include "remoter_message.h"
#include "remoter_main.h"

#if GUI_TYPE_EMWIN

#include "GUI.h"
#include "GUIDRV_Lin.h"
#include "BUTTON.h"

/* Work memory for emWin */
#define GUI_NUMBYTES 0x20000
#define GUI_MEMORY_ADDR (SDRAM_BASE_ADDR)

/* Display framebuffer */
#define VRAM_ADDR (GUI_MEMORY_ADDR + GUI_NUMBYTES)
#define VRAM_SIZE (LCD_HEIGHT * LCD_WIDTH * LCD_BITS_PER_PIXEL / 8)

extern ft5406_handle_t touch_handle;

#elif GUI_TYPE_TOUCHGFX

#endif

#endif /* REMOTER_GUI_H_ */
