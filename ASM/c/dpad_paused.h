#ifndef DPAD_PAUSED_H
#define DPAD_PAUSED_H

#include "z64.h"

/*typedef void(*draw_player_work_t)       (z64_game_t* game);
typedef void(*draw_equipment_image_t)   (z64_game_t* game, void* source, u32 width, u32 height);
typedef void(*draw_equipment_t)         (z64_game_t* game);*/

void handle_dpad_paused();
void handle_dpad_slots(  pad_t      pad_pressed);
void set_dpad_action(    pad_t      pad_pressed, z64_slot_t slot);
u8   run_set_dpad_action(z64_slot_t slot,        u8         button);
void handle_unequipping( pad_t      pad_pressed);
void handle_switch_mask( pad_t      pad_pressed);
u8   get_next_mask();
void update_trade_equips(u8         item,        u8         slot);
void handle_downgrading( pad_t      pad_pressed);
void swap_item(          z64_slot_t slot,        z64_item_t original, z64_item_t swap);
void unequip_gear(       u8         play);
void unequip_sword(      u8         play);
void unequip_shield();
void unequip_tunic();

/* Functions */
#define KaleidoScope_DrawPlayerWork       ((draw_player_work_t)     0x8038D388) // ROM: 0xBB5A08
#define KaleidoScope_DrawEquipmentImage   ((draw_equipment_image_t) 0x8038CF40) // ROM: 0xBB55C0
#define KaleidoScope_DrawEquipment        ((draw_equipment_t)       0x8038D52C) // ROM: 0xBB5BAC

#endif
