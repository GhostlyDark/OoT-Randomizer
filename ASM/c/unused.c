/* Backup */
/*
#define Player_IsHoldingHookshot          ((is_holding_hookshot_t)    0x80079854) // ROM: 0xAEF7B4
#define Player_ItemToItemAction           ((item_to_item_action_t)    0x8038A0EC) // ROM: 0xBCF0FC
#define Player_ItemIsInUse                ((item_is_in_use_t)         0x8038A654) // ROM: 0xBCF664
#define Player_ItemIsItemAction           ((item_is_item_action_t)    0x8038A6A0) // ROM: 0xBCF6B0
#define Player_GetItemOnButton            ((get_item_on_button_t)     0x8038A6DC) // ROM: 0xBCF6EC
#define z64_dpad_item_in_use              (*(u16*)                    0x8038A9D4)
#define z64_dpad_b_button_prompt          (*(u16*)                    0x803AABE8)
#define z64_dpad_b_button_item_check      (*(u16*)                    0x8038A73C)
#define z64_dpad_b_button_item            (*(u8*)                     0x8038A74B)
#define z64_dpad_item_b                   (*(u16*)                    0x8038A948)
#define z64_dpad_item_1                   (*(u16*)                    0x8038A978)
#define z64_dpad_item_2                   (*(u16*)                    0x8038A9A8)
#define z64_dpad_item_3                   (*(u16*)                    0x8038A9D4)
#define z64_dpad_index_b_check            (*(u16*)                    0x8038A724)
#define z64_dpad_index_cl_check           (*(u16*)                    0x8038A770)
#define z64_dpad_check_all_buttons_1      (*(u16*)                    0x8038AA10)
#define z64_dpad_check_all_buttons_2      (*(u16*)                    0x8038AA6C)
#define z64_dpad_held_button_1            (*(u16*)                    0x8038B6A8) // ROM: 0xBD06B8
#define z64_dpad_held_button_2            (*(u16*)                    0x8038BD1C) // ROM: 0xBD0D2C
#define z64_dpad_held_button_3            (*(u16*)                    0x8038BE70) // ROM: 0xBD0E80
#define z64_dpad_held_button_4            (*(u16*)                    0x8038C3D0) // ROM: 0xBD13E0
#define z64_held_item_check               (*(u16*)                    0x8038CDF4)
#define z64_dpad_get_index_none           (*(s8*)                     0x8038A6FB)
#define z64_dpad_buttons_prompt_1         (*(u32*)                    0x803AABE8)
#define z64_dpad_buttons_prompt_2         (*(u32*)                    0x803AABEC)
#define z64_dpad_get_index_cl_1           (*(u8*)                     0x8038A77F)
#define z64_dpad_get_index_cl_2           (*(u8*)                     0x8038A793)
*/

/* Transition */
/*
#define TRANS_TRIGGER_OFF    0
#define TRANS_TRIGGER_START  20
#define TRANS_TRIGGER_END   -20
*/

/*
#define GET_EVENTINF_INGO_RACE_STATE() (z64_file.event_inf[EVENTINF_HORSES_INDEX] & EVENTINF_INGO_RACE_STATE_MASK)
#define EVENTINF_HORSES_INDEX          0
#define EVENTINF_INGO_RACE_STATE_MASK  (0xF << 0)

#define YEARS_CHILD       5
#define YEARS_ADULT       17
#define LINK_AGE_IN_YEARS (!LINK_IS_ADULT ? YEARS_CHILD : YEARS_ADULT)
*/

