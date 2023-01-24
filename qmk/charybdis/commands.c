bool command_macro_pressed(uint16_t keycode) {
  switch (keycode) {
    case COM_UDO:
      if(active_os==MAC) SEND_STRING(SS_LGUI("z"));
      else SEND_STRING(SS_LCTL("z"));
      return true;
    case COM_RDO:
      if(active_os==MAC) SEND_STRING(SS_LSFT(SS_LGUI("z")));
      else SEND_STRING(SS_LSFT(SS_LCTL("z")));
      return true;
    case COM_FIND:
      if(active_os==MAC) SEND_STRING(SS_LGUI("f"));
      else SEND_STRING(SS_LCTL("f"));
      return true;
    case COM_FIND_NEXT:
      if(active_os==MAC) SEND_STRING(SS_LGUI("g"));
      else SEND_STRING(SS_TAP(X_F3));
      return true;
    case COM_FIND_PREVIOUS:
      if(active_os==MAC) SEND_STRING(SS_LSFT(SS_LGUI("g")));
      else SEND_STRING(SS_LSFT(SS_TAP(X_F3)));
      return true;
    case COM_COPY:
      if(active_os==MAC) SEND_STRING(SS_LGUI("c"));
      else SEND_STRING(SS_LCTL("c"));
      return true;
    case COM_PASTE:
      if(active_os==MAC) SEND_STRING(SS_LGUI("v"));
      else SEND_STRING(SS_LCTL("v"));
      return true;
    case COM_CUT:
      if(active_os==MAC) SEND_STRING(SS_LGUI("x"));
      else SEND_STRING(SS_LCTL("x"));
      return true;
    case COM_NEXT_TAB:
      SEND_STRING(SS_LCTL(SS_TAP(X_TAB)));
      return true;
    case COM_PREVIOUS_TAB:
      SEND_STRING(SS_LSFT(SS_LCTL(SS_TAP(X_TAB))));
      return true;

  }
  return false;
};

