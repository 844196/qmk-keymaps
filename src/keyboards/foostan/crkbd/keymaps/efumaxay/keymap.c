#include QMK_KEYBOARD_H
#include "efumaxay.h"
#include "g/keymap_combo.h"

/**
 * Layers
 */
enum layers {
    _BASE = 0,
    _NUM,
    _SYM,
    _NAV,
    _ADJUST,
};

enum tap_dances {
    TD_SYM,
    TD_MEDIA_CONTROL,
};

enum keymap_custom_keycodes {
    MY_ARW = NEW_SAFE_RANGE,
    MY_DARW,
};

#define MO_NAV MO(_NAV)
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
                unregister_code(KC_BSPC); // Avoid BSPC spamming
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
        case MY_ARW:
            if (record->event.pressed) {
                SEND_STRING("->");
            }
            break;
        case MY_DARW:
            if (record->event.pressed) {
                SEND_STRING("=>");
            }
            break;
        default:
            break;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3_ex2(
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_NO,    KC_NO,    KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_MINS,
        MY_CTL,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_NO,    KC_NO,    KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
        CW_TOGG,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                         KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_EQL,
                                                MO_NAV,   LT_SYM,   KC_SPC,   KC_ENT,   LT_NUM,   MO_NAV
    ),

    [_NUM] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_NO,    KC_NO,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_DEL,
        GRV_CTL,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_NO,    KC_NO,    KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,
        KC_LSFT,  KC_F11,   KC_F12,   _______,  _______,  _______,                      _______,  _______,  KC_COMM,  KC_DOT,   KC_SLSH,  KC_EQL,
                                                _______,  _______,  _______,  _______,  _______,  _______
    ),

    [_SYM] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,   _______,  KC_BSPC,  CTL_C,    CTL_V,    KC_ENT,   KC_NO,    KC_NO,    _______,  MY_ARW,   MY_DARW,  KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_NO,    KC_NO,    KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_UNDS,
        KC_LSFT,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  KC_LCBR,  KC_RCBR,  KC_PIPE,
                                                _______,  KC_NO,    _______,  _______,  _______,  _______
    ),

    [_NAV] = LAYOUT_split_3x6_3_ex2(
        KC_ESC,   XXXXXXX,  KC_BSPC,  CTL_C,    CTL_V,    KC_ENT,   KC_NO,    KC_NO,    XXXXXXX,  CTL_TAB,  ALT_TAB,  XXXXXXX,  XXXXXXX,  KC_DEL,
        KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LSFT,  KC_LCTL,  _______,  KC_NO,    KC_NO,    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  XXXXXXX,  KC_ENT,
        KC_LSFT,  XXXXXXX,  XXXXXXX,  _______,  _______,  XXXXXXX,                      KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   XXXXXXX,  KC_LSFT,
                                                _______,  XXXXXXX,  XXXXXXX,  MY_PSCR,  XXXXXXX,  _______
    ),

    [_ADJUST] = LAYOUT_split_3x6_3_ex2(
        _______,  _______,  _______,  _______,  _______,  QK_BOOT,  KC_NO,    KC_NO,    QK_BOOT,  _______,  _______,  _______,  _______,  _______,
        _______,  KC_VOLD,  KC_VOLU,  KC_MUTE,  KC_MCTL,  _______,  KC_NO,    KC_NO,    _______,  FZ_1,     FZ_2,     FZ_3,     FZ_4,     _______,
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

        case KC_MCTL:
            return TAPPING_TERM + 100;

        default:
            return TAPPING_TERM;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GRV_CTL:
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
        case KC_MINS:
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
