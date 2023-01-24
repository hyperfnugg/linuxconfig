
uint16_t  snipe_timer;
bool  snipe_shifted;
uint16_t  scroll_timer;
bool  scroll_shifted;
uint16_t  arrow_timer;
bool  arrow_shifted;

const int tap_time = 170;

bool navigation_macro_pressed(uint16_t keycode) {
  bool lshift =  get_mods() & MOD_BIT(KC_LSFT);
  bool rshift =  get_mods() & MOD_BIT(KC_RSFT);
  bool shifted = lshift || rshift;
  switch (keycode) {
    case NAV_SCROLL_LPAREN:
    case NAV_SCROLL_LBRACKET:
    case NAV_SCROLL_FND:
    case NAV_SCROLL_TILDE:
      scroll_shifted = shifted;
      scroll_timer = timer_read();
      charybdis_set_pointer_dragscroll_enabled(true);
      return true;
    case NAV_SNIPE_DASH:
    case NAV_SNIPE_QUESTION:
    case NAV_SNIPE_RDO:
    case NAV_SNIPE_PERCENT:
      snipe_shifted = shifted;
      snipe_timer = timer_read();
      charybdis_set_pointer_sniping_enabled(true);
      return true;
    case NAV_ARROW_QUOT:
    case NAV_ARROW_GRV:
    case NAV_ARROW_UDO:
    case NAV_ARROW_DOLLAR:
      arrow_shifted = shifted;
      arrow_timer = timer_read();
      return true;
  }
  return false;
}

void tap_shifted(bool shifted, uint16_t key, uint16_t key_on_shift) {
  bool lshift =  get_mods() & MOD_BIT(KC_LSFT);
  bool rshift =  get_mods() & MOD_BIT(KC_RSFT);
  if(lshift) unregister_code(KC_LSFT);
  if(rshift) unregister_code(KC_RSFT);
  if(shifted) {
    tap_code16(key_on_shift);
  }
  else
    tap_code16(key);
  if(lshift) register_code(KC_LSFT);
  if(rshift) register_code(KC_RSFT);
}

bool is_scroll_tap(void) {
  return TIMER_DIFF_16(timer_read(), scroll_timer) < tap_time;
}

void clear_scroll(void) {
  charybdis_set_pointer_dragscroll_enabled(false);
}

void scroll_release(uint16_t key, uint16_t key_shifted) {
  if(is_scroll_tap()) {
    tap_shifted(scroll_shifted, key, key_shifted);
  }
  clear_scroll();
}

bool is_snipe_tap(void) {
  return TIMER_DIFF_16(timer_read(), snipe_timer) < tap_time;
}

void clear_snipe(void) {
  charybdis_set_pointer_sniping_enabled(false);
}

void snipe_release(uint16_t key, uint16_t key_shifted) {
  if(is_snipe_tap()) {
    tap_shifted(snipe_shifted, key, key_shifted);
  }
  clear_snipe();
}

bool is_arrow_tap(void) {
  return TIMER_DIFF_16(timer_read(), arrow_timer) < tap_time;
}

void clear_arrow(void) {
}

void arrow_release(uint16_t key, uint16_t key_shifted) {
  if(is_arrow_tap()) {
    tap_shifted(arrow_shifted, key, key_shifted);
  }
  clear_arrow();
}

bool navigation_macro_released(uint16_t keycode) {
  switch (keycode) {
    case NAV_SCROLL_LPAREN:
      scroll_release(KC_LPRN, KC_LCBR);
      return true;
    case NAV_SCROLL_LBRACKET:
      scroll_release(KC_LBRC, 0);
      return true;
    case NAV_SCROLL_FND:
      if(is_scroll_tap()) {
        cmd_find();
      }
      clear_scroll();
      return true;
    case NAV_SCROLL_TILDE:
      scroll_release(KC_TILD, 0);
      return true;
    case NAV_ARROW_QUOT:
      arrow_release(KC_QUOT, KC_DQUO);
      return true;
    case NAV_ARROW_GRV:
      arrow_release(KC_GRV, 0);
      return true;
    case NAV_ARROW_UDO:
      if(is_arrow_tap()) {
        cmd_undo();
      }
      clear_arrow();
      return true;
    case NAV_ARROW_DOLLAR:
      arrow_release(KC_DLR, 0);
      return true;
    case NAV_SNIPE_DASH:
      snipe_release( KC_UNDS, KC_MINS);
      return true;
    case NAV_SNIPE_QUESTION:
      snipe_release(KC_QUES, 0);
      return true;
    case NAV_SNIPE_RDO:
      if(is_snipe_tap()) {
        cmd_redo();
      }
      clear_snipe();
      return true;
    case NAV_SNIPE_PERCENT:
      snipe_release(KC_PERC, 0);
      return true;
  }
  return false;
}