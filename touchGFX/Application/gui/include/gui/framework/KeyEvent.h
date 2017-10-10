/*
 * KeyEvent.h
 *
 *  Created on: 2017/10/01
 *      Author: yuhang
 */
#ifndef KEYEVENT_H
#define KEYEVENT_H
#ifndef SIMULATOR
#define KEYBOARD_GET_KEYEVENT(key) (uint8_t)(key >> 6)
#define KEYBOARD_GET_KEYCODE(key) (uint8_t)(key & 0X3F)
#else
#define KEYBOARD_GET_KEYEVENT(key) (uint8_t)(key)
#define KEYBOARD_GET_KEYCODE(key) (uint8_t)(key)
#endif
typedef enum key_event {
	KEY_EVENT_DOWN = 0x00,
	KEY_EVENT_UP = 0x01,
	KEY_EVENT_LONG_PRESS = 0x02,
} typedef_key_event;


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