/*typedef enum {
    MSGMODE_NONE,
    MSGMODE_TEXT_START,
    MSGMODE_TEXT_BOX_GROWING,
    MSGMODE_TEXT_STARTING,
    MSGMODE_TEXT_NEXT_MSG,
    MSGMODE_TEXT_CONTINUING,
    MSGMODE_TEXT_DISPLAYING,
    MSGMODE_TEXT_AWAIT_INPUT,
    MSGMODE_TEXT_DELAYED_BREAK,
    MSGMODE_OCARINA_STARTING,
    MSGMODE_SONG_DEMONSTRATION_STARTING,
    MSGMODE_SONG_PLAYBACK_STARTING,
    MSGMODE_OCARINA_PLAYING,
    MSGMODE_OCARINA_CORRECT_PLAYBACK,
    MSGMODE_OCARINA_FAIL,
    MSGMODE_OCARINA_FAIL_NO_TEXT,
    MSGMODE_OCARINA_NOTES_DROP,
    MSGMODE_SONG_PLAYED,
    MSGMODE_SETUP_DISPLAY_SONG_PLAYED,
    MSGMODE_DISPLAY_SONG_PLAYED,
    MSGMODE_DISPLAY_SONG_PLAYED_TEXT_BEGIN,
    MSGMODE_DISPLAY_SONG_PLAYED_TEXT,
    MSGMODE_SONG_PLAYED_ACT_BEGIN,
    MSGMODE_SONG_PLAYED_ACT,
    MSGMODE_SONG_DEMONSTRATION_SELECT_INSTRUMENT,
    MSGMODE_SONG_DEMONSTRATION,
    MSGMODE_SONG_DEMONSTRATION_DONE,
    MSGMODE_SONG_PLAYBACK,
    MSGMODE_SONG_PLAYBACK_SUCCESS,
    MSGMODE_SONG_PLAYBACK_FAIL,
    MSGMODE_SONG_PLAYBACK_NOTES_DROP,
    MSGMODE_OCARINA_AWAIT_INPUT,
    MSGMODE_UNK_20,
    MSGMODE_SCARECROW_LONG_RECORDING_START,
    MSGMODE_SCARECROW_LONG_RECORDING_ONGOING,
    MSGMODE_SCARECROW_LONG_PLAYBACK,
    MSGMODE_SCARECROW_SPAWN_RECORDING_START,
    MSGMODE_SCARECROW_SPAWN_RECORDING_ONGOING,
    MSGMODE_SCARECROW_SPAWN_RECORDING_FAILED,
    MSGMODE_SCARECROW_SPAWN_RECORDING_DONE,
    MSGMODE_SCARECROW_SPAWN_PLAYBACK,
    MSGMODE_MEMORY_GAME_START,
    MSGMODE_MEMORY_GAME_LEFT_SKULLKID_PLAYING,
    MSGMODE_MEMORY_GAME_LEFT_SKULLKID_WAIT,
    MSGMODE_MEMORY_GAME_RIGHT_SKULLKID_PLAYING,
    MSGMODE_MEMORY_GAME_RIGHT_SKULLKID_WAIT,
    MSGMODE_MEMORY_GAME_PLAYER_PLAYING,
    MSGMODE_MEMORY_GAME_ROUND_SUCCESS,
    MSGMODE_MEMORY_GAME_START_NEXT_ROUND,
    MSGMODE_FROGS_START,
    MSGMODE_FROGS_PLAYING,
    MSGMODE_FROGS_WAITING,
    MSGMODE_TEXT_AWAIT_NEXT,
    MSGMODE_TEXT_DONE,
    MSGMODE_TEXT_CLOSING,
    MSGMODE_PAUSED
} z64_message_mode;

typedef enum {
    INGO_RACE_STATE_OFFER_RENTAL,
    INGO_RACE_STATE_HORSE_RENTAL_PERIOD,
    INGO_RACE_STATE_RACING,
    INGO_RACE_STATE_PLAYER_LOSE,
    INGO_RACE_STATE_FIRST_WIN,
    INGO_RACE_STATE_TRAPPED_WIN_UNUSED,
    INGO_RACE_STATE_TRAPPED_WIN_EPONA,
    INGO_RACE_STATE_REMATCH
} z64_ingo_race_state;

typedef enum {
    TRANS_MODE_OFF,
    TRANS_MODE_SETUP,
    TRANS_MODE_INSTANCE_INIT,
    TRANS_MODE_INSTANCE_RUNNING,
    TRANS_MODE_FILL_WHITE_INIT,
    TRANS_MODE_FILL_IN,
    TRANS_MODE_FILL_OUT,
    TRANS_MODE_FILL_BROWN_INIT,
    TRANS_MODE_08,
    TRANS_MODE_09,
    TRANS_MODE_INSTANT,
    TRANS_MODE_INSTANCE_WAIT,
    TRANS_MODE_SANDSTORM_INIT,
    TRANS_MODE_SANDSTORM,
    TRANS_MODE_SANDSTORM_END_INIT,
    TRANS_MODE_SANDSTORM_END,
    TRANS_MODE_CS_BLACK_FILL_INIT,
    TRANS_MODE_CS_BLACK_FILL
} z64_transition_mode;*/

