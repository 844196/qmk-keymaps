#pragma once

#include "quantum.h"
#include "transactions.h"

#ifdef TAP_DANCE_ENABLE
    #include "./features/cur_dance/cur_dance.h"
    #include "./features/ear_pods/ear_pods.h"
#endif

#ifdef OLED_ENABLE
    #include "./features/oled_logo/oled_logo.h"
#endif

#ifdef HOME_ROW_COMBO_ENABLE
    #include "./features/home_row_combo/home_row_combo.h"
#endif

#ifdef NUM_WORD_ENABLE
    #include "./features/num_word/num_word.h"
#endif

#ifdef SUPER_TAB_ENABLE
    #include "./features/super_tab/super_tab.h"
#endif

/**
 * 以下を事前にIMEへ設定
 *
 * - キャンセル 変換前入力中
 * - キャンセル サジェスト表示中
 * - キャンセル サジェスト選択中
 * - キャンセル 変換中
 */
#define IME_CANCEL KC_F21

#define FZ_1 LCAG(KC_1)
#define FZ_2 LCAG(KC_2)
#define FZ_3 LCAG(KC_3)
#define FZ_4 LCAG(KC_4)

enum userspace_custom_keycodes {
    MY_ESC = SAFE_RANGE,

    IME_ON,
    IME_OFF,

    #ifdef NUM_WORD_ENABLE
        NW_TOGG,
    #endif

    #ifdef SUPER_TAB_ENABLE
        ALT_TAB,
        CTL_TAB,
    #endif

    NEW_SAFE_RANGE
};

#ifdef HOME_ROW_COMBO_ENABLE
    #define HRC_L_CTL OSM(MOD_LCTL)
    #define HRC_L_SFT OSM(MOD_LSFT)
    #define HRC_L_ALT OSM(MOD_LALT)
    #define HRC_L_GUI OSM(MOD_LGUI)
    #define HRC_R_CTL OSM(MOD_RCTL)
    #define HRC_R_SFT OSM(MOD_LSFT)
    #define HRC_R_ALT OSM(MOD_RALT)
    #define HRC_R_GUI OSM(MOD_LGUI)
    #define HRC_L_CTL_SFT OSM(MOD_LCTL | MOD_LSFT)
    #define HRC_R_CTL_SFT OSM(MOD_LCTL | MOD_LSFT)
#endif
