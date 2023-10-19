// Copyright 2022 Cole Smith <cole@boadsource.xyz>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "efumaxay.h"


/**
 * Layers
 */
enum layers {
    _BASE = 0,
    _ADJUST,
};

enum tap_dances {
    TD_E_OR_B,
    TD_M_OR_N,
};

#define MC_INVE TD(TD_E_OR_B)
#define MC_MAP TD(TD_M_OR_N)
#define MO_ADJ MO(_ADJUST)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                        XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        KC_TAB,   KC_Q,     KC_1,     KC_W,     MC_INVE,  KC_R,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        KC_LCTL,  KC_LALT,  KC_A,     KC_S,     KC_D,     KC_F,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        KC_LSFT,  KC_LSFT,  KC_X,     KC_C,     KC_V,     KC_B,     MC_MAP,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                      MO_ADJ,   KC_F2,    KC_LCTL,  KC_SPC,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
    ),

    [_ADJUST] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  QK_BOOT,                      _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
                                      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    ),

    // [_BLANK] = LAYOUT(
    //     _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
    //     _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
    //     _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
    //     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    //                                   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    // ),
};


/**
 * Tap-Hold Configurations
 */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MC_INVE:
        case MC_MAP:
            return TAPPING_TERM + 50;
        default:
            return TAPPING_TERM;
    }
}

/**
 * Tap dances
 */
tap_dance_action_t tap_dance_actions[] = {
    [TD_E_OR_B] = ACTION_TAP_DANCE_DOUBLE(KC_E, KC_B),
    [TD_M_OR_N] = ACTION_TAP_DANCE_DOUBLE(KC_M, KC_N),
};


/**
 * Display
 */
bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        return false;
    }

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_layer1_logo();
            break;
        case 1:
            oled_layer2_logo();
            break;
        case 2:
            oled_layer3_logo();
            break;
        case 3:
            oled_layer4_logo();
            break;
    }

    return false;
}