/*void interface_enable_buttons(z64_game_t* game) {
    refresh_interface = false;
    s16 i;
    
    if (z64_file.cutscene_index < 0xFFF0 || (game->scene_index == SCENE_LON_LON_RANCH && z64_file.cutscene_index == 0xFFF0) ) {
        z64_file.force_rising_button_alphas = false;

        if ( (z64_link.state_flags_1 & PLAYER_STATE1_RIDING) || game->shootingGalleryStatus > 1 || (game->scene_index == SCENE_BOMBCHU_BOWLING_ALLEY && Flags_GetSwitch(game, 0x38) ) ) {
            if (z64_file.button_items[0] != Z64_ITEM_NONE) {
                z64_file.force_rising_button_alphas = true;

                if (z64_file.button_status[0] == BTN_DISABLED)
                    z64_file.button_status[0] = z64_file.button_status[1] = z64_file.button_status[2] = z64_file.button_status[3] = BTN_ENABLED;

                if ((z64_file.button_items[0] != Z64_ITEM_SLINGSHOT) && z64_file.button_items[0] != Z64_ITEM_BOW && z64_file.button_items[0] != Z64_ITEM_BOMBCHU && z64_file.button_items[0] != Z64_ITEM_NONE) {
                    z64_file.button_status[0] = z64_file.button_items[0];
                    if ((game->scene_index == SCENE_BOMBCHU_BOWLING_ALLEY) && Flags_GetSwitch(game, 0x38)) {
                        z64_file.button_items[0] = Z64_ITEM_BOMBCHU;
                        Interface_LoadItemIcon1(game, 0);
                    }
                    else {
                        z64_file.button_items[0] = Z64_ITEM_BOW;
                        if (game->shootingGalleryStatus > 1) {
                            if (LINK_AGE_IN_YEARS == YEARS_CHILD && z64_file.items[Z64_SLOT_SLINGSHOT] == Z64_ITEM_SLINGSHOT)
                                z64_file.button_items[0] = Z64_ITEM_SLINGSHOT;
                            Interface_LoadItemIcon1(game, 0);
                        }
                        else {
                            if (z64_file.items[SLOT_BOW] == Z64_ITEM_NONE)
                                z64_file.button_items[0] = Z64_ITEM_NONE;
                            else Interface_LoadItemIcon1(game, 0);
                        }
                    }
                    z64_file.button_status[1] = z64_file.button_status[2] = z64_file.button_status[3] = BTN_DISABLED;
                    interface_change_hud_visibility_mode(HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP_FORCE);
                }
                
                if (game->transition_mode != TRANS_MODE_OFF)
                    interface_change_hud_visibility_mode(HUD_VISIBILITY_NOTHING);
                else if (z64_file.minigame_state == 1)
                    interface_change_hud_visibility_mode(HUD_VISIBILITY_B);
                else if (game->shootingGalleryStatus > 1)
                    interface_change_hud_visibility_mode(HUD_VISIBILITY_B);
                else if ((game->scene_index == SCENE_BOMBCHU_BOWLING_ALLEY) && Flags_GetSwitch(game, 0x38))
                    interface_change_hud_visibility_mode(HUD_VISIBILITY_B);
                else if (z64_link.state_flags_1 & PLAYER_STATE1_RIDING)
                    interface_change_hud_visibility_mode(HUD_VISIBILITY_A_B_MINIMAP);
            }
            else if (z64_link.state_flags_1 & PLAYER_STATE1_RIDING)
                interface_change_hud_visibility_mode(HUD_VISIBILITY_A_B_MINIMAP);
        }
        
        else if (game->scene_index == SCENE_CHAMBER_OF_THE_SAGES)
            interface_change_hud_visibility_mode(HUD_VISIBILITY_NOTHING);
        
        else if (game->scene_index == SCENE_FISHING_POND) {
            z64_file.force_rising_button_alphas = 2;
            if (z64_game.unk_260 != 0) {
                if (z64_file.button_items[0] != ITEM_FISHING_POLE) {
                    z64_file.button_status[0] = z64_file.button_items[0];
                    z64_file.button_items[0] = ITEM_FISHING_POLE;
                    z64_file.hud_visibility_mode = HUD_VISIBILITY_NO_CHANGE;
                    Interface_LoadItemIcon1(game, 0);
                    interface_change_hud_visibility_mode(HUD_VISIBILITY_A_B_MINIMAP);
                }
                if (z64_file.hud_visibility_mode != HUD_VISIBILITY_A_B_MINIMAP)
                    interface_change_hud_visibility_mode(HUD_VISIBILITY_A_B_MINIMAP);
            }
            else if (z64_file.button_items[0] == ITEM_FISHING_POLE) {
                z64_file.button_items[0] = z64_file.button_status[0];
                z64_file.hud_visibility_mode = HUD_VISIBILITY_NO_CHANGE;
                if (z64_file.button_items[0] != Z64_ITEM_NONE)
                    Interface_LoadItemIcon1(game, 0);
                z64_file.button_status[0] = z64_file.button_status[1] = z64_file.button_status[2] = z64_file.button_status[3] = BTN_DISABLED;
                interface_change_hud_visibility_mode(HUD_VISIBILITY_ALL);
            }
            else {
                if (z64_file.button_status[0] == BTN_ENABLED)
                    z64_file.hud_visibility_mode = HUD_VISIBILITY_NO_CHANGE;
                z64_file.button_status[0] = z64_file.button_status[1] = z64_file.button_status[2] = z64_file.button_status[3] = BTN_DISABLED;
                interface_change_hud_visibility_mode(HUD_VISIBILITY_ALL);
            }
        }
        
        else if (game->msgContext.msgMode == MSGMODE_NONE) {
            if ((Player_GetEnvironmentalHazard(game) >= PLAYER_ENV_HAZARD_UNDERWATER_FLOOR) && (Player_GetEnvironmentalHazard(game) <= PLAYER_ENV_HAZARD_UNDERWATER_FREE)) {
                if (z64_file.button_status[0] != BTN_DISABLED)
                    refresh_interface = true;
                z64_file.button_status[0] = BTN_DISABLED;
                
                for (i=1; i<4; i++) {
                    if (Player_GetEnvironmentalHazard(game) == PLAYER_ENV_HAZARD_UNDERWATER_FLOOR) {
                        if (z64_file.button_items[i] != Z64_ITEM_HOOKSHOT && z64_file.button_items[i] != Z64_ITEM_LONGSHOT) {
                            if (z64_file.button_status[i] == BTN_ENABLED)
                                refresh_interface = true;
                            z64_file.button_status[i] = BTN_DISABLED;
                        }
                        else {
                            if (z64_file.button_status[i] == BTN_DISABLED)
                                refresh_interface = true;
                            z64_file.button_status[i] = BTN_ENABLED;
                        }
                    }
                    else if (Player_GetEnvironmentalHazard(game) == PLAYER_ENV_HAZARD_SWIMMING && OPTION_ACTIVE(1, SAVE_MASK_ABILITIES, CFG_DEFAULT_MASK_ABILITIES)) {
                        if (z64_file.button_items[i] < Z64_ITEM_KEATON_MASK || z64_file.button_items[i] > Z64_ITEM_MASK_OF_TRUTH) {
                            if (z64_file.button_status[i] == BTN_ENABLED)
                                refresh_interface = true;
                            z64_file.button_status[i] = BTN_DISABLED;
                        }
                        else {
                            if (z64_file.button_status[i] == BTN_DISABLED)
                                refresh_interface = true;
                            z64_file.button_status[i] = BTN_ENABLED;
                        }
                    }
                    else {
                        if (z64_file.button_status[i] == BTN_ENABLED)
                            refresh_interface = true;
                        z64_file.button_status[i] = BTN_DISABLED;
                    }
                }
                
                if (refresh_interface)
                    z64_file.hud_visibility_mode = HUD_VISIBILITY_NO_CHANGE;
                interface_change_hud_visibility_mode(HUD_VISIBILITY_ALL);
            }
            
            else if ( (z64_link.state_flags_1 & PLAYER_STATE1_CLIMBING) || (z64_link.state_flags_2 & PLAYER_STATE2_CRAWLING) ) {
                if (z64_file.button_status[0] != BTN_DISABLED) {
                    z64_file.button_status[0] = z64_file.button_status[1] = z64_file.button_status[2] = z64_file.button_status[3] = BTN_DISABLED;
                    z64_file.hud_visibility_mode = HUD_VISIBILITY_NO_CHANGE;
                    interface_change_hud_visibility_mode(HUD_VISIBILITY_ALL);
                }
            }
            
            else if (GET_EVENTINF_INGO_RACE_STATE() == INGO_RACE_STATE_HORSE_RENTAL_PERIOD) {
                if (z64_link.state_flags_1 & PLAYER_STATE1_RIDING) {
                    if (z64_file.button_items[0] != Z64_ITEM_NONE && z64_file.button_items[0] != Z64_ITEM_BOW) {
                        if (z64_file.items[SLOT_BOW] == Z64_ITEM_NONE)
                            z64_file.button_items[0] = Z64_ITEM_NONE;
                        else {
                            z64_file.button_items[0] = Z64_ITEM_BOW;
                            refresh_interface = true;
                        }
                    }
                }
                else {
                    if (z64_file.button_items[0] == Z64_ITEM_NONE || z64_file.button_items[0] == Z64_ITEM_BOW) {
                        if (z64_file.button_items[0] != Z64_ITEM_KOKIRI_SWORD && z64_file.button_items[0] != Z64_ITEM_MASTER_SWORD && z64_file.button_items[0] != Z64_ITEM_BIGGORON_SWORD && z64_file.button_items[0] != Z64_ITEM_GIANTS_KNIFE)
                            z64_file.button_items[0] = z64_file.button_status[0];
                        else z64_file.button_status[0] = z64_file.button_items[0];
                    }
                    refresh_interface = true;
                }

                if (refresh_interface) {
                    Interface_LoadItemIcon1(game, 0);
                    refresh_interface = false;
                }

                for (i=1; i<4; i++) {
                    if (z64_file.button_items[i] != Z64_ITEM_FAIRY_OCARINA && z64_file.button_items[i] != Z64_ITEM_OCARINA_OF_TIME) {
                        if (z64_file.button_status[i] == BTN_ENABLED)
                            refresh_interface = true;
                        z64_file.button_status[i] = BTN_DISABLED;
                    }
                    else {
                        if (z64_file.button_status[i] == BTN_DISABLED)
                            refresh_interface = true;
                        z64_file.button_status[i] = BTN_ENABLED;
                    }
                }

                if (refresh_interface)
                    z64_file.hud_visibility_mode = HUD_VISIBILITY_NO_CHANGE;
                interface_change_hud_visibility_mode(HUD_VISIBILITY_ALL);
            }
            
            else {
                if (!z64_game.restriction_flags.b_button) {
                    if (z64_file.button_items[0] == Z64_ITEM_SLINGSHOT || z64_file.button_items[0] == ITEM_BOW || z64_file.button_items[0] == Z64_ITEM_BOMBCHU || z64_file.button_items[0] == Z64_ITEM_NONE) {
                        if (z64_file.button_items[0] != Z64_ITEM_NONE || z64_file.inf_table[INFTABLE_1DX_INDEX] == 0) {
                            z64_file.button_items[0] = z64_file.button_status[0];
                            refresh_interface = true;
                            if (z64_file.button_items[0] != Z64_ITEM_NONE)
                                Interface_LoadItemIcon1(game, 0);
                        }
                    }
                    else if ((z64_file.button_status[0] & 0xFF) == BTN_DISABLED) {
                        refresh_interface = true;
                        if ( (z64_file.button_status[0] & 0xFF) == BTN_DISABLED || (z64_file.button_status[0] & 0xFF) == BTN_ENABLED)
                            z64_file.button_status[0] = BTN_ENABLED;
                        else z64_file.button_items[0] = z64_file.button_status[0] & 0xFF;
                    }
                }
                else if (z64_game.restriction_flags.b_button) {
                    if (z64_file.button_items[0] == Z64_ITEM_SLINGSHOT || z64_file.button_items[0] == Z64_ITEM_BOW || z64_file.button_items[0] == Z64_ITEM_BOMBCHU || z64_file.button_items[0] == Z64_ITEM_NONE) {
                        if (z64_file.button_items[0] != Z64_ITEM_NONE || z64_file.inf_table[INFTABLE_1DX_INDEX] == 0) {
                            z64_file.button_items[0] = z64_file.button_status[0];
                            refresh_interface = true;
                            if (z64_file.button_items[0] != Z64_ITEM_NONE)
                                Interface_LoadItemIcon1(game, 0);
                        }
                    }
                    else {
                        if (z64_file.button_status[0] == BTN_ENABLED)
                            refresh_interface = true;
                        z64_file.button_status[0] = BTN_DISABLED;
                    }
                }
                
                // Define item groups
                z64_item_t bottle_items[]       = { Z64_ITEM_BOTTLE,        Z64_ITEM_POE             };
                z64_item_t trade_items[]        = { Z64_ITEM_WEIRD_EGG,     Z64_ITEM_CLAIM_CHECK     };
                z64_item_t hookshot_items[]     = { Z64_ITEM_HOOKSHOT,      Z64_ITEM_LONGSHOT        };
                z64_item_t ocarina_items[]      = { Z64_ITEM_FAIRY_OCARINA, Z64_ITEM_OCARINA_OF_TIME };
                z64_item_t dfnl_items[]         = { Z64_ITEM_DINS_FIRE,     Z64_ITEM_NAYRUS_LOVE     };
                z64_item_t farores_wind_items[] = { Z64_ITEM_FARORES_WIND                            };

                // Update restrictions
                update_button_status(z64_game.restriction_flags.bottles,      bottle_items,       ARRAY_SIZE(bottle_items)       );
                update_button_status(z64_game.restriction_flags.trade_items,  trade_items,        ARRAY_SIZE(trade_items)        );
                update_button_status(z64_game.restriction_flags.hookshot,     hookshot_items,     ARRAY_SIZE(hookshot_items)     );
                update_button_status(z64_game.restriction_flags.ocarina,      ocarina_items,      ARRAY_SIZE(ocarina_items)      );
                update_button_status(z64_game.restriction_flags.farores_wind, farores_wind_items, ARRAY_SIZE(farores_wind_items) );
                update_button_status(z64_game.restriction_flags.dfnl,         dfnl_items,         ARRAY_SIZE(dfnl_items)         );
                
                if (z64_game.restriction_flags.all) {
                    for (i=1; i<4; i++)
                        if (z64_file.button_items[i] != Z64_ITEM_FAIRY_OCARINA && z64_file.button_items[i] != Z64_ITEM_OCARINA_OF_TIME && !(z64_file.button_items[i] >= Z64_ITEM_BOTTLE && z64_file.button_items[i] <= Z64_ITEM_POE) && !(z64_file.button_items[i] >= Z64_ITEM_WEIRD_EGG && z64_file.button_items[i] <= Z64_ITEM_CLAIM_CHECK) ) {
                            if ((game->scene_index != SCENE_TREASURE_BOX_SHOP) || (z64_file.button_items[i] != Z64_ITEM_LENS)) {
                                if (z64_file.button_status[i] == BTN_ENABLED)
                                    refresh_interface = true;
                                z64_file.button_status[i] = BTN_DISABLED;
                            }
                            else {
                                if (z64_file.button_status[i] == BTN_DISABLED)
                                    refresh_interface = true;
                                z64_file.button_status[i] = BTN_ENABLED;
                            }
                        }
                }
                else if (!z64_game.restriction_flags.all) {
                    for (i=1; i<4; i++)
                        if (z64_file.button_items[i] != Z64_ITEM_DINS_FIRE && z64_file.button_items[i] != Z64_ITEM_HOOKSHOT && z64_file.button_items[i] != Z64_ITEM_LONGSHOT && z64_file.button_items[i] != Z64_ITEM_FARORES_WIND && z64_file.button_items[i] != ITEM_NAYRUS_LOVE && z64_file.button_items[i] != Z64_ITEM_FAIRY_OCARINA && z64_file.button_items[i] != Z64_ITEM_OCARINA_OF_TIME && !(z64_file.button_items[i] >= Z64_ITEM_BOTTLE && z64_file.button_items[i] <= Z64_ITEM_POE) && !(z64_file.button_items[i] >= Z64_ITEM_WEIRD_EGG && z64_file.button_items[i] <= Z64_ITEM_CLAIM_CHECK) ) {
                            if (z64_file.button_status[i] == BTN_DISABLED)
                                refresh_interface = true;
                            z64_file.button_status[i] = BTN_ENABLED;
                        }
                }
            }
        }
    }

    if (refresh_interface) {
        z64_file.hud_visibility_mode = HUD_VISIBILITY_NO_CHANGE;
        if ((game->scene_load_flag == TRANS_TRIGGER_OFF) && (game->transition_mode == TRANS_MODE_OFF))
            interface_change_hud_visibility_mode(HUD_VISIBILITY_ALL);
    }
}

void update_button_status(bool flag, z64_item_t items[], u8 size) {
    for (u8 i=1; i<4; i++)
        for (u8 j=0; j<size; j++)
            if (z64_file.button_items[i] == items[j]) {
                if (z64_file.button_status[i] == !flag)
                    refresh_interface = true;
                z64_file.button_status[i] = !flag;
                break;
            }
}*/

