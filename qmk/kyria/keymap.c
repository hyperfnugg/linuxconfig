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

enum layers {
  QWERTY = 0,
  QWERTY_MAC,
  CMD,
  CMD_MAC,
  QWERTY_MOD,
  NAVIGATION,
  NAVIGATION_MOD,
  NUMBERS,
  NUMBERS_MOD
};

enum os {
  WINDOWS = 0,
  MAC,
  LINUX
};

enum custom_keycodes {
  M_AE = SAFE_RANGE,
  M_OE,
  M_AA,
  M_CUT,
  M_COPY,
  M_PASTE,
  M_UNDO,
  M_REDO,
  M_FIND,
  M_FIND_CURSOR,
  M_FIND_NEXT,
  M_FIND_PREVIOUS,
  M_OS_WINDOWS,
  M_OS_LINUX,
  M_OS_MAC,
  M_ACCL_1,
  M_ACCL_2,
  M_ACCL_3,
  M_DIRECTIVE_TEXTMOTION,
  M_DIRECTIVE_MOUSE,
  M_DIRECTIVE_SCROLL
};

enum tap_dances {
  TD_ACC1_X,
  TD_ACC2_C,
  TD_ACC3_V,
};


enum DIRECTIVES{
  TEXTMOTION,
  MOUSE,
  SCROLL,
};

bool accelrated_1 = false;
bool accelrated_2 = false;
bool accelrated_3 = false;


