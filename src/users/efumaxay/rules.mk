EXTRAKEY_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes

# SEE: https://zenn.dev/koron/articles/98324ab760e83a
LTO_ENABLE = yes
COMMAND_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
MUSIC_ENABLE = no

SRC += efumaxay.c

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += $(USER_PATH)/features/cur_dance/cur_dance.c
	SRC += $(USER_PATH)/features/ear_pods/ear_pods.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += $(USER_PATH)/features/oled_logo/oled_logo.c
endif

ifeq ($(strip $(COMBO_ENABLE)), yes)
	ifeq ($(strip $(HOME_ROW_COMBO_ENABLE)), yes)
		SRC += $(USER_PATH)/features/home_row_combo/home_row_combo.c
		OPT_DEFS += -DHOME_ROW_COMBO_ENABLE
	endif
endif

ifeq ($(strip $(NUM_WORD_ENABLE)), yes)
	SRC += $(USER_PATH)/features/num_word/num_word.c
	OPT_DEFS += -DNUM_WORD_ENABLE
endif

ifeq ($(strip $(SUPER_TAB_ENABLE)), yes)
	SRC += $(USER_PATH)/features/super_tab/super_tab.c
	OPT_DEFS += -DSUPER_TAB_ENABLE
endif
