#ifndef DPAD_ACTIONS_H
#define DPAD_ACTIONS_H

#include "z64.h"
#include "buttons.h"

typedef void(*use_item_t)                   (z64_game_t* game, z64_link_t* link, u8  item);
typedef void(*update_bottle_item_t)         (z64_game_t* game, u8          item, u8  button);
typedef void(*update_bottle_held_t)         (z64_game_t* game, z64_link_t* link, s32 item, s32 item_action);
typedef s32(*get_environmental_hazard_t)    (z64_game_t* game);
typedef s32(*flags_get_switch_t)            (z64_game_t* game, s32 flag);

typedef enum {
    PLAYER_ENV_HAZARD_NONE,
    PLAYER_ENV_HAZARD_HOTROOM,
    PLAYER_ENV_HAZARD_UNDERWATER_FLOOR,
    PLAYER_ENV_HAZARD_SWIMMING,
    PLAYER_ENV_HAZARD_UNDERWATER_FREE
} z64_environment_hazard_t;

void change_sword(    z64_game_t* game, z64_link_t* link, u8 sword);
void change_shield(   z64_game_t* game, z64_link_t* link, u8 shield);
void change_tunic(    z64_game_t* game, z64_link_t* link, u8 tunic);
void change_boots(    z64_game_t* game, z64_link_t* link, u8 boots);
void change_equipment(z64_game_t* game, z64_link_t* link);

bool can_use_ocarina();
bool can_use_child_trade();
bool can_use_adult_trade();
bool can_use_items();
bool can_use_hookshot();
bool can_use_lens();
bool can_use_farores_wind();
bool is_semi_alpha(u8 alpha);

void  draw_dpad_actions(   z64_disp_buf_t* db,   u8          alpha);
void  run_equipment_action(z64_game_t*     game, z64_link_t* link,   u8  action);
void  draw_action(         z64_disp_buf_t* db,   z64_slot_t  action, s8  icon_x, s8  icon_y, s8 icon_big_x, s8 icon_big_y, u8 alpha);
void  draw_ammo(           z64_disp_buf_t* db,   u8          item,   u16 x,      u16 y,      u8 size,       s8 spacing,    u8 alpha, bool b_button);

void toggle_sword( z64_game_t* game, z64_link_t* link);
void toggle_shield(z64_game_t* game, z64_link_t* link);
void toggle_tunic( z64_game_t* game, z64_link_t* link);
void toggle_boots( z64_game_t* game, z64_link_t* link);
void swap_tunic(   z64_game_t* game, z64_link_t* link, u8 shift, u8 equip);
void swap_boots(   z64_game_t* game, z64_link_t* link, u8 shift, u8 equip);

void draw_sword_icon(      z64_disp_buf_t* db,                                     s8 icon_x, s8 icon_y,                                 u8 alpha);
void draw_shield_icon(     z64_disp_buf_t* db,                                     s8 icon_x, s8 icon_y,                                 u8 alpha);
void draw_tunic_icon(      z64_disp_buf_t* db,                                     s8 icon_x, s8 icon_y,                                 u8 alpha);
void draw_boots_icon(      z64_disp_buf_t* db,                                     s8 icon_x, s8 icon_y,                                 u8 alpha);
void draw_equipment_icon(  z64_disp_buf_t* db,                                     s8 icon_x, s8 icon_y, s8   icon_big_x, s8 icon_big_y, u8 alpha, u8 icon, bool has_item, bool is_equipped);
void draw_child_trade_icon(z64_disp_buf_t* db, z64_item_t item,                    s8 icon_x, s8 icon_y, s8   icon_big_x, s8 icon_big_y, u8 alpha);
void draw_adult_trade_icon(z64_disp_buf_t* db, z64_item_t item,                    s8 icon_x, s8 icon_y,                                 u8 alpha);
void draw_arrow_icon(      z64_disp_buf_t* db, z64_item_t item,   z64_slot_t slot, s8 icon_x, s8 icon_y, bool usability,                 u8 alpha);
void draw_item_icon(       z64_disp_buf_t* db, z64_item_t item,   z64_slot_t slot, s8 icon_x, s8 icon_y, bool usability,                 u8 alpha);
void draw_dpad_icon(       z64_disp_buf_t* db, sprite_t*  sprite, u8         icon, s8 x,      s8 y,      u8   size);

