#include "buttons.h"

extern colorRGB8_t CFG_TUNIC_MAGICIAN;
extern colorRGB8_t CFG_TUNIC_GUARDIAN;
extern colorRGB8_t CFG_TUNIC_HERO;
extern colorRGB8_t CFG_TUNIC_NONE;
extern colorRGB8_t CFG_TUNIC_SHADOW;

extern u8  compare_frames;
extern u16 play_sfx;
extern u16 dpad_alpha;

static u16* button_alphas[] = { &z64_game.alpha_channels.b_button, &z64_game.alpha_channels.cl_button, &z64_game.alpha_channels.cd_button, &z64_game.alpha_channels.cr_button, &z64_game.alpha_channels.a_button };

u8 block_r            = false;
u8 block_z            = false;
u8 pressed_r          = false;
u8 pressed_z          = false;
u8 pressed_stick      = false;
u8 pressed_dpad       = false;
u8 timer_holding_l    = 0;

u8 rupee_drain_frames = 0;
u8 rupee_drain_secs   = 0;
u8 restore_frames     = 0;
u8 restore_secs       = 0;
u8 magic_frames       = 0;
u8 magic_secs         = 0;
u8 restore_health     = 0;

s8 last_interface     = -1;

u8 checked_tunics     = 0;
colorRGB8_t tunic_kokiri;
colorRGB8_t tunic_goron;
colorRGB8_t tunic_zora;

void handle_l_button() {
    if (z64_game.pause_ctxt.state != PAUSE_STATE_OFF)
        return;
    if (!OPTION_ACTIVE(1, SAVE_30_FPS, CFG_DEFAULT_30_FPS) && !OPTION_VALUE(1, 2, SAVE_DPAD, CFG_DEFAULT_DPAD) && !OPTION_ACTIVE(2, SAVE_EXTRA_ABILITIES, CFG_DEFAULT_EXTRA_ABILITIES))
        return;
    
    if (OPTION_VALUE(1, 2, SAVE_DPAD, CFG_DEFAULT_DPAD)) {
        if (z64_game.common.input[0].raw.pad.r)
            pressed_r = true;
        if (z64_game.common.input[0].raw.pad.du || z64_game.common.input[0].raw.pad.dr || z64_game.common.input[0].raw.pad.dd || z64_game.common.input[0].raw.pad.dl)
            pressed_dpad = true;
    }
    else pressed_r = pressed_dpad = false;
    if (OPTION_ACTIVE(1, SAVE_30_FPS, CFG_DEFAULT_30_FPS)) {
        if (z64_game.common.input[0].raw.pad.z)
            pressed_z = true;
    }
    else pressed_z = false;
    if (OPTION_ACTIVE(2, SAVE_EXTRA_ABILITIES, CFG_DEFAULT_EXTRA_ABILITIES)) {
        if (z64_game.common.input[0].raw.x != 0 || z64_game.common.input[0].raw.y != 0)
            pressed_stick = true;
    }
    else pressed_stick = false;
    
    if (z64_game.common.input[0].pad_released.l)
        if (!pressed_r && !pressed_z && !pressed_stick && !pressed_dpad && timer_holding_l != 30 / fps_limit)
            toggle_minimap();
    if (!z64_game.common.input[0].raw.pad.l)
        pressed_r = pressed_z = pressed_stick = pressed_dpad = false;
    
    if (z64_game.common.input[0].pad_pressed.l) {
        if (OPTION_VALUE(1, 2, SAVE_DPAD, CFG_DEFAULT_DPAD))
            if (!z64_game.common.input[0].raw.pad.r)
                block_r = true;
        if (OPTION_ACTIVE(1, SAVE_30_FPS, CFG_DEFAULT_30_FPS))
            if (!z64_game.common.input[0].raw.pad.z)
                block_z = true;
    }
    
    if (z64_game.common.input[0].raw.pad.l && timer_holding_l < 30 / fps_limit)
        timer_holding_l++;
    if (!z64_game.common.input[0].raw.pad.l)
        block_r = block_z = timer_holding_l = false;
    
    if (block_r)
        z64_game.common.input[0].raw.pad.r = z64_game.common.input[0].pad_pressed.r = 0;
    if (block_z)
        z64_game.common.input[0].raw.pad.z = z64_game.common.input[0].pad_pressed.z = 0;
    
    z64_game.common.input[0].pad_pressed.l = false;
}

void handle_l_button_paused() {
    if (z64_game.pause_ctxt.state != PAUSE_STATE_MAIN || CFG_OPTIONS_MENU == 0)
        return;
    
    if (OPTION_VALUE(1, 2, SAVE_DPAD, CFG_DEFAULT_DPAD)) {
        if (z64_game.common.input[0].raw.pad.r)
            pressed_r = true;
    }
    else pressed_r = 0;
    if (OPTION_ACTIVE(1, SAVE_30_FPS, CFG_DEFAULT_30_FPS)) {
        if (z64_game.common.input[0].raw.pad.z)
            pressed_z = true;
    }
    else pressed_z = false;
    
    if (z64_game.common.input[0].pad_released.l)
        if (!pressed_r && !pressed_r && !pressed_z && timer_holding_l != 30 / fps_limit)
            toggle_options_menu();
    if (!z64_game.common.input[0].raw.pad.l)
        pressed_r = pressed_z = false;
    
    if (z64_game.common.input[0].pad_pressed.l) {
        if (OPTION_VALUE(1, 2, SAVE_DPAD, CFG_DEFAULT_DPAD))
            if (!z64_game.common.input[0].raw.pad.r)
                block_r = true;
        if (OPTION_ACTIVE(1, SAVE_30_FPS, CFG_DEFAULT_30_FPS))
            if (!z64_game.common.input[0].raw.pad.z)
                block_z = true;
    }
    
    if (z64_game.common.input[0].raw.pad.l && timer_holding_l < 30 / fps_limit)
        timer_holding_l++;
    if (!z64_game.common.input[0].raw.pad.l)
        block_r = block_z = timer_holding_l = false;
    
    if (block_r)
        z64_game.common.input[0].raw.pad.r = z64_game.common.input[0].pad_pressed.r = 0;
    if (block_z)
        z64_game.common.input[0].raw.pad.z = z64_game.common.input[0].pad_pressed.z = 0;
    
    z64_game.common.input[0].pad_pressed.l = false;
}

void toggle_options_menu() {
    play_sfx = 0x4813;
    if (z64_game.pause_ctxt.debugState == 0)
        z64_game.pause_ctxt.debugState = 3;
    else {
        z64_game.pause_ctxt.debugState = 0;
        play_sfx = 0x4814;
    }
}

void toggle_minimap() {
    if ( (z64_game.scene_index >= 0x00 && z64_game.scene_index <= 0x09 ) || (z64_game.scene_index >= 0x51 && z64_game.scene_index <= 0x64) ) {
        z64_gameinfo.minimap_disabled ^= 1;
        play_sfx = z64_gameinfo.minimap_disabled ? 0x4813 : 0x4814;
    }
}

