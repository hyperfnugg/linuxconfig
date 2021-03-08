/* Copyright 2019 Thomas Baart <thomas@splitkb.com> *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include "pointing_device.h"
#include "report.h"
#include <stdio.h>

enum layers {
  QWERTY = 0,
  QWERTY_MAC,
  CMD,
  CMD_MAC,
  QWERTY_MOD_L,
  QWERTY_MOD_R,
  NAVIGATION,
  NAVIGATION_MOD,
  NUMBERS,
  NUMBERS_MOD
};

enum os {
  WINDOWS = 0,
  MAC,
  LINUX
};

enum custom_keycodes {
  M_AE = SAFE_RANGE,
  M_OE,
  M_AA,
  M_FIND,
  M_FIND_CURSOR,
  M_FIND_NEXT,
  M_FIND_PREVIOUS,
  M_OS_WINDOWS,
  M_OS_LINUX,
  M_OS_MAC,
  M_ACCL_1,
  M_ACCL_2,
  M_ACCL_3,
  M_ACCL_4,
  M_DIRECTIVE_TEXTMOTION,
  M_DIRECTIVE_MOUSE,
  M_DIRECTIVE_SCROLL,
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

bool accelrated_1 = false;
bool accelrated_2 = false;
bool accelrated_3 = false;
bool accelrated_4 = false;


enum os active_os = MAC;
enum directive active_directive = TEXTMOTION;

static uint16_t directive_timer;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 
   * Base Layer: QWERTY
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |      |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |      |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |  Q     |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |   P    |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |MOD/Z |   X  |   C  |   V  |   B  |      |      |  |      |      |   N  |   M  | ,  < | . >  |MOD /?|        |
   * `----------------------+------+------+------+------+------+  |------+------+------+------+------+----------------------'
   *                        |Accel |      |LAYR  |LAYR  |LAYR  |  |Enter |Space |Space |      |      |
   *                        |      |      |  2   |  2   |  4   |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
  [QWERTY] = LAYOUT(
      KC_NO, KC_NO, KC_W, KC_E, KC_R, KC_T,
      KC_Y, KC_U, KC_I, KC_O, KC_NO, KC_NO,

      KC_Q, LALT_T(KC_A), LCTL_T(KC_S), LT(QWERTY_MOD_R, KC_D), LSFT_T(KC_F), KC_G,
      KC_H, RSFT_T(KC_J), LT(QWERTY_MOD_L, KC_K), LCTL_T(KC_L), RALT_T(KC_SCLN), KC_P,

      KC_NO, LGUI_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_BSLS, KC_INS,
      KC_LPRN, KC_RPRN, KC_N, KC_M, KC_COMM, KC_DOT, LGUI_T(KC_SLSH), KC_NO,

      M_ACCL_1, KC_NO, LT(NAVIGATION, KC_BSPC), LT(NAVIGATION,KC_BSPC), LT(NUMBERS,KC_TAB), 
      KC_ENT, KC_SPC, KC_SPC, KC_NO, M_ACCL_1
      ),

  /*
   * Mods for mac
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        |      |Win(S)|      |      |      |                              |      |      |      |Win(L)|      |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |Ctrl Z|      |      |      |      |      |      |  |      |      |      |      |      |      |ctrl/?|        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
  [QWERTY_MAC] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

      KC_TRNS, KC_TRNS, LGUI_T(KC_S), KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, LGUI_T(KC_L), KC_TRNS, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, LCTL_T(KC_Z), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LCTL_T(KC_SLSH), KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
      ),

  /*
   * Command mods
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |      |      |      |      |      |                              | Esc  |      |      |      |      |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        | Alt  | Ctrl | MOD  |Shift |      |                              |      |Shift | MOD  | Ctrl | Alt  |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        | Win  |      |      |      |      |      |      |  |      |      | Tab  |      |      |      | Win  |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
  [CMD] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

      KC_TRNS, KC_LALT, KC_LCTL, KC_TRNS, KC_LSHIFT, KC_TRNS,
      KC_ESC, KC_RSHIFT, KC_TRNS, KC_RCTL, KC_RALT, KC_BSPC,

      KC_TRNS, KC_LGUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TAB, KC_TRNS, KC_TRNS, KC_TRNS, KC_RGUI, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
      ),
  /*
   * Command mods for mac
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        |      | Win  |      |      |      |                              |      |      |      | Win  |      |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |Ctrl  |      |      |      |      |      |      |  |      |      |      |      |      |      |Ctrl  |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
  [CMD_MAC] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_LGUI, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_LGUI, KC_TRNS, KC_TRNS,

      KC_TRNS, KC_LCTL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCTL, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
      ),
  /*
   * Mod layer for QWERTY, common symbols
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |      |  @   |  #   |  $   |  %   |                              | Esc  |  &   |  *   |   ^  |      |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |   !    |  '   |  "   |  _   |  ()  |  {}  |                              |   =  |   Æ  |   Ø  |   Å  | Del  |BkSpace |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |  ~   |   `  |  -   |  _   |  +   |      |      |  |      |      | Tab  |  |   |  \   |      |      |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
  [QWERTY_MOD_L] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_AT, KC_HASH, KC_DLR, KC_PERC,
      KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

      KC_EXLM, KC_QUOT, KC_DQUO, KC_UNDS, M_PARENTHESIS, M_CURLIES,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC,

      KC_TRNS, KC_TILD, KC_GRV, KC_MINS, M_BRACKETS, KC_KP_PLUS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TAB, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

      KC_TRNS, KC_TRNS, MO(NAVIGATION_MOD), MO(NAVIGATION_MOD), MO(NUMBERS_MOD),
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
      ),

  /*
   * Mod layer for QWERTY, common symbols
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |      |  @   |  #   |  $   |  %   |                              | Esc  |  &   |  *   |   ^  |      |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |   !    |  '   |  "   |  _   |  ()  |  {}  |                              |   =  |   Æ  |   Ø  |   Å  | Del  |BkSpace |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |  ~   |   `  |  -   |  _   |  +   |      |      |  |      |      | Tab  |  |   |  \   |      |      |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
  [QWERTY_MOD_R] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_ESC, KC_AMPR, KC_ASTR, KC_CIRC, KC_TRNS, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_EQL, M_AE, M_OE, M_AA, KC_DEL, KC_BSPC,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TAB, KC_PIPE, KC_BSLS, KC_TRNS, KC_TRNS, KC_TRNS,

      KC_TRNS, KC_TRNS, MO(NAVIGATION_MOD), MO(NAVIGATION_MOD), MO(NUMBERS_MOD),
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
      ),
 

  /*
   * Navigation Layer
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |      |FindCr|Find  |FndNex|      |                              |Arrow |Alt-tb|Scroll|Histry|fw/bw |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |                              |Left  | Down |  Up  | Right|Mouse |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |      |  |      |      |Mouse1|Mouse2|Mouse3|      |TextMv|        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
  [NAVIGATION] = LAYOUT(
      KC_TRNS, KC_TRNS, M_FIND_CURSOR, M_FIND, M_FIND_NEXT, KC_TRNS,
      KC_TRNS, KC_TRNS, M_DIRECTIVE_SCROLL, KC_TRNS, KC_TRNS, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, LT(NAVIGATION_MOD, KC_TAB), KC_TRNS, KC_TRNS,
      M_LEFT, M_DOWN, M_UP, M_RIGHT, M_DIRECTIVE_MOUSE, KC_TRNS,

      KC_TRNS, KC_TRNS, M_ACCL_1, M_ACCL_2, M_ACCL_3, M_ACCL_4, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, M_MOUSE1, M_MOUSE2, M_MOUSE3, M_DIRECTIVE_TEXTMOTION, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
      ),
  /*
   * Mod navigation
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |Pause |PrScr |ScrLck|NumLck|CpsLck|                              | Esc  |      |      |      |      |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |                              | Home |Pg.Dwn|Pg.Up | End  |      |Backspce|
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |      |  |      |      | Tab  |      |      |      |      |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
  [NAVIGATION_MOD] = LAYOUT(
      KC_TRNS, KC_PAUS, KC_PSCR, KC_SLCK, KC_NLCK, KC_CAPS,
      KC_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_TRNS, KC_BSPC,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TAB, M_TOGGLE_MOUSE1, M_TOGGLE_MOUSE2, M_TOGGLE_MOUSE3, KC_TRNS, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
      ),


  /*
   * Numbers
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |      |      |      |      |      |                              | Esc  | 7 &  | 8 *  | 9 (  |      | - _    |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        | WIN  | Alt  | Ctrl |Shift |      |                              |  0   | 4 $  | 5 %  | 6 ^  | < ,  |Backspce|
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |      |  |      |      | Tab  | 1 !  | 2 @  | 3 #  | > .  |  = +   |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
  [NUMBERS] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_ESC, KC_7, KC_8, KC_9, KC_TRNS, KC_MINS,

      KC_TRNS, KC_TRNS, KC_TRNS, LT(NUMBERS_MOD, KC_TAB), KC_TRNS, KC_TRNS,
      KC_0, RSFT_T(KC_4), LT(QWERTY_MOD_L, KC_5), KC_6, KC_COMM, KC_BSPC,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TAB, KC_1, KC_2, KC_3, KC_DOT, KC_EQL,

      KC_TRNS, MO(NUMBERS_MOD), KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, MO(NUMBERS_MOD), KC_TRNS
      ),


  /*
   * Functional layer
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |   Mac  | RGB  | SAT+ | HUE+ |Brght+| MOD+ |                              | Esc  | F7   | F8   | F9   | F10  |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * | Linux  |      |      |      |      |      |                              |      | F4   | F5   | F6   | F11  |Backspce|
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |Windows |      | SAT- | HUE- |Brght+| MOD- |      |      |  |      |      | Tab  | F1   | F2   | F3   | F12  |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */

  [NUMBERS_MOD] = LAYOUT(
      M_OS_MAC, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,
      KC_ESC, KC_F7, KC_F8, KC_F9, KC_TRNS, KC_TRNS,

      M_OS_LINUX, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_F10, KC_F4, KC_F5, KC_F6, KC_F11, KC_BSPC,

      M_OS_WINDOWS, KC_TRNS, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TAB, KC_F1, KC_F2, KC_F3, KC_F12, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
      ),
  // /*
  //  * Layer template
  //  *
  //  * ,-------------------------------------------.                              ,-------------------------------------------.
  //  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
  //  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
  //  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
  //  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
  //  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
  //  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
  //  *                        |      |      |      |      |      |  |      |      |      |      |      |
  //  *                        |      |      |      |      |      |  |      |      |      |      |      |
  //  *                        `----------------------------------'  `----------------------------------'
  //  */
  //     [_LAYERINDEX] = LAYOUT(
  //       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
  //       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
  //       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  //                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  //     ),
};



