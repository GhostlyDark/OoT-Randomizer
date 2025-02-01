#ifndef DPAD_H
#define DPAD_H

#include "z64.h"

#include "gfx.h"
#include "dpad_paused.h"
#include "dpad_actions.h"
#include "options.h"
#include "buttons.h"
#include "fps.h"
#include "actor.h"
#include "debug.h"
#include "dungeon_info.h"

/* Functions */
typedef void(*playsfx_t) (u16 sfx, z64_xyzf_t *unk_00_, s8 unk_01_ , float *unk_02_, float *unk_03_, float *unk_04_);
#define z64_playsfx ((playsfx_t) 0x800C806C)

/* D-Pad SRAM locations & Button Mappings */
#define DPAD_CHILD_SET1_UP              (z64_file.dpad_item_slots[0x0])
#define DPAD_CHILD_SET1_RIGHT           (z64_file.dpad_item_slots[0x1])
#define DPAD_CHILD_SET1_DOWN            (z64_file.dpad_item_slots[0x2])
#define DPAD_CHILD_SET1_LEFT            (z64_file.dpad_item_slots[0x3])
#define DPAD_CHILD_SET2_UP              (z64_file.dpad_item_slots[0x4])
#define DPAD_CHILD_SET2_RIGHT           (z64_file.dpad_item_slots[0x5])
#define DPAD_CHILD_SET2_DOWN            (z64_file.dpad_item_slots[0x6])
#define DPAD_CHILD_SET2_LEFT            (z64_file.dpad_item_slots[0x7])
#define DPAD_ADULT_SET1_UP              (z64_file.dpad_item_slots[0x8])
#define DPAD_ADULT_SET1_RIGHT           (z64_file.dpad_item_slots[0x9])
#define DPAD_ADULT_SET1_DOWN            (z64_file.dpad_item_slots[0xA])
#define DPAD_ADULT_SET1_LEFT            (z64_file.dpad_item_slots[0xB])
#define DPAD_ADULT_SET2_UP              (z64_file.dpad_item_slots[0xC])
#define DPAD_ADULT_SET2_RIGHT           (z64_file.dpad_item_slots[0xD])
#define DPAD_ADULT_SET2_DOWN            (z64_file.dpad_item_slots[0xE])
#define DPAD_ADULT_SET2_LEFT            (z64_file.dpad_item_slots[0xF])

void handle_dpad();
void handle_restore_mask();
void run_default_options_setup();
void handle_dpad_ingame();
void draw_dpad();
void draw_name_panel(      z64_disp_buf_t* db);
void draw_settings_label(  z64_disp_buf_t* db);
void draw_swap_item_icons( z64_disp_buf_t* db, z64_item_t curr_item, z64_item_t next_item);
void draw_dpad_icons(      z64_disp_buf_t* db);
void interface_enable_swimming();

#endif