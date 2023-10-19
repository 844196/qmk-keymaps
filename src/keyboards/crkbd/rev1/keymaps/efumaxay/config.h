/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#pragma once

#define MASTER_LEFT
#define SPLIT_TRANSACTION_IDS_USER RPC_SYNC_SHARED_STATE

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define QUICK_TAP_TERM 0
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#define MK_COMBINED
#define MOUSEKEY_INTERVAL 10
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 2
#define MOUSEKEY_WHEEL_DELAY 0
#define MOUSEKEY_WHEEL_INTERVAL MOUSEKEY_INTERVAL
#define MOUSEKEY_WHEEL_MAX_SPEED MOUSEKEY_MAX_SPEED
#define MOUSEKEY_WHEEL_TIME_TO_MAX MOUSEKEY_TIME_TO_MAX

#define EXTRA_EXTRA_LONG_COMBOS
#define COMBO_TERM 40
#define COMBO_TERM_PER_COMBO
#define COMBO_MUST_HOLD_MODS
#define COMBO_HOLD_TERM 50

#define ONESHOT_TIMEOUT 3000
#define CAPS_WORD_IDLE_TIMEOUT 3000
#define NUM_WORD_IDLE_TIMEOUT 3000

#ifdef RGB_MATRIX_ENABLE
	#define SPLIT_LAYER_STATE_ENABLE
	#define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif
