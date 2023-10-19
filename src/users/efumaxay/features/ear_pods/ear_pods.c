#include "efumaxay.h"

static td_tap_t ear_pods_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void ear_pods_finished(tap_dance_state_t *state, void *user_data) {
    ear_pods_state.state = cur_dance(state);
    switch (ear_pods_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_MPLY);
            break;
        case TD_DOUBLE_TAP:
            register_code(KC_MNXT);
            break;
        // case TD_DOUBLE_HOLD:
        //     register_code(KC_MFFD);
        //     break;
        case TD_TRIPLE_TAP:
            register_code(KC_MPRV);
            break;
        // case TD_TRIPLE_HOLD:
        //     register_code(KC_MRWD);
        //     break;
        default:
            break;
    }
}

void ear_pods_reset(tap_dance_state_t *state, void *user_data) {
    switch (ear_pods_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_MPLY);
            break;
        case TD_DOUBLE_TAP:
            unregister_code(KC_MNXT);
            break;
        // case TD_DOUBLE_HOLD:
        //     unregister_code(KC_MFFD);
        //     break;
        case TD_TRIPLE_TAP:
            unregister_code(KC_MPRV);
            break;
        // case TD_TRIPLE_HOLD:
        //     unregister_code(KC_MRWD);
        //     break;
        default:
            break;
    }
    ear_pods_state.state = TD_NONE;
}
