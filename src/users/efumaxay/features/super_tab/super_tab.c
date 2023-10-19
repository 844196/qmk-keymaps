#include "efumaxay.h"

static bool _is_super_tab_active = false;

void super_tab_cancel(void) {
    if (_is_super_tab_active) {
        _is_super_tab_active = false;
        unregister_code(KC_LALT);
        unregister_code(KC_LCTL);
    }
}

bool process_super_tab(uint16_t keycode, keyrecord_t *record) {
    if (keycode != ALT_TAB && keycode != CTL_TAB) {
        return true;
    }

    if (record->event.pressed) {
        if (!_is_super_tab_active) {
            _is_super_tab_active = true;
            register_code(keycode == ALT_TAB ? KC_LALT : KC_LCTL);
        }

        register_code(KC_TAB);
    } else {
        unregister_code(KC_TAB);
    }

    return false;
}