#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
  static const char PROGMEM kyria_logo[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
    0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
    0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
  };
  oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}


static void set_os(enum os new_os) {
  active_os = new_os;
  if(active_os == MAC) layer_on(QWERTY_MAC);
  else layer_off(QWERTY_MAC);
}


static void set_directive(enum directive new_directive) {
  directive_timer = timer_read();
  active_directive = new_directive;
}

static void pointer(int x, int y, int h, int v) {
  report_mouse_t currentReport = pointing_device_get_report();
  currentReport.x = x;
  currentReport.y = y;
  currentReport.v = v;
  currentReport.h = h;
  pointing_device_set_report(currentReport);
  pointing_device_send();
}

static void mouse_down(uint8_t button) {
  directive_timer = timer_read();
  report_mouse_t currentReport = pointing_device_get_report();
  currentReport.buttons |= button;
  pointing_device_set_report(currentReport);
  pointing_device_send();
}

static void mouse_up(uint8_t button) {
  directive_timer = timer_read();
  report_mouse_t currentReport = pointing_device_get_report();
  currentReport.buttons &= ~button;
  pointing_device_set_report(currentReport);
  pointing_device_send();
}

static void mouse_toggle(uint8_t button) {
  directive_timer = timer_read();
  report_mouse_t currentReport = pointing_device_get_report();
  currentReport.buttons ^= button;
  pointing_device_set_report(currentReport);
  pointing_device_send();
}

