#ifndef FPS_H
#define FPS_H

#include "z64.h"

void handle_fps();
void reset_fps_values();

#define bottle_action                   (*(u32*)           0x801C86B2)
#define link_animation_parameter        (*(u32*)           0x801DABF0)
#define jump_gravity                    (*(u16*)           0x801DAA9C)
#define link_animation                  (*(u16*)           0x801DABDE)
#define deku_stick_timer                (*(u16*)           0x801DB280)
#define hover_boots_length              (*(u16*)           0x8039E612)
#define time_of_day_speed               (*(u16*)           0x800F1650)
#define time_remaining                  (*(u16*)           0x8011B9A0)
#define boomerang_active                (*(u16*)           0x800E8B8E)
#define hookshot_active                 (*(u16*)           0x801DAA50)
#define timer_type                      (*(u8*)            0x8011B99F)
#define seconds_left                    (*(u8*)            0x8011BF31)
#define playing_ocarina                 (*(u8*)            0x80102208)
#define talking_to_npc                  (*(u8*)            0x801DAA36)
#define fishing                         (*(u8*)            0x801C8C41)
#define frogs                           (*(u8*)            0x801C8835)
#define lens_of_truth_start             (*(u8*)            0x80072747)
#define lens_of_truth_interval          (*(u8*)            0x80072E0B) // 0x801D8BC1

#define timer1_1                        (*(u16*)           0x800772FE)
#define timer1_2                        (*(u16*)           0x80077366)
#define timer1_3                        (*(u16*)           0x800775D2)
#define timer1_4                        (*(u16*)           0x800778CE)
#define timer2_1                        (*(u16*)           0x800772EA)
#define timer2_2                        (*(u16*)           0x80077342)
#define timer2_3                        (*(u16*)           0x8007735A)
#define timer2_4                        (*(u16*)           0x800773C2)
#define timer2_5                        (*(u16*)           0x800774FE)
#define timer2_6                        (*(u16*)           0x8007782E)
#define timer2_7                        (*(u16*)           0x800778FE)
#define timer3_1                        (*(u16*)           0x80077956)
#define timer3_2                        (*(u16*)           0x80077A0A)
#define timer3_3                        (*(u16*)           0x80077C4A)
#define timer4_1                        (*(u16*)           0x800770AE)
#define timer4_2                        (*(u16*)           0x80077952)
#define timer4_3                        (*(u16*)           0x800779F6)
#define timer4_4                        (*(u16*)           0x80077A5E)
#define timer4_5                        (*(u16*)           0x80077B86)
#define timer4_6                        (*(u16*)           0x80077C8A)
#define timer4_7                        (*(u16*)           0x80077CF2)

#endif
