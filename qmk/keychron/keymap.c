#include QMK_KEYBOARD_H


enum layers {
  QWERTY = 0,
  QWERTY_PC,
  EXTRAS,
  CONFIG
};


enum custom_keycodes {
  M_AE = SAFE_RANGE,
  M_OE,
  M_AA,
  M_OS_WINDOWS,
  M_OS_LINUX,
  M_OS_MAC,
  M_HOME,
  M_END
};


enum os {
  WINDOWS = 0,
  MAC,
  LINUX
};

enum os active_os = MAC;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [QWERTY] = LAYOUT_ansi_82(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  LT(CONFIG, KC_DEL),KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGDN,
        LT(EXTRAS, KC_ESC), KC_A,KC_S,KC_D, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           M_END,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   
        KC_LGUI, KC_LCTL, KC_LALT,                   LT(EXTRAS, KC_SPC),                          KC_RALT, KC_RCTL, KC_RGUI, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [QWERTY_PC] = LAYOUT_ansi_82(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, 
        KC_LCTL, KC_LGUI, _______,                            _______,                            _______, KC_RGUI, KC_RCTL, _______, _______, _______
    ),

    [EXTRAS] = LAYOUT_ansi_82(
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_INS ,
        _______, _______, _______, _______, _______, _______, _______, KC_PGDN, KC_PGUP, _______, _______, M_AA   , _______, _______,            _______,
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,M_OE   , M_AE   ,          _______,          M_HOME,
        _______,          _______, _______, _______, _______, _______, M_HOME , M_END  , _______, _______, _______,          _______, _______,  
        _______, _______, _______,                            _______,                            _______, KC_MENU, _______, _______, _______, _______
    ),

    [CONFIG] = LAYOUT_ansi_82(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_VAD, RGB_VAI, _______,          RGB_MOD,
        _______, _______, M_OS_WINDOWS,_______,QK_BOOT,_______, _______, _______, _______, _______, _______, RGB_SPD, RGB_SPI, _______,          RGB_RMOD,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, M_OS_LINUX,_______,_______,         _______,          RGB_TOG,
        _______,          _______, _______, _______, _______, _______, KC_NUM, M_OS_MAC,_______, _______, _______,          _______, RGB_SAI,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_HUD, RGB_SAD, RGB_HUI
    )

};


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
    return true;
}


static void set_os(enum os new_os) {
  active_os = new_os;
  if(active_os == MAC) layer_off(QWERTY_PC);
  else layer_on(QWERTY_PC);
}



void shifted_tap(uint16_t key, uint16_t key_on_shift) {
    if(get_mods() & MOD_BIT(KC_LSFT))
      tap_code16(key_on_shift);
    else
      tap_code16(key);
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool lshift =  get_mods() & MOD_BIT(KC_LSFT);
  bool rshift =  get_mods() & MOD_BIT(KC_RSFT);
  bool shifted = lshift || rshift;
  if (record->event.pressed) {
    switch (keycode) {
      case M_AE:
        if(active_os==MAC) SEND_STRING(SS_LALT("'"));
        else if(active_os==WINDOWS && shifted) {
          if(lshift) unregister_code(KC_LSFT);
          if(rshift) unregister_code(KC_RSFT);
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
          if(lshift) unregister_code(KC_LSFT);
          if(rshift) unregister_code(KC_RSFT);
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
          if(lshift) unregister_code(KC_LSFT);
          if(rshift) unregister_code(KC_RSFT);
          SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_9) SS_TAP(X_KP_7)));
        }
        else if(active_os==WINDOWS)
          SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_2) SS_TAP(X_KP_2) SS_TAP(X_KP_9)));
        else if(active_os==LINUX && shifted) SEND_STRING(SS_LCTL(SS_LSFT("u")) "00c5" SS_TAP(X_ENT));
        else if(active_os==LINUX) SEND_STRING(SS_LCTL(SS_LSFT("u")) "00e5" SS_TAP(X_ENT));
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
      case M_HOME:
        if(active_os==MAC) {
          register_code16(G(KC_LEFT));
          unregister_code16(G(KC_LEFT));
        }
        else  SEND_STRING(SS_TAP(X_HOME));
        break;
      case M_END:
        if(active_os==MAC) {
          register_code16(G(KC_RIGHT));
          unregister_code16(G(KC_RIGHT));
        }
        else  SEND_STRING(SS_TAP(X_END));
        break;
    }
    if(lshift) register_code(KC_LSFT);
    if(rshift) register_code(KC_RSFT);
  } else {
    switch (keycode) {
    }
  }
  return true;
};
