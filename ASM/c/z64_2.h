#ifndef Z64_EXTENDED_H
#define Z64_EXTENDED_H

#include "z64.h"

#include <stdbool.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef float    f32;

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/* Important CFGs */
extern u8 CFG_WS;
extern u8 CFG_OPTIONS_MENU;

/* Default Options */
extern u8 CFG_DEFAULT_30_FPS;
extern u8 CFG_DEFAULT_ARROW_TOGGLE;
extern u8 CFG_DEFAULT_DPAD;
extern u8 CFG_DEFAULT_SHOW_DPAD;
extern u8 CFG_DEFAULT_HIDE_HUD;
extern u8 CFG_DEFAULT_HUD_LAYOUT;
extern u8 CFG_DEFAULT_SHOW_HEALTH;
extern u8 CFG_DEFAULT_SHOW_OVERLAY;
extern u8 CFG_DEFAULT_CHEST_CONTENTS;
extern u8 CFG_DEFAULT_A_BUTTON_SCALE;
extern u8 CFG_DEFAULT_B_BUTTON_SCALE;
extern u8 CFG_DEFAULT_C_LEFT_BUTTON_SCALE;
extern u8 CFG_DEFAULT_C_DOWN_BUTTON_SCALE;
extern u8 CFG_DEFAULT_C_RIGHT_BUTTON_SCALE;
extern u8 CFG_DEFAULT_INVERSE_AIM;
extern u8 CFG_DEFAULT_NO_IDLE_CAMERA;
extern u8 CFG_DEFAULT_KEEP_MASK;
extern u8 CFG_DEFAULT_TRISWIPE;
extern u8 CFG_DEFAULT_SWAP_ITEM;
extern u8 CFG_DEFAULT_UNEQUIP_GEAR;
extern u8 CFG_DEFAULT_ITEM_ON_B;
extern u8 CFG_DEFAULT_MASK_ABILITIES;
extern u8 CFG_DEFAULT_EXTRA_ABILITIES;
extern u8 CFG_DEFAULT_DAMAGE_TAKEN;
extern u8 CFG_DEFAULT_RANDOM_ENEMIES;
extern u8 CFG_DEFAULT_CROUCH_STAB_FIX;
extern u8 CFG_DEFAULT_WEAKER_SWORDS;
extern u8 CFG_DEFAULT_RUPEE_DRAIN;
extern u8 CFG_DEFAULT_FOG;
extern u8 CFG_DEFAULT_LEVITATION;
extern u8 CFG_DEFAULT_INFINITE_HP;
extern u8 CFG_DEFAULT_INFINITE_MP;
extern u8 CFG_DEFAULT_INFINITE_RUPEES;
extern u8 CFG_DEFAULT_INFINITE_AMMO;

typedef enum {
    OPTIONS_SIZE_CORE = 18,
    OPTIONS_SIZE_MAIN = 29,
    OPTIONS_SIZE_ALL  = 36,
    
    OPTION_30_FPS     = 0,
    OPTION_ARROW_TOGGLE,
    OPTION_DPAD,
    OPTION_SHOW_DPAD,
    OPTION_HIDE_HUD,
    OPTION_HUD_LAYOUT,
    OPTION_SHOW_HEALTH,
    OPTION_SHOW_OVERLAY,
    OPTION_CHEST_CONTENTS,
    OPTION_A_BUTTON_SCALE,
    OPTION_B_BUTTON_SCALE,
    OPTION_C_LEFT_BUTTON_SCALE,
    OPTION_C_DOWN_BUTTON_SCALE,
    OPTION_C_RIGHT_BUTTON_SCALE,
    OPTION_INVERSE_AIM,
    OPTION_NO_IDLE_CAMERA,
    OPTION_KEEP_MASK,
    OPTION_TRISWIPE,
    
    OPTION_SWAP_ITEM,
    OPTION_UNEQUIP_GEAR,
    OPTION_ITEM_ON_B,
    OPTION_MASK_ABILITIES,
    OPTION_EXTRA_ABILITIES,
    OPTION_DAMAGE_TAKEN,
    OPTION_RANDOM_ENEMIES,
    OPTION_CROUCH_STAB_FIX,
    OPTION_WEAKER_SWORDS,
    OPTION_RUPEE_DRAIN,
    
    OPTION_FOG,
    OPTION_ITEM_EDITOR,
    OPTION_MAP_SELECT,
    OPTION_LEVITATION,
    OPTION_INFINITE_HP,
    OPTION_INFINITE_MP,
    OPTION_INFINITE_RUPEES,
    OPTION_INFINITE_AMMO,
} option_t;

typedef enum {
    PLAYER_MASK_NONE,
    PLAYER_MASK_KEATON,
    PLAYER_MASK_SKULL,
    PLAYER_MASK_SPOOKY,
    PLAYER_MASK_BUNNY,
    PLAYER_MASK_GORON,
    PLAYER_MASK_ZORA,
    PLAYER_MASK_GERUDO,
    PLAYER_MASK_TRUTH,
    PLAYER_MASK_MAX
} z64_player_mask_t;

