#pragma once

enum layers {
  QWERTY = 0,
  QWERTY_MAC,
  COMMAND,
  CMD_MAC,
  SYMBOL,
  NUMBERS,
  FUN
};


enum custom_keycodes {
  M_AE = SAFE_RANGE,
  M_OE,
  M_AA,
  M_FIND,
  M_FIND_CURSOR,
  M_FIND_NEXT,
  M_FIND_PREVIOUS,
  M_OS_WIN,
  M_OS_LINUX,
  M_OS_MAC,
  M_ACCL_1,
  M_ACCL_2,
  M_ACCL_3,
  M_ACCL_4,
  DIR_TEXTMOTION,
  DIR_MOUSE,
  DIR_SCROLL,
  M_UP,
  M_DOWN,
  M_LEFT,
  M_RIGHT,
  M_MOUSE1,
  M_TOGGLE_MOUSE1,
  M_MOUSE2,
  M_TOGGLE_MOUSE2,
  M_MOUSE3,
  M_TOGGLE_MOUSE3,
  M_PARENTHESIS,
  M_CURLIES,
  M_BRACKETS
};

enum tap_dances {
  TD_ACC1_X,
  TD_ACC2_C,
  TD_ACC3_V,
};


enum directive {
  TEXTMOTION,
  MOUSE,
  SCROLL
};

enum DIRECTION{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

enum os {
  WINDOWS = 0,
  MAC,
  LINUX
};
