#include "fps.h"

bool fps_switch                 = true;
bool deku_stick_timer_switch    = false;
bool nayrus_love_timer_switch   = false;
bool damage_frames_timer_switch = false;
u16  last_time                  = 0;
u16  started_timer              = 0;

extern u16 play_sfx;

void handle_fps() {
    if (!OPTION_ACTIVE(1, SAVE_30_FPS, CFG_DEFAULT_30_FPS) || z64_file.game_mode != 0)
        return;
    
    if ( (z64_game.common.input[0].raw.pad.l && z64_game.common.input[0].pad_pressed.z) || (z64_game.common.input[0].raw.pad.z && z64_game.common.input[0].pad_pressed.l) ) {
        fps_switch ^= 1;
        if (fps_switch)
            play_sfx = 0x4814;
        else play_sfx = 0x4813;
    }
    
    if (z64_game.pause_ctxt.state != PAUSE_STATE_OFF)
        return;
    
    if (!fps_switch)
        fps_limit = 3;
    else if (playing_ocarina || (z64_link.state_flags_1 & PLAYER_STATE1_NO_CONTROL) || talking_to_npc)
        fps_limit = 2;
    else if (z64_file.game_mode == 1 || !CAN_CONTROL_LINK || hookshot_active == 0x100B || link_animation == 0x2708 || bottle_action == 0x00010005 || frogs > 1)
        fps_limit = 3;
    else if (fps_switch)
        fps_limit = 2;
    
    if (fps_limit == 2) {
        if (deku_stick_timer == 100 && !deku_stick_timer_switch) {
            deku_stick_timer += 100;
            deku_stick_timer_switch = 1;
        }
        else if (deku_stick_timer == 0 && deku_stick_timer_switch)
            deku_stick_timer_switch = false;
        
        if (z64_file.nayrus_love_timer == 601 && !nayrus_love_timer_switch) {
            z64_file.nayrus_love_timer -= 600;
            nayrus_love_timer_switch = true;
        }
        else if ( (z64_file.nayrus_love_timer == 0 || z64_file.nayrus_love_timer > 601) && nayrus_love_timer_switch)
            nayrus_love_timer_switch = false;
        
        if (z64_damage_frames == 1 && !damage_frames_timer_switch) {
            z64_damage_frames += 10;
            damage_frames_timer_switch = true;
        }
        else if (z64_damage_frames == 0 && damage_frames_timer_switch)
            damage_frames_timer_switch = false;
        
        if (link_animation == 0x2968 || link_animation == 0x2970 || link_animation == 0x2A80 || link_animation == 0x2A90)
            link_animation_parameter = 0x3F4CCCCD;
        
        if (jump_gravity != 0)
            jump_gravity = 0xBF34;
        
        if (time_of_day_speed == 10)
            time_of_day_speed = 7;
        if (hover_boots_length == 19)
            hover_boots_length = 30;
        if (lens_of_truth_start == 80)
            lens_of_truth_start = lens_of_truth_interval = 120;
        
        // Timers
        if (timer1_1 == 0x14) {
            timer1_1 = timer1_2 = timer1_3 = timer1_4 = 0x1E;
            timer2_1 = timer2_2 = timer2_3 = timer2_4 = timer2_5 = timer2_6 = 0x1E;
            timer2_7 = 0x3C;
            timer3_1 = timer3_2 = timer3_3 = 0x1E;
            timer4_2 = timer4_3 = timer4_4 = timer4_5 = 0x1E;
            timer4_1 = timer4_6 = timer4_7 = 0x3C;
        }
    }
    else if (fps_limit == 3)
        reset_fps_values();
}

void reset_fps_values() {
    if (time_of_day_speed == 7)
        time_of_day_speed = 10;
    if (hover_boots_length == 30)
        hover_boots_length = 19;
    if (lens_of_truth_start == 120)
        lens_of_truth_start = lens_of_truth_interval = 80;
        
    // Timers
    if (timer1_1 == 0x1E) {
        timer1_1 = timer1_2 = timer1_3 = timer1_4                       = 0x14;
        timer2_1 = timer2_2 = timer2_3 = timer2_4 = timer2_5 = timer2_6 = 0x14;
        timer2_7                                                        = 0x28;
        timer3_1 = timer3_2 = timer3_3                                  = 0x14;
        timer4_2 = timer4_3 = timer4_4 = timer4_5                       = 0x14;
        timer4_1 = timer4_6 = timer4_7                                  = 0x28;
    }
}