u16 get_scale_value(u8 scale) {
    switch (scale) {
        case 31: return 525;
        case 30: return 550;
        case 29: return 575;
        case 28: return 605;
        case 27: return 620;
        case 26: return 640;
        case 25: return 660;
        case 24: return 680;
        case 23: return 705;
        case 22: return 735;
        case 21: return 770;
        case 20: return 810;
        case 19: return 860;
        case 18: return 910;
        case 17: return 960;
        case 16: return 1020;
        case 15: return 1090;
        case 14: return 1175;
        case 13: return 1270;
        case 12: return 1370;
        case 11: return 1480;
        case 10: return 1620;
        case 9:  return 1780;
        default: return 550;
    }
}

void set_scale_values(u8 option, u8 button, s8 icon_size, s8 c_size) {
    switch (option) {
        case 1:
            z64_gameinfo.item_button_space[button] = 28 + c_size;
            break;
        
        case 2:
            z64_gameinfo.item_button_space[button] = 27 + c_size;
            break;
        
        case 3:
            z64_gameinfo.item_button_space[button] = 25 + c_size;
            break;
        
        case 4:
            z64_gameinfo.item_button_space[button] = 23 + c_size;
            break;
        
        case 5:
            z64_gameinfo.item_button_space[button] = 21 + c_size;
            break;
        
        case 6:
            z64_gameinfo.item_button_space[button] = 19 + c_size;
            break;
        
        case 7:
            z64_gameinfo.item_button_space[button] = 17 + c_size;
            break;
    }
        
    z64_gameinfo.item_icon_space[button] = z64_gameinfo.item_button_space[button] + icon_size;
    z64_gameinfo.item_button_dd[button]  = get_scale_value(z64_gameinfo.item_button_space[button]);
    z64_gameinfo.item_icon_dd[button]    = get_scale_value(z64_gameinfo.item_icon_space[button]);
}

void handle_button_scaling() {
    if (OPTION_ACTIVE(1, SAVE_A_BUTTON_SCALE       > 0, CFG_DEFAULT_A_BUTTON_SCALE       > 0))   { A_BUTTON_SCALE = A_BUTTON_TEXT_SCALE = 0x3F80 - 0x40 * CFG_OPTIONS_MENU >= 1 ? SAVE_A_BUTTON_SCALE : CFG_DEFAULT_A_BUTTON_SCALE; }
    if (OPTION_ACTIVE(1, SAVE_B_BUTTON_SCALE       > 0, CFG_DEFAULT_B_BUTTON_SCALE       > 0))   { set_scale_values(CFG_OPTIONS_MENU >= 1 ? SAVE_B_BUTTON_SCALE       : CFG_DEFAULT_B_BUTTON_SCALE,       0,  1,  0); }
    if (OPTION_ACTIVE(1, SAVE_C_LEFT_BUTTON_SCALE  > 0, CFG_DEFAULT_C_LEFT_BUTTON_SCALE  > 0))   { set_scale_values(CFG_OPTIONS_MENU >= 1 ? SAVE_C_LEFT_BUTTON_SCALE  : CFG_DEFAULT_C_LEFT_BUTTON_SCALE,  1, -3, -2); }
    if (OPTION_ACTIVE(1, SAVE_C_DOWN_BUTTON_SCALE  > 0, CFG_DEFAULT_C_DOWN_BUTTON_SCALE  > 0))   { set_scale_values(CFG_OPTIONS_MENU >= 1 ? SAVE_C_DOWN_BUTTON_SCALE  : CFG_DEFAULT_C_LEFT_BUTTON_SCALE,  2, -3, -2); }
    if (OPTION_ACTIVE(1, SAVE_C_RIGHT_BUTTON_SCALE > 0, CFG_DEFAULT_C_RIGHT_BUTTON_SCALE > 0))   { set_scale_values(CFG_OPTIONS_MENU >= 1 ? SAVE_C_RIGHT_BUTTON_SCALE : CFG_DEFAULT_C_RIGHT_BUTTON_SCALE, 3, -3, -2); }
}

