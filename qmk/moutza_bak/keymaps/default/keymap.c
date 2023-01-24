#include QMK_KEYBOARD_H

#include "pointing_device.h"
#include "report.h"
#include <stdio.h>

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
    RESET,     KC_B,     KC_V,     KC_G,                     KC_W,     KC_K,     KC_Z,     KC_QUOT,
    _______,  KC_C,     KC_H,     KC_P,                     KC_Y,     KC_O,     KC_J,     _______,
    KC_R,     KC_S,     KC_N,     KC_T,                     KC_U,     KC_E,     KC_I,     KC_A,
    KC_R,     KC_S,     KC_N,     KC_T,                     KC_U,     KC_E,     KC_I,     KC_A,
    KC_X,     KC_M, KC_L, KC_D,                 KC_F,KC_COMM,KC_DOT,KC_SLSH,
    KC_BSPC,  KC_LEAD,                              KC_ENT, KC_SPC,
    _______,_______,                                           _______,_______,
    _______,                                                   _______

),

};

