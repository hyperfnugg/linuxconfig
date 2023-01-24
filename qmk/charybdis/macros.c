
void tap_shifted(uint16_t key, uint16_t key_on_shift) {
  bool lshift =  get_mods() & MOD_BIT(KC_LSFT);
  bool rshift =  get_mods() & MOD_BIT(KC_RSFT);
  if(lshift) unregister_code(KC_LSFT);
  if(rshift) unregister_code(KC_RSFT);
  bool shifted = lshift || rshift;
  if(shifted) {
    tap_code16(key_on_shift);
  }
  else
    tap_code16(key);
  if(lshift) register_code(KC_LSFT);
  if(rshift) register_code(KC_RSFT);
}

bool macro_pressed(uint16_t keycode) {
  switch (keycode) {
    case M_PAREN:
      tap_shifted(KC_LPRN, KC_RPRN);
      return true;
    case M_CURLY:
      tap_shifted(KC_LCBR, KC_RCBR);
      return true;
    case M_CROCODILE:
      tap_shifted(KC_LT, KC_GT);
      return true;
    case M_BRACKET:
      tap_shifted(KC_LBRC, KC_RBRC);
      return true;
    case M_DASH:
      tap_shifted(KC_UNDS, KC_MINS);
      return true;
  }
  return false;
}