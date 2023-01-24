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
#include "commands.c"
#include "macros.c"
#include "norwegian.c"



#define __ KC_TRNS
#define XX KC_NO



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 
   * Base Layer: QWERTY
   *
   * ,----------------------------------.    ,----------------------------------.
   * |   @  |   U  |   _  |   Y  |      |    |      |   P  |   G  |   M  |      |
   * |------+------+------+------+------|    |------+------+------+------+------|
   * |   O  |   I  |   E  |   A  |   ;  |    |   W  |   T  |   S  |   R  |   N  |
   * |------+------+------+------+------+    +------+------+------+------+------|
   * |   =  |   '  |   (  |   {  |   \  |    |      |   L  |   D  |   H  |   C  |
   * `-------------+------+------+------+    +------+------+------+-------------'
   *        | NAV  |EXTRA |  NUM |                  |  SYM |  FUN |
   *        | Lead | Bspc | Tab  |                  |Enter |Space |
   *        `--------------------'                  `-------------'
   */
  [QWERTY] = LAYOUT_charybdis_3x5(
      KC_AT, KC_U, M_DASH, KC_Y, __,
      __, KC_P, KC_G, KC_M, __,

      LCTL_T(KC_O), LALT_T(KC_I), LGUI_T(KC_E), LSFT_T(KC_A), KC_SCLN,
      KC_W, RSFT_T(KC_T), RGUI_T(KC_S), RALT_T(KC_R), RCTL_T(KC_N),

      KC_EQL, KC_QUOT, M_PAREN, M_CURLY, KC_BSLS,
      KC_V, KC_L, KC_D, KC_H, KC_C,

      LT(NAV, KC_LEAD), LT(EXTRA,KC_BSPC), LT(NUM, KC_TAB),
      LT(EXTRA,KC_ENT), LT(NUM,KC_SPC)
      ),

  [QWERTY_PC] = LAYOUT_charybdis_3x5(
      __, __, __, __, __,
      __, __, __, __, __,

      LGUI_T(KC_O), __, LCTL_T(KC_E), __, __,
      __, __, RCTL_T(KC_S), __, RGUI_T(KC_N),

      __, __, __, __, __,
      __, __, __, __, __,

      LT(NAV_PC, KC_LEAD), LT(EXTRA_PC,KC_BSPC), LT(NUM_PC, KC_TAB),
      LT(EXTRA_PC,KC_ENT), LT(NUM_PC,KC_SPC)
      ),

  [NUM] = LAYOUT_charybdis_3x5(
      KC_F10, KC_F7, KC_F8, KC_F9, XX,
      KC_KP_PLUS, KC_7, KC_8, KC_9, KC_PCMM,

      LCTL_T(KC_F11), LALT_T(KC_F4), LGUI_T(KC_F5), LSFT_T(KC_F6), XX,
      KC_PEQL, RSFT_T(KC_4), LGUI_T(KC_5), RALT_T(KC_6), RCTL_T(KC_0),

      KC_F12, KC_F1, KC_F2, KC_F3, XX,
      KC_MINS, KC_1, KC_2, KC_3, KC_PDOT,

      LT(SYSTEM, KC_LEAD), LT(SYSTEM,KC_DEL), LT(SYSTEM, KC_TAB),
      LT(SYSTEM,KC_ENT), LT(SYSTEM,KC_SPC)
      ),

  [NUM_PC] = LAYOUT_charybdis_3x5(
      __, __, __, __, __,
      __, __, __, __, __,

      LGUI_T(KC_F11), __, LCTL_T(KC_F5), __, __,
      __, __, RCTL_T(KC_5), __, RGUI_T(KC_0),

      __, __, __, __, __,
      __, __, __, __, __,

      __, __, __,
      __, __
      ),

  [EXTRA] = LAYOUT_charybdis_3x5(
      M_AE, M_OE, M_AA, XX, XX,
      XX, KC_Z, KC_Q, KC_X, XX,

      LCTL_T(KC_GRV), LALT_T(KC_EQL), LGUI_T(KC_COMM), LSFT_T(KC_DOT), KC_INS,
      KC_ESC, RSFT_T(KC_B), LGUI_T(KC_F), RALT_T(KC_J), RCTL_T(KC_V),

      KC_EXLM, KC_ASTR, M_BRACKET, M_CROCODILE, KC_BSLS,
      KC_INS, KC_K, KC_BTN2, KC_BTN1, KC_BTN3,

      __, __, __,
      __, __
      ),

  [EXTRA_PC] = LAYOUT_charybdis_3x5(
      __, __, __, __, __,
      __, __, __, __, __,

      LGUI_T(KC_GRV), __, LCTL_T(KC_COMM), __, __,
      __, __, RCTL_T(KC_F), __, RGUI_T(KC_V),

      __, __, __, __, __,
      __, __, __, __, __,

      __, __, __,
      __, __
      ),



  [NAV] = LAYOUT_charybdis_3x5(
      XX, XX, XX, XX, XX,
      COM_FIND_PREVIOUS, COM_CUT, COM_COPY, COM_PASTE, XX,

      KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XX,
      COM_FIND, KC_DOWN, KC_UP, KC_LEFT, KC_RGHT,

      COM_PREVIOUS_TAB, COM_NEXT_TAB, COM_UDO, COM_RDO, XX,
      COM_FIND_NEXT, KC_PGDN, KC_PGUP, KC_HOME, KC_END,

      __, __, __,
      __, __
      ),

  [NAV_PC] = LAYOUT_charybdis_3x5(
      __, __, __, __, __,
      __, __, __, __, __,

      KC_LGUI, __, KC_LCTL, __, __,
      __, __, __, __, __,

      __, __, __, __, __,
      __, __, __, __, __,

      __, __, __,
      __, __
      ),

  [SYSTEM] = LAYOUT_charybdis_3x5(
      QK_BOOT, XX, XX, XX, KC_CAPS,
      XX, XX, XX, M_OS_MAC, XX,

      XX, XX, XX, XX, XX,
      M_OS_WINDOWS, KC_PSCR, XX, XX, XX,

      POINTER_DEFAULT_DPI_REVERSE, POINTER_DEFAULT_DPI_FORWARD, XX, XX, KC_NUM,
      XX, M_OS_LINUX, XX, XX, XX,

      XX, XX, XX,
      XX, XX
      ),

//  [NUM] = LAYOUT_charybdis_3x5(
//      __, __, __, __, __,
//      __, __, __, __, __,
//
//      __, __, __, __, __,
//      __, __, __, __, __,
//
//      __, __, __, __, __,
//      __, __, __, __, __,
//
//      __, __, __,
//      __, __
//      ),
};



static void set_os(enum os new_os) {
  active_os = new_os;
  if(active_os != MAC) layer_on(QWERTY_PC);
  else layer_off(QWERTY_PC);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    if(
      norwegian_macro_pressed(keycode)
      || macro_pressed(keycode)
      || command_macro_pressed(keycode)
     ) return false;
      switch (keycode) {
        case M_OS_WINDOWS:
          set_os(WINDOWS);
          break;
        case M_OS_LINUX:
          set_os(LINUX);
          break;
        case M_OS_MAC:
          set_os(MAC);
          break;
      }
  }
  return true;
};