void handle_layout() {
    if (OPTION_VALUE(1, 0, SAVE_HUD_LAYOUT, CFG_DEFAULT_HUD_LAYOUT) && OPTION_VALUE(1, 0, SAVE_B_BUTTON_SCALE,      CFG_DEFAULT_B_BUTTON_SCALE)      && OPTION_VALUE(1, 0, SAVE_C_LEFT_BUTTON_SCALE,  CFG_DEFAULT_C_LEFT_BUTTON_SCALE) \
                                                                    && OPTION_VALUE(1, 0, SAVE_C_DOWN_BUTTON_SCALE, CFG_DEFAULT_C_DOWN_BUTTON_SCALE) && OPTION_VALUE(1, 0, SAVE_C_RIGHT_BUTTON_SCALE, CFG_DEFAULT_C_RIGHT_BUTTON_SCALE))
        return;
    
    if (z64_game.pause_ctxt.state == PAUSE_STATE_MAIN && OPTION_ACTIVE(1, SAVE_HUD_LAYOUT > 0, CFG_DEFAULT_HUD_LAYOUT > 0)) {
        if (OPTION_VALUE(1, 3, SAVE_HUD_LAYOUT, CFG_DEFAULT_HUD_LAYOUT)) { // Nintendo
            z64_c_left_x_set_item  = 0x343 + (0x208 * CFG_WS);
            z64_c_down_x_set_item  = 0x4FB + (0x208 * CFG_WS);
            z64_c_right_x_set_item = 0x1D1 + (0x208 * CFG_WS);
            z64_c_left_y_set_item  = 0x44C; z64_c_down_y_set_item = 0x492; z64_c_right_y_set_item = 0x352;
        }
        else if (OPTION_VALUE(1, 4, SAVE_HUD_LAYOUT, CFG_DEFAULT_HUD_LAYOUT)) { // Modern
            z64_c_left_x_set_item  = 0x217 + (0x208 * CFG_WS);
            z64_c_down_x_set_item  = 0x4FB + (0x208 * CFG_WS);
            z64_c_right_x_set_item = 0x2FD + (0x208 * CFG_WS);
            z64_c_left_y_set_item  = 0x352; z64_c_down_y_set_item = 0x492; z64_c_right_y_set_item = 0x44C;
        }
        else if (OPTION_VALUE(1, 5, SAVE_HUD_LAYOUT, CFG_DEFAULT_HUD_LAYOUT)) { // GameCube (Original)
            z64_c_left_x_set_item  = 0x3C0 + (0x208 * CFG_WS);
            z64_c_down_x_set_item  = 0x4FB + (0x208 * CFG_WS);
            z64_c_right_x_set_item = 0x4FE + (0x208 * CFG_WS);
            z64_c_left_y_set_item  = 0x4C9; z64_c_down_y_set_item = 0x492; z64_c_right_y_set_item = 0x314;
        }
        else if (OPTION_VALUE(1, 6, SAVE_HUD_LAYOUT, CFG_DEFAULT_HUD_LAYOUT)) { // GameCube (Modern)
            z64_c_left_x_set_item  = 0x544 + (0x208 * CFG_WS);
            z64_c_down_x_set_item  = 0x4FB + (0x208 * CFG_WS);
            z64_c_right_x_set_item = 0x37A + (0x208 * CFG_WS);
            z64_c_left_y_set_item = 0x314; z64_c_down_y_set_item = 0x492; z64_c_right_y_set_item = 0x4C9;
        }
    }
    
    if (CAN_DRAW_HUD && ( (!CFG_WS && z64_gameinfo.a_button_x == 186) || (CFG_WS && z64_gameinfo.a_button_x == 290) ) & z64_gameinfo.a_button_y == 9 && z64_gameinfo.item_button_y[0] == 0x11 && z64_gameinfo.item_button_y[1] == 0x12 && z64_gameinfo.item_button_y[2] == 0x22 && z64_gameinfo.item_button_y[3] == 0x12 && z64_gameinfo.c_up_button_y == 0x10) {
        u16 a_x = 0, a_y = 0, b_x = 0, b_y = 0, c_left_x = 0, c_left_y = 0, c_down_x = 0, c_down_y = 0, c_right_x = 0, c_right_y = 0, c_up_x = 0, c_up_y = 0;
        
        if (OPTION_VALUE(1, 1, SAVE_HUD_LAYOUT, CFG_DEFAULT_HUD_LAYOUT)) { // Majora's Mask
            a_x       = 4;   // 186 -> 190
            a_y       = 14;  // 9   -> 23
            b_x       = 7;   // 160 -> 167
        }
        else if (OPTION_VALUE(1, 2, SAVE_HUD_LAYOUT, CFG_DEFAULT_HUD_LAYOUT)) { // Inverted A and B
            a_x       = -34; // 186 -> 152
            b_x       = 34;  // 160 -> 194
        }
        else if (OPTION_VALUE(1, 3, SAVE_HUD_LAYOUT, CFG_DEFAULT_HUD_LAYOUT)) { // Nintendo
            a_x       = 70;  // 186 -> 256
            a_y       = 23;  // 9   -> 32
            b_x       = 80;  // 160 -> 240
            b_y       = 45;  // 11  -> 56
            c_left_x  = 14;  // 227 -> 241
            c_left_y  = 0;   // 18  -> 18
            c_down_x  = 30;  // 249 -> 279
            c_down_y  = -20; // 34  -> 14
            c_right_x = -54; // 271 -> 217
            c_right_y = 20;  // 18  -> 38
            c_up_x    = 10;  // 254 -> 264
            c_up_y    = -10; // 16  -> 6
        }
        else if (OPTION_VALUE(1, 4, SAVE_HUD_LAYOUT, CFG_DEFAULT_HUD_LAYOUT)) { // Modern
            a_x       = 46;  // 186 -> 234
            a_y       = 45;  // 9   -> 54
            b_x       = 104; // 160 -> 264
            b_y       = 23;  // 11  -> 33
            c_left_x  = -10; // 227 -> 217
            c_left_y  = 20;  // 18  -> 38
            c_down_x  = 30;  // 249 -> 279        
            c_down_y  = -20; // 34  -> 14        
            c_right_x = -30; // 271 -> 241
            c_right_y = 0;   // 18  -> 18
            c_up_x    = 10;  // 254 -> 264        
            c_up_y    = -10; // 16  -> 6        
        }
        else if (OPTION_VALUE(1, 5, SAVE_HUD_LAYOUT, CFG_DEFAULT_HUD_LAYOUT)) { // GameCube (Original)
            a_x       = 55;  // 186 -> 241
            a_y       = 20;  // 9   -> 29
            b_x       = 65;  // 160 -> 225
            b_y       = 40;  // 11  -> 51
            c_left_x  = 24;  // 227 -> 251
            c_left_y  = -10; // 18  -> 8
            c_down_x  = 30;  // 249 -> 279
            c_down_y  = -20; // 34  -> 14
            c_right_x = 11;  // 271 -> 282
            c_right_y = 25;  // 18  -> 43
            c_up_x    = -20; // 254 -> 234
        }
        else if (OPTION_VALUE(1, 6, SAVE_HUD_LAYOUT, CFG_DEFAULT_HUD_LAYOUT)) { // GameCube (Modern)
            a_x       = 55;  // 186 -> 241
            a_y       = 20;  // 9   -> 29
            b_x       = 65;  // 160 -> 225
            b_y       = 40;  // 11  -> 51
            c_left_x  = 55;  // 227 -> 282
            c_left_y  = 25;  // 18  -> 43
            c_down_x  = 30;  // 249 -> 279
            c_down_y  = -20; // 34  -> 14
            c_right_x = -20; // 271 -> 251
            c_right_y = -10; // 18  -> 8
            c_up_x    = -20; // 254 -> 234
        }
        
        if (OPTION_ACTIVE(1, SAVE_B_BUTTON_SCALE > 0, CFG_DEFAULT_B_BUTTON_SCALE > 0)) {
            u8 val = CFG_OPTIONS_MENU >= 1 ? SAVE_B_BUTTON_SCALE : CFG_DEFAULT_B_BUTTON_SCALE * 0.5;
            b_x   += val;
            b_y   += val;
            z64_b_button_label_x -= val / 2;
            z64_b_button_label_y -= val / 1.3;
        }
        if (OPTION_ACTIVE(1, SAVE_C_LEFT_BUTTON_SCALE > 0, CFG_DEFAULT_C_LEFT_BUTTON_SCALE > 0)) {
            u8 val    = CFG_OPTIONS_MENU >= 1 ? SAVE_C_LEFT_BUTTON_SCALE : CFG_DEFAULT_C_LEFT_BUTTON_SCALE * 0.5;
            c_left_x += val;
            c_left_y += val;
        }
        if (OPTION_ACTIVE(1, SAVE_C_DOWN_BUTTON_SCALE > 0, CFG_DEFAULT_C_DOWN_BUTTON_SCALE > 0)) {
            u8 val    = CFG_OPTIONS_MENU >= 1 ? SAVE_C_DOWN_BUTTON_SCALE : CFG_DEFAULT_C_DOWN_BUTTON_SCALE * 0.5;
            c_down_x += val;
            c_down_y += val;
        }
        if (OPTION_ACTIVE(1, SAVE_C_RIGHT_BUTTON_SCALE > 0, CFG_DEFAULT_C_RIGHT_BUTTON_SCALE > 0)) {
            u8 val     = CFG_OPTIONS_MENU >= 1 ? SAVE_C_RIGHT_BUTTON_SCALE : CFG_DEFAULT_C_RIGHT_BUTTON_SCALE * 0.5;
            c_right_x += val;
            c_right_y += val;
        }
    
        z64_gameinfo.a_button_x       += a_x;       z64_gameinfo.a_button_y       += a_y;       z64_gameinfo.a_button_icon_x += a_x;       z64_gameinfo.a_button_icon_y += a_y;
        z64_gameinfo.item_button_x[0] += b_x;       z64_gameinfo.item_button_y[0] += b_y;       z64_gameinfo.item_icon_x[0]  += b_x;       z64_gameinfo.item_icon_y[0]  += b_y;       z64_gameinfo.item_ammo_x[0] += b_x;       z64_gameinfo.item_ammo_y[0] += b_y; z64_b_button_label_x += b_x; z64_b_button_label_y += b_y;
        z64_gameinfo.item_button_x[1] += c_left_x;  z64_gameinfo.item_button_y[1] += c_left_y;  z64_gameinfo.item_icon_x[1]  += c_left_x;  z64_gameinfo.item_icon_y[1]  += c_left_y;  z64_gameinfo.item_ammo_x[1] += c_left_x;  z64_gameinfo.item_ammo_y[1] += c_left_y;
        z64_gameinfo.item_button_x[2] += c_down_x;  z64_gameinfo.item_button_y[2] += c_down_y;  z64_gameinfo.item_icon_x[2]  += c_down_x;  z64_gameinfo.item_icon_y[2]  += c_down_y;  z64_gameinfo.item_ammo_x[2] += c_down_x;  z64_gameinfo.item_ammo_y[2] += c_down_y;
        z64_gameinfo.item_button_x[3] += c_right_x; z64_gameinfo.item_button_y[3] += c_right_y; z64_gameinfo.item_icon_x[3]  += c_right_x; z64_gameinfo.item_icon_y[3]  += c_right_y; z64_gameinfo.item_ammo_x[3] += c_right_x; z64_gameinfo.item_ammo_y[3] += c_right_y;
        z64_gameinfo.c_up_button_x    += c_up_x;    z64_gameinfo.c_up_button_y    += c_up_y;    z64_gameinfo.c_up_icon_x     += c_up_x;    z64_gameinfo.c_up_icon_y     += c_up_y;
    }
}

