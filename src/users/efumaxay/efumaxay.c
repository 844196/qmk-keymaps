#include "efumaxay.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!(
#ifdef NUM_WORD_ENABLE
            process_num_word(keycode, record) &&
#endif
#ifdef HOME_ROW_COMBO_ENABLE
            process_home_row_combo(keycode, record) &&
#endif
#ifdef SUPER_TAB_ENABLE
            process_super_tab(keycode, record) &&
#endif
    true)) {
        return false;
    }

    switch (keycode) {
        case MY_ESC:
            if (record->event.pressed) {
#ifdef CAPS_WORD_ENABLE
                caps_word_off();
#endif
#ifdef NUM_WORD_ENABLE
                num_word_off();
#endif

                if (is_oneshot_layer_active()) {
                    clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                }

                tap_code(IME_CANCEL);
                tap_code(KC_LNG2);

                register_code(KC_ESC);
            } else {
                unregister_code(KC_ESC);
            }
            break;

        case IME_ON:
            if (record->event.pressed) {
                register_code(KC_LNG1);
            } else {
                unregister_code(KC_LNG1);
            }
            break;

        case IME_OFF:
            tap_code(IME_CANCEL);
            if (record->event.pressed) {
                register_code(KC_LNG2);
            } else {
                unregister_code(KC_LNG2);
            }
            break;
    }

    return process_record_keymap(keycode, record);
}

__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) {
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef SUPER_TAB_ENABLE
    super_tab_cancel();
#endif

    return layer_state_set_keymap(state);
}

// SEE: https://docs.qmk.fm/#/squeezing_avr?id=magic-keycodes
uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}

// SEE: https://docs.qmk.fm/#/squeezing_avr?id=magic-keycodes
uint8_t mod_config(uint8_t mod) {
    return mod;
}
