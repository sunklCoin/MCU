/*
 * KeyEvent.h
 *
 *  Created on: 2017/10/01
 *      Author: yuhang
 */
#ifndef KEYEVENT_H
#define KEYEVENT_H

typedef enum key_code {
#ifdef SIMULATOR
    KEYCODE_UNKNOWN = 0,
    KEYCODE_HOME = 0x31, //  1
    KEYCODE_MIC = 0x32, //   2
    KEYCODE_BACK = 0x33,//   3
    KEYCODE_CHANNEL_UP = 0x34,//   4
    KEYCODE_UP = 0x35,//   5
    KEYCODE_VOLUME_UP = 0x36,//   6
    KEYCODE_RIGHT = 0x37,//   7
    KEYCODE_OK = 0x20,//   "space"
    KEYCODE_LEFT = 0x38,//   8
    KEYCODE_CHANNEL_DOWN = 0x39,//   9
    KEYCODE_DOWN = 0x3b,//   ;
    KEYCODE_VOLUME_DOWN = 0x3d,//   =
    KEYCODE_POWER = 0x2c//   ,
#else
    KEYCODE_UNKNOWN = 0,
    KEYCODE_HOME = 1,
    KEYCODE_MIC = 2,
    KEYCODE_BACK = 3,
    KEYCODE_CHANNEL_UP = 4,
    KEYCODE_UP = 5,
    KEYCODE_VOLUME_UP = 6,
    KEYCODE_RIGHT = 7,
    KEYCODE_OK = 8,
    KEYCODE_LEFT = 9,
    KEYCODE_CHANNEL_DOWN = 10,
    KEYCODE_DOWN = 11,
    KEYCODE_VOLUME_DOWN = 12,
    KEYCODE_POWER = 13
#endif
} typedef_key_code;

#endif /* KEYEVENT_H */
