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
#ifndef KEYBOARD_KEY_MAPPING_H
#define KEYBOARD_KEY_MAPPING_H

#include <touchgfx/widgets/Keyboard.hpp>
using namespace touchgfx;

/**
 * This file contains all the keymappings for the CustomKeyboard.
 */
static const Keyboard::KeyMapping keyMappingsAlphaLower[30] =
{
    { 1, 113},  // q
    { 2, 119},  // w
    { 3, 101},  // e
    { 4, 114},  // r
    { 5, 116},  // t
    { 6, 121},  // y
    { 7, 117},  // u
    { 8, 105},  // i
    { 9, 111},  // o
    {10, 112},  // p

    {11,  97},  // a
    {12, 115},  // s
    {13, 100},  // d
    {14, 102},  // f
    {15, 103},  // g
    {16, 104},  // h
    {17, 106},  // j
    {18, 107},  // k
    {19, 108},  // l

    {20, 122},  // z
    { 21, 120 },  // x
    {22,  99},  // c
    {23, 118},  // v
    {24,  98},  // b
    {25, 110},  // n
    {26, 109},  // m

    {27, 45},   // -
    { 28, 46 },   // .
    { 29, 44 },   // ,
    {30,  32},  // space
};

static const Keyboard::KeyMappingList keyMappingListAlphaLower =
{
    keyMappingsAlphaLower,
    30
};

static const Keyboard::KeyMapping keyMappingsAlphaUpper[30] =
{
    { 1, 113 - 32},  // Q
    { 2, 119 - 32},  // W
    { 3, 101 - 32},  // E
    { 4, 114 - 32},  // R
    { 5, 116 - 32},  // T
    { 6, 121 - 32},  // Y
    { 7, 117 - 32},  // U
    { 8, 105 - 32},  // I
    { 9, 111 - 32},  // O
    {10, 112 - 32},  // P

    {11,  97 - 32},  // A
    {12, 115 - 32},  // S
    { 13, 100 - 32 },  // D
    { 14, 102 - 32 },  // F
    { 15, 103 - 32 },  // G
    { 16, 104 - 32 },  // H
    { 17, 106 - 32 },  // J
    { 18, 107 - 32 },  // K
    { 19, 108 - 32 },  // L

    {20, 122 - 32},  // Z
    {21, 120 - 32},  // X
    {22,  99 - 32},  // C
    { 23, 118 - 32 },  // V
    { 24, 98 - 32 },  // B
    { 25, 110 - 32 },  // N
    { 26, 109 - 32 },  // M

    { 27, 47 },        // /
    { 28, 58 },        // :
    { 29, 59 },        //
    {30,  32}        // space
};

static const Keyboard::KeyMappingList keyMappingListAlphaUpper =
{
    keyMappingsAlphaUpper,
    30
};

static const Keyboard::KeyMapping keyMappingsNumLower[30] =
{
    { 1,  49},  // 1
    { 2,  50},  // 2
    { 3,  51},  // 3
    { 4,  52},  // 4
    { 5,  53},  // 5
    { 6,  54},  // 6
    { 7,  55},  // 7
    { 8,  56},  // 8
    { 9,  57},  // 9
    {10,  48},  // 0

    {11,  64},  // @
    {12,  35},  // #
    {13,  36},  // $
    {14,  37},  // %
    {15,  38},  // &
    {16,  42},  // *
    {17,  45},  // -
    {18,  43},  // +
    {19,  40},  // (
    {20,  41},  // )
    {21,  33},  // !

    {22,  34},  // "
    {23,  39},  // '
    {24,  58},  // :
    {25,  59},  // ;
    {26,  47},  // /
    {27,  63},  // ?
    {28,  44},  // ,
    {29,  46},  // .

    {30,  32}   // space
};

static const Keyboard::KeyMappingList keyMappingListNumLower =
{
    keyMappingsNumLower,
    30
};

static const Keyboard::KeyMapping keyMappingsNumUpper[30] =
{
    { 1,  126},  // ~
    { 2,  177},  // +/-
    { 3,  215},  // x
    { 4,  247},  // -
    { 5,  8226}, // *
    { 6,  186},  // o
    { 7,  96},   // '
    { 8,  180},  // '
    { 9,  123},  // {
    {10,  125},  // }

    {11,  169},  // (c)
    {12, 163},   // pound
    {13,  8364}, // euro
    {14,  94},   // ^
    {15,  174},  // (R)
    {16,  165},  // yen
    {17,  95},   // _
    {18,  61},   // =
    {19,  91},   // [
    {20,  93},   // ]
    {21,  60},   // <

    {22, 62},    // >
    {23,  161},  // !
    {24,  162},  // cent
    {25,  124},  // |
    {26,  92},   // \ .
    {27,  191},  // ?
    {28,  44},   // ,
    {29,  46},   // .

    {30,  32}   // space
};

static const Keyboard::KeyMappingList keyMappingListNumUpper =
{
    keyMappingsNumUpper,
    30
};

#endif