/*{ "Borrowed Keaton Mask",     ITEM,        ITEMGETINF_BORROWED_KEATON_MASK,         0                          },
    { "Borrowed Skull Mask",      ITEM,        ITEMGETINF_BORROWED_SKULL_MASK,          0                          },
    { "Borrowed Spooky Mask",     ITEM,        ITEMGETINF_BORROWED_SPOOKY_MASK,         0                          },
    { "Borrowed Bunny Hood",      ITEM,        ITEMGETINF_BORROWED_BUNNY_HOOD,          0                          },
    { "Sold Keaton Mask",         ITEM,        ITEMGETINF_SOLD_KEATON_MASK,             0                          },
    { "Sold Skull Mask",          ITEM,        ITEMGETINF_SOLD_SKULL_MASK,              0                          },
    { "Sold Spooky Mask",         ITEM,        ITEMGETINF_SOLD_SPOOKY_MASK,             0                          },
    { "Sold Bunny Hood",          ITEM,        ITEMGETINF_SOLD_BUNNY_HOOD,              0                          },
    { "Paid Back Keaton Mask",    EVENT,       EVENTCHKINF_PAID_BACK_KEATON_MASK,       0                          },
    { "Paid Back Skull Mask",     EVENT,       EVENTCHKINF_PAID_BACK_SKULL_MASK,        0                          },
    { "Paid Back Spooky Mask",    EVENT,       EVENTCHKINF_PAID_BACK_SPOOKY_MASK,       0                          },
    { "Paid Back Bunny Hood",     EVENT,       EVENTCHKINF_PAID_BACK_BUNNY_HOOD,        0                          },
    { "Other Masks Available",    ITEM,        ITEMGETINF_OTHER_MASKS_AVAILABLE,        0                          },
    { "Mask of Truth Loaned",     ITEM,        ITEMGETINF_MASK_OF_TRUTH_LOANED,         0                          },*/