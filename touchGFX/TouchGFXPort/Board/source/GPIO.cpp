/******************************************************************************
 *
 * @brief     This file is part of the TouchGFX 4.6.0 standard distribution.
 *
 * @author    Draupner Graphics A/S <http://www.touchgfx.com>
 *
 ******************************************************************************
 *
 * @section Copyright
 *
 * Copyright (C) 2014-2016 Draupner Graphics A/S <http://www.touchgfx.com>.
 * All rights reserved.
 *
 * TouchGFX is protected by international copyright laws and the knowledge of
 * this source code may not be used to write a similar product. This file may
 * only be used in accordance with a license and should not be re-
 * distributed in any way without the prior permission of Draupner Graphics.
 *
 * This is licensed software, any use must strictly comply with the signed
 * license agreement and associated Terms & Conditions.
 *
 * Standard Terms & Conditions can be seen on www.touchgfx.com
 *
 * @section Disclaimer
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Draupner Graphics A/S has
 * no obligation to support this software. Draupner Graphics A/S is providing
 * the software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Draupner Graphics A/S can not be held liable for any consequential,
 * incidental, or special damages, or any other relief, or for any claim by
 * any third party, arising from your use of this software.
 *
 *****************************************************************************/
#include "board.h"
#undef GPIO
#include <touchgfx/hal/GPIO.hpp>

using namespace touchgfx;

static bool gpioState[4];
void GPIO::init()
{
    LED1_INIT(LOGIC_LED_OFF); 
    LED2_INIT(LOGIC_LED_OFF); 
    LED3_INIT(LOGIC_LED_OFF); 
    
    for (int i = 0; i < 4; i++)
    {
        gpioState[i] = 0;
    }
}

void GPIO::set(GPIO_ID id)
{
    switch(id)
    {
    case VSYNC_FREQ:
      LED1_ON();
      break;
    case RENDER_TIME:
      LED2_ON();
      break;
    case FRAME_RATE:
      LED3_ON();
      break;
    }
    gpioState[id] = 1;
}

void GPIO::clear(GPIO_ID id)
{
    switch(id)
    {
    case VSYNC_FREQ:
      LED1_OFF();
      break;
    case RENDER_TIME:
      LED2_OFF();
      break;
    case FRAME_RATE:
      LED3_OFF();
      break;
    }
    gpioState[id] = 0;
}

void GPIO::toggle(GPIO_ID id)
{
    if (get(id))
    {
        clear(id);
    }
    else
    {
        set(id);
    }
}

bool GPIO::get(GPIO_ID id)
{
    return gpioState[id];;
}