static void move(enum DIRECTION dir) {
  directive_timer = timer_read();
  int mult = 1;
  int x = 0;
  int y = 0;
  switch (active_directive) {
    case MOUSE:
      mult=25;
      if(accelrated_4)
        mult = 1;
      else if (accelrated_3 || accelrated_2) 
        mult = 125;
      else if (accelrated_1)
        mult = 5;  

      switch (dir) {
        case UP:
          y = 0-mult;
          break;
        case DOWN:
          y = mult;
          break;
        case LEFT:
          x = 0-mult;
          break;
        case RIGHT:
          x = mult;
          break;
      }

      pointer(x, y, 0, 0);
      if(accelrated_3) {
        pointer(x, y, 0, 0);
        pointer(x, y, 0, 0);
        pointer(x, y, 0, 0);
        pointer(x, y, 0, 0);
        pointer(1, 1, 0, 0);
      }
      break;

    case SCROLL:
      mult=3;
      if(accelrated_4)
        mult = 1;
      else if (accelrated_3 || accelrated_2) 
        mult = 27;
      else if (accelrated_1)
        mult = 9;  

      switch (dir) {
        case UP:
          y = mult;
          break;
        case DOWN:
          y = 0-mult;
          break;
        case LEFT:
          x = 0-mult;
          break;
        case RIGHT:
          x = mult;
          break;
      }
      if (active_os==MAC)
        y = 0-y;

      pointer(0, 0, x, y);
      if (active_os==MAC)
        pointer(0, 0, x, y);
      if(accelrated_3) {
        pointer(0, 0, x, y);
        pointer(0, 0, x, y);
        pointer(0, 0, x, y);
        pointer(0, 0, x, y);
      }
      break;

    case TEXTMOTION:
      switch (dir) {
        case UP:
          register_code(KC_UP);
          break;
        case DOWN:
          register_code(KC_DOWN);
          break;
        case LEFT:
          register_code(KC_LEFT);
          break;
        case RIGHT:
          register_code(KC_RIGHT);
          break;
      }
      break;

  }
}

