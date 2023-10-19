#pragma once

#include "efumaxay.h"

#ifndef NUM_WORD_IDLE_TIMEOUT
    #define NUM_WORD_IDLE_TIMEOUT 5000
#endif

layer_state_t num_word_layer(void);
bool num_word_press_user(uint16_t keycode);

bool is_num_word_on(void);
void num_word_on(void);
void num_word_off(void);
void num_word_continue(void);

bool process_num_word(uint16_t keycode, keyrecord_t *record);
