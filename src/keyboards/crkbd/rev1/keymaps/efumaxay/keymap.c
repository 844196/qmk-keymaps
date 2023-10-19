/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "efumaxay.h"
#include "g/keymap_combo.h"
#include "arasaka.h"

/**
 * Layers
 */
enum layers {
    _BASE = 0,
    _NUM,
    _SYM,
    _MOUSE,
    _NAV,
    _ADJUST,
};

enum tap_dances {
    TD_SYM,
    TD_MEDIA_CONTROL,
};

#define LT_NAV LT(_NAV, KC_NO)
#define LT_SYM TD(TD_SYM)
#define LT_NUM LT(_NUM, KC_NO)
#define MY_CTL KC_RCTL
#define GRV_CTL MT(MOD_RCTL, KC_GRV)
#define MY_PSCR LGUI(LSFT(KC_S))
#define KC_MCTL TD(TD_MEDIA_CONTROL)
#define CTL_C LCTL(KC_C)
#define CTL_V LCTL(KC_V)

static bool is_my_ctrl_held = false;
static bool is_ctrl_c_active = false;
static deferred_token ctl_c_callback_token = INVALID_DEFERRED_TOKEN;

uint32_t ctl_c_callback(uint32_t trigger_time, void *cb_arg) {
    is_ctrl_c_active = false;
    return 0;
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_C:
            if (record->event.pressed) {
                is_ctrl_c_active = true;
                ctl_c_callback_token = defer_exec(150, ctl_c_callback, NULL);
            }
            break;
        case MY_CTL:
            if (record->event.pressed) {
                is_my_ctrl_held = true;
            } else {
                is_my_ctrl_held = false;
            }
            break;
        case LT_NUM:
            if (record->tap.count && record->event.pressed) {
                if (is_num_word_on()) {
                    num_word_off();
                } else {
                    num_word_on();
                }
                return false;
            }
            break;
        case LT_NAV:
            if (record->tap.count && record->event.pressed) {
                if (get_highest_layer(layer_state) == _MOUSE) {
                    layer_off(_MOUSE);
                } else {
                    layer_on(_MOUSE);
                }
            } else if (record->event.pressed) {
                layer_on(_NAV);
            } else {
                layer_off(_NAV);
            }
            return false;
        case KC_H:
            if (is_caps_word_on() && is_my_ctrl_held) {
                if (record->event.pressed) {
                    del_mods(MOD_MASK_CTRL);
                    register_code(KC_BSPC);
                } else {
                    unregister_code(KC_BSPC);
                }
                return false;
            }
            break;
        case KC_QUOT:
            if (is_caps_word_on()) {
                if (record->event.pressed) {
                    register_code16(KC_UNDS);
                } else {
                    unregister_code16(KC_UNDS);
                }
                return false;
            }
            break;
        default:
            break;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_MINS,
        MY_CTL,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                         KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
        CW_TOGG,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                         KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_EQL,
                                                LT_NAV,   LT_SYM,   KC_SPC,   KC_ENT,   LT_NUM,   LT_NAV
    ),

    [_NUM] = LAYOUT_split_3x6_3(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                        KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_DEL,
        GRV_CTL,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,
        KC_LSFT,  KC_F11,   KC_F12,   _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
                                                _______,  _______,  _______,  _______,  _______,  _______
    ),

    [_SYM] = LAYOUT_split_3x6_3(
        KC_ESC,   _______,  _______,  CTL_C,    CTL_V,    KC_ENT,                       _______,  _______,  _______,  KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                      KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_UNDS,
        KC_LSFT,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  KC_LCBR,  KC_RCBR,  KC_PIPE,
                                                _______,  KC_NO,    _______,  _______,  _______,  _______
    ),

    [_MOUSE] = LAYOUT_split_3x6_3(
        KC_ESC,   XXXXXXX,  KC_BTN4,  KC_MS_U,  KC_BTN5,  KC_ENT,                       XXXXXXX,  KC_BTN4,  KC_BTN5,  XXXXXXX,  XXXXXXX,  KC_DEL,
        KC_LCTL,  KC_BTN2,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_WH_U,                      KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  KC_BTN2,  KC_ENT,
        KC_LSFT,  KC_ACL0,  XXXXXXX,  CTL_C,    CTL_V,    KC_WH_D,                      KC_WH_L,  KC_WH_D,  KC_WH_U,  KC_WH_R,  XXXXXXX,  KC_LSFT,
                                                _______,  KC_BTN3,  KC_BTN1,  KC_BTN1,  KC_BTN3,  _______
    ),

    [_NAV] = LAYOUT_split_3x6_3(
        KC_ESC,   XXXXXXX,  XXXXXXX,  CTL_C,    CTL_V,    KC_ENT,                       XXXXXXX,  CTL_TAB,  ALT_TAB,  XXXXXXX,  XXXXXXX,  KC_DEL,
        KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LSFT,  KC_LCTL,  XXXXXXX,                      KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  XXXXXXX,  KC_ENT,
        KC_LSFT,  XXXXXXX,  XXXXXXX,  _______,  _______,  XXXXXXX,                      KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   XXXXXXX,  KC_LSFT,
                                                _______,  XXXXXXX,  XXXXXXX,  MY_PSCR,  XXXXXXX,  _______
    ),

    [_ADJUST] = LAYOUT_split_3x6_3(
        _______,  _______,  _______,  _______,  _______,  QK_BOOT,                      QK_BOOT,  _______,  _______,  _______,  _______,  _______,
        _______,  KC_VOLD,  KC_VOLU,  KC_MUTE,  KC_MCTL,  _______,                      _______,  FZ_1,     FZ_2,     FZ_3,     FZ_4,     _______,
        _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
                                                _______,  _______,  _______,  _______,  _______,  _______
    ),
};