static void release_move(enum DIRECTION dir) {
  switch (active_directive) {
    case TEXTMOTION:
      switch (dir) {
        case UP:
          unregister_code(KC_UP);
          break;
        case DOWN:
          unregister_code(KC_DOWN);
          break;
        case LEFT:
          unregister_code(KC_LEFT);
          break;
        case RIGHT:
          unregister_code(KC_RIGHT);
          break;
      }
      break;
    case SCROLL:
    case MOUSE:
      break;
  }
}

void shifted_tap(uint16_t key, uint16_t key_on_shift) {
    if(get_mods() & MOD_BIT(KC_LSHIFT))
      tap_code16(key_on_shift);
    else
      tap_code16(key);
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool lshift =  get_mods() & MOD_BIT(KC_LSHIFT);
  bool rshift =  get_mods() & MOD_BIT(KC_RSHIFT);
  bool shifted = lshift || rshift;
  if (record->event.pressed) {
    switch (keycode) {
      case M_AE:
        if(active_os==MAC) SEND_STRING(SS_LALT("'"));
        if(active_os==WINDOWS) SEND_STRING(SS_LALT("'"));
        if(active_os==LINUX) SEND_STRING(SS_LCTL(SS_LSFT("u")) "00f8" SS_TAP(X_ENT));
        break;
      case M_OE:
        SEND_STRING(SS_LALT("o"));
        break;
      case M_AA:
        SEND_STRING(SS_LALT("a"));
        break;
      case M_ACCL_1:
        accelrated_1 = true; 
        break;
      case   M_ACCL_2:
        accelrated_2 = true; 
        break;
      case   M_ACCL_3:
        accelrated_3 = true; 
        break;
      case   M_ACCL_4:
        accelrated_4 = true; 
        break;
      case M_FIND:
        SEND_STRING(SS_LGUI("f"));
        break;
      case M_FIND_NEXT:
        SEND_STRING(SS_LGUI("g"));
        break;
      case M_FIND_PREVIOUS:
        SEND_STRING(SS_LGUI(SS_LALT(SS_LSFT("g"))));
        break;
      case M_FIND_CURSOR:
        SEND_STRING(SS_LGUI("cf") SS_DELAY(40) SS_LGUI("v") SS_TAP(X_ENT));
        break;

      case M_OS_WINDOWS:
        set_os(WINDOWS);
        break;
      case M_OS_LINUX:
        set_os(LINUX);
        break;
      case M_OS_MAC:
        set_os(MAC);
        break;

      case   M_DIRECTIVE_TEXTMOTION:
        set_directive(TEXTMOTION);
          break;
      case   M_DIRECTIVE_MOUSE:
        set_directive(MOUSE);
          break;
      case   M_DIRECTIVE_SCROLL:
        set_directive(SCROLL);
          break;
      case   M_UP:
        move(UP);
        break;
      case   M_DOWN:
        move(DOWN);
        break;
      case   M_LEFT:
        move(LEFT);
        break;
      case   M_RIGHT:
        move(RIGHT);
        break;

      case M_MOUSE1:
        mouse_down(MOUSE_BTN1);
        break;
      case M_TOGGLE_MOUSE1:
        mouse_toggle(MOUSE_BTN1);
        break;

      case M_MOUSE2:
        mouse_down(MOUSE_BTN2);
        break;
      case M_TOGGLE_MOUSE2:
        mouse_toggle(MOUSE_BTN2);
        break;

      case M_MOUSE3:
        mouse_down(MOUSE_BTN3);
        break;
      case M_TOGGLE_MOUSE3:
        mouse_toggle(MOUSE_BTN3);
        break;

      case   M_PARENTHESIS:
        if(!shifted) tap_code16(S(KC_LEFT_PAREN));
        else tap_code16(KC_RIGHT_PAREN);
        break;
      case   M_CURLIES:
        if(!shifted) tap_code16(S(KC_LEFT_CURLY_BRACE));
        else tap_code16(KC_RIGHT_CURLY_BRACE);
        break;
      case M_BRACKETS:
        if(!shifted) tap_code16(KC_LBRACKET);
        else {
          if(lshift) unregister_code(KC_LSHIFT);
          if(rshift) unregister_code(KC_RSHIFT);
          tap_code(KC_RBRACKET);
          if(lshift) register_code(KC_LSHIFT);
          if(rshift) register_code(KC_RSHIFT);
        }
    }
  } else {
    switch (keycode) {
      case M_ACCL_1:
        accelrated_1 = false; 
        break;
      case M_ACCL_2:
        accelrated_2 = false; 
        break;
      case M_ACCL_3:
        accelrated_3 = false; 
        break;
      case M_ACCL_4:
        accelrated_4 = false; 
        break;
      case   M_UP:
        release_move(UP);
        break;
      case   M_DOWN:
        release_move(DOWN);
        break;
      case   M_LEFT:
        release_move(LEFT);
        break;
      case   M_RIGHT:
        release_move(RIGHT);
        break;
      case M_MOUSE1:
        mouse_up(MOUSE_BTN1);
        break;
      case M_MOUSE2:
        mouse_up(MOUSE_BTN2);
        break;
      case M_MOUSE3:
        mouse_up(MOUSE_BTN3);
        break;
    }
  }
  return true;
};

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}


