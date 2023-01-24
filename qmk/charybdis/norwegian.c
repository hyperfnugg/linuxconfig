bool norwegian_macro_pressed(uint16_t keycode) {
  bool handled = false;
  bool lshift =  get_mods() & MOD_BIT(KC_LSFT);
  bool rshift =  get_mods() & MOD_BIT(KC_RSFT);
  bool shifted = lshift || rshift;
  switch (keycode) {
    case M_AE:
      handled = true;
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
      handled = true;
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
      handled = true;
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
      }
    if(handled) {
      if(lshift) register_code(KC_LSFT);
      if(rshift) register_code(KC_RSFT);
    }
    return handled;
}