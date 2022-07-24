
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