void reset_layout() {
    A_BUTTON_SCALE = A_BUTTON_TEXT_SCALE = 0x3F80;
    z64_gameinfo.item_button_dd[0]    = 575;
    z64_gameinfo.item_icon_dd[0]      = 550;
    z64_gameinfo.item_button_space[0] = 29;
    z64_gameinfo.item_icon_space[0]   = 30;
    z64_gameinfo.item_button_dd[1]    = z64_gameinfo.item_button_dd[2]    = z64_gameinfo.item_button_dd[3]    = 620;
    z64_gameinfo.item_icon_dd[1]      = z64_gameinfo.item_icon_dd[2]      = z64_gameinfo.item_icon_dd[3]      = 680;
    z64_gameinfo.item_button_space[1] = z64_gameinfo.item_button_space[2] = z64_gameinfo.item_button_space[3] = 27;
    z64_gameinfo.item_icon_space[1]   = z64_gameinfo.item_icon_space[2]   = z64_gameinfo.item_icon_space[3]   = 24;
    
    z64_gameinfo.a_button_y           = z64_gameinfo.a_button_icon_y = 0x9;
    z64_gameinfo.item_button_y[0]     = z64_gameinfo.item_icon_y[0]  = 0x11;
    z64_gameinfo.item_ammo_y[0]       = z64_gameinfo.item_ammo_y[1]  = z64_gameinfo.item_ammo_y[3] = 0x23;
    z64_b_button_label_y              = 0x16;
    z64_gameinfo.item_button_y[1]     = z64_gameinfo.item_icon_y[1]  = 0x12;
    z64_gameinfo.item_button_y[2]     = z64_gameinfo.item_icon_y[2]  = 0x22;
    z64_gameinfo.item_ammo_y[2]       = 0x33;
    z64_gameinfo.item_button_y[3]     = z64_gameinfo.item_icon_y[3]  = 0x12;
    z64_gameinfo.c_up_button_y        = 0x10;
    z64_gameinfo.c_up_icon_y          = 0x14;
    
    z64_gameinfo.a_button_x           = z64_gameinfo.a_button_icon_x = 0xBA + (0x68 * CFG_WS);
    z64_gameinfo.item_button_x[0]     = z64_gameinfo.item_icon_x[0]  = 0xA2 + (0x66 * CFG_WS);
    z64_gameinfo.item_ammo_x[0]       = 0xA4  + (0x66 * CFG_WS);
    z64_b_button_label_x              = 0x94  + (0x68 * CFG_WS);
    z64_gameinfo.item_ammo_x[1]       = 0xE4  + (0x68 * CFG_WS);
    z64_gameinfo.item_button_x[1]     = z64_gameinfo.item_icon_x[1] = 0xE3 + (0x68 * CFG_WS);
    z64_gameinfo.item_button_x[2]     = z64_gameinfo.item_icon_x[2] = 0xF9 + (0x68 * CFG_WS);
    z64_gameinfo.item_ammo_x[2]       = 0xFA  + (0x67 * CFG_WS);
    z64_gameinfo.item_button_x[3]     = z64_gameinfo.item_icon_x[3] = 0x10F + (0x68 * CFG_WS);
    z64_gameinfo.item_ammo_x[3]       = 0x110 + (0x68 * CFG_WS);
    z64_gameinfo.c_up_button_x        = 0xFE  + (0x68 * CFG_WS);
    z64_gameinfo.c_up_icon_x          = 0xF7  + (0x68 * CFG_WS);
    
    if (z64_game.pause_ctxt.state == PAUSE_STATE_MAIN && OPTION_ACTIVE(1, SAVE_HUD_LAYOUT <= 1, CFG_DEFAULT_HUD_LAYOUT <= 1)) {
        z64_c_left_x_set_item  = 0x294 + (0x208 * CFG_WS);
        z64_c_down_x_set_item  = 0x384 + (0x218 * CFG_WS);
        z64_c_right_x_set_item = 0x474 + (0x208 * CFG_WS);
        z64_c_left_y_set_item  = 0x44C; z64_c_down_y_set_item  = 0x398; z64_c_right_y_set_item = 0x44C;
    }
}

void set_b_button(pad_t pad_pressed) {
    if (!OPTION_ACTIVE(2, SAVE_ITEM_ON_B, CFG_DEFAULT_ITEM_ON_B) || !z64_game.common.input[0].pad_pressed.a || z64_game.pause_ctxt.pageIndex != SUBSCREEN_ITEM || z64_game.pause_ctxt.debugState != 0 || \
        z64_game.pause_ctxt.cursorSpecialPos == 0x0A || z64_game.pause_ctxt.cursorSpecialPos == 0x0B || z64_game.pause_ctxt.cursorPoint[PAUSE_ITEM] <= Z64_SLOT_STICK || z64_game.pause_ctxt.cursorPoint[PAUSE_ITEM] >= Z64_SLOT_CHILD_TRADE)
        return;
    
    z64_item_t item = 0xFF;
    for (u8 i=0; i<18; i++)
        if (z64_game.pause_ctxt.cursorPoint[PAUSE_ITEM] == i) {
            if ( (!z64_file.link_age && z64_usability.item[i] == 1) || (z64_file.link_age && z64_usability.item[i] == 0) )
                item = 0xFF;
            else item = z64_file.items[i];
        }
    
    if (item != Z64_ITEM_SLINGSHOT && item != Z64_ITEM_BOW && item != Z64_ITEM_BOMBCHU && item != Z64_ITEM_LENS && item <= Z64_ITEM_NAYRUS_LOVE) {
        z64_file.button_items[0] = item;
        if (!z64_file.link_age)
            z64_file.adult_button_items[0] = item;
        else if    (z64_file.link_age)
            z64_file.child_button_items[0] = item;
        z64_UpdateItemButton(&z64_game, 0);
        z64_file.equip_sword = 0;
        play_sfx = 0x4808;
    }
}