layer_state_t layer_state_set_keymap(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NUM, _ADJUST);
}


/**
 * Tap-Hold Configurations
 */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GRV_CTL:
            return TAPPING_TERM - 20;

        case LT_SYM:
        case LT_NUM:
            return TAPPING_TERM - 75;

        case LT_NAV:
            return TAPPING_TERM + 25;

        case KC_MCTL:
            return TAPPING_TERM + 100;

        default:
            return TAPPING_TERM;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GRV_CTL:
        case LT_NAV:
            return true;

        case LT_SYM:
        case LT_NUM:
            // falseだと update_tri_layer_state() で_ADJUSTに切り替わるのが遅くなるため
            return true;

        default:
            return false;
    }
}


/**
 * Caps Word
 */
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_G:
        case KC_I ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to next key.
            return true;

        case KC_H:
            if (is_my_ctrl_held) {
                // process_record_keymap で処理させるため、ONのままパススルーさせる
            } else {
                add_weak_mods(MOD_BIT(KC_LSFT));
            }
            return true;

        case KC_1 ... KC_0:
        case MY_CTL:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        case KC_QUOT:
            return true; // process_record_keymap で処理させるため、ONのままパススルーさせる

        default:
            return false;
    }
}


/**
 * Num Word
 */
layer_state_t num_word_layer(void) {
    return _NUM;
}

bool num_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_1 ... KC_0:
            return true;

        case KC_DOT:
        case KC_MINS:
        case KC_UNDS:
            return true;

        case GRV_CTL:
        case KC_BSPC:
            return true;

        case LT_NUM:
            return true; // process_record_keymap で処理させるため、ONのままパススルーさせる

        default:
            return false;
    }
}


/**
 * Combos
 */
uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        case COMBO_ESC_BASE_L:
        case COMBO_ESC_BASE_R:
            return 30;

        default:
            return COMBO_TERM;
    }
}


/**
 * Key Overrides
 */
const key_override_t override_rctl_w = ko_make_with_layers(MOD_BIT(KC_RCTL), KC_W, LCTL(KC_BSPC), 1 << _BASE);
const key_override_t override_rctl_h_base = ko_make_with_layers(MOD_BIT(KC_RCTL), KC_H, KC_BSPC, 1 << _BASE);
const key_override_t override_rctl_h_num = ko_make_with_layers(MOD_BIT(KC_RCTL), KC_6, KC_BSPC, 1 << _NUM);

const key_override_t **key_overrides = (const key_override_t *[]){
    &override_rctl_w,
    &override_rctl_h_base,
    &override_rctl_h_num,
    NULL
};


/**
 * Tap dances
 */
// TD_SYM
static td_tap_t sym_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void sym_finished(tap_dance_state_t *state, void *user_data) {
    sym_state.state = cur_dance(state);
    switch (sym_state.state) {
        case TD_SINGLE_TAP:
            if (is_oneshot_layer_active()) {
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            } else {
                set_oneshot_layer(_SYM, ONESHOT_START);
                clear_oneshot_layer_state(ONESHOT_PRESSED);
            }
            break;
        case TD_SINGLE_HOLD:
            layer_on(_SYM);
            break;
        default:
            break;
    }
}

void sym_reset(tap_dance_state_t *state, void *user_data) {
    switch (sym_state.state) {
        case TD_SINGLE_HOLD:
            layer_off(_SYM);
            break;
        default:
            break;
    }
    sym_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_MEDIA_CONTROL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ear_pods_finished, ear_pods_reset),
    [TD_SYM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sym_finished, sym_reset),
};


