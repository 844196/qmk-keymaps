#include "efumaxay.h"

__attribute__((weak)) layer_state_t num_word_layer(void) {
    return 0;
}

__attribute__((weak)) bool num_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_1 ... KC_0:
            return true;

        case KC_DOT:
        case KC_MINS:
        case KC_UNDS:
            return true;

        default:
            return false;
    }
}

static bool _is_num_word_on = false;

static deferred_token num_word_timeout_callback_token = INVALID_DEFERRED_TOKEN;

uint32_t num_word_timeout_callback(uint32_t trigger_time, void *cb_arg) {
    _is_num_word_on = false;
    layer_off(num_word_layer());
    return 0;
}

bool is_num_word_on(void) {
    return _is_num_word_on;
}

void num_word_on(void) {
    _is_num_word_on = true;
    layer_on(num_word_layer());
    num_word_timeout_callback_token = defer_exec(NUM_WORD_IDLE_TIMEOUT, num_word_timeout_callback, NULL);
}

void num_word_off(void) {
    _is_num_word_on = false;
    layer_off(num_word_layer());
    cancel_deferred_exec(num_word_timeout_callback_token);
}

void num_word_continue(void) {
    extend_deferred_exec(num_word_timeout_callback_token, NUM_WORD_IDLE_TIMEOUT);
}

bool process_num_word(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    if (keycode == NW_TOGG) {
        if (_is_num_word_on) {
            num_word_off();
        } else {
            num_word_on();
        }
        return true;
    }

    if (_is_num_word_on) {
        if (num_word_press_user(keycode)) {
            num_word_continue();
        } else {
            num_word_off();
        }
    }

    return true;
}