typedef enum {
    /* 0x01 */ CHEST_BOMBS_5 = 1,
    /* 0x02 */ CHEST_DEKU_NUTS,
    /* 0x03 */ CHEST_BOMBCHU_10,
    /* 0x04 */ CHEST_FAIRY_BOW,
    /* 0x05 */ CHEST_FAIRY_SLINGSHOT,
    /* 0x06 */ CHEST_BOOMERANG,
    /* 0x07 */ CHEST_DEKU_STICK_1,
    /* 0x08 */ CHEST_HOOKSHOT,
    /* 0x09 */ CHEST_LONGSHOT,
    /* 0x0A */ CHEST_LENS_OF_TRUTH,
    /* 0x0B */ CHEST_ZELDAS_LETTER,
    /* 0x0C */ CHEST_OCARINA_OF_TIME,
    /* 0x0D */ CHEST_MEGATON_HAMMER,
    /* 0x0E */ CHEST_COJIRO,
    /* 0x0F */ CHEST_EMPTY_BOTTLE,
    /* 0x10 */ CHEST_RED_POTION,
    /* 0x11 */ CHEST_GREEN_POTION,
    /* 0x12 */ CHEST_BLUE_POTION,
    /* 0x13 */ CHEST_FAIRY,
    /* 0x14 */ CHEST_LON_LON_MILK_FULL,
    /* 0x15 */ CHEST_RUTOS_LETTER,
    /* 0x16 */ CHEST_MAGIC_BEAN,
    /* 0x17 */ CHEST_SKULL_MASK,
    /* 0x18 */ CHEST_SPOOKY_MASK,
    /* 0x19 */ CHEST_CUCCO,
    /* 0x1A */ CHEST_KEATON_MASK,
    /* 0x1B */ CHEST_BUNNY_HOOD,
    /* 0x1C */ CHEST_MASK_OF_TRUTH,
    /* 0x1D */ CHEST_POCKET_EGG,
    /* 0x1E */ CHEST_POCKET_CUCCO,
    /* 0x1F */ CHEST_ODD_MUSHROOM,
    /* 0x20 */ CHEST_ODD_POTION,
    /* 0x21 */ CHEST_POACHERS_SAW,
    /* 0x22 */ CHEST_BROKEN_GORONS_SWORD,
    /* 0x23 */ CHEST_PRESCRIPTION,
    /* 0x24 */ CHEST_EYEBALL_FROG,
    /* 0x25 */ CHEST_EYE_DROPS,
    /* 0x26 */ CHEST_CLAIM_CHECK,
    /* 0x27 */ CHEST_KOKIRI_SWORD,
    /* 0x28 */ CHEST_GIANTS_KNIFE,
    /* 0x29 */ CHEST_DEKU_SHIELD,
    /* 0x2A */ CHEST_HYLIAN_SHIELD,
    /* 0x2B */ CHEST_MIRROR_SHIELD,
    /* 0x2C */ CHEST_GORON_TUNIC,
    /* 0x2D */ CHEST_ZORA_TUNIC,
    /* 0x2E */ CHEST_IRON_BOOTS,
    /* 0x2F */ CHEST_HOVER_BOOTS,
    /* 0x30 */ CHEST_QUIVER_40,
    /* 0x31 */ CHEST_QUIVER_50,
    /* 0x32 */ CHEST_BOMB_BAG_20,
    /* 0x33 */ CHEST_BOMB_BAG_30,
    /* 0x34 */ CHEST_BOMB_BAG_40,
    /* 0x35 */ CHEST_SILVER_GAUNTLETS,
    /* 0x36 */ CHEST_GOLDEN_GAUNTLETS,
    /* 0x37 */ CHEST_SILVER_SCALE,
    /* 0x38 */ CHEST_GOLDEN_SCALE,
    /* 0x39 */ CHEST_STONE_OF_AGONY,
    /* 0x3A */ CHEST_GERUDO_MEMBERSHIP_CARD,
    /* 0x3B */ CHEST_FAIRY_OCARINA,
    /* 0x3C */ CHEST_DEKU_SEEDS_5,
    /* 0x3D */ CHEST_HEART_CONTAINER,
    /* 0x3E */ CHEST_PIECE_OF_HEART,
    /* 0x3F */ CHEST_BOSS_KEY,
    /* 0x40 */ CHEST_COMPASS,
    /* 0x41 */ CHEST_DUNGEON_MAP,
    /* 0x42 */ CHEST_SMALL_KEY,
    /* 0x43 */ CHEST_SMALL_MAGIC_JAR,
    /* 0x44 */ CHEST_LARGE_MAGIC_JAR,
    /* 0x45 */ CHEST_ADULT_WALLET,
    /* 0x46 */ CHEST_GIANT_WALLET,
    /* 0x47 */ CHEST_WEIRD_EGG,
    /* 0x48 */ CHEST_RECOVERY_HEART,
    /* 0x49 */ CHEST_ARROWS_5,
    /* 0x4A */ CHEST_ARROWS_10,
    /* 0x4B */ CHEST_ARROWS_30,
    /* 0x4C */ CHEST_GREEN_RUPEE,
    /* 0x4D */ CHEST_BLUE_RUPEE,
    /* 0x4E */ CHEST_RED_RUPEE,
    /* 0x4F */ CHEST_HEART_CONTAINER_2,
    /* 0x50 */ CHEST_LON_LON_MILK,
    /* 0x51 */ CHEST_GORON_MASK,
    /* 0x52 */ CHEST_ZORA_MASK,
    /* 0x53 */ CHEST_GERUDO_MASK,
    /* 0x54 */ CHEST_GORONS_BRACELET,
    /* 0x55 */ CHEST_PURPLE_RUPEE,
    /* 0x56 */ CHEST_GOLD_RUPEE,
    /* 0x57 */ CHEST_BIGGORON_SWORD,
    /* 0x58 */ CHEST_FIRE_ARROW,
    /* 0x59 */ CHEST_ICE_ARROW,
    /* 0x5A */ CHEST_LIGHT_ARROW,
    /* 0x5B */ CHEST_GOLD_SKULLTULA_TOKEN,
    /* 0x5C */ CHEST_DINS_FIRE,
    /* 0x5D */ CHEST_FARORES_WIND,
    /* 0x5E */ CHEST_NAYRUS_LOVE,
    /* 0x5F */ CHEST_BULLET_BAG_30,
    /* 0x60 */ CHEST_BULLET_BAG_40,
    /* 0x61 */ CHEST_DEKU_STICKS_5,
    /* 0x62 */ CHEST_DEKU_STICK_10,
    /* 0x63 */ CHEST_DEKU_NUTS_5,
    /* 0x64 */ CHEST_DEKU_NUTS_10,
    /* 0x65 */ CHEST_BOMB,
    /* 0x66 */ CHEST_BOMBS_10,
    /* 0x67 */ CHEST_BOMBS_20,
    /* 0x68 */ CHEST_BOMBS_30,
    /* 0x69 */ CHEST_DEKU_SEEDS_30,
    /* 0x6A */ CHEST_BOMBCHU_5,
    /* 0x6B */ CHEST_BOMBCHU_20,
    /* 0x6C */ CHEST_FISH,
    /* 0x6D */ CHEST_BUG,
    /* 0x6E */ CHEST_BLUE_FIRE,
    /* 0x6F */ CHEST_POE,
    /* 0x70 */ CHEST_BIG_POE,
    /* 0x71 */ CHEST_DOOR_KEY,
    /* 0x72 */ CHEST_LOSER_GREEN_RUPEE,
    /* 0x73 */ CHEST_LOSER_BLUE_RUPEE,
    /* 0x74 */ CHEST_LOSER_RED_RUPEE,
    /* 0x75 */ CHEST_WINNER_PURPLE_RUPEE,
    /* 0x76 */ CHEST_WINNER_PIECE_OF_HEART,
    /* 0x77 */ CHEST_DEKU_STICK_UPGRADE_20,
    /* 0x78 */ CHEST_DEKU_STICK_UPGRADE_30,
    /* 0x79 */ CHEST_DEKU_NUT_UPGRADE_30,
    /* 0x7A */ CHEST_DEKU_NUT_UPGRADE_40,
    /* 0x7B */ CHEST_BULLET_BAG_50,
    /* 0x7C */ CHEST_ICE_TRAP,
} z64_chest_item_id_t;