static void render_status(void) {
  // QMK Logo and version information
  render_qmk_logo();
  oled_write_P(PSTR("       Kyria rev1.0\n\n"), false);

  if(active_directive != TEXTMOTION && timer_elapsed(directive_timer) > 15000) {
    active_directive = TEXTMOTION;
  }
  // Host Keyboard Layer Status
  oled_write_P(PSTR("Layer: "), false);
  switch (get_highest_layer(layer_state)) {
    case QWERTY:
      oled_write_P(PSTR("Qwerty\n"), false);
      break;
    case QWERTY_MAC:
      oled_write_P(PSTR("Qwerty (M)\n"), false);
      break;
    case QWERTY_MOD_L: case QWERTY_MOD_R:
      oled_write_P(PSTR("Mod(Qerty)\n"), false);
      break;
    case NAVIGATION:
      oled_write_P(PSTR("Navigation\n"), false);
      break;
    case NAVIGATION_MOD:
      oled_write_P(PSTR("Mod(Nav)\n"), false);
      break;
    case NUMBERS:
      oled_write_P(PSTR("Numeric\n"), false);
      break;
    case NUMBERS_MOD:
      oled_write_P(PSTR("Mod(Numeric)\n"), false);
      break;
    default:
      oled_write_P(PSTR("Undefined\n"), false);
  }

  switch (active_os) {
    case MAC:
      oled_write_P(PSTR("MACINTOSH     "), false);
      break;
    case WINDOWS:
      oled_write_P(PSTR("WINDOWS       "), false);
      break;
    case LINUX:
      oled_write_P(PSTR("LUNIX         "), false);
      break;
    default:
      oled_write_P(PSTR("Undefined     "), false);
  }
  
  (active_directive) == TEXTMOTION ? oled_write_P(PSTR("ARROWS "), false)
  : (active_directive) == MOUSE ? oled_write_P(PSTR("MOUSE  "), false)
  :(active_directive) == SCROLL ? oled_write_P(PSTR("SCROLL "), false)
    :oled_write_P(PSTR("UNKNOWN"), false);


  // Host Keyboard LED Status
  //uint8_t led_usb_state = host_keyboard_leds();
  //oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK)    ? PSTR("NUMLCK") : PSTR("      "), false);
  //oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK)   ? PSTR("CAPLCK") : PSTR("      "), false);
  //oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK") : PSTR("      "), false);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  //if(get_highest_layer(state) < QWERTY_MOD_L && IS_LAYER_ON_STATE(state, CMD)) {
  if(get_highest_layer(state) < QWERTY_MOD_L) 
    return state & (~((1 << CMD) | (1 << CMD_MAC)));
  
  if(active_os == MAC)
    return state  | (1 << CMD_MAC) | (1 << CMD);
  return state  | (1 << CMD);
}

void suspend_power_down_user(void) {
  if(active_os == MAC)
    layer_on(QWERTY_MAC);
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  } else {
    render_kyria_logo();
  }
}
#endif

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool antiClockwise) {
  if (index == 0) {
    for(int i = 0; i < (accelrated_1 ? 10 : 1); i++) {
      if (antiClockwise) {
        //tap_code(KC_UP);
        move(UP);
        release_move(UP);
      } else {
        //tap_code(KC_DOWN);
        move(DOWN);
        release_move(DOWN);
      }
    }
  } else if (index == 1) {
    for(int i = 0; i < (accelrated_1 ? 5 : 1); i++) {
      if (antiClockwise) {
        //tap_code(KC_LEFT);
        move(LEFT);
        release_move(LEFT);
      } else {
        //tap_code(KC_RIGHT);
        move(RIGHT);
        release_move(RIGHT);
      }
    }
  }
}
#endif