void handle_rupee_drain() {
    if (OPTION_VALUE(2, 0, SAVE_RUPEE_DRAIN, CFG_DEFAULT_RUPEE_DRAIN))
        return;
    
    if (z64_file.energy > 1) {
        rupee_drain_frames++;
    
        if (rupee_drain_frames >= compare_frames) {
            rupee_drain_frames = 0;
            rupee_drain_secs++;
        }
    
        if (rupee_drain_secs >= ( (CFG_OPTIONS_MENU >= 2) ? SAVE_RUPEE_DRAIN : CFG_DEFAULT_RUPEE_DRAIN) ) {
            rupee_drain_secs = 0;
        
            if (z64_file.rupees > 0)
                z64_file.rupees--;
            else {
                z64_file.energy -= z64_file.energy > 7 ? 4 : 1;
                z64_LinkInvincibility(&z64_link, 0x14);
                play_sfx = z64_file.link_age ? 0x6825 : 0x6805;
            }
        }
    }
    else rupee_drain_frames = rupee_drain_secs = 0;
}

void handle_power_crouch_stab_fix() {
    if (!OPTION_ACTIVE(2, SAVE_CROUCH_STAB_FIX, CFG_DEFAULT_CROUCH_STAB_FIX))
        return;
    
    if ( !(z64_link.state_flags_1 & PLAYER_STATE1_HOLDING_Z) && (z64_link.state_flags_1 & PLAYER_STATE1_SHIELDING) && (z64_link.state_flags_2 & PLAYER_STATE2_PULLING_ITEM) ) {
        if (z64_link.held_item_action == PLAYER_IA_SWORD_KOKIRI || (z64_link.held_item_action == PLAYER_IA_SWORD_BIGGORON && z64_file.broken_giants_knife) )
            z64_damage_flag_1 = z64_damage_flag_2 = DMG_SLASH_KOKIRI;
        else if (z64_link.held_item_action == PLAYER_IA_SWORD_MASTER)
            z64_damage_flag_1 = z64_damage_flag_2 = DMG_SLASH_MASTER;
        else if (z64_link.held_item_action == PLAYER_IA_SWORD_BIGGORON)
            z64_damage_flag_1 = z64_damage_flag_2 = DMG_SLASH_GIANT;
        else if (z64_link.held_item_action == PLAYER_IA_DEKU_STICK)
            z64_damage_flag_1 = z64_damage_flag_2 = DMG_DEKU_STICK;
        else if (z64_link.held_item_action == PLAYER_IA_HAMMER)
            z64_damage_flag_1 = z64_damage_flag_2 = DMG_HAMMER_SWING;
    }
}

void handle_weaker_swords() {
    if (!(z64_link.state_flags_2 & PLAYER_STATE2_PULLING_ITEM))
        return;
    
    bool weaker   = OPTION_ACTIVE(2, SAVE_WEAKER_SWORDS, CFG_DEFAULT_WEAKER_SWORDS);
    bool stronger = OPTION_ACTIVE(2, SAVE_EXTRA_ABILITIES, CFG_DEFAULT_EXTRA_ABILITIES) && z64_file.water_medallion && z64_file.equip_tunic == 3;
    bool is_ganon = z64_game.scene_index == 0x4F;
    
    if (stronger) {
        if (z64_link.held_item_action == PLAYER_IA_SWORD_KOKIRI && z64_damage_flag_1 == DMG_SLASH_KOKIRI)
            z64_damage_flag_1 = z64_damage_flag_2 = DMG_JUMP_KOKIRI;
        else if (z64_link.held_item_action == PLAYER_IA_SWORD_MASTER && z64_damage_flag_1 == DMG_SLASH_MASTER)
            z64_damage_flag_1 = z64_damage_flag_2 = DMG_JUMP_MASTER;
        else if (z64_link.held_item_action == PLAYER_IA_SWORD_BIGGORON && z64_damage_flag_1 == DMG_SLASH_GIANT)
            z64_damage_flag_1 = z64_damage_flag_2 = DMG_JUMP_GIANT;
    }
    
    if (weaker) {
        if (z64_link.held_item_action == PLAYER_IA_SWORD_KOKIRI || (z64_link.held_item_action == PLAYER_IA_SWORD_BIGGORON && z64_file.broken_giants_knife) ) {
            if (!stronger && z64_damage_flag_1 == DMG_JUMP_KOKIRI)
                z64_damage_flag_1 = z64_damage_flag_2 = DMG_SLASH_KOKIRI;
        }
        
        if (z64_link.held_item_action == PLAYER_IA_SWORD_MASTER) {
            if (!stronger && z64_damage_flag_1 == DMG_SLASH_MASTER && !is_ganon)
                z64_damage_flag_1 = z64_damage_flag_2 = DMG_SLASH_KOKIRI;
            else if (z64_damage_flag_1 == DMG_JUMP_MASTER)
                z64_damage_flag_1 = z64_damage_flag_2 = DMG_SLASH_MASTER;
            else if (z64_damage_flag_1 == DMG_SPIN_MASTER && !is_ganon)
                z64_damage_flag_1 = z64_damage_flag_2 = DMG_SPIN_KOKIRI;
        }
        
        else if (z64_link.held_item_action == PLAYER_IA_SWORD_BIGGORON && !z64_file.broken_giants_knife) {
            if (!stronger && z64_damage_flag_1 == DMG_SLASH_GIANT && !is_ganon)
                z64_damage_flag_1 = z64_damage_flag_2 = DMG_SLASH_MASTER;
            else if (z64_damage_flag_1 == DMG_JUMP_GIANT && !is_ganon)
                z64_damage_flag_1 = z64_damage_flag_2 = DMG_SLASH_GIANT;
            else if (z64_damage_flag_1 == DMG_SPIN_GIANT && !is_ganon)
                z64_damage_flag_1 = z64_damage_flag_2 = DMG_SPIN_MASTER;
        }
        
        else if (z64_link.held_item_action == PLAYER_IA_DEKU_STICK) {
            if (z64_damage_flag_1 == DMG_DEKU_STICK)
                z64_damage_flag_1 = z64_damage_flag_2 = DMG_SLASH_KOKIRI;
            else if (z64_damage_flag_1 == DMG_JUMP_MASTER)
                z64_damage_flag_1 = z64_damage_flag_2 = DMG_JUMP_KOKIRI;
        }
    
        else if (z64_link.held_item_action == PLAYER_IA_HAMMER && z64_game.scene_index != 0x15) {
            if (z64_damage_flag_1 == DMG_HAMMER_SWING)
                z64_damage_flag_1 = z64_damage_flag_2 = DMG_SLASH_KOKIRI;
            else if (z64_damage_flag_1 == DMG_HAMMER_JUMP)
                z64_damage_flag_1 = z64_damage_flag_2 = DMG_JUMP_KOKIRI;
        }
    }
}