typedef enum {
/* 0x00 */ SCENE_DEKU_TREE,
/* 0x01 */ SCENE_DODONGOS_CAVERN,
/* 0x02 */ SCENE_JABU_JABU,
/* 0x03 */ SCENE_FOREST_TEMPLE,
/* 0x04 */ SCENE_FIRE_TEMPLE,
/* 0x05 */ SCENE_WATER_TEMPLE,
/* 0x06 */ SCENE_SPIRIT_TEMPLE,
/* 0x07 */ SCENE_SHADOW_TEMPLE,
/* 0x08 */ SCENE_BOTTOM_OF_THE_WELL,
/* 0x09 */ SCENE_ICE_CAVERN,
/* 0x0A */ SCENE_GANONS_TOWER,
/* 0x0B */ SCENE_GERUDO_TRAINING_GROUND,
/* 0x0C */ SCENE_THIEVES_HIDEOUT,
/* 0x0D */ SCENE_INSIDE_GANONS_CASTLE,
/* 0x0E */ SCENE_GANONS_TOWER_COLLAPSE_INTERIOR,
/* 0x0F */ SCENE_INSIDE_GANONS_CASTLE_COLLAPSE,
/* 0x10 */ SCENE_TREASURE_BOX_SHOP,
/* 0x11 */ SCENE_DEKU_TREE_BOSS,
/* 0x12 */ SCENE_DODONGOS_CAVERN_BOSS,
/* 0x13 */ SCENE_JABU_JABU_BOSS,
/* 0x14 */ SCENE_FOREST_TEMPLE_BOSS,
/* 0x15 */ SCENE_FIRE_TEMPLE_BOSS,
/* 0x16 */ SCENE_WATER_TEMPLE_BOSS,
/* 0x17 */ SCENE_SPIRIT_TEMPLE_BOSS,
/* 0x18 */ SCENE_SHADOW_TEMPLE_BOSS,
/* 0x19 */ SCENE_GANONDORF_BOSS,
/* 0x1A */ SCENE_GANONS_TOWER_COLLAPSE_EXTERIOR,
/* 0x1B */ SCENE_MARKET_ENTRANCE_DAY,
/* 0x1C */ SCENE_MARKET_ENTRANCE_NIGHT,
/* 0x1D */ SCENE_MARKET_ENTRANCE_RUINS,
/* 0x1E */ SCENE_BACK_ALLEY_DAY,
/* 0x1F */ SCENE_BACK_ALLEY_NIGHT,
/* 0x20 */ SCENE_MARKET_DAY,
/* 0x21 */ SCENE_MARKET_NIGHT,
/* 0x22 */ SCENE_MARKET_RUINS,
/* 0x23 */ SCENE_TEMPLE_OF_TIME_EXTERIOR_DAY,
/* 0x24 */ SCENE_TEMPLE_OF_TIME_EXTERIOR_NIGHT,
/* 0x25 */ SCENE_TEMPLE_OF_TIME_EXTERIOR_RUINS,
/* 0x26 */ SCENE_KNOW_IT_ALL_BROS_HOUSE,
/* 0x27 */ SCENE_TWINS_HOUSE,
/* 0x28 */ SCENE_MIDOS_HOUSE,
/* 0x29 */ SCENE_SARIAS_HOUSE,
/* 0x2A */ SCENE_KAKARIKO_CENTER_GUEST_HOUSE,
/* 0x2B */ SCENE_BACK_ALLEY_HOUSE,
/* 0x2C */ SCENE_BAZAAR,
/* 0x2D */ SCENE_KOKIRI_SHOP,
/* 0x2E */ SCENE_GORON_SHOP,
/* 0x2F */ SCENE_ZORA_SHOP,
/* 0x30 */ SCENE_POTION_SHOP_KAKARIKO,
/* 0x31 */ SCENE_POTION_SHOP_MARKET,
/* 0x32 */ SCENE_BOMBCHU_SHOP,
/* 0x33 */ SCENE_HAPPY_MASK_SHOP,
/* 0x34 */ SCENE_LINKS_HOUSE,
/* 0x35 */ SCENE_DOG_LADY_HOUSE,
/* 0x36 */ SCENE_STABLE,
/* 0x37 */ SCENE_IMPAS_HOUSE,
/* 0x38 */ SCENE_LAKESIDE_LABORATORY,
/* 0x39 */ SCENE_CARPENTERS_TENT,
/* 0x3A */ SCENE_GRAVEKEEPERS_HUT,
/* 0x3B */ SCENE_GREAT_FAIRYS_FOUNTAIN_MAGIC,
/* 0x3C */ SCENE_FAIRYS_FOUNTAIN,
/* 0x3D */ SCENE_GREAT_FAIRYS_FOUNTAIN_SPELLS,
/* 0x3E */ SCENE_GROTTOS,
/* 0x3F */ SCENE_REDEAD_GRAVE,
/* 0x40 */ SCENE_GRAVE_WITH_FAIRYS_FOUNTAIN,
/* 0x41 */ SCENE_ROYAL_FAMILYS_TOMB,
/* 0x42 */ SCENE_SHOOTING_GALLERY,
/* 0x43 */ SCENE_TEMPLE_OF_TIME,
/* 0x44 */ SCENE_CHAMBER_OF_THE_SAGES,
/* 0x45 */ SCENE_CASTLE_COURTYARD_GUARDS_DAY,
/* 0x46 */ SCENE_CASTLE_COURTYARD_GUARDS_NIGHT,
/* 0x47 */ SCENE_CUTSCENE_MAP,
/* 0x48 */ SCENE_WINDMILL_AND_DAMPES_GRAVE,
/* 0x49 */ SCENE_FISHING_POND,
/* 0x4A */ SCENE_CASTLE_COURTYARD_ZELDA,
/* 0x4B */ SCENE_BOMBCHU_BOWLING_ALLEY,
/* 0x4C */ SCENE_LON_LON_BUILDINGS,
/* 0x4D */ SCENE_MARKET_GUARD_HOUSE,
/* 0x4E */ SCENE_POTION_SHOP_GRANNY,
/* 0x4F */ SCENE_GANON_BOSS,
/* 0x50 */ SCENE_HOUSE_OF_SKULLTULA,
/* 0x51 */ SCENE_HYRULE_FIELD,
/* 0x52 */ SCENE_KAKARIKO_VILLAGE,
/* 0x53 */ SCENE_GRAVEYARD,
/* 0x54 */ SCENE_ZORAS_RIVER,
/* 0x55 */ SCENE_KOKIRI_FOREST,
/* 0x56 */ SCENE_SACRED_FOREST_MEADOW,
/* 0x57 */ SCENE_LAKE_HYLIA,
/* 0x58 */ SCENE_ZORAS_DOMAIN,
/* 0x59 */ SCENE_ZORAS_FOUNTAIN,
/* 0x5A */ SCENE_GERUDO_VALLEY,
/* 0x5B */ SCENE_LOST_WOODS,
/* 0x5C */ SCENE_DESERT_COLOSSUS,
/* 0x5D */ SCENE_GERUDOS_FORTRESS,
/* 0x5E */ SCENE_HAUNTED_WASTELAND,
/* 0x5F */ SCENE_HYRULE_CASTLE,
/* 0x60 */ SCENE_DEATH_MOUNTAIN_TRAIL,
/* 0x61 */ SCENE_DEATH_MOUNTAIN_CRATER,
/* 0x62 */ SCENE_GORON_CITY,
/* 0x63 */ SCENE_LON_LON_RANCH,
/* 0x64 */ SCENE_OUTSIDE_GANONS_CASTLE,
} z64_scene_id_t;

