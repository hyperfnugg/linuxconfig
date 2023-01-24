#include QMK_KEYBOARD_H

#include "pointing_device.h"
#include "report.h"
#include <stdio.h>
#include "state.h"
#include "state.c"
#include "navigation.c"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define LA  LALT_T
#define LC  LCTL_T
#define LW  LGUI_T
#define RA  LALT_T
#define RC  LCTL_T
#define RW  LGUI_T
#define __XX___  KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
    KC_Q,     KC_B,     KC_V,     KC_G,                     KC_W,     KC_K,     KC_Z,     KC_QUOT,   
              KC_C,     KC_H,     KC_P,                     KC_Y,     KC_O,     KC_J,    
    KC_R,     KC_S,     KC_N,     KC_T,                     KC_U,     KC_E,     KC_I,     KC_A,
    KC_X,     LW(KC_M), LA(KC_L), LC(KC_D),                 RC(KC_F),RA(KC_COMM),RW(KC_DOT),KC_SLSH,
          LT(SYMBOL,KC_BSPC), LSFT_T(KC_LEAD),     LT(FUN,KC_ENT), LT(NUMBERS,KC_SPC) 
),

[QWERTY_MAC] = LAYOUT(
    _______,  _______,  _______,  _______,                  _______,  _______,  _______,  _______,  
              _______,  _______,  _______,                  _______,  _______,  _______,            
    _______,  _______,  _______,  _______,                  _______,  _______,  _______,  _______,  
    _______,  LC(KC_M), _______, LW(KC_D),                 RW(KC_F),  _______,RC(KC_DOT), _______,
                        _______,  _______,                  _______,  _______
),

[COMMAND] = LAYOUT(
    __XX___,  __XX___,  __XX___,  __XX___,                  KC_ESC ,  __XX___,  __XX___,  KC_DEL ,  
              __XX___,  __XX___,  __XX___,                  __XX___,  __XX___,  __XX___,            
    __XX___,  __XX___,  __XX___,  __XX___,                  __XX___,  __XX___,  __XX___,  __XX___,  
    __XX___,  KC_LGUI,  KC_LALT,  KC_LCTL,                  KC_RCTL,  KC_RALT,  KC_RGUI,  KC_TAB ,
                        _______,  _______,                  _______,  _______
),

[CMD_MAC] = LAYOUT(
    _______,  _______,  _______,  _______,                  _______,  _______,  _______,  _______,  
              _______,  _______,  _______,                  _______,  _______,  _______,            
    _______,  _______,  _______,  _______,                  _______,  _______,  _______,  _______,  
    _______,  KC_LCTL,  _______,  KC_LGUI,                  KC_LGUI,  _______,  KC_LCTL,  _______,
                        _______,  _______,                  _______,  _______
),

[SYMBOL] = LAYOUT(
    _______,  KC_SCLN,  KC_LBRC,  KC_RBRC,                  _______,  KC_BSLS,  KC_PIPE,  _______,  
            KC_KP_PLUS, KC_LCBR,  KC_RCBR,                  KC_AMPR,  KC_ASTR,  KC_UNDS,            
    KC_COLN,  KC_EQL ,  M_MOUSE2, M_MOUSE1,                 KC_DLR ,  KC_PERC,  KC_CIRC,  KC_GRV ,  
    KC_TILD,  KC_MINS,  KC_LPRN,  KC_RPRN,                  KC_EXLM,  KC_AT  ,  KC_HASH,  _______,
                        _______,  _______,                  _______,  _______
),


[NUMBERS] = LAYOUT(

    _______,  M_AE   , M_OE    , M_AA    ,                  _______,  _______,  _______,  _______,  
            DIR_SCROLL, _______, DIR_MOUSE,                 KC_7   ,  KC_8   ,  KC_9   ,            
    M_LEFT , M_RIGHT , M_DOWN  , M_UP    ,                  KC_4   ,  KC_5   ,  KC_6   ,  KC_0   ,  
 DIR_TEXTMOTION,_______,_______,  _______,                  KC_1   ,  KC_2   ,  KC_3   ,  _______,
                        _______,  _______,                  _______,  _______
),

[FUN] = LAYOUT(
    _______,M_OS_WIN, M_OS_MAC,M_OS_LINUX,                  KC_F10 ,  KC_F11 ,  KC_F12 ,  _______,  
              _______,  _______,  _______,                  KC_F7  ,  KC_F8  ,  KC_F9  ,            
    KC_HOME,  KC_END ,  KC_PGDN,  KC_PGUP,                  KC_F4  ,  KC_F5  ,  KC_F6  ,  _______,  
    _______,  _______,  _______,  _______,                  KC_F1  ,  KC_F2  ,  KC_F3  ,  _______,
                        _______,  _______,                  _______,  _______
)




//M_FIND_CURSOR, M_FIND, M_FIND_NEXT
//M_ACCL_1, M_ACCL_2, M_ACCL_3, M_ACCL_4
//KC_PAUS, KC_PSCR, KC_SLCK, KC_NLCK, KC_CAPS
//KC_INS 

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

      case M_OS_WIN:
        set_os(WINDOWS);
        break;
      case M_OS_LINUX:
        set_os(LINUX);
        break;
      case M_OS_MAC:
        set_os(MAC);
        break;

      case   DIR_TEXTMOTION:
        set_directive(TEXTMOTION);
          break;
      case   DIR_MOUSE:
        set_directive(MOUSE);
          break;
      case   DIR_SCROLL:
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
