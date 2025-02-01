#ifndef BUTTONS_H
#define BUTTONS_H

#include "z64.h"

void handle_l_button();
void handle_l_button_paused();
void toggle_options_menu();
void toggle_minimap();
u16 get_scale_value(u8 scale);
void set_scale_values(u8 option, u8 button, s8 icon_size, s8 c_size);
void handle_button_scaling();
void handle_layout();
void reset_layout();
void set_b_button();
void handle_rupee_drain();
void handle_weaker_swords();
void handle_abilities();
void handle_abilities_tunic_colors();
void handle_power_crouch_stab_fix();
void handle_infinite();
void interface_raise_button_alphas(       z64_game_t* game,         u8 rising_alpha);
void interface_dim_button_alphas(         z64_game_t* game,         u8 dimming_alpha, u8 rising_alpha);
void interface_Update_hud_alphas(         z64_game_t* game,         u8 dimming_alpha);
void interface_change_hud_visibility_mode(u16 hud_visibility_mode);

/* Extra Ability Tunic Colors */
#define TUNIC_KOKIRI_R                  (*(u8*)            0x800F7AD8)
#define TUNIC_KOKIRI_G                  (*(u8*)            0x800F7AD9)
#define TUNIC_KOKIRI_B                  (*(u8*)            0x800F7ADA)
#define TUNIC_GORON_R                   (*(u8*)            0x800F7ADB)
#define TUNIC_GORON_G                   (*(u8*)            0x800F7ADC)
#define TUNIC_GORON_B                   (*(u8*)            0x800F7ADD)
#define TUNIC_ZORA_R                    (*(u8*)            0x800F7ADE)
#define TUNIC_ZORA_G                    (*(u8*)            0x800F7ADF)
#define TUNIC_ZORA_B                    (*(u8*)            0x800F7AE0)
#define TUNIC_UNUSED_R                  (*(u8*)            0x800F7AE1)
#define TUNIC_UNUSED_G                  (*(u8*)            0x800F7AE2)
#define TUNIC_UNUSED_B                  (*(u8*)            0x800F7AE3)

/* DRAM addresses & data for HUD */
#define z64_b_button_label_x            (*(u16*)           0x801C7C3A)
#define z64_b_button_label_y            (*(u16*)           0x801C7C3E)
#define z64_c_left_x_set_item           (*(u16*)           0x8039EAF8)
#define z64_c_left_y_set_item           (*(u16*)           0x8039EB00)
#define z64_c_down_x_set_item           (*(u16*)           0x8039EAFA)
#define z64_c_down_y_set_item           (*(u16*)           0x8039EB02)
#define z64_c_right_x_set_item          (*(u16*)           0x8039EAFC)
#define z64_c_right_y_set_item          (*(u16*)           0x8039EB04)

#endif
