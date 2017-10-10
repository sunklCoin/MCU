/******************************************************************************
 *
 * @brief     This file is part of the TouchGFX 4.8.0 evaluation distribution.
 *
 * @author    Draupner Graphics A/S <http://www.touchgfx.com>
 *
 ******************************************************************************
 *
 * @section Copyright
 *
 * This file is free software and is provided for example purposes. You may
 * use, copy, and modify within the terms and conditions of the license
 * agreement.
 *
 * This is licensed software for evaluation use, any use must strictly comply
 * with the evaluation license agreement provided with delivery of the
 * TouchGFX software.
 *
 * The evaluation license agreement can be seen on www.touchgfx.com
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
#ifndef GUI_UTILS_HPP
#define GUI_UTILS_HPP

#include <touchgfx/hal/HAL.hpp>

#ifdef SIMULATOR
#include <stdlib.h>
#define TOUCH_GFX_LOG printf
#else
#define TOUCH_GFX_LOG
#endif

class Utils
{
public:
    static int randomNumberBetween(int lowest, int highest)
    {
#ifdef SIMULATOR
        return (int)(lowest + (highest - lowest) * (rand() / (float)RAND_MAX));
#else
        uint32_t random = (touchgfx::HAL::getInstance()->getCPUCycles() * touchgfx::HAL::getInstance()->getCPUCycles());
        return lowest + (random % (highest - lowest));
#endif
    }

    static int nextRand(int lowest, int highest)
    {
        static uint32_t seed = 0;
        seed = ((214013 * (uint32_t)(seed) + 2531011) >> 16);
        return lowest + (seed % (highest - lowest));
    }
};


#endif /* GUI_UTILS_HPP */
