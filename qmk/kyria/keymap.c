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
#include "state.c"
#include "oled.c"
#include "navigation.c"





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

      M_ACCL_1, KC_NO, KC_BSPC, KC_BSPC, KC_TAB, 
      LT(NUMBERS,KC_ENT), LT(NAVIGATION,KC_SPC), LT(NAVIGATION, KC_SPC), KC_NO, M_ACCL_1
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

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      MO(NUMBERS_MOD), MO(NAVIGATION_MOD), MO(NAVIGATION_MOD), KC_TRNS, KC_TRNS
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

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      MO(NUMBERS_MOD), MO(NAVIGATION_MOD), MO(NAVIGATION_MOD), KC_TRNS, KC_TRNS
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

      M_OS_LINUX, M_OS_MAC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_F10, KC_F4, KC_F5, KC_F6, KC_F11, KC_BSPC,

      M_OS_WINDOWS, M_OS_WINDOWS, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, KC_TRNS, KC_TRNS,
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





static void set_os(enum os new_os) {
  active_os = new_os;
  if(active_os == MAC) layer_on(QWERTY_MAC);
  else layer_off(QWERTY_MAC);
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
        else if(active_os==WINDOWS && shifted) {
          if(lshift) unregister_code(KC_LSHIFT);
          if(rshift) unregister_code(KC_RSHIFT);
          SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_9) SS_TAP(X_KP_8)));
        }
        else if(active_os==WINDOWS)
          SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_3) SS_TAP(X_KP_0)));
        else if(active_os==LINUX && shifted) SEND_STRING(SS_LCTL(SS_LSFT("u")) "00c6" SS_TAP(X_ENT));
        else if(active_os==LINUX) SEND_STRING(SS_LCTL(SS_LSFT("u")) "00e6" SS_TAP(X_ENT));
        break;
      case M_OE:
        if(active_os==MAC) SEND_STRING(SS_LALT("o"));
        else if(active_os==WINDOWS && shifted) {
          if(lshift) unregister_code(KC_LSHIFT);
          if(rshift) unregister_code(KC_RSHIFT);
          SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_1) SS_TAP(X_KP_6)));
        }
        else if(active_os==WINDOWS)
          SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_4) SS_TAP(X_KP_8)));
        else if(active_os==LINUX && shifted) SEND_STRING(SS_LCTL(SS_LSFT("u")) "00d8" SS_TAP(X_ENT));
        else if(active_os==LINUX) SEND_STRING(SS_LCTL(SS_LSFT("u")) "00f8" SS_TAP(X_ENT));
        break;
      case M_AA:
        if(active_os==MAC) SEND_STRING(SS_LALT("a"));
        else if(active_os==WINDOWS && shifted) {
          if(lshift) unregister_code(KC_LSHIFT);
          if(rshift) unregister_code(KC_RSHIFT);
          SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_9) SS_TAP(X_KP_7)));
        }
        else if(active_os==WINDOWS)
          SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_9)));
        else if(active_os==LINUX && shifted) SEND_STRING(SS_LCTL(SS_LSFT("u")) "00c5" SS_TAP(X_ENT));
        else if(active_os==LINUX) SEND_STRING(SS_LCTL(SS_LSFT("u")) "00e5" SS_TAP(X_ENT));
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
        }
    }
    if(lshift) register_code(KC_LSHIFT);
    if(rshift) register_code(KC_RSHIFT);
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