void handle_abilities_tunic_colors() {
    if (!checked_tunics) {
        checked_tunics = 1;
        tunic_kokiri.r = TUNIC_KOKIRI_R;
        tunic_kokiri.g = TUNIC_KOKIRI_G;
        tunic_kokiri.b = TUNIC_KOKIRI_B;
        tunic_goron.r  = TUNIC_GORON_R;
        tunic_goron.g  = TUNIC_GORON_G;
        tunic_goron.b  = TUNIC_GORON_B;
        tunic_zora.r   = TUNIC_ZORA_R;
        tunic_zora.g   = TUNIC_ZORA_G;
        tunic_zora.b   = TUNIC_ZORA_B;
    }
    
    if (z64_file.forest_medallion && OPTION_ACTIVE(2, SAVE_EXTRA_ABILITIES, CFG_DEFAULT_EXTRA_ABILITIES)) {
        TUNIC_KOKIRI_R = CFG_TUNIC_MAGICIAN.r;
        TUNIC_KOKIRI_G = CFG_TUNIC_MAGICIAN.g;
        TUNIC_KOKIRI_B = CFG_TUNIC_MAGICIAN.b;
    }
    else {
        TUNIC_KOKIRI_R = tunic_kokiri.r;
        TUNIC_KOKIRI_G = tunic_kokiri.g;
        TUNIC_KOKIRI_B = tunic_kokiri.b;
    }
        
    if (z64_file.fire_medallion && OPTION_ACTIVE(2, SAVE_EXTRA_ABILITIES, CFG_DEFAULT_EXTRA_ABILITIES)) {
        TUNIC_GORON_R = CFG_TUNIC_GUARDIAN.r;
        TUNIC_GORON_G = CFG_TUNIC_GUARDIAN.g;
        TUNIC_GORON_B = CFG_TUNIC_GUARDIAN.b;
    }
    else {
        TUNIC_GORON_R = tunic_goron.r;
        TUNIC_GORON_G = tunic_goron.g;
        TUNIC_GORON_B = tunic_goron.b;
    }
        
    if (z64_file.water_medallion && OPTION_ACTIVE(2, SAVE_EXTRA_ABILITIES, CFG_DEFAULT_EXTRA_ABILITIES)) {
        TUNIC_ZORA_R = CFG_TUNIC_HERO.r;
        TUNIC_ZORA_G = CFG_TUNIC_HERO.g;
        TUNIC_ZORA_B = CFG_TUNIC_HERO.b;
    }
    else {
        TUNIC_ZORA_R = tunic_zora.r;
        TUNIC_ZORA_G = tunic_zora.g;
        TUNIC_ZORA_B = tunic_zora.b;
    }
    
    if (z64_file.equip_tunic == 0)
        z64_tunic_color = 3;
    if (z64_file.shadow_medallion && OPTION_ACTIVE(2, SAVE_EXTRA_ABILITIES, CFG_DEFAULT_EXTRA_ABILITIES)) {
        TUNIC_UNUSED_R = CFG_TUNIC_SHADOW.r;
        TUNIC_UNUSED_G = CFG_TUNIC_SHADOW.g;
        TUNIC_UNUSED_B = CFG_TUNIC_SHADOW.b;
    }
    else {
        TUNIC_UNUSED_R = CFG_TUNIC_NONE.r;
        TUNIC_UNUSED_G = CFG_TUNIC_NONE.g;
        TUNIC_UNUSED_B = CFG_TUNIC_NONE.b;
    }
}

void handle_abilities() {
    if (!OPTION_ACTIVE(2, SAVE_EXTRA_ABILITIES, CFG_DEFAULT_EXTRA_ABILITIES))
        return;
    
    if (z64_file.light_medallion && (z64_file.equip_boots == 1 || (z64_file.spirit_medallion && z64_file.equip_boots == 3) ) && z64_game.common.input[0].raw.pad.l) {
        if (z64_link_animation_parameter == 0x3FA0)
            z64_link_a_action = 0x40FF;
    }
    
    if (z64_file.forest_medallion && z64_file.equip_tunic == 1 && HAS_MAGIC) {
        if ( (z64_file.magic < 0x30 && !z64_file.magic_capacity) || (z64_file.magic < 0x60 && z64_file.magic_capacity) ) {
            if (z64_damage_frames == 12 && restore_health == 0)
                restore_health = 1;
            else if (z64_damage_frames == 0)
                restore_health = 0;
            
            if (restore_health == 1) {
                restore_health = 2;
                z64_file.magic += 4;
                play_sfx = 0x480B;
                
                if (z64_file.magic > 0x60 && z64_file.magic_capacity)
                    z64_file.magic = 0x60;
                else if (z64_file.magic > 0x30)
                    z64_file.magic = 0x30;
            }
        }
    }
        
    if (z64_file.fire_medallion && z64_file.equip_tunic == 2) {
        z64_damage_taken_modifier_1 = 0x62843;
        z64_damage_taken_modifier_2 = 0x52C00;
    }
    else {
        z64_damage_taken_modifier_1 = 0x62C00;
        z64_damage_taken_modifier_2 = 0;
    }
        
    if (z64_file.shadow_medallion && z64_file.equip_tunic == 0) {
        if (z64_file.energy < z64_file.energy_capacity && z64_file.magic > 0 && HAS_MAGIC) {
            restore_frames++;
        
            if (restore_frames >= compare_frames) {
                restore_frames = 0;
                restore_secs++;
            }
        
            if (restore_secs >= 3) {
                restore_secs = 0;
                z64_file.energy += 4;
                z64_file.magic -= z64_file.magic >= 4 ? 4 : 0;
                play_sfx = 0x480B;
            }
        }
        else restore_frames = restore_secs = 0;
    }
        
    if (z64_file.spirit_medallion ) {
        z64_inner_red_trail_r = z64_outer_red_trail_r = 0xFF;
        z64_inner_red_trail_g = z64_outer_red_trail_g = 0xD7;
        z64_inner_red_trail_b = z64_outer_red_trail_b = 0x00;
    }
    
    if (z64_file.kokiris_emerald && (z64_file.equip_boots == 1 || (z64_file.spirit_medallion && z64_file.equip_boots == 3) ) && z64_game.common.input[0].raw.pad.l && HAS_MAGIC && z64_file.magic > 0) {
        if (z64_move_speed >= z64_max_move_speed - 0x1A) {
            magic_frames++;
                
            if (magic_frames >= compare_frames/2) {
                magic_frames = 0;
                magic_secs++;
            }
                
            if (magic_secs >= 1) {
                magic_secs = 0;
                u8 drain        = 2 - z64_file.zoras_sapphire;
                z64_file.magic -= z64_file.magic >= drain ? drain : 0;
            }
                
            z64_move_speed = z64_max_move_speed + 0x50 + (z64_file.gorons_ruby * 0x50);
        }
    }
    else magic_frames = magic_secs = 0;
}

void handle_infinite() {
    if (z64_game.pause_ctxt.debugState != 0)
        return;
    
    if (OPTION_ACTIVE(3, SAVE_INFINITE_HP, CFG_DEFAULT_INFINITE_HP))
        z64_file.energy = z64_file.energy_capacity;
    
    if (OPTION_ACTIVE(3, SAVE_INFINITE_MP, CFG_DEFAULT_INFINITE_MP)) {
        if (HAS_MAGIC) {
            if (z64_file.magic_capacity)
                z64_file.magic = 0x60;
            else z64_file.magic = 0x30;
        }
    }
    
    if (OPTION_ACTIVE(3, SAVE_INFINITE_AMMO, CFG_DEFAULT_INFINITE_AMMO)) {
        z64_file.ammo[Z64_SLOT_STICK]     = z64_capacity.stick_upgrade[z64_file.stick_upgrade];
        z64_file.ammo[Z64_SLOT_NUT]       = z64_capacity.nut_upgrade[z64_file.nut_upgrade];
        z64_file.ammo[Z64_SLOT_BOMB]      = z64_capacity.bomb_bag[z64_file.bomb_bag];
        z64_file.ammo[Z64_SLOT_BOW]       = z64_capacity.quiver[z64_file.quiver];
        z64_file.ammo[Z64_SLOT_SLINGSHOT] = z64_capacity.bullet_bag[z64_file.bullet_bag];
        z64_file.ammo[Z64_SLOT_BOMBCHU]   = 50;
    }
    
    if (OPTION_ACTIVE(3, SAVE_INFINITE_RUPEES, CFG_DEFAULT_INFINITE_RUPEES))
        z64_file.rupees = z64_capacity.wallet[z64_file.wallet];
}