/**
 * Init
 */
enum RPC_SHARED_STATE {
    RPC_SHARED_STATE_NONE = 0,
    RPC_SHARED_STATE_IS_CAPS_WORD_ON = 1,
    RPC_SHARED_STATE_IS_ONE_SHOT_MOD_ON = 2,
    RPC_SHARED_STATE_IS_CTRL_C_ACTIVE = 4,
};
static uint8_t rpc_shared_state = RPC_SHARED_STATE_NONE;

void rpc_sync_shared_state(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    memcpy(&rpc_shared_state, in_data, in_buflen);
}

void keyboard_post_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
#endif

    transaction_register_rpc(RPC_SYNC_SHARED_STATE, rpc_sync_shared_state);
}

void housekeeping_task_user(void) {
    if (!is_keyboard_master()) {
        return;
    }

    static uint32_t last_sync_shared_state = 0;
    if (timer_elapsed32(last_sync_shared_state) > 50) {
        if (is_caps_word_on()) {
            rpc_shared_state |= RPC_SHARED_STATE_IS_CAPS_WORD_ON;
        } else {
            rpc_shared_state &= ~RPC_SHARED_STATE_IS_CAPS_WORD_ON;
        }
        if (get_oneshot_mods()) {
            rpc_shared_state |= RPC_SHARED_STATE_IS_ONE_SHOT_MOD_ON;
        } else {
            rpc_shared_state &= ~RPC_SHARED_STATE_IS_ONE_SHOT_MOD_ON;
        }
        if (is_ctrl_c_active) {
            rpc_shared_state |= RPC_SHARED_STATE_IS_CTRL_C_ACTIVE;
        } else {
            rpc_shared_state &= ~RPC_SHARED_STATE_IS_CTRL_C_ACTIVE;
        }

        if (transaction_rpc_send(RPC_SYNC_SHARED_STATE, sizeof(rpc_shared_state), &rpc_shared_state)) {
            last_sync_shared_state = timer_read32();
        }
    }
}


/**
 * OLED
 */
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return is_keyboard_master() ? OLED_ROTATION_0 : OLED_ROTATION_270;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        if (rpc_shared_state & RPC_SHARED_STATE_IS_CAPS_WORD_ON) {
            oled_caps_word_logo();
            return false;
        }
        switch (get_highest_layer(layer_state)) {
            case _BASE:
                oled_layer1_logo();
                break;
            case _SYM:
                oled_layer2_logo();
                break;
            case _NUM:
                oled_layer3_logo();
                break;
            case _ADJUST:
                oled_layer4_logo();
                break;
        }
    } else {
        switch (get_highest_layer(layer_state)) {
            case _MOUSE:
            case _NAV:
                arasaka_draw();
                break;
            default:
                oled_clear();
                break;
        }
    }
    return false;
}
#endif


/**
 * RGB Matrix
 */
#ifdef RGB_MATRIX_ENABLE
#define INDICATOR_PRIMARY 6, 33
#define INDICATOR_SECONDARY 13, 40

void indicator_set_color(int master_idx, int non_master_idx, uint8_t r, uint8_t g, uint8_t b) {
    if (is_keyboard_master()) {
        rgb_matrix_set_color(master_idx, r, g, b);
    } else {
        rgb_matrix_set_color(non_master_idx, r, g, b);
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    rgb_matrix_set_color_all(RGB_OFF);

    switch (get_highest_layer(layer_state)) {
        case _SYM:
            indicator_set_color(INDICATOR_PRIMARY, RGB_CHARTREUSE);
            break;
        case _NUM:
            indicator_set_color(INDICATOR_PRIMARY, RGB_RED);
            break;
        case _NAV:
            indicator_set_color(INDICATOR_PRIMARY, RGB_CYAN);
            break;
        case _MOUSE:
            indicator_set_color(INDICATOR_PRIMARY, RGB_PURPLE);
            break;
        case _ADJUST:
            indicator_set_color(INDICATOR_PRIMARY, RGB_ORANGE);
            break;
        default:
            break;
    }

    if (rpc_shared_state & RPC_SHARED_STATE_IS_ONE_SHOT_MOD_ON) {
        indicator_set_color(INDICATOR_PRIMARY, RGB_BLUE);
    }

    if (rpc_shared_state & RPC_SHARED_STATE_IS_CAPS_WORD_ON) {
        indicator_set_color(INDICATOR_PRIMARY, RGB_WHITE);
    }

    if (rpc_shared_state & RPC_SHARED_STATE_IS_CTRL_C_ACTIVE) {
        indicator_set_color(INDICATOR_SECONDARY, RGB_PINK);
    }

    return true;
}
#endif