enum os active_os = MAC;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 
   * Base Layer: QWERTY
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |   = +  |   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |Backspac|
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |   tab  |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |   Esc  |MOD/Z |   X  |   C  |   V  |   B  | \ |  |Insert|  |   (  |  )   |   N  |   M  | ,  < | . >  |MOD /?|  - _   |
   * `----------------------+------+------+------+------+------+  |------+------+------+------+------+----------------------'
   *                        |Accel |      |LAYR  |LAYR  |LAYR  |  |Enter |Space |Space |      |      |
   *                        |      |      |  2   |  2   |  4   |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
  [QWERTY] = LAYOUT(
      KC_EQL, KC_Q, KC_W, KC_E, KC_R, KC_T,
      KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,

      KC_TAB, LALT_T(KC_A), LCTL_T(KC_S), LT(QWERTY_MOD, KC_D), LSFT_T(KC_F), KC_G,
      KC_H, RSFT_T(KC_J), LT(QWERTY_MOD, KC_K), RCTL_T(KC_L), RALT_T(KC_SCLN), KC_QUOT,

      KC_ESC, LGUI_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_BSLS, KC_INS,
      KC_LPRN, KC_RPRN, KC_N, KC_M, KC_COMM, KC_DOT, RGUI_T(KC_SLSH), KC_MINS,

      M_ACCL_1, KC_NO, TT(NAVIGATION), TT(NAVIGATION), TT(NUMBERS), 
      KC_ENT, KC_SPC, KC_SPC, KC_NO, M_ACCL_1
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
      KC_TRNS, KC_TRNS, KC_TRNS, RGUI_T(KC_L), KC_TRNS, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, LCTL_T(KC_Z), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RCTL_T(KC_SLSH), KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
      ),

  /*
   * Command mods
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        | Alt  | Ctrl | MOD  |Shift |      |                              |      |Shift | MOD  | Ctrl | Alt  |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        | Win  |      |      |      |      |      |      |  |      |      |      |      |      |      | Win  |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
  [CMD] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

      KC_TRNS, KC_LALT, KC_LCTL, KC_TRNS, KC_LSHIFT, KC_TRNS,
      KC_TRNS, KC_RSHIFT, KC_TRNS, KC_RCTL, KC_RALT, KC_TRNS,

      KC_TRNS, KC_LGUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RGUI, KC_TRNS,

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
   * |        |      |Find  |FndNex|      |  ~   |                              |  @   |  (   |  )   |   [  |  ]   | Delete |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        |      |      |      |      |  `   |                              | Undo |   Æ  |   Ø  |   Å  |  \   |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |      |  |      |      | Redo |  {   |  }   |      |  |   |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
  [QWERTY_MOD] = LAYOUT(
      KC_TRNS, M_FIND_CURSOR, M_FIND, M_FIND_NEXT, KC_TRNS, KC_TILD,
      KC_AT, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_DEL,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_GRV,
      M_UNDO, M_AE, M_OE, M_AA, KC_BSLS, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, M_REDO, KC_LCBR, KC_RCBR, KC_TRNS, KC_PIPE, KC_TRNS,

      KC_TRNS, KC_TRNS, MO(NAVIGATION_MOD), MO(NAVIGATION_MOD), MO(NUMBERS_MOD),
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
      ),


  /*
   * Navigation Layer
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |      |      |      |      |      |                              |Arrow |Alt-tb|Scroll|Histry|fw/bw |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |                              |Left  | Down |  Up  | Right|Mouse |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |      |  |      |      |Mouse1|Mouse2| Copy |Paste | Cut  |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
  [NAVIGATION] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, LT(NAVIGATION_MOD, KC_TAB), KC_TRNS, KC_TRNS,
      KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_TRNS, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_ACL0, KC_ACL1, KC_ACL2, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2, M_COPY, M_PASTE, M_CUT, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
      ),
  /*
   * Mod navigation
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |Pause |PrScr |ScrLck|NumLck|CpsLck|                              |      |      |      |      |      |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        |      |      |      |      |      |                              | Home |Pg.Dwn|Pg.Up | End  |      |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
  [NAVIGATION_MOD] = LAYOUT(
      KC_TRNS, KC_PAUS, KC_PSCR, KC_SLCK, KC_NLCK, KC_CAPS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_TRNS, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
      ),


  /*
   * Numbers
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |        |      |      |      |      |      |                              |   )  | 7 &  | 8 *  | 9 (  |      | - _    |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * |        | WIN  | Alt  | Ctrl |Shift |      |                              |  (   | 4 $  | 5 %  | 6 ^  | < ,  | '  "   |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |        |      |      |      |      |      |      |      |  |      |      | 0 )  | 1 !  | 2 @  | 3 #  | > .  |  = +   |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */
  [NUMBERS] = LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_RPRN, KC_7, KC_8, KC_9, KC_TRNS, KC_MINS,

      KC_TRNS, KC_TRNS, KC_TRNS, LT(NUMBERS_MOD, KC_TAB), KC_TRNS, KC_TRNS,
      KC_LPRN, KC_4, KC_5, KC_6, KC_COMM, KC_QUOT,

      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_0, KC_1, KC_2, KC_3, KC_DOT, KC_EQL,

      KC_TRNS, MO(NUMBERS_MOD), KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, MO(NUMBERS_MOD), KC_TRNS
      ),


  /*
   * Functional layer
   *
   * ,-------------------------------------------.                              ,-------------------------------------------.
   * |   Mac  | RGB  | SAT+ | HUE+ |Brght+| MOD+ |                              |      | F7   | F8   | F9   | F10  |        |
   * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
   * | Linux  |      |      |      |      |      |                              |      | F4   | F5   | F6   | F11  |        |
   * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
   * |Windows |      | SAT- | HUE- |Brght+| MOD- |      |      |  |      |      |      | F1   | F2   | F3   | F12  |        |
   * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        |      |      |      |      |      |  |      |      |      |      |      |
   *                        `----------------------------------'  `----------------------------------'
   */

  [NUMBERS_MOD] = LAYOUT(
      M_OS_MAC, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,
      KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS,

      M_OS_LINUX, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_F4, KC_F5, KC_F6, KC_F11, KC_TRNS,

      M_OS_WINDOWS, KC_TRNS, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F12, KC_TRNS,

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



#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
  static const char PROGMEM kyria_logo[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
    0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
    0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
  };
  oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}


