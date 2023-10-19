#include "efumaxay.h"

enum HRC_STATE {
    HRC_STATE_NONE = 0,
    HRC_STATE_L_CTL_HELD = 1,
    HRC_STATE_L_ALT_HELD = 2,
    HRC_STATE_R_CTL_HELD = 4,
    HRC_STATE_R_ALT_HELD = 8,
};

static uint8_t hrcm_state = HRC_STATE_NONE;

bool process_home_row_combo(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HRC_L_CTL:
            if (record->event.pressed) {
                hrcm_state |= HRC_STATE_L_CTL_HELD;
            } else {
                hrcm_state &= ~HRC_STATE_L_CTL_HELD;
            }
            break;
        case HRC_L_ALT:
            if (record->event.pressed) {
                hrcm_state |= HRC_STATE_L_ALT_HELD;
            } else {
                hrcm_state &= ~HRC_STATE_L_ALT_HELD;
            }
            break;
        case HRC_R_CTL:
            record->keycode = HRC_L_CTL;
            if (record->event.pressed) {
                hrcm_state |= HRC_STATE_R_CTL_HELD;
            } else {
                hrcm_state &= ~HRC_STATE_R_CTL_HELD;
            }
            break;
        case HRC_R_ALT:
            record->keycode = HRC_L_ALT;
            if (record->event.pressed) {
                hrcm_state |= HRC_STATE_R_ALT_HELD;
            } else {
                hrcm_state &= ~HRC_STATE_R_ALT_HELD;
            }
            break;
        case KC_S:
            if (hrcm_state & HRC_STATE_L_CTL_HELD) {
                if (record->event.pressed) {
                    register_code(KC_LSFT);
                } else {
                    unregister_code(KC_LSFT);
                }
                return false;
            }
            break;
        case KC_D:
            if (hrcm_state & HRC_STATE_L_ALT_HELD) {
                if (record->event.pressed) {
                    register_code(KC_LSFT);
                } else {
                    unregister_code(KC_LSFT);
                }
                return false;
            }
            break;
        case KC_L:
            if (hrcm_state & HRC_STATE_R_CTL_HELD) {
                if (record->event.pressed) {
                    register_code(KC_LSFT);
                } else {
                    unregister_code(KC_LSFT);
                }
                return false;
            }
            break;
        case KC_K:
            if (hrcm_state & HRC_STATE_R_ALT_HELD) {
                if (record->event.pressed) {
                    register_code(KC_LSFT);
                } else {
                    unregister_code(KC_LSFT);
                }
                return false;
            }
            break;
        default:
            break;
    }
    return true;
}
