#include QMK_KEYBOARD_H

enum {
  BASE_LAYER = 0,
  HELD_LAYER,
  TAP_LAYER
};

enum custom_keycodes {
  LAYER_TAP_HOLD = SAFE_RANGE,
  M_REPEAT,
};
static bool is_m_repeat = false;
//qmk json2c idobo_justgook.json >> keymapAAA.c

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_5x15(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, RGUI(KC_BSPC), KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_DEL, KC_BSPC, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_BSLS, KC_SFTENT, KC_SFTENT, KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_COMM, KC_DOT, KC_SLSH, KC_UP, KC_SFTENT, LAYER_TAP_HOLD, KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_SPC, KC_RGUI, KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
	[1] = LAYOUT_ortho_5x15(KC_NO, KC_BRID, KC_BRIU, KC_F16, KC_F17, KC_NO, KC_NO, KC_MRWD, KC_MPLY, KC_MFFD, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_BSPC, KC_NO, M_REPEAT, KC_BTN1, KC_BTN1, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PSLS, KC_7, KC_8, KC_9, KC_MINS, RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PAST, KC_4, KC_5, KC_6, KC_PLUS, LGUI(KC_GRV), KC_GRV, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_1, KC_2, KC_3, KC_PENT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_0, KC_DOT, KC_NO, KC_PEQL),
	[2] = LAYOUT_ortho_5x15(KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_RSFT, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO)
};

static uint16_t key_timer;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LAYER_TAP_HOLD:
        if(record->event.pressed) {
            key_timer = timer_read();
            layer_on(HELD_LAYER);
        }
        else {
            layer_off(HELD_LAYER);
            if(timer_elapsed(key_timer) < 150){
                layer_on(TAP_LAYER);
                set_oneshot_layer(TAP_LAYER, ONESHOT_START);
                clear_oneshot_layer_state(ONESHOT_PRESSED);
            }
        }
        return false;
        break;

    case M_REPEAT:
        is_m_repeat = record->event.pressed;
        break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {
    if (is_m_repeat) {
        register_code(KC_BTN1);
        unregister_code(KC_BTN1);
    }
}

void led_set_user(uint8_t usb_led) {

}