static void set_os(enum os new_os) {
  active_os = new_os;
  if(active_os == MAC) layer_on(QWERTY_MAC);
  else layer_off(QWERTY_MAC);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case M_AE:
        SEND_STRING(SS_LALT("'"));
        break;
      case M_OE:
        SEND_STRING(SS_LALT("o"));
        break;
      case M_AA:
        SEND_STRING(SS_LALT("a"));
        break;
      case M_ACCL_1:
        accelrated_1 = true; 
        break;

      case M_CUT:
        SEND_STRING(SS_LGUI("x"));
        break;
      case M_COPY:
        SEND_STRING(SS_LGUI("c"));
        break;
      case M_PASTE:
        SEND_STRING(SS_LGUI("v"));
        break;
      case M_UNDO:
        SEND_STRING(SS_LGUI("z"));
        break;
      case M_REDO:
        SEND_STRING(SS_LGUI(SS_LALT(SS_LSFT("z"))));
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
    }
  } else {
    switch (keycode) {
      case M_ACCL_1:
        accelrated_1 = false; 
        break;
    }
  }
  return true;
};

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
  // QMK Logo and version information
  render_qmk_logo();
  oled_write_P(PSTR("       Kyria rev1.0\n\n"), false);

  // Host Keyboard Layer Status
  oled_write_P(PSTR("Layer: "), false);
  switch (get_highest_layer(layer_state)) {
    case QWERTY: case QWERTY_MAC:
      oled_write_P(PSTR("Qwerty\n"), false);
      break;
    case QWERTY_MOD:
      oled_write_P(PSTR("Mod(Qerty)\n"), false);
      break;
    case NAVIGATION:
      oled_write_P(PSTR("Navigation\n"), false);
      break;
    case NAVIGATION_MOD:
      oled_write_P(PSTR("Mod(Nav)\n"), false);
      break;
    case NUMBERS:
      oled_write_P(PSTR("Numeric\n"), false);
      break;
    case NUMBERS_MOD:
      oled_write_P(PSTR("Mod(Numeric)\n"), false);
      break;
    default:
      oled_write_P(PSTR("Undefined\n"), false);
  }

  switch (active_os) {
    case MAC:
      oled_write_P(PSTR("MACINTOSH     "), false);
      break;
    case WINDOWS:
      oled_write_P(PSTR("WINDOWS       "), false);
      break;
    case LINUX:
      oled_write_P(PSTR("LUNIX         "), false);
      break;
    default:
      oled_write_P(PSTR("Undefined     "), false);
  }

  // Host Keyboard LED Status
  uint8_t led_usb_state = host_keyboard_leds();
  oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK)    ? PSTR("NUMLCK") : PSTR("      "), false);
  oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK)   ? PSTR("CAPLCK") : PSTR("      "), false);
  oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK") : PSTR("      "), false);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  if(get_highest_layer(state) < QWERTY_MOD && IS_LAYER_ON_STATE(state, CMD)) {
    layer_state_t s = state | (1 << CMD);
    if(active_os == MAC)
      return s  | (1 << CMD_MAC);
    else
      return s  & ~(1 << CMD_MAC); 
  }
  else if(!IS_LAYER_ON_STATE(state, CMD)) {
    return state & (~((1 << CMD) | (1 << CMD_MAC)));
  }

  return state;
}

void suspend_power_down_user(void) {
  if(active_os == MAC)
    layer_on(QWERTY_MAC);
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  } else {
    render_kyria_logo();
  }
}
#endif

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool antiClockwise) {
  if (index == 0) {
    for(int i = 0; i < (accelrated_1 ? 10 : 1); i++) {
      if (antiClockwise) {
        tap_code(KC_UP);
      } else {
        tap_code(KC_DOWN);
      }
    }
  } else if (index == 1) {
    for(int i = 0; i < (accelrated_1 ? 5 : 1); i++) {
      if (antiClockwise) {
        tap_code(KC_LEFT);
      } else {
        tap_code(KC_RIGHT);
      }
    }
  }
}
#endif
