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
//#include "navigation.c"



#define __ KC_TRNS
#define XX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 
   * Base Layer: QWERTY
   *
   * ,----------------------------------.    ,----------------------------------.
   * |   Y  |   U  |   ,  |   .  |   J  |    |   B  |   P  |   G  |   M  |   F  |
   * |------+------+------+------+------|    |------+------+------+------+------|
   * |   O  |   E  |   I  |   A  |   ;  |    |   W  |   T  |   S  |   R  |   N  |
   * |------+------+------+------+------+    +------+------+------+------+------|
   * |   '  |   -  |   (  |   )  |   K  |    |   V  |   L  |   D  |   H  |   C  |
   * `-------------+------+------+------+    +------+------+------+-------------'
   *        | SYM  |      |      |                  |  NAV |  NUM |
   *        | BSPC |  M1  |  M2  |                  |Enter |Space |
   *        `--------------------'                  `-------------'
   */
  [QWERTY] = LAYOUT_charybdis_3x5(
      KC_Y, KC_U, KC_COMM, KC_DOT, KC_J,
      KC_B, KC_P, KC_G, KC_M, KC_F,

      LGUI_T(KC_HASH), LALT_T(KC_E), LCTL_T(KC_I), LSFT_T(KC_A), KC_SCLN,
      KC_W, RSFT_T(KC_T), RCTL_T(KC_S), RALT_T(KC_R), RGUI_T(KC_N),

      KC_QUOT, KC_MINS, M_LPARENTHESIS, M_RPARENTHESIS, KC_K,
      KC_V, KC_L, KC_D, KC_H, KC_C,

      LT(SYM,KC_BSPC), KC_BTN1, KC_BTN2,
      LT(NAV,KC_ENT), LT(NUM,KC_SPC)
      ),

  [QWERTY_MAC] = LAYOUT_charybdis_3x5(
      __, __, __, __, __,
      __, __, __, __, __,

      LCTL_T(KC_O), __, LGUI_T(KC_I), __, __,
      __, __, RGUI_T(KC_S), __, RCTL_T(KC_N),

      __, __, __, __, __,
      __, __, __, __, __,

      __, __, __,
      LT(NAV_MAC,KC_ENT), __
      ),

  [NUM] = LAYOUT_charybdis_3x5(
      XX, KC_AMPR, KC_CIRC, KC_TILD, XX,
      KC_KP_PLUS, KC_P7, KC_P8, KC_P9, KC_PCMM,

      KC_HASH, KC_BSLS, KC_PAST, KC_EXLM, XX,
      KC_PEQL, KC_P4, KC_P5, KC_P6, KC_P0,

      KC_DLR, KC_PERC, KC_TILD, XX, XX,
      KC_TAB, KC_P1, KC_P2, KC_P3, KC_PDOT,

      LT(EXTRA,KC_BSPC), __, __,
      __, __
      ),

  [SYM] = LAYOUT_charybdis_3x5(
      M_AE, M_OE, M_AA, KC_KP_PLUS, XX,
      XX, KC_F7, KC_F8, KC_F9, KC_F10,

      KC_KP_PLUS, KC_SLSH, KC_BTN3, KC_TAB, KC_AT,
      KC_ESC, KC_F4, KC_F5, KC_F6, KC_F11,

      KC_GRV, KC_QUES, KC_LCBR, KC_RCBR, XX,
      KC_INS, KC_F1, KC_F2, KC_F3, KC_F12,

      __, __, __,
      __, LT(EXTRA,KC_SPC)
      ),



  [NAV] = LAYOUT_charybdis_3x5(
      XX, M_NTAB, M_NWIN, M_PROGRAM_WINDOW, XX,
      KC_Q, KC_PSTE, KC_COPY, KC_CUT, XX,

      KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_PSCR,
      XX, KC_DOWN, KC_UP, KC_LEFT, KC_RGHT,

      KC_AGIN, KC_UNDO, KC_FIND, M_FIND_NEXT, XX,
      KC_X, KC_PGDN, KC_PGUP, KC_HOME, KC_END,

      __, __, __,
      __, __
      ),

  [NAV_MAC] = LAYOUT_charybdis_3x5(
      __, __, __, __, __,
      __, __, __, __, __,

      KC_LCTL, __, KC_LGUI, __, __,
      __, __, __, __, __,

      __, __, __, __, __,
      __, __, __, __, __,

      __, __, __,
      __, __
      ),

  [EXTRA] = LAYOUT_charybdis_3x5(
      QK_BOOT, XX, XX, M_OS_MAC, KC_CAPS,
      XX, XX, XX, XX, XX,

      XX, XX, XX, XX, XX,
      M_OS_WINDOWS, XX, XX, XX, XX,

      XX, XX, XX, XX, XX,
      XX, M_OS_LINUX, XX, XX, KC_NUM,

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
//      case M_ACCL_1:
//        accelrated_1 = true;
//        break;
//      case   M_ACCL_2:
//        accelrated_2 = true;
//        break;
//      case   M_ACCL_3:
//        accelrated_3 = true;
//        break;
//      case   M_ACCL_4:
//        accelrated_4 = true;
//        break;
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

//      case   M_DIRECTIVE_TEXTMOTION:
//        set_directive(TEXTMOTION);
//          break;
//      case   M_DIRECTIVE_MOUSE:
//        set_directive(MOUSE);
//          break;
//      case   M_DIRECTIVE_SCROLL:
//        set_directive(SCROLL);
//          break;
//      case   M_UP:
//        move(UP);
//        break;
//      case   M_DOWN:
//        move(DOWN);
//        break;
//      case   M_LEFT:
//        move(LEFT);
//        break;
//      case   M_RIGHT:
//        move(RIGHT);
//        break;

//      case M_MOUSE1:
//        mouse_down(MOUSE_BTN1);
//        break;
//      case M_TOGGLE_MOUSE1:
//        mouse_toggle(MOUSE_BTN1);
//        break;
//
//      case M_MOUSE2:
//        mouse_down(MOUSE_BTN2);
//        break;
//      case M_TOGGLE_MOUSE2:
//        mouse_toggle(MOUSE_BTN2);
//        break;
//
//      case M_MOUSE3:
//        mouse_down(MOUSE_BTN3);
//        break;
//      case M_TOGGLE_MOUSE3:
//        mouse_toggle(MOUSE_BTN3);
//        break;

      case   M_LPARENTHESIS:
        if(!shifted) tap_code16(S(KC_LEFT_PAREN));
        else tap_code16(KC_LCBR);
        break;
      case   M_RPARENTHESIS:
        if(!shifted) tap_code16(S(KC_RIGHT_PAREN));
        else tap_code16(KC_RCBR);
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
//      case   M_UP:
//        release_move(UP);
//        break;
//      case   M_DOWN:
//        release_move(DOWN);
//        break;
//      case   M_LEFT:
//        release_move(LEFT);
//        break;
//      case   M_RIGHT:
//        release_move(RIGHT);
//        break;
//      case M_MOUSE1:
//        mouse_up(MOUSE_BTN1);
//        break;
//      case M_MOUSE2:
//        mouse_up(MOUSE_BTN2);
//        break;
//      case M_MOUSE3:
//        mouse_up(MOUSE_BTN3);
//        break;
    }
  }
  return true;
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_QUOT_SNIPE]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
};


//void encoder_update_user(uint8_t index, bool antiClockwise) {
//  if (index == 0) {
//    for(int i = 0; i < (accelrated_1 ? 10 : 1); i++) {
//      if (antiClockwise) {
//        //tap_code(KC_UP);
//        move(UP);
//        release_move(UP);
//      } else {
//        //tap_code(KC_DOWN);
//        move(DOWN);
//        release_move(DOWN);
//      }
//    }
//  } else if (index == 1) {
//    for(int i = 0; i < (accelrated_1 ? 5 : 1); i++) {
//      if (antiClockwise) {
//        //tap_code(KC_LEFT);
//        move(LEFT);
//        release_move(LEFT);
//      } else {
//        //tap_code(KC_RIGHT);
//        move(RIGHT);
//        release_move(RIGHT);
//      }
//    }
//  }
//}