typedef enum RoomBehaviorType1 {
    /* 0 */ ROOM_BEHAVIOR_TYPE1_0,
    /* 1 */ ROOM_BEHAVIOR_TYPE1_1,
    /* 2 */ ROOM_BEHAVIOR_TYPE1_2,
    /* 3 */ ROOM_BEHAVIOR_TYPE1_3, // unused
    /* 4 */ ROOM_BEHAVIOR_TYPE1_4, // unused
    /* 5 */ ROOM_BEHAVIOR_TYPE1_5
} z64_room_behavior_type_1;

typedef enum {
    B_BUTTON,
    C_LEFT_BUTTON,
    C_DOWN_BUTTON,
    C_RIGHT_BUTTON,
} z64_item_button_t;

typedef enum ButtonStatus {
    BTN_ENABLED,
    BTN_DISABLED = 0xFF
} z64_button_status_t;

typedef struct {
    u8 item[0x002C];
} z64_usability_t;

typedef struct {
    u16 quiver[4];        // 0,  30,  40,  50
    u16 bomb_bag[4];      // 0,  20,  30,  40
    u16 u1[8];            // Unused
    u16 wallet[4];        // 99, 200, 500, 500
    u16 bullet_bag[4];    // 0,  30,  40,  50
    u16 stick_upgrade[4]; // 0,  20,  30,  40
    u16 nut_upgrade[4];   // 0,  10,  20,  30
} z64_capacity_t;