void interface_raise_button_alphas(z64_game_t* game, u8 rising_alpha) {
    for (u8 i=0; i<5; i++) {
        if (z64_file.button_status[i] == BTN_DISABLED) {
            if (*button_alphas[i] != 70)
                *button_alphas[i] = 70;
        }
        else if (*button_alphas[i] != 255)
            *button_alphas[i] = rising_alpha;
    }
    
    if ((z64_link.state_flags_1 & PLAYER_STATE1_CLIMBING) || (z64_link.state_flags_2 & PLAYER_STATE2_CRAWLING)) {
        if (dpad_alpha != 70)
            dpad_alpha = 70;
    }
    else if (dpad_alpha != 255)
        dpad_alpha = rising_alpha;
}

void interface_dim_button_alphas(z64_game_t* game, u8 dimming_alpha, u8 rising_alpha) {
    if (z64_file.force_rising_button_alphas) {
        interface_raise_button_alphas(game, rising_alpha);
        return;
    }
    
    for (u8 i=0; i<4; i++)
        if (*button_alphas[i] != 0 && *button_alphas[i] > dimming_alpha)
            *button_alphas[i] = dimming_alpha;
        
    if (dpad_alpha != 0 && dpad_alpha > dimming_alpha)
            dpad_alpha = dimming_alpha;
}