void                   player_update_bottle_item(  z64_game_t* game, z64_item_t              item, u8                button);
void                   update_c_button_bottle_item(z64_game_t* game, z64_item_t              item, z64_item_button_t button);
void                   player_process_item_buttons(z64_link_t* link, z64_game_t*             game);
bool                   player_item_is_in_use(      z64_link_t* link, z64_item_t              item);
z64_action_parameter_t player_item_to_item_action( z64_item_t  item);
bool                   player_item_is_item_action( z64_item_t  item,  z64_action_parameter_t item_action);
z64_item_t             player_get_item_on_button(  z64_game_t* game,  u8                     index);
z64_item_t             get_dpad_btn_item(          u8          button);
bool                   has_lens_on_dpad_button();

/* D-Pad */
#define CHECK_BTN_ALL(state, combo)         (((state) & (combo)) == (combo))
#define BTN_B                               0x4000
#define BTN_CLEFT                           0x0002
#define BTN_CDOWN                           0x0004
#define BTN_CRIGHT                          0x0001
#define BTN_DUP                             0x0800
#define BTN_DDOWN                           0x0400
#define BTN_DLEFT                           0x0200
#define BTN_DRIGHT                          0x0100
#define BLOCK_ITEMS                         (PLAYER_STATE1_RIDING | PLAYER_STATE1_CLIMBING | PLAYER_STATE1_SWIMMING)
#define BLOCK_ITEMS_BUT_SWIMMING            (PLAYER_STATE1_RIDING | PLAYER_STATE1_CLIMBING)
#define B_BTN_ITEM                          ((z64_file.button_status[0] == Z64_ITEM_NONE) ? Z64_ITEM_NONE : (z64_file.button_items[0] == Z64_ITEM_GIANTS_KNIFE) ? Z64_ITEM_BIGGORON_SWORD : z64_file.button_items[0])
#define C_BTN_ITEM(button)                  ((z64_file.button_status[(button) + 1] != BTN_DISABLED) ? z64_file.button_items[(button) + 1] : Z64_ITEM_NONE)
#define BLOCK_HOOKSHOT                      (((z64_link.state_flags_3 & (1 << 7))) && z64_game.bombchuBowlingStatus == 0 && z64_game.shootingGalleryStatus == 0)

/* D-Pad variables and checks */
#define z64_use_held_item                   (*(s32*)           0x803A9E74)
#define z64_held_item_button_is_held_down   (*(s32*)           0x803A9E78)
#define z64_dpad_lens_1                     (*(u16*)           0x80072D40)
#define z64_dpad_lens_2                     (*(u16*)           0x80072D4C)
#define z64_dpad_lens_3                     (*(u16*)           0x80072D58)
#define z64_throw_check_1                   (*(u8*)            0x8038B8B6)
#define z64_throw_check_2                   (*(u8*)            0x803955A2)
#define z64_throw_check_3                   (*(u8*)            0x8039AC2E)
#define z64_throw_check_4                   (*(u8*)            0x8039CDAE)

#define use_item_check                      (*(u16*)           0x8038CA3C)
#define underwater_item_check               (*(u16*)           0x8006E84C)

/* Functions */
#define Player_UseItem                      ((use_item_t)                 0x8038C9A0) // ROM: 0xBD19B0
#define Inventory_UpdateBottleItem          ((update_bottle_item_t)       0x80071B7C) // ROM: 0xAE7ADC
#define Player_UpdateBottleHeld             ((update_bottle_held_t)       0x80079848) // ROM: 0xAEF7A8
#define Player_GetEnvironmentalHazard       ((get_environmental_hazard_t) 0x80079DD0) // ROM: 0xAEFD30
#define Flags_GetSwitch                     ((flags_get_switch_t)         0x80020498) // ROM: 0xA963F8

#endif