typedef enum {
    HUD_VISIBILITY_NO_CHANGE       = 0,
    HUD_VISIBILITY_NOTHING,
    HUD_VISIBILITY_NOTHING_ALT,
    HUD_VISIBILITY_HEARTS_FORCE,
    HUD_VISIBILITY_A,
    HUD_VISIBILITY_A_HEARTS_MAGIC_FORCE,
    HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP_FORCE,
    HUD_VISIBILITY_ALL_NO_MINIMAP_BY_BTN_STATUS,
    HUD_VISIBILITY_B,
    HUD_VISIBILITY_HEARTS_MAGIC,
    HUD_VISIBILITY_B_ALT,
    HUD_VISIBILITY_HEARTS,
    HUD_VISIBILITY_A_B_MINIMAP,
    HUD_VISIBILITY_HEARTS_MAGIC_FORCE,
    HUD_VISIBILITY_ALL             = 50,
    HUD_VISIBILITY_NOTHING_INSTANT = 52
} z64_hud_visibility_mode_t;

/* DRAM addresses & data */
#define z64_usability                   (*(z64_usability_t*)    0x8039F114)
#define z64_capacity                    (*(z64_capacity_t*)     0x800F8CCC)
//#define z64_change_scene              (*(u32*)                0x801DB09C)
#define z64_has_minimap                 (*(u16*)                0x8018884C) // 0x8011B9B3, 8017643C, 8018884C
#define z64_dungeon_scene               (*(u16*)                0x801D8BEA)
#define z64_scene                       (*(u16*)                0x801C8544)
#define z64_camera_view                 (*(u8*)                 0x801DB0CD)
//#define z64_mask_equipped             (*(u8*)                 0x801DAB7F)
#define z64_throwing_nut                (*(u8*)                 0x80124696)
#define z64_triswipe                    (*(u8*)                 0x8011B9ED)
#define z64_x_axis_input                (*(s8*)                 0x801C84C8)
#define z64_y_axis_input                (*(s8*)                 0x801C84C9)
#define z64_button_input                (*(s16*)                0x801C84C0) // 801C84B4, 801C84BA, 801C84C6
#define z64_link_animation_parameter    (*(u16*)                0x801DABF0)
#define z64_link_a_action               (*(u16*)                0x801DAA90)
#define z64_idle_camera_counter         (*(u8*)                 0x801C86CF)
#define z64_inventory_editor_index      (*(u8*)                 0x8039EA59)
#define z64_damage_taken_modifier_1     (*(u32*)                0x8038E5D0)
#define z64_damage_taken_modifier_2     (*(u32*)                0x8038E5D8)
#define z64_damage_taken_modifier_3     (*(u16*)                0x8038E5EA)
#define z64_textbox                     (*(u16*)                0x801D8870)
#define z64_check_lava_floor            (*(u16*)                0x8038EBE4)
#define z64_check_lava_trail_1          (*(u8*)                 0x8007A6F7)
#define z64_check_lava_trail_2          (*(u8*)                 0x8007A6FF)
#define z64_check_wall_damage           (*(u32*)                0x800347EC)
#define z64_check_freeze                (*(u16*)                0x8038E760)
#define z64_check_shock                 (*(u16*)                0x8038E7C8)

/* DRAM addresses & data for FPS */
#define fps_limit                       (*(u8*)                 0x801C6FA1)
#define control_link                    (*(u16*)                0x801DAADE)

/* DRAM addresses & data for Medallion Abilities */
#define z64_tunic_color                 (*(u8*)                 0x801DAB6C)
#define z64_move_speed                  (*(u16*)                0x801DB258)
#define z64_max_move_speed              (*(u16*)                0x801DB2A0)
#define z64_damage_frames               (*(u8*)                 0x801DB498)
#define z64_damage_flag_1               (*(u32*)                0x801DAF1C)
#define z64_damage_flag_2               (*(u32*)                0x801DAF9C)
#define z64_inner_red_trail_r           (*(u8*)                 0x80273794)
#define z64_inner_red_trail_g           (*(u8*)                 0x80273795)
#define z64_inner_red_trail_b           (*(u8*)                 0x80273796)
#define z64_outer_red_trail_r           (*(u8*)                 0x802738B4)
#define z64_outer_red_trail_g           (*(u8*)                 0x802738B5)
#define z64_outer_red_trail_b           (*(u8*)                 0x802738B6)