void interface_update_hud_alphas(z64_game_t* game, u8 dimming_alpha) {
    u8 rising_alpha = 255 - dimming_alpha;
    
    switch (z64_file.next_hud_visibility_mode) {
        case HUD_VISIBILITY_NOTHING:
        case HUD_VISIBILITY_NOTHING_ALT:
        case HUD_VISIBILITY_B: {
            if (z64_file.next_hud_visibility_mode == HUD_VISIBILITY_B) {
                if (game->alpha_channels.b_button != 255)
                    game->alpha_channels.b_button = rising_alpha;
            }
            else if (game->alpha_channels.b_button != 0 && game->alpha_channels.b_button > dimming_alpha)
                game->alpha_channels.b_button = dimming_alpha;
            
            static u16* dimming_alphas[] = { &z64_game.alpha_channels.a_button, &z64_game.alpha_channels.cl_button, &z64_game.alpha_channels.cd_button, &z64_game.alpha_channels.cr_button, &z64_game.alpha_channels.health, &z64_game.alpha_channels.magic, &z64_game.alpha_channels.minimap, &dpad_alpha };
            for (u8 i=0; i<ARRAY_SIZE(dimming_alphas); i++)
                if (*dimming_alphas[i] != 0 && *dimming_alphas[i] > dimming_alpha)
                    *dimming_alphas[i] = dimming_alpha;
            break;
        }

        case HUD_VISIBILITY_HEARTS_FORCE: {
            if (game->alpha_channels.a_button != 0 && game->alpha_channels.a_button > dimming_alpha)
                game->alpha_channels.a_button  = dimming_alpha;
            
            interface_dim_button_alphas(game, dimming_alpha, rising_alpha);
            
            static u16* dimming_alphas[] = { &z64_game.alpha_channels.magic, &z64_game.alpha_channels.minimap };
            for (u8 i=0; i<ARRAY_SIZE(dimming_alphas); i++)
                if (*dimming_alphas[i] != 0 && *dimming_alphas[i] > dimming_alpha)
                    *dimming_alphas[i] = dimming_alpha;
            
            if (game->alpha_channels.health   != 255)
                game->alpha_channels.health    = rising_alpha;
            break;
        }

        case HUD_VISIBILITY_A: {
            static u16* dimming_alphas[] = { &z64_game.alpha_channels.b_button, &z64_game.alpha_channels.a_button, &z64_game.alpha_channels.cl_button, &z64_game.alpha_channels.cd_button, &z64_game.alpha_channels.cr_button, &z64_game.alpha_channels.health, &z64_game.alpha_channels.magic, &z64_game.alpha_channels.minimap, &dpad_alpha };
            for (u8 i=0; i<ARRAY_SIZE(dimming_alphas); i++)
                if (*dimming_alphas[i] != 0 && *dimming_alphas[i] > dimming_alpha)
                    *dimming_alphas[i] = dimming_alpha;
                
            if (game->alpha_channels.a_button != 255)
                game->alpha_channels.a_button = rising_alpha;
            break;
        }

        case HUD_VISIBILITY_A_HEARTS_MAGIC_FORCE: {
            interface_dim_button_alphas(game, dimming_alpha, rising_alpha);
            
            if (game->alpha_channels.minimap  != 0 && game->alpha_channels.minimap > dimming_alpha)
                game->alpha_channels.minimap   = dimming_alpha;
            
            static u16* rising_alphas[] = { &z64_game.alpha_channels.a_button, &z64_game.alpha_channels.health, &z64_game.alpha_channels.magic };
            for (u8 i=0; i<ARRAY_SIZE(rising_alphas); i++)
                if (*rising_alphas[i] != 255)
                *rising_alphas[i] = rising_alpha;
            break;
        }

        case HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP_FORCE: {
            interface_dim_button_alphas(game, dimming_alpha, rising_alpha);
            
            static u16* rising_alphas[] = { &z64_game.alpha_channels.a_button, &z64_game.alpha_channels.health, &z64_game.alpha_channels.magic };
            for (u8 i=0; i<ARRAY_SIZE(rising_alphas); i++)
                if (*rising_alphas[i] != 255)
                    *rising_alphas[i] = rising_alpha;

            switch (game->scene_index) {
                case SCENE_HYRULE_FIELD:
                case SCENE_KAKARIKO_VILLAGE:
                case SCENE_GRAVEYARD:
                case SCENE_ZORAS_RIVER:
                case SCENE_KOKIRI_FOREST:
                case SCENE_SACRED_FOREST_MEADOW:
                case SCENE_LAKE_HYLIA:
                case SCENE_ZORAS_DOMAIN:
                case SCENE_ZORAS_FOUNTAIN:
                case SCENE_GERUDO_VALLEY:
                case SCENE_LOST_WOODS:
                case SCENE_DESERT_COLOSSUS:
                case SCENE_GERUDOS_FORTRESS:
                case SCENE_HAUNTED_WASTELAND:
                case SCENE_HYRULE_CASTLE:
                case SCENE_DEATH_MOUNTAIN_TRAIL:
                case SCENE_DEATH_MOUNTAIN_CRATER:
                case SCENE_GORON_CITY:
                case SCENE_LON_LON_RANCH:
                case SCENE_OUTSIDE_GANONS_CASTLE:
                    game->alpha_channels.minimap = (game->alpha_channels.minimap < 170) ? rising_alpha : 170;
                    break;
                default:
                    if (game->alpha_channels.minimap != 255)
                        game->alpha_channels.minimap  = rising_alpha;
                    break;
            }
            break;
        }

        case HUD_VISIBILITY_ALL_NO_MINIMAP_BY_BTN_STATUS:
            if (game->alpha_channels.minimap != 0 && game->alpha_channels.minimap > dimming_alpha)
                game->alpha_channels.minimap  = dimming_alpha;
            
            interface_raise_button_alphas(game, rising_alpha);
            
            static u16* rising_alphas[] = { &z64_game.alpha_channels.health, &z64_game.alpha_channels.magic };
            for (u8 i=0; i<ARRAY_SIZE(rising_alphas); i++)
                if (*rising_alphas[i] != 255)
                    *rising_alphas[i] = rising_alpha;
            break;

        case HUD_VISIBILITY_HEARTS_MAGIC: {
            static u16* dimming_alphas[] = { &z64_game.alpha_channels.b_button, &z64_game.alpha_channels.a_button, &z64_game.alpha_channels.cl_button, &z64_game.alpha_channels.cd_button, &z64_game.alpha_channels.cr_button, &z64_game.alpha_channels.minimap, &dpad_alpha };
            for (u8 i=0; i<ARRAY_SIZE(dimming_alphas); i++)
                if (*dimming_alphas[i] != 0 && *dimming_alphas[i] > dimming_alpha)
                    *dimming_alphas[i] = dimming_alpha;
            
            static u16* rising_alphas[] = { &z64_game.alpha_channels.health, &z64_game.alpha_channels.magic };
            for (u8 i=0; i<ARRAY_SIZE(rising_alphas); i++)
                if (*rising_alphas[i] != 255)
                    *rising_alphas[i] = rising_alpha;
            break;
        }

        case HUD_VISIBILITY_B_ALT: {
            static u16* dimming_alphas[] = { &z64_game.alpha_channels.a_button, &z64_game.alpha_channels.cl_button, &z64_game.alpha_channels.cd_button, &z64_game.alpha_channels.cr_button, &z64_game.alpha_channels.health, &z64_game.alpha_channels.magic, &z64_game.alpha_channels.minimap, &dpad_alpha };
            for (u8 i=0; i<ARRAY_SIZE(dimming_alphas); i++)
                if (*dimming_alphas[i] != 0 && *dimming_alphas[i] > dimming_alpha)
                    *dimming_alphas[i] = dimming_alpha;
            
            if (game->alpha_channels.b_button != 255)
                game->alpha_channels.b_button = rising_alpha;
            break;
        }

        case HUD_VISIBILITY_HEARTS: {
            static u16* dimming_alphas[] = { &z64_game.alpha_channels.b_button, &z64_game.alpha_channels.a_button, &z64_game.alpha_channels.cl_button, &z64_game.alpha_channels.cd_button, &z64_game.alpha_channels.cr_button, &z64_game.alpha_channels.minimap, &z64_game.alpha_channels.magic, &dpad_alpha };
            for (u8 i=0; i<ARRAY_SIZE(dimming_alphas); i++)
                if (*dimming_alphas[i] != 0 && *dimming_alphas[i] > dimming_alpha)
                    *dimming_alphas[i] = dimming_alpha;
            
            if (game->alpha_channels.health != 255)
                game->alpha_channels.health = rising_alpha;
            break;
        }

        case HUD_VISIBILITY_A_B_MINIMAP: {
            static u16* rising_alphas[] = { &z64_game.alpha_channels.a_button, &z64_game.alpha_channels.b_button, &z64_game.alpha_channels.minimap };
            for (u8 i=0; i<ARRAY_SIZE(rising_alphas); i++)
                if (*rising_alphas[i] != 255)
                    *rising_alphas[i] = rising_alpha;
            
            static u16* dimming_alphas[] = { &z64_game.alpha_channels.cl_button, &z64_game.alpha_channels.cd_button, &z64_game.alpha_channels.cr_button, &z64_game.alpha_channels.magic, &z64_game.alpha_channels.health, &dpad_alpha };
            for (u8 i=0; i<ARRAY_SIZE(dimming_alphas); i++)
                if (*dimming_alphas[i] != 0 && *dimming_alphas[i] > dimming_alpha)
                    *dimming_alphas[i] = dimming_alpha;
            break;
        }

        case HUD_VISIBILITY_HEARTS_MAGIC_FORCE: {
            interface_dim_button_alphas(game, dimming_alpha, rising_alpha);
            
            static u16* dimming_alphas[] = { &z64_game.alpha_channels.minimap, &z64_game.alpha_channels.a_button };
            for (u8 i=0; i<ARRAY_SIZE(dimming_alphas); i++)
                if (*dimming_alphas[i] != 0 && *dimming_alphas[i] > dimming_alpha)
                    *dimming_alphas[i] = dimming_alpha;
                
            static u16* rising_alphas[] = { &z64_game.alpha_channels.health, &z64_game.alpha_channels.magic };
            for (u8 i=0; i<ARRAY_SIZE(rising_alphas); i++)
                if (*rising_alphas[i] != 255)
                    *rising_alphas[i] = rising_alpha;
            break;
        }
    }
    
    if ((game->room_behavior_type_1 == ROOM_BEHAVIOR_TYPE1_1) && (game->alpha_channels.minimap >= 255))
        game->alpha_channels.minimap = 255;
}

void interface_change_hud_visibility_mode(u16 hud_visibility_mode) {
    if (hud_visibility_mode != z64_file.hud_visibility_mode) {
        u8 mode = hud_visibility_mode;
        
        if (!z64_game.pause_ctxt.state) {
            if (OPTION_VALUE(1, 0, SAVE_HIDE_HUD, CFG_DEFAULT_HIDE_HUD) && last_interface >= 0) {
                mode           = HUD_VISIBILITY_ALL;
                last_interface = -1;
            }
            else if (OPTION_VALUE(1, 1, SAVE_HIDE_HUD, CFG_DEFAULT_HIDE_HUD) && last_interface != HUD_VISIBILITY_NOTHING)
                mode = last_interface = HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP_FORCE;
            else if (OPTION_VALUE(1, 2, SAVE_HIDE_HUD, CFG_DEFAULT_HIDE_HUD) && last_interface != HUD_VISIBILITY_NOTHING)
                mode = last_interface = HUD_VISIBILITY_HEARTS_MAGIC;
            else if (OPTION_VALUE(1, 3, SAVE_HIDE_HUD, CFG_DEFAULT_HIDE_HUD) && last_interface != HUD_VISIBILITY_NOTHING)
                mode = last_interface = HUD_VISIBILITY_HEARTS;
            else if (OPTION_VALUE(1, 4, SAVE_HIDE_HUD, CFG_DEFAULT_HIDE_HUD))
                mode = last_interface = HUD_VISIBILITY_NOTHING;
        }
        
        z64_file.hud_visibility_mode = z64_file.next_hud_visibility_mode = mode;
        z64_file.hud_visibility_mode_timer = 1;
    }
}