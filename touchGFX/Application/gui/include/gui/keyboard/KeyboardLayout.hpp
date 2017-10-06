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
#ifndef KEYBOARD_LAYOUT
#define KEYBOARD_LAYOUT

#include <touchgfx/widgets/Keyboard.hpp>
#include <touchgfx/hal/Types.hpp>
#include <fonts/ApplicationFontProvider.hpp>
#include "BitmapDatabase.hpp"

using namespace touchgfx;
#define KEYBOARD_KEY_OFFSET_Y (0)//(133)
/**
 * Array specifying the keys used in the CustomKeyboard.
 */
static const Keyboard::Key keyArray[30] =
{
	{ 1, Rect(1, KEYBOARD_KEY_OFFSET_Y + 7, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 2, Rect(1 + 24, KEYBOARD_KEY_OFFSET_Y + 7, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 3, Rect(1 + 24 * 2, KEYBOARD_KEY_OFFSET_Y + 7, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 4, Rect(1 + 24 * 3, KEYBOARD_KEY_OFFSET_Y + 7, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 5, Rect(1 + 24 * 4, KEYBOARD_KEY_OFFSET_Y + 7, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 6, Rect(1 + 24 * 5, KEYBOARD_KEY_OFFSET_Y + 7, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 7, Rect(1 + 24 * 6, KEYBOARD_KEY_OFFSET_Y + 7, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 8, Rect(1 + 24 * 7, KEYBOARD_KEY_OFFSET_Y + 7, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 9, Rect(1 + 24 * 8, KEYBOARD_KEY_OFFSET_Y + 7, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 10, Rect(1 + 24 * 9, KEYBOARD_KEY_OFFSET_Y + 7, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },

	{ 11, Rect(13, KEYBOARD_KEY_OFFSET_Y + 53, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 12, Rect(13 + 24, KEYBOARD_KEY_OFFSET_Y + 53, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 13, Rect(13 + 24 * 2, KEYBOARD_KEY_OFFSET_Y + 53, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 14, Rect(13 + 24 * 3, KEYBOARD_KEY_OFFSET_Y + 53, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 15, Rect(13 + 24 * 4, KEYBOARD_KEY_OFFSET_Y + 53, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 16, Rect(13 + 24 * 5, KEYBOARD_KEY_OFFSET_Y + 53, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 17, Rect(13 + 24 * 6, KEYBOARD_KEY_OFFSET_Y + 53, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 18, Rect(13 + 24 * 7, KEYBOARD_KEY_OFFSET_Y + 53, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 19, Rect(13 + 24 * 8, KEYBOARD_KEY_OFFSET_Y + 53, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },

	{ 20, Rect(37, KEYBOARD_KEY_OFFSET_Y + 99, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 21, Rect(37 + 24, KEYBOARD_KEY_OFFSET_Y + 99, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 22, Rect(37 + 24 * 2, KEYBOARD_KEY_OFFSET_Y + 99, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 23, Rect(37 + 24 * 3, KEYBOARD_KEY_OFFSET_Y + 99, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 24, Rect(37 + 24 * 4, KEYBOARD_KEY_OFFSET_Y + 99, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 25, Rect(37 + 24 * 5, KEYBOARD_KEY_OFFSET_Y + 99, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 26, Rect(37 + 24 * 6, KEYBOARD_KEY_OFFSET_Y + 99, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },

	{ 27, Rect(37, KEYBOARD_KEY_OFFSET_Y + 145, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 28, Rect(37 + 24, KEYBOARD_KEY_OFFSET_Y + 145, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 29, Rect(37 + 24 * 2, KEYBOARD_KEY_OFFSET_Y + 145, 22, 41), BITMAP_KEYBOARD_KEY_HIGHLIGHTED_ID },
	{ 30, Rect(37 + 24 * 3, KEYBOARD_KEY_OFFSET_Y + 145, 130, 41), BITMAP_KEYBOARD_SPACE_HIGHLIGHTED_ID }
};

/**
 * Callback areas for the special buttons on the CustomKeyboard.
 */
static Keyboard::CallbackArea callbackAreas[3] =
{
	{ Rect(1, KEYBOARD_KEY_OFFSET_Y + 99, 34, 41), 0, BITMAP_KEYBOARD_KEY_SHIFT_HIGHLIGHTED_ID },     // caps-lock
	{ Rect(205, KEYBOARD_KEY_OFFSET_Y + 99, 34, 41), 0, BITMAP_KEYBOARD_KEY_DELETE_HIGHLIGHTED_ID },  // backspace
	{ Rect(1, KEYBOARD_KEY_OFFSET_Y + 145, 34, 41), 0, BITMAP_KEYBOARD_KEY_NUM_HIGHLIGHTED_ID },       // mode
};

/**
 * The layout for the CustomKeyboard.
 */
static /*const*/ Keyboard::Layout layout =
{
    BITMAP_KEYBOARD_BACKGROUND_ID,
    keyArray,
    30,
    callbackAreas,
    3,
    Rect(0, 7, 10 * 24, 41),
    TypedText(T_ENTEREDTEXT),
#if !defined(USE_BPP) || USE_BPP==16
    0x0000,
#elif USE_BPP==24
    0xFFFFFF,
#elif USE_BPP==4
    0xF,
#elif USE_BPP==2
    0x3,
#else
#error Unknown USE_BPP
#endif
    Typography::KEYBOARD,
    0
};

#endif