/* Options */
#define OPTION_ACTIVE(menu, save, default)       ( (CFG_OPTIONS_MENU >= menu && save)          || (CFG_OPTIONS_MENU < menu && default)          )
#define OPTION_VALUE(menu, value, save, default) ( (CFG_OPTIONS_MENU >= menu && save == value) || (CFG_OPTIONS_MENU < menu && default == value) )
#define IS_MASK_COMPLETED(paid_back, sold)       (GET_EVENTCHKINF(paid_back) && GET_ITEMGETINF(sold) )

/* Availability */
#define HAS_MAGIC                       (z64_file.magic_acquired && z64_file.magic_capacity_set)
#define CAN_CONTROL_LINK                (z64_game.pause_ctxt.state == PAUSE_STATE_OFF && (u32)z64_ctxt.state_dtor == z64_state_ovl_tab[3].vram_dtor && z64_file.game_mode == 0 && (z64_event_state_1 & 0x20) == 0)
#define IS_PAUSE_SCREEN_CURSOR          (z64_game.pause_ctxt.state == PAUSE_STATE_MAIN && z64_game.pause_ctxt.debugState == 0 && z64_game.pause_ctxt.cursorSpecialPos != 0xA && z64_game.pause_ctxt.cursorSpecialPos != 0xB)
#define TYCOON_WALLET                   (z64_file.event_chk_inf[13] & (1 << 13) )

/* D-Pad & Controls Availability */
#define BLOCK_DPAD                      (PLAYER_STATE1_EXITING | PLAYER_STATE1_SWINGING_BOTTLE | PLAYER_STATE1_DEATH | PLAYER_STATE1_OPENING_CHEST | PLAYER_STATE1_PLAYING_OCARINA | PLAYER_STATE1_NO_CONTROL)
#define CAN_USE_DPAD                    ( (z64_link.state_flags_1 & BLOCK_DPAD) == 0 && (u32)z64_ctxt.state_dtor == z64_state_ovl_tab[3].vram_dtor && z64_file.game_mode == 0 && (z64_event_state_1 & 0x20) == 0)
#define CAN_DRAW_HUD                    ( ( (u32)z64_ctxt.state_dtor==z64_state_ovl_tab[3].vram_dtor) && (z64_file.game_mode == 0) )
#define CAN_USE_SWAP(index)             (IS_PAUSE_SCREEN_CURSOR && (z64_game.pause_ctxt.mainState == 0 || z64_game.pause_ctxt.mainState == 3) && z64_game.pause_ctxt.pageIndex == index)
#define CAN_USE_MASK_SWAP               (CAN_USE_SWAP(0) && z64_game.pause_ctxt.cursorPoint[PAUSE_ITEM]  == Z64_SLOT_CHILD_TRADE && OPTION_ACTIVE(2, SAVE_SWAP_ITEM, CFG_DEFAULT_SWAP_ITEM) && GET_INFTABLE(INFTABLE_GIVEN_ZELDAS_LETTER) && \
                                        z64_file.items[Z64_SLOT_CHILD_TRADE] >= Z64_ITEM_KEATON_MASK && z64_file.items[Z64_SLOT_CHILD_TRADE] <= Z64_ITEM_MASK_OF_TRUTH) 
#define CAN_USE_OCARINA_SWAP            (CAN_USE_SWAP(0) && z64_game.pause_ctxt.cursorPoint[PAUSE_ITEM]  == Z64_SLOT_OCARINA  && OPTION_ACTIVE(2, SAVE_SWAP_ITEM, CFG_DEFAULT_SWAP_ITEM) && DOWNGRADE_OCARINA)
#define CAN_USE_HOOKSHOT_SWAP           (CAN_USE_SWAP(0) && z64_game.pause_ctxt.cursorPoint[PAUSE_ITEM]  == Z64_SLOT_HOOKSHOT && OPTION_ACTIVE(2, SAVE_SWAP_ITEM, CFG_DEFAULT_SWAP_ITEM) && DOWNGRADE_HOOKSHOT)
#define CAN_USE_GIANTS_KNIFE_SWAP       (CAN_USE_SWAP(3) && z64_game.pause_ctxt.cursorPoint[PAUSE_EQUIP] == 3 && OPTION_ACTIVE(2, SAVE_SWAP_ITEM, CFG_DEFAULT_SWAP_ITEM) && DOWNGRADE_GIANTS_KNIFE)

/* D-Pad SRAM locations & Button Mappings */
#define DPAD_BUTTON_INDEX(index)        ( (z64_file.link_age ? 0 : 8) + (GET_DPAD_ALT ? 4 : 0) + index)
#define DPAD_SET_BUTTON(index)          (z64_file.dpad_item_slots[index])
#define DPAD_SET_BUTTON_INDEX(index)    (z64_file.dpad_item_slots[DPAD_BUTTON_INDEX(index)])

/* Extra saving for Redux Options (8011B4C8) */
#define DPAD_INIT_SETUP                 ( (z64_file.inf_table[0x15] & 0x0001) >> 0)
#define DOWNGRADE_GIANTS_KNIFE          ( (z64_file.inf_table[0x15] & 0x0002) >> 1)
#define DOWNGRADE_OCARINA               ( (z64_file.inf_table[0x15] & 0x0004) >> 2)
#define DOWNGRADE_HOOKSHOT              ( (z64_file.inf_table[0x15] & 0x0008) >> 3)

#define SAVE_MASK_ABILITIES             ( (z64_file.inf_table[0x13] & 0x0001) >> 0)

#define SAVE_CROUCH_STAB_FIX            ( (z64_file.inf_table[0x14] & 0x0100) >> 8)
#define SAVE_WEAKER_SWORDS              ( (z64_file.inf_table[0x14] & 0x0200) >> 9)
#define SAVE_EXTRA_ABILITIES            ( (z64_file.inf_table[0x14] & 0x0400) >> 10)
#define SAVE_LEVITATION                 ( (z64_file.inf_table[0x14] & 0x0800) >> 11)
#define SAVE_INFINITE_HP                ( (z64_file.inf_table[0x14] & 0x1000) >> 12)
#define SAVE_INFINITE_MP                ( (z64_file.inf_table[0x14] & 0x2000) >> 13)
#define SAVE_INFINITE_RUPEES            ( (z64_file.inf_table[0x14] & 0x4000) >> 14)
#define SAVE_INFINITE_AMMO              ( (z64_file.inf_table[0x14] & 0x8000) >> 15)

#define SAVE_30_FPS                     ( (z64_file.inf_table[0x15] & 0x0010) >> 4)
#define SAVE_ARROW_TOGGLE               ( (z64_file.inf_table[0x15] & 0x0020) >> 5)
#define SAVE_SHOW_HEALTH                ( (z64_file.inf_table[0x15] & 0x0040) >> 6)
#define SAVE_SHOW_OVERLAY               ( (z64_file.inf_table[0x15] & 0x1000) >> 12)
#define SAVE_CHEST_CONTENTS             ( (z64_file.inf_table[0x15] & 0x0080) >> 7)
#define SAVE_INVERSE_AIM                ( (z64_file.inf_table[0x15] & 0x0100) >> 8)
#define SAVE_NO_IDLE_CAMERA             ( (z64_file.inf_table[0x15] & 0x0200) >> 9)
#define SAVE_KEEP_MASK                  ( (z64_file.inf_table[0x15] & 0x0400) >> 10)
#define SAVE_TRISWIPE                   ( (z64_file.inf_table[0x15] & 0x0800) >> 11)
#define SAVE_UNEQUIP_GEAR               ( (z64_file.inf_table[0x15] & 0x2000) >> 13)
#define SAVE_ITEM_ON_B                  ( (z64_file.inf_table[0x15] & 0x4000) >> 14)
#define SAVE_SWAP_ITEM                  ( (z64_file.inf_table[0x15] & 0x8000) >> 15)

#define SAVE_RUPEE_DRAIN                ( (z64_file.inf_table[0x18] & 0x000F) >> 0)  // Options: 15
#define SAVE_FOG                        ( (z64_file.inf_table[0x18] & 0x00F0) >> 4)  // Options: 15

#define SAVE_DPAD                       ( (z64_file.inf_table[0x1B] & 0x0003) >> 0)  // Options: 2
#define SAVE_SHOW_DPAD                  ( (z64_file.inf_table[0x1B] & 0x000C) >> 2)  // Options: 3
#define SAVE_HIDE_HUD                   ( (z64_file.inf_table[0x1B] & 0x0070) >> 4)  // Options: 4
#define SAVE_HUD_LAYOUT                 ( (z64_file.inf_table[0x1B] & 0x0380) >> 7)  // Options: 6
#define SAVE_A_BUTTON_SCALE             ( (z64_file.inf_table[0x1B] & 0x0C00) >> 10) // Options: 2
#define SAVE_B_BUTTON_SCALE             ( (z64_file.inf_table[0x1B] & 0x7000) >> 12) // Options: 7
#define SAVE_RANDOM_ENEMIES             ( (z64_file.inf_table[0x1B] & 0x8000) >> 15) // Options: 1

#define SAVE_C_LEFT_BUTTON_SCALE        ( (z64_file.inf_table[0x1C] & 0x0007) >> 0)  // Options: 7
#define SAVE_C_DOWN_BUTTON_SCALE        ( (z64_file.inf_table[0x1C] & 0x0070) >> 4)  // Options: 7
#define SAVE_C_RIGHT_BUTTON_SCALE       ( (z64_file.inf_table[0x1C] & 0x0700) >> 8)  // Options: 7
#define SAVE_DAMAGE_TAKEN               ( (z64_file.inf_table[0x1C] & 0x7000) >> 12) // Options: 7

/* Extra Saving for Redux */
#define LAST_MASK                       ( z64_file.unk_06_[z64_file.link_age] )
#define SET_DPAD_ALT_                   ( SET_INFTABLE(INFTABLE_02) )
#define CLEAR_DPAD_ALT                  ( CLEAR_INFTABLE(INFTABLE_02) )
#define GET_DPAD_ALT                    ( (OPTION_VALUE(1, 2, SAVE_DPAD, CFG_DEFAULT_DPAD) ) ? GET_INFTABLE(INFTABLE_02) : 0)
#define TOGGLE_DPAD_ALT                 ( GET_INFTABLE(INFTABLE_02) ?  CLEAR_INFTABLE(INFTABLE_02) : SET_INFTABLE(INFTABLE_02) )

/* Keeping track of values */
#define A_BUTTON_SCALE                  (*(u16*)           0x80074F76)
#define A_BUTTON_TEXT_SCALE             (*(u16*)           0x8007650E)
#define MAX_SWORD_HEALTH                (*(u8*)            0x8038E1A3)
#define SWORD_HEALTH                    (*(u8*)            0x8011B4F8) // 0x30

#define MP_FIRE_ARROW                   (*(u8*)            0x803AAC00)
#define MP_ICE_ARROW                    (*(u8*)            0x803AAC01)
#define MP_LIGHT_ARROW                  (*(u8*)            0x803AAC02)

/* Player States */
#define PLAYER_STATE1_EXITING                   (1 << 0)
#define PLAYER_STATE1_SWINGING_BOTTLE           (1 << 1)
#define PLAYER_STATE1_2                         (1 << 2)
#define PLAYER_STATE1_HOLDING_RANGED            (1 << 3)
#define PLAYER_STATE1_HAS_TARGET                (1 << 4)
#define PLAYER_STATE1_5                         (1 << 5)
#define PLAYER_STATE1_TALKING_1                 (1 << 6)
#define PLAYER_STATE1_DEATH                     (1 << 7)
#define PLAYER_STATE1_START_CHANGING_HELD_ITEM  (1 << 8)
#define PLAYER_STATE1_AIMING                    (1 << 9)
#define PLAYER_STATE1_OPENING_CHEST             (1 << 10)
#define PLAYER_STATE1_HOLDING_ABOVE_HEAD        (1 << 11)
#define PLAYER_STATE1_12                        (1 << 12)
#define PLAYER_STATE1_HANGING                   (1 << 13)
#define PLAYER_STATE1_FINISHED_CLIMBING_1       (1 << 14)
#define PLAYER_STATE1_HOLDING_Z                 (1 << 15)
#define PLAYER_STATE1_TALKING_2                 (1 << 16)
#define PLAYER_STATE1_FIXED_MOVEMENT            (1 << 17)
#define PLAYER_STATE1_JUMPING                   (1 << 18)
#define PLAYER_STATE1_FINISHED_CLIMBING_2       (1 << 19)
#define PLAYER_STATE1_FIRST_PERSON              (1 << 20)
#define PLAYER_STATE1_CLIMBING                  (1 << 21)
#define PLAYER_STATE1_SHIELDING                 (1 << 22)
#define PLAYER_STATE1_RIDING                    (1 << 23)
#define PLAYER_STATE1_USING_BOOMERANG           (1 << 24)
#define PLAYER_STATE1_BOOMERANG_THROWN          (1 << 25)
#define PLAYER_STATE1_DAMAGED                   (1 << 26)
#define PLAYER_STATE1_SWIMMING                  (1 << 27)
#define PLAYER_STATE1_PLAYING_OCARINA           (1 << 28)
#define PLAYER_STATE1_NO_CONTROL                (1 << 29)
#define PLAYER_STATE1_30                        (1 << 30)
#define PLAYER_STATE1_31                        (1 << 31)

#define PLAYER_STATE2_0                         (1 << 0)
#define PLAYER_STATE2_1                         (1 << 1)
#define PLAYER_STATE2_2                         (1 << 2)
#define PLAYER_STATE2_PULLING_ITEM              (1 << 3)
#define PLAYER_STATE2_4                         (1 << 4)
#define PLAYER_STATE2_MOVING                    (1 << 5)
#define PLAYER_STATE2_HANGING                   (1 << 6)
#define PLAYER_STATE2_7                         (1 << 7)
#define PLAYER_STATE2_8                         (1 << 8)
#define PLAYER_STATE2_FORCE_SAND_FLOOR_SOUND    (1 << 9)
#define PLAYER_STATE2_10                        (1 << 10)
#define PLAYER_STATE2_11                        (1 << 11)
#define PLAYER_STATE2_IDLE_ON_LADDER            (1 << 12)
#define PLAYER_STATE2_13                        (1 << 13)
#define PLAYER_STATE2_14                        (1 << 14)
#define PLAYER_STATE2_15                        (1 << 15)
#define PLAYER_STATE2_DO_ACTION_ENTER           (1 << 16) // Turns on the "Enter On A" DoAction
#define PLAYER_STATE2_17                        (1 << 17)
#define PLAYER_STATE2_CRAWLING                  (1 << 18) // Crawling through a crawlspace
#define PLAYER_STATE2_JUMPING                   (1 << 19)
#define PLAYER_STATE2_NAVI_PRESENT              (1 << 20)
#define PLAYER_STATE2_21                        (1 << 21)
#define PLAYER_STATE2_22                        (1 << 22)
#define PLAYER_STATE2_23                        (1 << 23)
#define PLAYER_STATE2_24                        (1 << 24)
#define PLAYER_STATE2_25                        (1 << 25)
#define PLAYER_STATE2_26                        (1 << 26)
#define PLAYER_STATE2_PLAYING_OCARINA           (1 << 27)
#define PLAYER_STATE2_IDLE                      (1 << 28)
#define PLAYER_STATE2_29                        (1 << 29)
#define PLAYER_STATE2_30                        (1 << 30)
#define PLAYER_STATE2_31                        (1 << 31)

#endif