#ifndef Z64_H
#define Z64_H
#include <stdint.h>
#include <n64.h>
#include "z64_2.h"
#include "z64_math.h"
#include "color.h"
#include "z64collision_check.h"

#define Z64_OOT10             0x00
#define Z64_OOT11             0x01
#define Z64_OOT12             0x02

#define Z64_SCREEN_WIDTH      320
#define Z64_SCREEN_HEIGHT     240

#define Z64_SEG_PHYS          0x00
#define Z64_SEG_TITLE         0x01
#define Z64_SEG_SCENE         0x02
#define Z64_SEG_ROOM          0x03
#define Z64_SEG_KEEP          0x04
#define Z64_SEG_SKEEP         0x05
#define Z64_SEG_OBJ           0x06
#define Z64_SEG_ZIMG          0x0E
#define Z64_SEG_CIMG          0x0F

#define Z64_ETAB_LENGTH       0x0614

#define NA_BGM_SMALL_ITEM_GET    0x39
#define NA_SE_SY_GET_RUPY        0x4803
#define NA_SE_SY_GET_ITEM        0x4824
#define NA_SE_SY_DECIDE          0x4808
#define NA_SE_SY_CURSOR          0x4809
#define NA_SE_SY_CANCEL          0x480A
#define NA_SE_SY_FSEL_CURSOR     0x4839
#define NA_SE_SY_FSEL_DECIDE_S   0x483A
#define NA_SE_SY_FSEL_DECIDE_L   0x483B
#define NA_SE_SY_FSEL_CLOSE      0x483C

#define FONT_CHAR_TEX_SIZE          ((16 * 16) / 2)
#define OFFSETOF(structure, member) ((size_t)&(((structure *)0)->member))

#define REG_PAGES                  6
#define REGS_PER_PAGE              16
#define REGS_PER_GROUP             (REG_PAGES * REGS_PER_PAGE)
#define REG_EDITOR_DATA            ((int16_t *)0x801C6EA4)
#define BASE_REG(n, r)             REG_EDITOR_DATA[(n)*REGS_PER_GROUP + (r)]
#define REG(r)                     BASE_REG(0, (r))
#define SREG(r)                    BASE_REG(1, (r))
#define R_PAUSE_BG_PRERENDER_STATE SREG(94)

typedef struct {
  uint16_t    type;
  struct {
    uint16_t  unk_00_ : 3;
    uint16_t  va      : 13;
  };
  struct {
    uint16_t  unk_01_ : 3;
    uint16_t  vb      : 13;
  };
  uint16_t    vc;
  z64_xyz_t   norm;
  int16_t     dist;
} z64_col_poly_t;

typedef struct {
  struct {
    uint32_t  unk_00_     : 1;
    uint32_t  drop        : 1; /* link drops one unit into the floor */
    uint32_t  special     : 4;
    uint32_t  interaction : 5;
    uint32_t  unk_01_     : 3;
    uint32_t  behavior    : 5;
    uint32_t  exit        : 5;
    uint32_t  camera      : 8;
  } flags_1;                    /* 0x0000 */
  struct {
    uint32_t  pad_00_     : 4;
    uint32_t  wall_damage : 1;
    uint32_t  unk_00_     : 6;
    uint32_t  unk_01_     : 3;
    uint32_t  hookshot    : 1;
    uint32_t  echo        : 6;
    uint32_t  unk_02_     : 5;
    uint32_t  terrain     : 2;
    uint32_t  material    : 4;
  } flags_2;                    /* 0x0004 */
} z64_col_type_t;

typedef struct {
  z64_xyz_t pos;
  z64_xyz_t rot;
  int16_t   fov;
  int16_t   unk_00_;
} z64_camera_params_t;

typedef struct {
  uint16_t mode;
  uint16_t unk_01_;
  uint32_t seg_params; /* segment address of z64_camera_params_t */
} z64_camera_t;

typedef struct {
  z64_xyz_t     pos;
  int16_t       width;
  int16_t       depth;
  struct {
    uint32_t    unk_00_ : 12;
    uint32_t    active  : 1;
    uint32_t    group   : 6; /* ? */
    uint32_t    unk_01_ : 5;
    uint32_t    camera  : 8;
  } flags;
} z64_col_water_t;

typedef struct {
  z64_xyz_t         min;
  z64_xyz_t         max;
  uint16_t          n_vtx;
  z64_xyz_t        *vtx;
  uint16_t          n_poly;
  z64_col_poly_t   *poly;
  z64_col_type_t   *type;
  z64_camera_t     *camera;
  uint16_t          n_water;
  z64_col_water_t  *water;
} z64_col_hdr_t;

typedef enum {
  Z64_ITEM_STICK,
  Z64_ITEM_NUT,
  Z64_ITEM_BOMB,
  Z64_ITEM_BOW,
  Z64_ITEM_FIRE_ARROW,
  Z64_ITEM_DINS_FIRE,
  Z64_ITEM_SLINGSHOT,
  Z64_ITEM_FAIRY_OCARINA,
  Z64_ITEM_OCARINA_OF_TIME,
  Z64_ITEM_BOMBCHU,
  Z64_ITEM_HOOKSHOT,
  Z64_ITEM_LONGSHOT,
  Z64_ITEM_ICE_ARROW,
  Z64_ITEM_FARORES_WIND,
  Z64_ITEM_BOOMERANG,
  Z64_ITEM_LENS,
  Z64_ITEM_BEANS,
  Z64_ITEM_HAMMER,
  Z64_ITEM_LIGHT_ARROW,
  Z64_ITEM_NAYRUS_LOVE,
  Z64_ITEM_BOTTLE,
  Z64_ITEM_RED_POTION,
  Z64_ITEM_GREEN_POTION,
  Z64_ITEM_BLUE_POTION,
  Z64_ITEM_FAIRY,
  Z64_ITEM_FISH,
  Z64_ITEM_MILK_FULL,
  Z64_ITEM_LETTER,
  Z64_ITEM_BLUE_FIRE,
  Z64_ITEM_BUG,
  Z64_ITEM_BIG_POE,
  Z64_ITEM_MILK_HALF,
  Z64_ITEM_POE,
  Z64_ITEM_WEIRD_EGG,
  Z64_ITEM_CHICKEN,
  Z64_ITEM_ZELDAS_LETTER,
  Z64_ITEM_KEATON_MASK,
  Z64_ITEM_SKULL_MASK,
  Z64_ITEM_SPOOKY_MASK,
  Z64_ITEM_BUNNY_HOOD,
  Z64_ITEM_GORON_MASK,
  Z64_ITEM_ZORA_MASK,
  Z64_ITEM_GERUDO_MASK,
  Z64_ITEM_MASK_OF_TRUTH,
  Z64_ITEM_SOLD_OUT,
  Z64_ITEM_POCKET_EGG,
  Z64_ITEM_POCKET_CUCCO,
  Z64_ITEM_COJIRO,
  Z64_ITEM_ODD_MUSHROOM,
  Z64_ITEM_ODD_POTION,
  Z64_ITEM_POACHERS_SAW,
  Z64_ITEM_BROKEN_GORONS_SWORD,
  Z64_ITEM_PRESCRIPTION,
  Z64_ITEM_EYEBALL_FROG,
  Z64_ITEM_EYE_DROPS,
  Z64_ITEM_CLAIM_CHECK,
  Z64_ITEM_BOW_FIRE_ARROW,
  Z64_ITEM_BOW_ICE_ARROW,
  Z64_ITEM_BOW_LIGHT_ARROW,
  Z64_ITEM_KOKIRI_SWORD,
  Z64_ITEM_MASTER_SWORD,
  Z64_ITEM_BIGGORON_SWORD,
  Z64_ITEM_DEKU_SHIELD,
  Z64_ITEM_HYLIAN_SHIELD,
  Z64_ITEM_MIRROR_SHIELD,
  Z64_ITEM_KOKIRI_TUNIC,
  Z64_ITEM_GORON_TUNIC,
  Z64_ITEM_ZORA_TUNIC,
  Z64_ITEM_KOKIRI_BOOTS,
  Z64_ITEM_IRON_BOOTS,
  Z64_ITEM_HOVER_BOOTS,
  Z64_ITEM_BULLET_BAG_30,
  Z64_ITEM_BULLET_BAG_40,
  Z64_ITEM_BULLET_BAG_50,
  Z64_ITEM_QUIVER_30,
  Z64_ITEM_QUIVER_40,
  Z64_ITEM_QUIVER_50,
  Z64_ITEM_BOMB_BAG_20,
  Z64_ITEM_BOMB_BAG_30,
  Z64_ITEM_BOMB_BAG_40,
  Z64_ITEM_GORONS_BRACELET,
  Z64_ITEM_SILVER_GAUNTLETS,
  Z64_ITEM_GOLDEN_GAUNTLETS,
  Z64_ITEM_SILVER_SCALE,
  Z64_ITEM_GOLDEN_SCALE,
  Z64_ITEM_GIANTS_KNIFE,
  Z64_ITEM_ADULTS_WALLET,
  Z64_ITEM_GIANTS_WALLET,
  Z64_ITEM_DEKU_SEEDS,
  Z64_ITEM_FISHING_POLE,
  Z64_ITEM_MINUET,
  Z64_ITEM_BOLERO,
  Z64_ITEM_SERENADE,
  Z64_ITEM_REQUIEM,
  Z64_ITEM_NOCTURNE,
  Z64_ITEM_PRELUDE,
  Z64_ITEM_ZELDAS_LULLABY,
  Z64_ITEM_EPONAS_SONG,
  Z64_ITEM_SARIAS_SONG,
  Z64_ITEM_SUNS_SONG,
  Z64_ITEM_SONG_OF_TIME,
  Z64_ITEM_SONG_OF_STORMS,
  Z64_ITEM_MEDALLION_FOREST,
  Z64_ITEM_MEDALLION_FIRE,
  Z64_ITEM_MEDALLION_WATER,
  Z64_ITEM_MEDALLION_SPIRIT,
  Z64_ITEM_MEDALLION_SHADOW,
  Z64_ITEM_MEDALLION_LIGHT,
  Z64_ITEM_KOKIRIS_EMERALD,
  Z64_ITEM_GORONS_RUBY,
  Z64_ITEM_ZORAS_SAPPHIRE,
  Z64_ITEM_STONE_OF_AGONY,
  Z64_ITEM_GERUDOS_CARD,
  Z64_ITEM_GOLD_SKULLTULA,
  Z64_ITEM_HEART_CONTAINER,
  Z64_ITEM_PIECE_OF_HEART,
  Z64_ITEM_BOSS_KEY,
  Z64_ITEM_COMPASS,
  Z64_ITEM_DUNGEON_MAP,
  Z64_ITEM_SMALL_KEY,
  Z64_ITEM_MAGIC_SMALL,
  Z64_ITEM_MAGIC_LARGE,
  Z64_ITEM_HEART_PIECE_2,
  Z64_ITEM_INVALID_1,
  Z64_ITEM_INVALID_2,
  Z64_ITEM_INVALID_3,
  Z64_ITEM_INVALID_4,
  Z64_ITEM_INVALID_5,
  Z64_ITEM_INVALID_6,
  Z64_ITEM_INVALID_7,
  Z64_ITEM_MILK,
  Z64_ITEM_RECOVERY_HEART,
  Z64_ITEM_RUPEE_GREEN,
  Z64_ITEM_RUPEE_BLUE,
  Z64_ITEM_RUPEE_RED,
  Z64_ITEM_RUPEE_PURPLE,
  Z64_ITEM_RUPEE_GOLD,
  Z64_ITEM_INVALID_8,
  Z64_ITEM_DEKU_STICKS_5,
  Z64_ITEM_DEKU_STICKS_10,
  Z64_ITEM_DEKU_NUTS_5,
  Z64_ITEM_DEKU_NUTS_10,
  Z64_ITEM_BOMBS_5,
  Z64_ITEM_BOMBS_10,
  Z64_ITEM_BOMBS_20,
  Z64_ITEM_BOMBS_30,
  Z64_ITEM_ARROWS_5,
  Z64_ITEM_ARROWS_10,
  Z64_ITEM_ARROWS_30,
  Z64_ITEM_DEKU_SEEDS_30,
  Z64_ITEM_BOMBCHUS_5,
  Z64_ITEM_BOMBCHUS_20,
  Z64_ITEM_DEKU_STICK_UPGRADE_20,
  Z64_ITEM_DEKU_STICK_UPGRADE_30,
  Z64_ITEM_DEKU_NUT_UPGRADE_30,
  Z64_ITEM_DEKU_NUT_UPGRADE_40,
  Z64_ITEM_SWORD_CS = 0xFC,
  Z64_ITEM_NONE_FE  = 0xFE,
  Z64_ITEM_NONE     = 0xFF,
} z64_item_t;

typedef enum {
  Z64_EXCH_ITEM_NONE,
  Z64_EXCH_ITEM_LETTER_ZELDA,
  Z64_EXCH_ITEM_WEIRD_EGG,
  Z64_EXCH_ITEM_CHICKEN,
  Z64_EXCH_ITEM_BEAN,
  Z64_EXCH_ITEM_POCKET_EGG,
  Z64_EXCH_ITEM_POCKET_CUCCO,
  Z64_EXCH_ITEM_COJIRO,
  Z64_EXCH_ITEM_ODD_MUSHROOM,
  Z64_EXCH_ITEM_ODD_POTION,
  Z64_EXCH_ITEM_SAW,
  Z64_EXCH_ITEM_SWORD_BROKEN,
  Z64_EXCH_ITEM_PRESCRIPTION,
  Z64_EXCH_ITEM_FROG,
  Z64_EXCH_ITEM_EYEDROPS,
  Z64_EXCH_ITEM_CLAIM_CHECK,
  Z64_EXCH_ITEM_MASK_SKULL,
  Z64_EXCH_ITEM_MASK_SPOOKY,
  Z64_EXCH_ITEM_MASK_KEATON,
  Z64_EXCH_ITEM_MASK_BUNNY,
  Z64_EXCH_ITEM_MASK_TRUTH,
  Z64_EXCH_ITEM_MASK_GORON,
  Z64_EXCH_ITEM_MASK_ZORA,
  Z64_EXCH_ITEM_MASK_GERUDO,
  Z64_EXCH_ITEM_FISH,
  Z64_EXCH_ITEM_BLUE_FIRE,
  Z64_EXCH_ITEM_BUG,
  Z64_EXCH_ITEM_POE,
  Z64_EXCH_ITEM_BIG_POE,
  Z64_EXCH_ITEM_LETTER_RUTO,
  Z64_EXCH_ITEM_MAX,
} z64_exchange_item_t;

typedef enum {
  PLAYER_IA_NONE,
  PLAYER_IA_SWORD_CS,
  PLAYER_IA_FISHING_POLE,
  PLAYER_IA_SWORD_MASTER,
  PLAYER_IA_SWORD_KOKIRI,
  PLAYER_IA_SWORD_BIGGORON,
  PLAYER_IA_DEKU_STICK,
  PLAYER_IA_HAMMER,
  PLAYER_IA_BOW,
  PLAYER_IA_BOW_FIRE,
  PLAYER_IA_BOW_ICE,
  PLAYER_IA_BOW_LIGHT,
  PLAYER_IA_BOW_0C,
  PLAYER_IA_BOW_0D,
  PLAYER_IA_BOW_0E,
  PLAYER_IA_SLINGSHOT,
  PLAYER_IA_HOOKSHOT,
  PLAYER_IA_LONGSHOT,
  PLAYER_IA_BOMB,
  PLAYER_IA_BOMBCHU,
  PLAYER_IA_BOOMERANG,
  PLAYER_IA_MAGIC_SPELL_15,
  PLAYER_IA_MAGIC_SPELL_16,
  PLAYER_IA_MAGIC_SPELL_17,
  PLAYER_IA_FARORES_WIND,
  PLAYER_IA_NAYRUS_LOVE,
  PLAYER_IA_DINS_FIRE,
  PLAYER_IA_DEKU_NUT,
  PLAYER_IA_OCARINA_FAIRY,
  PLAYER_IA_OCARINA_OF_TIME,
  PLAYER_IA_BOTTLE,
  PLAYER_IA_BOTTLE_FISH,
  PLAYER_IA_BOTTLE_FIRE,
  PLAYER_IA_BOTTLE_BUG,
  PLAYER_IA_BOTTLE_POE,
  PLAYER_IA_BOTTLE_BIG_POE,
  PLAYER_IA_BOTTLE_RUTOS_LETTER,
  PLAYER_IA_BOTTLE_POTION_RED,
  PLAYER_IA_BOTTLE_POTION_BLUE,
  PLAYER_IA_BOTTLE_POTION_GREEN,
  PLAYER_IA_BOTTLE_MILK_FULL,
  PLAYER_IA_BOTTLE_MILK_HALF,
  PLAYER_IA_BOTTLE_FAIRY,
  PLAYER_IA_ZELDAS_LETTER,
  PLAYER_IA_WEIRD_EGG,
  PLAYER_IA_CHICKEN,
  PLAYER_IA_MAGIC_BEAN,
  PLAYER_IA_POCKET_EGG,
  PLAYER_IA_POCKET_CUCCO,
  PLAYER_IA_COJIRO,
  PLAYER_IA_ODD_MUSHROOM,
  PLAYER_IA_ODD_POTION,
  PLAYER_IA_POACHERS_SAW,
  PLAYER_IA_BROKEN_GORONS_SWORD,
  PLAYER_IA_PRESCRIPTION,
  PLAYER_IA_FROG,
  PLAYER_IA_EYEDROPS,
  PLAYER_IA_CLAIM_CHECK,
  PLAYER_IA_MASK_KEATON,
  PLAYER_IA_MASK_SKULL,
  PLAYER_IA_MASK_SPOOKY,
  PLAYER_IA_MASK_BUNNY_HOOD,
  PLAYER_IA_MASK_GORON,
  PLAYER_IA_MASK_ZORA,
  PLAYER_IA_MASK_GERUDO,
  PLAYER_IA_MASK_TRUTH,
  PLAYER_IA_LENS_OF_TRUTH,
  PLAYER_IA_MAX
} z64_action_parameter_t;

typedef enum {
  SI_DEKU_NUTS_5,
  SI_ARROWS_30,
  SI_ARROWS_50,
  SI_BOMBS_5_R25,
  SI_DEKU_NUTS_10,
  SI_DEKU_STICK,
  SI_BOMBS_10,
  SI_FISH,
  SI_RED_POTION_R30,
  SI_GREEN_POTION,
  SI_BLUE_POTION,
  SI_LONGSWORD,
  SI_HYLIAN_SHIELD,
  SI_DEKU_SHIELD,
  SI_GORON_TUNIC,
  SI_ZORA_TUNIC,
  SI_RECOVERY_HEART,
  SI_MILK_BOTTLE,
  SI_WEIRD_EGG,
  SI_19,
  SI_20,
  SI_BOMBCHU_10_1,
  SI_BOMBCHU_20_1,
  SI_BOMBCHU_20_2,
  SI_BOMBCHU_10_2,
  SI_BOMBCHU_10_3,
  SI_BOMBCHU_20_3,
  SI_BOMBCHU_20_4,
  SI_BOMBCHU_10_4,
  SI_DEKU_SEEDS_30,
  SI_KEATON_MASK,
  SI_SPOOKY_MASK,
  SI_SKULL_MASK,
  SI_BUNNY_HOOD,
  SI_MASK_OF_TRUTH,
  SI_ZORA_MASK,
  SI_GORON_MASK,
  SI_GERUDO_MASK,
  SI_SOLD_OUT,
  SI_BLUE_FIRE,
  SI_BUGS,
  SI_BIG_POE,
  SI_POE,
  SI_FAIRY,
  SI_ARROWS_10,
  SI_BOMBS_20,
  SI_BOMBS_30,
  SI_BOMBS_5_R35,
  SI_RED_POTION_R40,
  SI_RED_POTION_R50,
  SI_MAX
} z64_shop_item_t;

typedef enum {
  Z64_SLOT_STICK,
  Z64_SLOT_NUT,
  Z64_SLOT_BOMB,
  Z64_SLOT_BOW,
  Z64_SLOT_FIRE_ARROW,
  Z64_SLOT_DINS_FIRE,
  Z64_SLOT_SLINGSHOT,
  Z64_SLOT_OCARINA,
  Z64_SLOT_BOMBCHU,
  Z64_SLOT_HOOKSHOT,
  Z64_SLOT_ICE_ARROW,
  Z64_SLOT_FARORES_WIND,
  Z64_SLOT_BOOMERANG,
  Z64_SLOT_LENS,
  Z64_SLOT_BEANS,
  Z64_SLOT_HAMMER,
  Z64_SLOT_LIGHT_ARROW,
  Z64_SLOT_NAYRUS_LOVE,
  Z64_SLOT_BOTTLE_1,
  Z64_SLOT_BOTTLE_2,
  Z64_SLOT_BOTTLE_3,
  Z64_SLOT_BOTTLE_4,
  Z64_SLOT_ADULT_TRADE,
  Z64_SLOT_CHILD_TRADE,
  
  // Extra
  Z64_SLOT_QUIVER,
  Z64_SLOT_KOKIRI_SWORD,
  Z64_SLOT_MASTER_SWORD,
  Z64_SLOT_GIANTS_KNIFE,
  Z64_SLOT_BOMB_BAG,
  Z64_SLOT_DEKU_SHIELD,
  Z64_SLOT_HYLIAN_SHIELD,
  Z64_SLOT_MIRROR_SHIELD,
  Z64_SLOT_STRENGTH,
  Z64_SLOT_KOKIRI_TUNIC,
  Z64_SLOT_GORON_TUNIC,
  Z64_SLOT_ZORA_TUNIC,
  Z64_SLOT_SCALE,
  Z64_SLOT_KOKIRI_BOOTS,
  Z64_SLOT_IRON_BOOTS,
  Z64_SLOT_HOVER_BOOTS,
  
  Z64_SLOT_NULL = 0xFF,
} z64_slot_t;

typedef enum {
  Z64_ITEMBTN_B,
  Z64_ITEMBTN_CL,
  Z64_ITEMBTN_CD,
  Z64_ITEMBTN_CR,
} z64_itembtn_t;

typedef enum {
    PAUSE_ITEM,
    PAUSE_MAP,
    PAUSE_QUEST,
    PAUSE_EQUIP,
    PAUSE_WORLD_MAP
} z64_pause_menu_page_t;

typedef struct {
  char      unk_00_[0x006E];        /* 0x0000 */
  int16_t   run_speed_limit;        /* 0x006E */
  char      unk_01_[0x0004];        /* 0x0070 */
  int16_t   run_speed_max_anim;     /* 0x0074 */
  char      unk_02_[0x0026];        /* 0x0076 */
  int16_t   gravity;                /* 0x009C */
  char      unk_03_[0x0072];        /* 0x009E */
  uint16_t  update_rate;            /* 0x0110 */
  char      unk_04_[0x0022];        /* 0x0112 */
  int16_t   override_aspect;        /* 0x0134 */
  uint16_t  aspect_width;           /* 0x0136 */
  uint16_t  aspect_height;          /* 0x0138 */
  char      unk_05_[0x0050];        /* 0x013A */
  int16_t   game_playing;           /* 0x018A */
  char      unk_06_[0x03B8];        /* 0x018C */
  uint16_t  c_up_icon_x;            /* 0x0544 */
  uint16_t  c_up_icon_y;            /* 0x0546 */
  char      unk_07_[0x021C];        /* 0x0548 */
  uint16_t  game_freeze;            /* 0x0764 */
  char      unk_08_[0x002E];        /* 0x0766 */
  uint16_t  magic_fill_r;           /* 0x0794 */
  uint16_t  magic_fill_g;           /* 0x0796 */
  uint16_t  magic_fill_b;           /* 0x0798 */
  char      unk_09_[0x004A];        /* 0x079A */
  uint16_t  c_button_r;             /* 0x07E4 */
  uint16_t  c_button_g;             /* 0x07E6 */
  uint16_t  c_button_b;             /* 0x07E8 */
  uint16_t  b_button_r;             /* 0x07EA */
  uint16_t  b_button_g;             /* 0x07EC */
  uint16_t  b_button_b;             /* 0x07EE */
  char      unk_0A_[0x0004];        /* 0x07F0 */
  qs510_t   start_icon_dd;          /* 0x07F4 */
  int16_t   start_icon_scale;       /* 0x07F6 */
  char      unk_0B_[0x0006];        /* 0x07F8 */
  uint16_t  start_icon_y;           /* 0x07FE */
  char      unk_0C_[0x0002];        /* 0x0800 */
  uint16_t  start_icon_x;           /* 0x0802 */
  char      unk_0D_[0x000C];        /* 0x0804 */
  uint16_t  c_up_button_x;          /* 0x0810 */
  uint16_t  c_up_button_y;          /* 0x0812 */
  char      unk_0E_[0x0008];        /* 0x0814 */
  uint16_t  start_button_x;         /* 0x081C */
  uint16_t  start_button_y;         /* 0x081E */
  uint16_t  item_button_x[4];       /* 0x0820 */
  uint16_t  item_button_y[4];       /* 0x0828 */
  qs510_t   item_button_dd[4];      /* 0x0830 */
  uint16_t  item_icon_x[4];         /* 0x0838 */
  uint16_t  item_icon_y[4];         /* 0x0840 */
  qs510_t   item_icon_dd[4];        /* 0x0848 */
  char      unk_0F_[0x0264];        /* 0x0850 */
  uint16_t  a_button_y;             /* 0x0AB4 */
  uint16_t  a_button_x;             /* 0x0AB6 */
  char      unk_10_[0x0002];        /* 0x0AB8 */
  uint16_t  a_button_icon_y;        /* 0x0ABA */
  uint16_t  a_button_icon_x;        /* 0x0ABC */
  char      unk_11_[0x0002];        /* 0x0ABE */
  uint16_t  a_button_r;             /* 0x0AC0 */
  uint16_t  a_button_g;             /* 0x0AC2 */
  uint16_t  a_button_b;             /* 0x0AC4 */
  char      unk_12_[0x0030];        /* 0x0AC6 */
  uint16_t  magic_bar_x;            /* 0x0AF6 */
  uint16_t  magic_bar_y;            /* 0x0AF8 */
  uint16_t  magic_fill_x;           /* 0x0AFA */
  char      unk_13_[0x02D6];        /* 0x0AFC */
  int16_t   minimap_disabled;       /* 0x0DD2 */
  char      unk_14_[0x01C0];        /* 0x0DD4 */
  uint16_t  item_ammo_x[4];         /* 0x0F94 */
  uint16_t  item_ammo_y[4];         /* 0x0F9C */
  char      unk_15_[0x0008];        /* 0x0FA4 */
  uint16_t  item_icon_space[4];     /* 0x0FAC */
  uint16_t  item_button_space[4];   /* 0x0FB4 */
                                    /* 0x0FBC */
} z64_gameinfo_t;

typedef enum {
    /* 0x00 */ RESPAWN_MODE_DOWN,   /* Normal Void Outs */
    /* 0x01 */ RESPAWN_MODE_RETURN, /* Grotto Returnpoints */
    /* 0x02 */ RESPAWN_MODE_TOP,    /* Farore's Wind */
    /* 0x03 */ RESPAWN_MODE_MAX
} RespawnMode;

typedef struct {
    /* 0x00 */ z64_xyzf_t pos;
    /* 0x0C */ int16_t yaw;
    /* 0x0E */ int16_t playerParams;
    /* 0x10 */ int16_t entranceIndex;
    /* 0x12 */ uint8_t roomIndex;
    /* 0x13 */ int8_t data;
    /* 0x14 */ uint32_t tempSwchFlags;
    /* 0x18 */ uint32_t tempCollectFlags;
} RespawnData; // size = 0x1C

typedef struct {
  int32_t         entrance_index;            /* 0x0000 */
  int32_t         link_age;                  /* 0x0004 */
  char            unk_00_[0x0002];           /* 0x0008 */
  uint16_t        cutscene_index;            /* 0x000A */
  uint16_t        day_time;                  /* 0x000C */
  char            unk_01_[0x0002];           /* 0x000E */
  int32_t         night_flag;                /* 0x0010 */
  char            unk_02_[0x0008];           /* 0x0014 */
  char            id[6];                     /* 0x001C */
  int16_t         deaths;                    /* 0x0022 */
  char            file_name[0x08];           /* 0x0024 */
  int16_t         n64dd_flag;                /* 0x002C */
  int16_t         energy_capacity;           /* 0x002E */
  int16_t         energy;                    /* 0x0030 */
  uint8_t         magic_capacity_set;        /* 0x0032 */
  uint8_t         magic;                     /* 0x0033 */
  uint16_t        rupees;                    /* 0x0034 */
  uint16_t        bgs_hits_left;             /* 0x0036 */
  uint16_t        navi_timer;                /* 0x0038 */
  uint8_t         magic_acquired;            /* 0x003A */
  char            unk_03_;                   /* 0x003B */
  uint8_t         magic_capacity;            /* 0x003C */
  int8_t          double_defense;            /* 0x003D */
  uint8_t         bgs_flag;                  /* 0x003E */
  char            ocarina_game_round_num;    /* 0x003F */
  uint8_t         child_button_items[4];     /* 0x0040 */
  uint8_t         child_c_button_slots[3];   /* 0x0044 */
  union
  {
    uint16_t      child_equips;              /* 0x0048 */
    struct
    {
      uint16_t    child_equip_boots   : 4;
      uint16_t    child_equip_tunic   : 4;
      uint16_t    child_equip_shield  : 4;
      uint16_t    child_equip_sword   : 4;
    };
  };
  uint8_t         adult_button_items[4];     /* 0x004A */
  uint8_t         adult_c_button_slots[3];   /* 0x004E */
  union
  {
    uint16_t      adult_equips;              /* 0x0052 */
    struct
    {
      uint16_t    adult_equip_boots   : 4;
      uint16_t    adult_equip_tunic   : 4;
      uint16_t    adult_equip_shield  : 4;
      uint16_t    adult_equip_sword   : 4;
    };
  };
  uint32_t        unk_04;                    /* 0x0054 */
  char            unk_06_[0x000E];           /* 0x0058 */
  int16_t         scene_index;               /* 0x0066 */
  uint8_t         button_items[4];           /* 0x0068 */
  uint8_t         c_button_slots[3];         /* 0x006C */
  union
  {
    uint16_t      equips;                    /* 0x0070 */
    struct
    {
      uint16_t    equip_boots         : 4;
      uint16_t    equip_tunic         : 4;
      uint16_t    equip_shield        : 4;
      uint16_t    equip_sword         : 4;
    };
  };
  char            unk_07_[0x0002];           /* 0x0072 */
  uint8_t         items[24];                 /* 0x0074 */
  int8_t          ammo[15];                  /* 0x008C */
  uint8_t         magic_beans_sold;          /* 0x009B */
  union
  {
    uint16_t      equipment;                 /* 0x009C */
    struct
    {
      uint16_t                        : 1;
      uint16_t    hover_boots         : 1;
      uint16_t    iron_boots          : 1;
      uint16_t    kokiri_boots        : 1;
      uint16_t                        : 1;
      uint16_t    zora_tunic          : 1;
      uint16_t    goron_tunic         : 1;
      uint16_t    kokiri_tunic        : 1;
      uint16_t                        : 1;
      uint16_t    mirror_shield       : 1;
      uint16_t    hylian_shield       : 1;
      uint16_t    deku_shield         : 1;
      uint16_t    broken_giants_knife : 1;
      uint16_t    giants_knife        : 1;
      uint16_t    master_sword        : 1;
      uint16_t    kokiri_sword        : 1;
    };
  };
  char            unk_08_[0x0002];          /* 0x009E */
  union
  {
    uint32_t      equipment_items;          /* 0x00A0 */
    struct
    {
      uint32_t                        : 9;
      uint32_t    nut_upgrade         : 3;
      uint32_t    stick_upgrade       : 3;
      uint32_t    bullet_bag          : 3;
      uint32_t    wallet              : 2;
      uint32_t    diving_upgrade      : 3;
      uint32_t    strength_upgrade    : 3;
      uint32_t    bomb_bag            : 3;
      uint32_t    quiver              : 3;
    };
  };
  union
  {
    uint32_t      quest_items;              /* 0x00A4 */
    struct
    {
      uint32_t    heart_pieces        : 8;
      uint32_t    gold_skulltula      : 1;
      uint32_t    gerudos_card        : 1;
      uint32_t    stone_of_agony      : 1;
      uint32_t    zoras_sapphire      : 1;
      uint32_t    gorons_ruby         : 1;
      uint32_t    kokiris_emerald     : 1;
      uint32_t    song_of_storms      : 1;
      uint32_t    song_of_time        : 1;
      uint32_t    suns_song           : 1;
      uint32_t    sarias_song         : 1;
      uint32_t    eponas_song         : 1;
      uint32_t    zeldas_lullaby      : 1;
      uint32_t    prelude_of_light    : 1;
      uint32_t    nocturne_of_shadow  : 1;
      uint32_t    requiem_of_spirit   : 1;
      uint32_t    serenade_of_water   : 1;
      uint32_t    bolero_of_fire      : 1;
      uint32_t    minuet_of_forest    : 1;
      uint32_t    light_medallion     : 1;
      uint32_t    shadow_medallion    : 1;
      uint32_t    spirit_medallion    : 1;
      uint32_t    water_medallion     : 1;
      uint32_t    fire_medallion      : 1;
      uint32_t    forest_medallion    : 1;
    };
  };
  union
  {
    uint8_t       items;
    struct
    {
      uint8_t                         : 5;
      uint8_t     map                 : 1;
      uint8_t     compass             : 1;
      uint8_t     boss_key            : 1;
    };
  }               dungeon_items[20];         /* 0x00A8 */
  int8_t          dungeon_keys[19];          /* 0x00BC */
  uint8_t         defense_hearts;            /* 0x00CF */
  int16_t         gs_tokens;                 /* 0x00D0 */
  char            unk_09_[0x0002];           /* 0x00D2 */
  struct
  {
    uint32_t      chest;
    uint32_t      swch;
    uint32_t      clear;
    uint32_t      collect;
    uint32_t      unk_00_;
    uint32_t      rooms_1;
    uint32_t      rooms_2;
  }               scene_flags[124];          /* 0x00D4 */
  struct {
    z64_xyzf_t    pos;
    int32_t       yaw;
    int32_t       playerParams;
    int32_t       entranceIndex;
    int32_t       roomIndex;
    int32_t       set;
    int32_t       tempSwchFlags;
    int32_t       tempCollectFlags;
  }               FaroresWindData;            /* 0x0E64 */
  uint8_t         dpad_item_slots[0x10];      /* 0x0E8C */
  uint8_t         gs_flags[56];               /* 0x0E9C */
  uint16_t        event_chk_inf[14];          /* 0x0ED4 */
  uint16_t        item_get_inf[4];            /* 0x0EF0 */
  uint16_t        inf_table[29];              /* 0x0EF8 */
  uint16_t        sword_flag;                 /* 0x0F32 */
  char            unk_0D_[0x041E];            /* 0x0F34 */
  uint16_t        checksum;                   /* 0x1352 */
  char            unk_0E_[0x0003];            /* 0x1354 */
  int8_t          file_index;                 /* 0x1357 */
  char            unk_0F_[0x0004];            /* 0x1358 */
  int32_t         game_mode;                  /* 0x135C */
  uint32_t        scene_setup_index;          /* 0x1360 */
  int32_t         respawn_flag;               /* 0x1364 */
  RespawnData     respawn[RESPAWN_MODE_MAX];  /* 0x1368 */
  float           entranceSpeed;              /* 0x13BC */
  uint16_t        entranceSound;              /* 0x13C0 */
  char            unk_10_[0x0001];            /* 0x13C2 */
  uint8_t         retainWeatherMode;          /* 0x13C3 */
  int16_t         dogParams;                  /* 0x13C4 */
  uint8_t         envHazardTextTriggerFlags;  /* 0x13C6 */
  uint8_t         showTitleCard;              /* 0x13C7 */
  uint16_t        nayrus_love_timer;          /* 0x13C8 */
  char            unk_13_[0x0004];            /* 0x13CA */
  int16_t         timer_1_state;              /* 0x13CE */
  int16_t         timer_1_value;              /* 0x13D0 */
  int16_t         timer_2_state;              /* 0x13D2 */
  int16_t         timer_2_value;              /* 0x13D4 */
  char            unk_14_[0x000A];            /* 0x13D6 */
  int8_t          seq_index;                  /* 0x13E0 */
  int8_t          night_sfx;                  /* 0x13E1 */
  uint8_t         button_status[5];           /* 0x13E2 */
  uint8_t         force_rising_button_alphas; /* 0x13E7 */
  uint16_t        next_hud_visibility_mode;   /* 0x13E8 */
  uint16_t        hud_visibility_mode;        /* 0x13EA */
  uint16_t        hud_visibility_mode_timer;  /* 0x13EC */
  uint16_t        prev_hud_visibility_mode;   /* 0x13EE */
  int16_t         magic_consume_state;        /* 0x13F0 */
  char            unk_15_2_[0x0002];          /* 0x13F2 */
  uint16_t        magic_meter_size;           /* 0x13F4 */
  char            unk_16_[0x0004];            /* 0x13F6 */
  uint16_t        event_inf[4];               /* 0x13FA */
  char            unk_17_[0x0001];            /* 0x1402 */
  uint8_t         minimap_index;              /* 0x1403 */
  int16_t         minigame_state;             /* 0x1404 */
  char            unk_18_[0x0003];            /* 0x1406 */
  uint8_t         language;                   /* 0x1409 */
  char            unk_19_[0x0002];            /* 0x140A */
  uint8_t         z_targeting;                /* 0x140C */
  char            unk_1A_[0x0001];            /* 0x140D */
  uint16_t        disable_music_flag;         /* 0x140E */
  char            unk_1B_[0x0002];            /* 0x1410 */
  uint16_t        cutscene_next;              /* 0x1412 */
  char            unk_1C_[0x0010];            /* 0x1414 */
  uint16_t        refill_hearts;              /* 0x1424 */
  char            unk_1D_[0x000A];            /* 0x1426 */
  z64_gameinfo_t *gameinfo;                   /* 0x1430 */
  char            unk_1E_[0x001C];            /* 0x1434 */
                                              /* 0x1450 */
} z64_file_t;

typedef struct
{
    uint8_t       sound_options;             /* 0x0000 */
    uint8_t       z_target_options;          /* 0x0001 */
    uint8_t       language_options;          /* 0x0002 */
    char          verification_string[9];    /* 0x0003 */
    char          unk_00_[0x0014];           /* 0x000C */
    z64_file_t    primary_saves[3];          /* 0x0020 */
    z64_file_t    backup_saves[3];           /* 0x3D10 */
                                             /* 0x7A00 */
} z64_sram_data_t;

typedef struct
{
  uint32_t seg[16];
} z64_stab_t;

typedef struct
{
  uint8_t       scene_index;
  uint8_t       entrance_index;
  union
  {
    uint16_t    variable;
    struct
    {
      uint16_t  transition_out  : 7;
      uint16_t  transition_in   : 7;
      uint16_t  unk_00_         : 1;
      uint16_t  continue_music  : 1;
    };
  };
} z64_entrance_table_t;

typedef struct
{
  uint32_t scene_vrom_start;
  uint32_t scene_vrom_end;
  uint32_t title_vrom_start;
  uint32_t title_vrom_end;
  char     unk_00_;
  uint8_t  scene_config;
  char     unk_01_;
  char     padding_00_;
} z64_scene_table_t;

typedef struct
{
  uint32_t        size;                 /* 0x0000 */
  Gfx            *buf;                  /* 0x0004 */
  Gfx            *p;                    /* 0x0008 */
  Gfx            *d;                    /* 0x000C */
} z64_disp_buf_t;

typedef struct
{
  Gfx            *poly_opa_w;           /* 0x0000 */
  Gfx            *poly_xlu_w;           /* 0x0004 */
  char            unk_00_[0x0008];      /* 0x0008 */
  Gfx            *overlay_w;            /* 0x0010 */
  char            unk_01_[0x00A4];      /* 0x0014 */
  Gfx            *work_c;               /* 0x00B8 */
  uint32_t        work_c_size;          /* 0x00BC */
  char            unk_02_[0x00F0];      /* 0x00C0 */
  Gfx            *work_w;               /* 0x01B0 */
  z64_disp_buf_t  work;                 /* 0x01B4 */
  char            unk_03_[0x00E4];      /* 0x01C4 */
  z64_disp_buf_t  overlay;              /* 0x02A8 */
  z64_disp_buf_t  poly_opa;             /* 0x02B8 */
  z64_disp_buf_t  poly_xlu;             /* 0x02C8 */
  uint32_t        frame_count_1;        /* 0x02D8 */
  void           *frame_buffer;         /* 0x02DC */
  char            unk_04_[0x0008];      /* 0x02E0 */
  uint32_t        frame_count_2;        /* 0x02E8 */
                                        /* 0x02EC */
} z64_gfx_t;

typedef union
{
  struct
  {
    uint16_t  a  : 1;
    uint16_t  b  : 1;
    uint16_t  z  : 1;
    uint16_t  s  : 1;
    uint16_t  du : 1;
    uint16_t  dd : 1;
    uint16_t  dl : 1;
    uint16_t  dr : 1;
    uint16_t     : 2;
    uint16_t  l  : 1;
    uint16_t  r  : 1;
    uint16_t  cu : 1;
    uint16_t  cd : 1;
    uint16_t  cl : 1;
    uint16_t  cr : 1;
  };
  uint16_t    pad;
} pad_t;

typedef struct
{
  pad_t         pad;
  int8_t        x;
  int8_t        y;
} z64_controller_t;

typedef enum {
    ACTORTYPE_SWITCH,
    ACTORTYPE_BG,
    ACTORTYPE_PLAYER,
    ACTORTYPE_EXPLOSIVES,
    ACTORTYPE_NPC,
    ACTORTYPE_ENEMY,
    ACTORTYPE_PROP,
    ACTORTYPE_ITEMACTION,
    ACTORTYPE_MISC,
    ACTORTYPE_BOSS,
    ACTORTYPE_DOOR,
    ACTORTYPE_CHEST
} actor_type_t;

typedef struct z64_actor_s z64_actor_t;
struct z64_game_t;
typedef void (*ActorFunc)(z64_actor_t*, struct z64_game_t*);

typedef struct {
    /* 0x00 */ int16_t id;
    /* 0x02 */ uint8_t category; // Classifies actor and determines when it will update or draw
    /* 0x04 */ uint32_t flags;
    /* 0x08 */ int16_t objectId;
    /* 0x0C */ uint32_t instanceSize;
    /* 0x10 */ ActorFunc init; // Constructor
    /* 0x14 */ ActorFunc destroy; // Destructor
    /* 0x18 */ ActorFunc update; // Update Function
    /* 0x1C */ ActorFunc draw; // Draw function
} ActorInit; // size = 0x20

typedef struct {
    /* 0x00 */ uintptr_t vromStart;
    /* 0x04 */ uintptr_t vromEnd;
    /* 0x08 */ void* vramStart;
    /* 0x0C */ void* vramEnd;
    /* 0x10 */ void* loadedRamAddr; // original name: "allocp"
    /* 0x14 */ ActorInit* initInfo;
    /* 0x18 */ char* name;
    /* 0x1C */ uint16_t allocType; // See `ACTOROVL_ALLOC_` defines
    /* 0x1E */ int8_t numLoaded; // original name: "clients"
} ActorOverlay; // size = 0x20

struct z64_actor_s {
  int16_t         actor_id;             /* 0x0000 */
  uint8_t         actor_type;           /* 0x0002 */
  int8_t          room_index;           /* 0x0003 */
  uint32_t        flags;                /* 0x0004 */
  z64_xyzf_t      pos_init;             /* 0x0008 */
  z64_rot_t       rot_init;             /* 0x0014 */
  char            unk_01_[0x0002];      /* 0x001A */
  uint16_t        variable;             /* 0x001C */
  uint8_t         alloc_index;          /* 0x001E */
  char            navi_tgt_dist;        /* 0x001F */
  uint16_t        sound_effect;         /* 0x0020 */
  char            unk_03_[0x0002];      /* 0x0022 */
  z64_xyzf_t      pos_world;            /* 0x0024 */
  z64_rot_t       rot_world;            /* 0x0030 */
  char            unk_04_[0x0002];      /* 0x0036 */
  z64_xyzf_t      pos_focus;            /* 0x0038 */
  z64_rot_t       rot_focus;            /* 0x0044 */
  char            unk_06_[0x0002];      /* 0x004A */
  float           lock_on_arrow;        /* 0x004C */
  z64_xyzf_t      scale;                /* 0x0050 */
  z64_xyzf_t      vel_1;                /* 0x005C */
  float           xz_speed;             /* 0x0068 */
  float           gravity;              /* 0x006C */
  float           min_vel_y;            /* 0x0070 */
  void           *unk_08_;              /* 0x0074 */
  z64_col_poly_t* floor_poly;           /* 0x0078 */
  char            unk_09_[0x000C];      /* 0x007C */
  uint16_t        unk_flags_00;         /* 0x0088 */
  int16_t         unk_roty;             /* 0x008A */
  float           distsq_from_link;     /* 0x008C */
  float           xzdist_from_link;     /* 0x0090 */
  float           ydist_from_link;      /* 0x0094 */
  void           *damage_table;         /* 0x0098 */
  z64_xyzf_t      vel_2;                /* 0x009C */
  int16_t         cyl_radius;           /* 0x00A8 */
  int16_t         cyl_reight;           /* 0x00AA */
  int16_t         cyl_y_shift;          /* 0x00AC */
  uint8_t         mass;                 /* 0x00AE */
  uint8_t         health;               /* 0x00AF */
  uint8_t         damage;               /* 0x00B0 */
  uint8_t         damage_effect;        /* 0x00B1 */
  uint8_t         at_hit_effect;        /* 0x00B2 */
  uint8_t         ac_hit_effect;        /* 0x00B3 */
  z64_rot_t       rot_2;                /* 0x00B4 */
  int16_t         face;                 /* 0x00BA */
  float           yOffset;              /* 0x00BC */
  char            unk_0F_[0x0024];      /* 0x00C0 */
  z64_xyzf_t      pos_projected;        /* 0x00E4 */
  float           projected_w;          /* 0x0F0 */
  float           uncull_zone_forward;  /* 0x0F4 */
  float           uncull_zone_scale;    /* 0x0F8 */
  float           uncull_zone_downward; /* 0x0FC */
  z64_xyzf_t      pos_previous;         /* 0x0100 */
  uint8_t         is_locked_on;         /* 0x010C */
  uint8_t         attention_priority;   /* 0x010D */
  uint16_t        text_id;              /* 0x010E */
  uint16_t        frozen;               /* 0x0110 */
  uint16_t        color_filter_params;  /* 0x0112 */
  uint8_t         color_filter_timer;   /* 0x0114 */
  uint8_t         active;               /* 0x0115 */
  uint8_t         drop_flag;            /* 0x0116 */
  uint8_t         navi_enemy_id;        /* 0x0117 */
  z64_actor_t    *parent;               /* 0x0118 */
  z64_actor_t    *child;                /* 0x011C */
  z64_actor_t    *prev;                 /* 0x0120 */
  z64_actor_t    *next;                 /* 0x0124 */
  void           *ctor;                 /* 0x0128 */
  void           *dtor;                 /* 0x012C */
  void           *main_proc;            /* 0x0130 */
  void           *draw_proc;            /* 0x0134 */
  void           *code_entry;           /* 0x0138 */
                                        /* 0x013C */
};

typedef struct {
    /* 0x00 */ uint16_t   id;
    /* 0x02 */ z64_xyz_t  pos;
    /* 0x08 */ z64_xyz_t  rot;
    /* 0x0E */ uint16_t   params;
} ActorEntry; // size = 0x10

typedef struct {
  z64_actor_t  common;                 /* 0x0000 */
  int8_t       current_tunic;          /* 0x013C */
  int8_t       current_sword_item_id;  /* 0x013D */
  int8_t       current_shield;         /* 0x013E */
  int8_t       current_boots;          /* 0x013F */
  int8_t       held_item_button;       /* 0x0140 */ // RAM: 801DAB70
  int8_t       held_item_action;       /* 0x0141 */ // RAM: 801DAB71
  int8_t       held_item_id;           /* 0x0142 */ // RAM: 801DAB72
  int8_t       previous_boots;         /* 0x0143 */
  int8_t       item_action;            /* 0x0144 */
  char         unk_00_[0x0003];        /* 0x0145 */
  uint8_t      model_group;            /* 0x0148 */
  uint8_t      next_model_group;       /* 0x0149 */
  int8_t       item_change_type;       /* 0x014A */
  uint8_t      model_anim_type;        /* 0x014B */
  uint8_t      left_hand_type;         /* 0x014C */
  uint8_t      right_hand_type;        /* 0x014D */
  uint8_t      sheath_type;            /* 0x014E */
  uint8_t      current_mask;           /* 0x014F */
  char         unk_01_[0x025C];        /* 0x0150 */
  z64_actor_t *held_actor;             /* 0x03AC */
  char         unk_0A_[0x0074];        /* 0x03B0 */
  int8_t       incoming_item_id;       /* 0x0424 */
  char         unk_02_[0x0003];        /* 0x0425 */
  z64_actor_t *incoming_item_actor;    /* 0x0428 */
  char         unk_03_[0x0008];        /* 0x042C */
  uint8_t      action;                 /* 0x0434 */
  char         unk_04_[0x0237];        /* 0x0435 */
  uint32_t     state_flags_1;          /* 0x066C */ // RAM: 801DB09C
  uint32_t     state_flags_2;          /* 0x0670 */ // RAM: 801DB0A0
  char         unk_05_[0x0004];        /* 0x0674 */
  z64_actor_t *boomerang_actor;        /* 0x0678 */
  z64_actor_t *navi_actor;             /* 0x067C */
  uint16_t     naviTextId;             /* 0x0680 */
  uint8_t      state_flags_3;          /* 0x0682 */ // RAM: 801DB0B2
  char         unk_06_[0x01A5];        /* 0x0683 */
  float        linear_vel;             /* 0x0828 */
  char         unk_07_[0x0002];        /* 0x082C */
  uint16_t     target_yaw;             /* 0x082E */
  char         unk_08_[0x0003];        /* 0x0830 */
  int8_t       sword_state;            /* 0x0833 */
  char         unk_09_[0x0050];        /* 0x0834 */
  int16_t      drop_y;                 /* 0x0884 */
  int16_t      drop_distance;          /* 0x0886 */
                                       /* 0x0888 */
} z64_link_t;

typedef struct DynaPolyActor {
  z64_actor_t  actor;    /* 0x000 */
  int32_t      bgId;     /* 0x14C */
  float        unk_150;  /* 0x150 */
  float        unk_154;  /* 0x154 */
  int16_t      unk_158;  /* 0x158 */  // y rotation?
  uint16_t     unk_15A;  /* 0x15A */
  uint32_t     unk_15C;  /* 0x15C */
  uint8_t      unk_160;  /* 0x160 */
  int16_t      unk_162;  /* 0x162 */
} DynaPolyActor; // size = 0x164

typedef struct {
  z64_controller_t  raw;
  uint16_t          unk_00_;
  z64_controller_t  raw_prev;
  uint16_t          unk_01_;
  pad_t             pad_pressed;
  int8_t            x_diff;
  int8_t            y_diff;
  char              unk_02_[0x0002];
  pad_t             pad_released;
  int8_t            adjusted_x;
  int8_t            adjusted_y;
  char              unk_03_[0x0002];
} z64_input_t;

/* context base */
typedef struct
{
  z64_gfx_t      *gfx;                    /* 0x0000 */
  void           *state_main;             /* 0x0004 */
  void           *state_dtor;             /* 0x0008 */
  void           *next_ctor;              /* 0x000C */
  uint32_t        next_size;              /* 0x0010 */
  z64_input_t     input[4];               /* 0x0014 */
  uint32_t        state_heap_size;        /* 0x0074 */
  void           *state_heap;             /* 0x0078 */
  void           *heap_start;             /* 0x007C */
  void           *heap_end;               /* 0x0080 */
  void           *state_heap_node;        /* 0x0084 */
  char            unk_00_[0x0010];        /* 0x0088 */
  int32_t         state_continue;         /* 0x0098 */
  int32_t         state_frames;           /* 0x009C */
  uint32_t        unk_01_;                /* 0x00A0 */
                                          /* 0x00A4 */
} z64_ctxt_t;

typedef struct
{
  /* file loading params */
  uint32_t      vrom_addr;
  void         *dram_addr;
  uint32_t      size;
  /* unknown, seem to be unused */
  void         *unk_00_;
  uint32_t      unk_01_;
  uint32_t      unk_02_;
  /* completion notification params */
  OSMesgQueue  *notify_queue;
  OSMesg        notify_message;
} z64_getfile_t;

/* object structs */
typedef struct
{
  int16_t       id;
  void         *data;
  z64_getfile_t getfile;
  OSMesgQueue   load_mq;
  OSMesg        load_m;
} z64_mem_obj_t;

typedef struct
{
  void         *obj_space_start;
  void         *obj_space_end;
  uint8_t       n_objects;
  char          unk_00_;
  uint8_t       keep_index;
  uint8_t       skeep_index;
  z64_mem_obj_t objects[19];
} z64_obj_ctxt_t;

typedef struct
{
    char              view[0x128];              /* 0x0000 */
    void             *iconItemSegment;          /* 0x0128 */
    void             *iconItem24Segment;        /* 0x012C */
    void             *iconItemAltSegment;       /* 0x0130 */
    void             *iconItemLangSegment;      /* 0x0134 */
    void             *nameSegment;              /* 0x0138 */
    void             *playerSegment;            /* 0x013C */
    char              unk_01[0x94];             /* 0x0140 */
    uint16_t          state;                    /* 0x01D4 */
    uint16_t          debugState;               /* 0x01D6 */
    char              eye[12];                  /* 0x01D8 */
    uint16_t          mainState;                /* 0x01E4 */
    uint16_t          nextPageMode;             /* 0x01E6 */
    uint16_t          pageIndex;                /* 0x01E8 */
    uint16_t          pageSwitchTimer;          /* 0x01EA */
    uint16_t          savePromptState;          /* 0x01EC */
    char              unk_02[0x0026];           /* 0x01EE */
    int16_t           stickAdjX;                /* 0x0214 */
    int16_t           stickAdjY;                /* 0x0216 */
    int16_t           cursorPoint[5];           /* 0x0218 */
    int16_t           cursorX[5];               /* 0x0222 */
    int16_t           cursorY[5];               /* 0x022C */
    int16_t           dungeonMapSlot;           /* 0x0236 */
    int16_t           cursorSpecialPos;         /* 0x0238 */
    int16_t           pageSwitchInputTimer;     /* 0x023A */
    uint16_t          namedItem;                /* 0x023C */
    uint16_t          cursorItem[4];            /* 0x023E */
    uint16_t          cursorSlot[4];            /* 0x0246 */
    char              unk_03[22];               /* 0x024E */
    int16_t           ocarinaSongIdx;           /* 0x0264 */
    uint8_t           worldMapPoints[20];       /* 0x0266 */
    uint8_t           tradeQuestMarker;         /* 0x027A */
    char              unk_04[0x39];             /* 0x027C */
                                                /* 0x02B4 */
} z64_pause_ctxt_t;

typedef struct
{
  uint32_t vrom_start;
  uint32_t vrom_end;
} z64_object_table_t;

/* lighting structs */
typedef struct
{
  int8_t  dir[3];
  uint8_t col[3];
} z64_light1_t;

typedef struct
{
  int16_t x;
  int16_t y;
  int16_t z;
  uint8_t col[3];
  int16_t intensity;
} z64_light2_t;

typedef union
{
  z64_light1_t  light1;
  z64_light2_t  light2;
} z64_lightn_t;

typedef struct
{
  uint8_t       type;
  z64_lightn_t  lightn;
} z64_light_t;

typedef struct z64_light_node_s z64_light_node_t;
struct z64_light_node_s
{
  z64_light_t      *light;
  z64_light_node_t *prev;
  z64_light_node_t *next;
};

typedef struct {
  z64_light_node_t *light_list;
  uint8_t           ambient[3];
  uint8_t           fog[3];
  int16_t           fog_position;
  int16_t           draw_distance;
} z64_lighting_t;

typedef struct {
  int8_t  numlights;
  Lightsn lites;
} z64_gbi_lights_t;

typedef void (*z64_light_handler_t)(z64_gbi_lights_t*, z64_lightn_t*,
                                    z64_actor_t*);


typedef struct {
  uint8_t          freeze_flash_timer; /* 0x0000 */
  char             unk_01_[0x01];      /* 0x0001 */
  uint8_t          unk_02;             /* 0x0002 */
  uint8_t          lens_active;        /* 0x0003 */
  char             unk_04_[0x04];      /* 0x0004 */
} z64_actor_ctxt_t;

typedef struct {
    /* 0x0000 */ uint32_t     msgOffset;
    /* 0x0004 */ uint32_t     msgLength;
    /* 0x0008 */ uint8_t      charTexBuf[FONT_CHAR_TEX_SIZE * 120];
    /* 0x3C08 */ uint8_t      iconBuf[FONT_CHAR_TEX_SIZE];
    /* 0x3C88 */ uint8_t      fontBuf[FONT_CHAR_TEX_SIZE * 320];
    union {
    /* 0xDC88 */ char         msgBuf[1280];
    /* 0xDC88 */ uint16_t     msgBufWide[640];
    };
} Font; // size = 0xE188

typedef struct {
    /* 0x0000 */ uint8_t      view[0x128];
    /* 0x0128 */ Font         font;
    /* 0xE2B0 */ void*        textboxSegment; // original name: "fukidashiSegment"
    /* 0xE2B4 */ char         unk_E2B4[0x4];
    /* 0xE2B8 */ void*        ocarinaStaff; // original name : "info"
    /* 0xE2BC */ char         unk_E2BC[0x3C];
    /* 0xE2F8 */ uint16_t     textId;
    /* 0xE2FA */ uint16_t     choiceTextId;
    /* 0xE2FC */ uint8_t      textBoxProperties; // original name : "msg_disp_type"
    /* 0xE2FD */ uint8_t      textBoxType; // "Text Box Type"
    /* 0xE2FE */ uint8_t      textBoxPos; // text box position
    /* 0xE300 */ int32_t      msgLength; // original name : "msg_data"
    /* 0xE304 */ uint8_t      msgMode; // original name: "msg_mode"
    /* 0xE305 */ char         unk_E305[0x1];
    /* 0xE306 */ uint8_t      msgBufDecoded[200]; // decoded message buffer, may be smaller than this
    /* 0xE3CE */ uint16_t     msgBufPos; // original name : "rdp"
    /* 0xE3D0 */ uint16_t     unk_E3D0; // unused, only ever set to 0
    /* 0xE3D2 */ uint16_t     textDrawPos; // draw all decoded characters up to this buffer position
    /* 0xE3D4 */ uint16_t     decodedTextLen; // decoded message buffer length
    /* 0xE3D6 */ uint16_t     textUnskippable;
    /* 0xE3D8 */ int16_t      textPosX;
    /* 0xE3DA */ int16_t      textPosY;
    /* 0xE3DC */ int16_t      textColorR;
    /* 0xE3DE */ int16_t      textColorG;
    /* 0xE3E0 */ int16_t      textColorB;
    /* 0xE3E2 */ int16_t      textColorAlpha;
    /* 0xE3E4 */ uint8_t      textboxEndType; // original name : "select"
    /* 0xE3E5 */ uint8_t      choiceIndex;
    /* 0xE3E6 */ uint8_t      choiceNum; // textboxes that are not choice textboxes have a choiceNum of 1
    /* 0xE3E7 */ uint8_t      stateTimer;
    /* 0xE3E8 */ uint16_t     textDelayTimer;
    /* 0xE3EA */ uint16_t     textDelay;
    /* 0xE3EA */ uint16_t     lastPlayedSong; // original references : "Ocarina_Flog" , "Ocarina_Free"
    /* 0xE3EE */ uint16_t     ocarinaMode; // original name : "ocarina_mode"
    /* 0xE3F0 */ uint16_t     ocarinaAction; // original name : "ocarina_no"
    /* 0xE3F2 */ uint16_t     unk_E3F2; // this is like "lastPlayedSong" but set less often, original name : "chk_ocarina_no"
    /* 0xE3F4 */ uint16_t     unk_E3F4; // unused, only set to 0 in z_actor
    /* 0xE3F6 */ uint16_t     textboxBackgroundIdx;
    /* 0xE3F8 */ uint8_t      textboxBackgroundForeColorIdx;
    /* 0xE3F8 */ uint8_t      textboxBackgroundBackColorIdx;
    /* 0xE3F8 */ uint8_t      textboxBackgroundYOffsetIdx;
    /* 0xE3F8 */ uint8_t      textboxBackgroundUnkArg; // unused, set by the textbox background control character arguments
    /* 0xE3FC */ char         unk_E3FC[0x2];
    /* 0xE3FE */ int16_t      textboxColorRed;
    /* 0xE400 */ int16_t      textboxColorGreen;
    /* 0xE402 */ int16_t      textboxColorBlue;
    /* 0xE404 */ int16_t      textboxColorAlphaTarget;
    /* 0xE406 */ int16_t      textboxColorAlphaCurrent;
    /* 0xE408 */ z64_actor_t* talkActor;
    /* 0xE40C */ int16_t      disableWarpSongs; // warp song flag set by scene commands
    /* 0xE40E */ int16_t      unk_E40E; // ocarina related
    /* 0xE410 */ uint8_t      lastOcaNoteIdx;
} MessageContext; // size = 0xE414

typedef enum {
    /* 0x00 */ CAM_MODE_NORMAL,
    /* 0x01 */ CAM_MODE_Z_PARALLEL, // Holding Z but with no target, keeps the camera aligned
    /* 0x02 */ CAM_MODE_Z_TARGET_FRIENDLY,
    /* 0x03 */ CAM_MODE_TALK,
    /* 0x04 */ CAM_MODE_Z_TARGET_UNFRIENDLY,
    /* 0x05 */ CAM_MODE_WALL_CLIMB, // Climbing a wall: ladders and vines
    /* 0x06 */ CAM_MODE_FIRST_PERSON,
    /* 0x07 */ CAM_MODE_AIM_ADULT, // First person aiming as adult: bow and hookshot
    /* 0x08 */ CAM_MODE_Z_AIM, // Third person aiming for all items, child and adult
    /* 0x09 */ CAM_MODE_HOOKSHOT_FLY, // Player being pulled by the hookshot to a target
    /* 0x0A */ CAM_MODE_AIM_BOOMERANG, // Aiming the boomerang
    /* 0x0B */ CAM_MODE_AIM_CHILD, // First person aiming as child: slingshot
    /* 0x0C */ CAM_MODE_Z_WALL_CLIMB, // Climbing a wall with Z pressed: ladders and vines
    /* 0x0D */ CAM_MODE_JUMP, // Falling in air from a ledge jump
    /* 0x0E */ CAM_MODE_LEDGE_HANG, // Hanging from and climbing a ledge
    /* 0x0F */ CAM_MODE_Z_LEDGE_HANG, // Hanging from and climbing a ledge with Z pressed
    /* 0x10 */ CAM_MODE_FREE_FALL, // Falling in air except for a ledge jump or knockback
    /* 0x11 */ CAM_MODE_CHARGE, // Charging a spin attack
    /* 0x12 */ CAM_MODE_STILL, // Attacks without Z pressed, falling in air from knockback
    /* 0x13 */ CAM_MODE_PUSH_PULL,
    /* 0x14 */ CAM_MODE_FOLLOW_BOOMERANG, // Boomerang has been thrown, force-target the boomerang as it flies
    /* 0x15 */ CAM_MODE_MAX
} CameraModeType;

/* game context */
typedef struct {
  z64_ctxt_t       common;                 /* 0x00000 */
  int16_t          scene_index;            /* 0x000A4 */
  uint8_t          scene_config;           /* 0x000A6  */
  char             unk_00_[0x09];          /* 0x000A7 */
  void*            scene_segment;          /* 0x000B0 */
  char             unk_001_[0x0C];         /* 0x000B4 */
  uint32_t         screen_top;             /* 0x000C0 */
  uint32_t         screen_bottom;          /* 0x000C4 */
  uint32_t         screen_left;            /* 0x000C8 */
  uint32_t         screen_right;           /* 0x000CC */
  float            camera_distance;        /* 0x000D0 */
  float            fog_distance;           /* 0x000D4 */
  float            z_distance;             /* 0x000D8 */
  float            unk_01_;                /* 0x000DC */
  char             unk_02_[0x0190];        /* 0x000E0 */
  z64_actor_t     *camera_focus;           /* 0x00270 */
  char             unk_03_[0x00AE];        /* 0x00274 */
  uint16_t         camera_setting;         /* 0x00322 */
  uint16_t         camera_mode;            /* 0x00324 */
  char             unk_04_[0x0018];        /* 0x00326 */
  uint16_t         camera_flag_1;          /* 0x0033E */
  char             unk_05_[0x016C];        /* 0x00340 */
  int16_t          event_flag;             /* 0x004AC */
  char             unk_06_[0x02E6];        /* 0x004AE */
  uint32_t         camera_2;               /* 0x00794 */
  char             unk_07_[0x0010];        /* 0x00798 */
  z64_lighting_t   lighting;               /* 0x007A8 */
  char             unk_08_[0x0008];        /* 0x007B8 */
  z64_col_hdr_t   *col_hdr;                /* 0x007C0 */
  char             unk_09_[0x1460];        /* 0x007C4 */
  z64_actor_ctxt_t actor_ctxt;             /* 0x01C24 */
  uint8_t          n_actors_loaded;        /* 0x01C2C */
  char             unk_0A_[0x0003];        /* 0x01C2D */
  struct {
    uint32_t       length;
    z64_actor_t   *first;
  }                actor_list[12];         /* 0x01C30 */
  char             unk_0B_[0x0038];        /* 0x01C90 */
  z64_actor_t     *arrow_actor;            /* 0x01CC8 */
  z64_actor_t     *target_actor;           /* 0x01CCC */
  char             unk_0C_1_[0x000A];      /* 0x01CD0 */
  uint8_t          target_actor_type;      /* 0x01CDA */
  char             unk_0C_2_[0x0005];      /* 0x01CDB */
  struct {
    z64_xyzf_t     pos;
    float          unk;
    colorRGB8_t    color;
  }                target_arr[3];          /* 0x01CE0 */
  char             unk_0C_3_[0x000C];      /* 0x01D1C */
  uint32_t         swch_flags;             /* 0x01D28 */
  uint32_t         temp_swch_flags;        /* 0x01D2C */
  uint32_t         unk_flags_0;            /* 0x01D30 */
  uint32_t         unk_flags_1;            /* 0x01D34 */
  uint32_t         chest_flags;            /* 0x01D38 */
  uint32_t         clear_flags;            /* 0x01D3C */
  uint32_t         temp_clear_flags;       /* 0x01D40 */
  uint32_t         collect_flags;          /* 0x01D44 */
  uint32_t         temp_collect_flags;     /* 0x01D48 */
  void            *title_card_texture;     /* 0x01D4C */
  char             unk_0D_[0x0007];        /* 0x01D50 */
  uint8_t          title_card_delay;       /* 0x01D57 */
  char             unk_0E_[0x0010];        /* 0x01D58 */
  void            *cutscene_ptr;           /* 0x01D68 */
  int8_t           cutscene_state;         /* 0x01D6C */
  char             unk_0F_[0x036B];        /* 0x01D6D */
  MessageContext   msgContext;             /* 0x020D8 */
  char             unk_12_[0x0246];        /* 0x104EC */
  struct {
    uint16_t       unk_00_;
    uint16_t       fadeout;
    uint16_t       a_button;
    uint16_t       b_button;
    uint16_t       cl_button;
    uint16_t       cd_button;
    uint16_t       cr_button;
    uint16_t       health;
    uint16_t       magic;
    uint16_t       minimap;
  }                alpha_channels;        /* 0x10732 */
  char             unk_13_[0x000A];       /* 0x10746 */
  uint8_t          unk_260;               /* 0x10750 */
  uint8_t          unk_261;               /* 0x10750 */
  struct {
    uint8_t        unk_00_;
    uint8_t        b_button;
    uint8_t        unk_01_;
    uint8_t        bottles;
    uint8_t        trade_items;
    uint8_t        hookshot;
    uint8_t        ocarina;
    uint8_t        warp_songs;
    uint8_t        suns_song;
    uint8_t        farores_wind;
    uint8_t        dfnl;
    uint8_t        all;
  }                restriction_flags;      /* 0x10752 */
  char             unk_14_[0x0002];        /* 0x1075E */
  z64_pause_ctxt_t pause_ctxt;             /* 0x10760 */
  char             unk_15_[0x0D90];        /* 0x10A14 */
  z64_obj_ctxt_t   obj_ctxt;               /* 0x117A4 */
  int8_t           room_index;             /* 0x11CBC */
  int8_t           room_unk_01;            /* 0x11CBD */
  int8_t           room_behavior_type_2;   /* 0x11CBE */
  int8_t           room_behavior_type_1;   /* 0x11CBF */
  int8_t           room_echo;              /* 0x11CC0 */
  int8_t           room_lens_Mode;         /* 0x11CC1 */
  char             unk_16_[0x0006];        /* 0x11CC2 */
  void            *room_ptr;               /* 0x11CC8 */
  char             unk_17_[0x0118];        /* 0x11CCC */
  uint32_t         gameplay_frames;        /* 0x11DE4 */
  uint8_t          link_age;               /* 0x11DE8 */
  char             unk_18_;                /* 0x11DE9 */
  uint8_t          spawn_index;            /* 0x11DEA */
  uint8_t          n_map_actors;           /* 0x11DEB */
  uint8_t          n_rooms;                /* 0x11DEC */
  char             unk_19_[0x000B];        /* 0x11DED */
  void            *map_actor_list;         /* 0x11DF8 */
  char             unk_20_[0x0008];        /* 0x11DFC */
  void            *scene_exit_list;        /* 0x11E04 */
  char             unk_21_[0x000C];        /* 0x11E08 */
  uint8_t          skybox_type;            /* 0x11E14 */
  int8_t           scene_load_flag;        /* 0x11E15 */
  char             unk_22_[0x0004];        /* 0x11E16 */
  int16_t          entrance_index;         /* 0x11E1A */
  char             unk_23_[0x0040];        /* 0x11E1C */
  uint8_t          shootingGalleryStatus;  /* 0x11E5C */
  uint8_t          bombchuBowlingStatus;   /* 0x11E5D */
  uint8_t          fadeout_transition;     /* 0x11E5E */
  char             unk_24_[0x5BC];         /* 0x11E5F */
  uint8_t          transition_mode;        /* 0x1241B */
                                           /* 0x12518 */
} z64_game_t;

typedef struct {
  char              unk_00_[0x01D8];          /* 0x00000 */
  z64_sram_data_t  *sram_buffer;              /* 0x001D8 */
  char              unk_01_[0x1C812];         /* 0x001DC */
  uint16_t          deaths[3];                /* 0x1C9EE */
  uint8_t           name[3][8];               /* 0x1C9F4 */
  uint16_t          hearts[3];                /* 0x1CA0C */
  uint32_t          quest_items[3];           /* 0x1CA14 */
  uint16_t          disk_drive[3];            /* 0x1CA20 */
  uint8_t           double_defense[3];        /* 0x1CA26 */
  char              unk_02_[0x0001];          /* 0x1CA29 */
  uint16_t          selected_item;            /* 0x1CA2A */
  uint16_t          selected_sub_item;        /* 0x1CA2C */
  uint16_t          menu_depth;               /* 0x1CA2E */
  uint16_t          alt_transition;           /* 0x1CA30 */
  char              unk_03_[0x0004];          /* 0x1CA32 */
  uint16_t          menu_transition;          /* 0x1CA36 */
  uint16_t          selected_file;            /* 0x1CA38 */
  char              unk_04_[0x0008];          /* 0x1CA3A */
  uint16_t          transition_frame;         /* 0x1CA42 */
  struct {
    int16_t         file[3];                  /* 0x1CA44 */
    int16_t         yes;                      /* 0x1CA4A */
    int16_t         quit;                     /* 0x1CA4C */
    int16_t         options;                  /* 0x1CA4E */
  }                 button_offsets;
  int16_t           unk_05_;                  /* 0x1CA50 */
  int16_t           file_message;             /* 0x1CA52 */
  int16_t           unk_06_;                  /* 0x1CA54 */
  int16_t           message_id[2];            /* 0x1CA56 */
  colorRGB16_t      panel_color;              /* 0x1CA5A */
  struct {
    uint16_t        message[2];               /* 0x1CA60 */
    uint16_t        panel;                    /* 0x1CA64 */
    uint16_t        file[3];                  /* 0x1CA66 */
    uint16_t        tag[3];                   /* 0x1CA6C */
    uint16_t        name_text[3];             /* 0x1CA72 */
    uint16_t        link[3];                  /* 0x1CA78 */
    uint16_t        file_details[3];          /* 0x1CA7E */
    uint16_t        copy_button;              /* 0x1CA84 */
    uint16_t        erase_button;             /* 0x1CA86 */
    uint16_t        yes_button;               /* 0x1CA88 */
    uint16_t        quit_button;              /* 0x1CA8A */
    uint16_t        options_button;           /* 0x1CA8C */
    uint16_t        unk_00_;                  /* 0x1CA8E */
    uint16_t        input_button_text;        /* 0x1CA90 */
    uint16_t        unk_01_;                  /* 0x1CA92 */
  } alpha_levels;
  colorRGB16_t      cursor_color;             /* 0x1CA94 */
} z64_menudata_t;

typedef struct
{
  void             *ptr;                      /* 0x0000 */
  uint32_t          vrom_start;               /* 0x0004 */
  uint32_t          vrom_end;                 /* 0x0008 */
  uint32_t          vram_start;               /* 0x000C */
  uint32_t          vram_end;                 /* 0x0010 */
  char              unk_00_[0x0004];          /* 0x0014 */
  uint32_t          vram_ctor;                /* 0x0018 */
  uint32_t          vram_dtor;                /* 0x001C */
  char              unk_01_[0x000C];          /* 0x0020 */
  char              ctxt_size;                /* 0x002C */
                                              /* 0x0030 */
} z64_state_ovl_t;

typedef struct
{
  /* state ? */
  int32_t           state;                    /* 0x0000 */
  /* elapsed time */
  int32_t           time;                     /* 0x0004 */
  /* point 1 */
  int16_t           p1x;                      /* 0x0008 */
  int16_t           p1y;                      /* 0x000A */
  int16_t           p1z;                      /* 0x000C */
  /* point 2 */
  int16_t           p2x;                      /* 0x000E */
  int16_t           p2y;                      /* 0x0010 */
  int16_t           p2z;                      /* 0x0012 */
  /* flags ? */
  uint16_t          flags;                    /* 0x0014 */
  char              pad_00_[0x0002];          /* 0x0016 */
                                              /* 0x0018 */
} z64_trail_cp_t;

typedef struct
{
  /* control points */
  z64_trail_cp_t    cp[16];                   /* 0x0000 */
  /* interpolation mode ? */
  uint32_t          ipn_mode;                 /* 0x0180 */
  /* parameter for interpolation mode 4 */
  float             f184;                     /* 0x0184 */
  /* flags ? */
  uint16_t          h188;                     /* 0x0188 */
  /* counter increment, counter, what for ? */
  int16_t           h18A;                     /* 0x018A */
  int16_t           h18C;                     /* 0x018C */
  /* point 1 starting color */
  colorRGBA8_t      p1_start;                 /* 0x018E */
  /* point 2 starting color */
  colorRGBA8_t      p2_start;                 /* 0x0192 */
  /* point 1 ending color */
 colorRGBA8_t       p1_end;                   /* 0x0196 */
  /* point 2 ending color */
  colorRGBA8_t      p2_end;                   /* 0x019A */
  /* number of active control points */
  uint8_t           n_cp;                     /* 0x019E */
  /* control point duration */
  uint8_t           duration;                 /* 0x019F */
  /* unknown */
  uint8_t           b1A0;                     /* 0x01A0 */
  /* render mode */
  /* 0:   simple */
  /* 1:   simple with alternate colors */
  /* 2+:  smooth */
  uint8_t           mode;                     /* 0x01A1 */
  /* alternate colors */
  /* inner color */
  uint8_t           m1r1;                     /* 0x01A2 */
  uint8_t           m1g1;                     /* 0x01A3 */
  uint8_t           m1b1;                     /* 0x01A4 */
  uint8_t           m1a1;                     /* 0x01A5 */
  /* outer color */
  uint8_t           m1r2;                     /* 0x01A6 */
  uint8_t           m1g2;                     /* 0x01A7 */
  uint8_t           m1b2;                     /* 0x01A8 */
  uint8_t           m1a2;                     /* 0x01A9 */
                                              /* 0x01AC */
} z64_trail_fx_t;

typedef struct
{
  uint8_t           active;                   /* 0x0000 */
  char              pad_00_[0x0003];          /* 0x0001 */
  z64_trail_fx_t    fx;                       /* 0x0004 */
                                              /* 0x01B0 */
} z64_trail_t;

typedef enum {
    /* 0x00 */ ITEM00_RUPEE_GREEN,
    /* 0x01 */ ITEM00_RUPEE_BLUE,
    /* 0x02 */ ITEM00_RUPEE_RED,
    /* 0x03 */ ITEM00_HEART,
    /* 0x04 */ ITEM00_BOMBS_A,
    /* 0x05 */ ITEM00_ARROWS_SINGLE,
    /* 0x06 */ ITEM00_HEART_PIECE,
    /* 0x07 */ ITEM00_HEART_CONTAINER,
    /* 0x08 */ ITEM00_ARROWS_SMALL,
    /* 0x09 */ ITEM00_ARROWS_MEDIUM,
    /* 0x0A */ ITEM00_ARROWS_LARGE,
    /* 0x0B */ ITEM00_BOMBS_B,
    /* 0x0C */ ITEM00_NUTS,
    /* 0x0D */ ITEM00_STICK,
    /* 0x0E */ ITEM00_MAGIC_LARGE,
    /* 0x0F */ ITEM00_MAGIC_SMALL,
    /* 0x10 */ ITEM00_SEEDS,
    /* 0x11 */ ITEM00_SMALL_KEY,
    /* 0x12 */ ITEM00_FLEXIBLE,
    /* 0x13 */ ITEM00_RUPEE_ORANGE,
    /* 0x14 */ ITEM00_RUPEE_PURPLE,
    /* 0x15 */ ITEM00_SHIELD_DEKU,
    /* 0x16 */ ITEM00_SHIELD_HYLIAN,
    /* 0x17 */ ITEM00_TUNIC_ZORA,
    /* 0x18 */ ITEM00_TUNIC_GORON,
    /* 0x19 */ ITEM00_BOMBS_SPECIAL
} Item00Type;

typedef enum {
    /* 0x00 */ SLOT_STICK,
    /* 0x01 */ SLOT_NUT,
    /* 0x02 */ SLOT_BOMB,
    /* 0x03 */ SLOT_BOW,
    /* 0x04 */ SLOT_ARROW_FIRE,
    /* 0x05 */ SLOT_DINS_FIRE,
    /* 0x06 */ SLOT_SLINGSHOT,
    /* 0x07 */ SLOT_OCARINA,
    /* 0x08 */ SLOT_BOMBCHU,
    /* 0x09 */ SLOT_HOOKSHOT,
    /* 0x0A */ SLOT_ARROW_ICE,
    /* 0x0B */ SLOT_FARORES_WIND,
    /* 0x0C */ SLOT_BOOMERANG,
    /* 0x0D */ SLOT_LENS,
    /* 0x0E */ SLOT_BEAN,
    /* 0x0F */ SLOT_HAMMER,
    /* 0x10 */ SLOT_ARROW_LIGHT,
    /* 0x11 */ SLOT_NAYRUS_LOVE,
    /* 0x12 */ SLOT_BOTTLE_1,
    /* 0x13 */ SLOT_BOTTLE_2,
    /* 0x14 */ SLOT_BOTTLE_3,
    /* 0x15 */ SLOT_BOTTLE_4,
    /* 0x16 */ SLOT_TRADE_ADULT,
    /* 0x17 */ SLOT_TRADE_CHILD,
    /* 0xFF */ SLOT_NONE = 0xFF
} InventorySlot;

typedef enum {
    /* 0x00 */ ITEM_STICK,
    /* 0x01 */ ITEM_NUT,
    /* 0x02 */ ITEM_BOMB,
    /* 0x03 */ ITEM_BOW,
    /* 0x04 */ ITEM_ARROW_FIRE,
    /* 0x05 */ ITEM_DINS_FIRE,
    /* 0x06 */ ITEM_SLINGSHOT,
    /* 0x07 */ ITEM_OCARINA_FAIRY,
    /* 0x08 */ ITEM_OCARINA_TIME,
    /* 0x09 */ ITEM_BOMBCHU,
    /* 0x0A */ ITEM_HOOKSHOT,
    /* 0x0B */ ITEM_LONGSHOT,
    /* 0x0C */ ITEM_ARROW_ICE,
    /* 0x0D */ ITEM_FARORES_WIND,
    /* 0x0E */ ITEM_BOOMERANG,
    /* 0x0F */ ITEM_LENS,
    /* 0x10 */ ITEM_BEAN,
    /* 0x11 */ ITEM_HAMMER,
    /* 0x12 */ ITEM_ARROW_LIGHT,
    /* 0x13 */ ITEM_NAYRUS_LOVE,
    /* 0x14 */ ITEM_BOTTLE,
    /* 0x15 */ ITEM_POTION_RED,
    /* 0x16 */ ITEM_POTION_GREEN,
    /* 0x17 */ ITEM_POTION_BLUE,
    /* 0x18 */ ITEM_FAIRY,
    /* 0x19 */ ITEM_FISH,
    /* 0x1A */ ITEM_MILK_BOTTLE,
    /* 0x1B */ ITEM_LETTER_RUTO,
    /* 0x1C */ ITEM_BLUE_FIRE,
    /* 0x1D */ ITEM_BUG,
    /* 0x1E */ ITEM_BIG_POE,
    /* 0x1F */ ITEM_MILK_HALF,
    /* 0x20 */ ITEM_POE,
    /* 0x21 */ ITEM_WEIRD_EGG,
    /* 0x22 */ ITEM_CHICKEN,
    /* 0x23 */ ITEM_LETTER_ZELDA,
    /* 0x24 */ ITEM_MASK_KEATON,
    /* 0x25 */ ITEM_MASK_SKULL,
    /* 0x26 */ ITEM_MASK_SPOOKY,
    /* 0x27 */ ITEM_MASK_BUNNY,
    /* 0x28 */ ITEM_MASK_GORON,
    /* 0x29 */ ITEM_MASK_ZORA,
    /* 0x2A */ ITEM_MASK_GERUDO,
    /* 0x2B */ ITEM_MASK_TRUTH,
    /* 0x2C */ ITEM_SOLD_OUT,
    /* 0x2D */ ITEM_POCKET_EGG,
    /* 0x2E */ ITEM_POCKET_CUCCO,
    /* 0x2F */ ITEM_COJIRO,
    /* 0x30 */ ITEM_ODD_MUSHROOM,
    /* 0x31 */ ITEM_ODD_POTION,
    /* 0x32 */ ITEM_SAW,
    /* 0x33 */ ITEM_SWORD_BROKEN,
    /* 0x34 */ ITEM_PRESCRIPTION,
    /* 0x35 */ ITEM_FROG,
    /* 0x36 */ ITEM_EYEDROPS,
    /* 0x37 */ ITEM_CLAIM_CHECK,
    /* 0x38 */ ITEM_BOW_ARROW_FIRE,
    /* 0x39 */ ITEM_BOW_ARROW_ICE,
    /* 0x3A */ ITEM_BOW_ARROW_LIGHT,
    /* 0x3B */ ITEM_SWORD_KOKIRI,
    /* 0x3C */ ITEM_SWORD_MASTER,
    /* 0x3D */ ITEM_SWORD_BGS,
    /* 0x3E */ ITEM_SHIELD_DEKU,
    /* 0x3F */ ITEM_SHIELD_HYLIAN,
    /* 0x40 */ ITEM_SHIELD_MIRROR,
    /* 0x41 */ ITEM_TUNIC_KOKIRI,
    /* 0x42 */ ITEM_TUNIC_GORON,
    /* 0x43 */ ITEM_TUNIC_ZORA,
    /* 0x44 */ ITEM_BOOTS_KOKIRI,
    /* 0x45 */ ITEM_BOOTS_IRON,
    /* 0x46 */ ITEM_BOOTS_HOVER,
    /* 0x47 */ ITEM_BULLET_BAG_30,
    /* 0x48 */ ITEM_BULLET_BAG_40,
    /* 0x49 */ ITEM_BULLET_BAG_50,
    /* 0x4A */ ITEM_QUIVER_30,
    /* 0x4B */ ITEM_QUIVER_40,
    /* 0x4C */ ITEM_QUIVER_50,
    /* 0x4D */ ITEM_BOMB_BAG_20,
    /* 0x4E */ ITEM_BOMB_BAG_30,
    /* 0x4F */ ITEM_BOMB_BAG_40,
    /* 0x50 */ ITEM_BRACELET,
    /* 0x51 */ ITEM_GAUNTLETS_SILVER,
    /* 0x52 */ ITEM_GAUNTLETS_GOLD,
    /* 0x53 */ ITEM_SCALE_SILVER,
    /* 0x54 */ ITEM_SCALE_GOLDEN,
    /* 0x55 */ ITEM_SWORD_KNIFE,
    /* 0x56 */ ITEM_WALLET_ADULT,
    /* 0x57 */ ITEM_WALLET_GIANT,
    /* 0x58 */ ITEM_SEEDS,
    /* 0x59 */ ITEM_FISHING_POLE,
    /* 0x5A */ ITEM_SONG_MINUET,
    /* 0x5B */ ITEM_SONG_BOLERO,
    /* 0x5C */ ITEM_SONG_SERENADE,
    /* 0x5D */ ITEM_SONG_REQUIEM,
    /* 0x5E */ ITEM_SONG_NOCTURNE,
    /* 0x5F */ ITEM_SONG_PRELUDE,
    /* 0x60 */ ITEM_SONG_LULLABY,
    /* 0x61 */ ITEM_SONG_EPONA,
    /* 0x62 */ ITEM_SONG_SARIA,
    /* 0x63 */ ITEM_SONG_SUN,
    /* 0x64 */ ITEM_SONG_TIME,
    /* 0x65 */ ITEM_SONG_STORMS,
    /* 0x66 */ ITEM_MEDALLION_FOREST,
    /* 0x67 */ ITEM_MEDALLION_FIRE,
    /* 0x68 */ ITEM_MEDALLION_WATER,
    /* 0x69 */ ITEM_MEDALLION_SPIRIT,
    /* 0x6A */ ITEM_MEDALLION_SHADOW,
    /* 0x6B */ ITEM_MEDALLION_LIGHT,
    /* 0x6C */ ITEM_KOKIRI_EMERALD,
    /* 0x6D */ ITEM_GORON_RUBY,
    /* 0x6E */ ITEM_ZORA_SAPPHIRE,
    /* 0x6F */ ITEM_STONE_OF_AGONY,
    /* 0x70 */ ITEM_GERUDO_CARD,
    /* 0x71 */ ITEM_SKULL_TOKEN,
    /* 0x72 */ ITEM_HEART_CONTAINER,
    /* 0x73 */ ITEM_HEART_PIECE,
    /* 0x74 */ ITEM_KEY_BOSS,
    /* 0x75 */ ITEM_COMPASS,
    /* 0x76 */ ITEM_DUNGEON_MAP,
    /* 0x77 */ ITEM_KEY_SMALL,
    /* 0x78 */ ITEM_MAGIC_SMALL,
    /* 0x79 */ ITEM_MAGIC_LARGE,
    /* 0x7A */ ITEM_HEART_PIECE_2,
    /* 0x7B */ ITEM_INVALID_1,
    /* 0x7C */ ITEM_INVALID_2,
    /* 0x7D */ ITEM_INVALID_3,
    /* 0x7E */ ITEM_INVALID_4,
    /* 0x7F */ ITEM_INVALID_5,
    /* 0x80 */ ITEM_INVALID_6,
    /* 0x81 */ ITEM_INVALID_7,
    /* 0x82 */ ITEM_MILK,
    /* 0x83 */ ITEM_HEART,
    /* 0x84 */ ITEM_RUPEE_GREEN,
    /* 0x85 */ ITEM_RUPEE_BLUE,
    /* 0x86 */ ITEM_RUPEE_RED,
    /* 0x87 */ ITEM_RUPEE_PURPLE,
    /* 0x88 */ ITEM_RUPEE_GOLD,
    /* 0x89 */ ITEM_INVALID_8,
    /* 0x8A */ ITEM_STICKS_5,
    /* 0x8B */ ITEM_STICKS_10,
    /* 0x8C */ ITEM_NUTS_5,
    /* 0x8D */ ITEM_NUTS_10,
    /* 0x8E */ ITEM_BOMBS_5,
    /* 0x8F */ ITEM_BOMBS_10,
    /* 0x90 */ ITEM_BOMBS_20,
    /* 0x91 */ ITEM_BOMBS_30,
    /* 0x92 */ ITEM_ARROWS_SMALL,
    /* 0x93 */ ITEM_ARROWS_MEDIUM,
    /* 0x94 */ ITEM_ARROWS_LARGE,
    /* 0x95 */ ITEM_SEEDS_30,
    /* 0x96 */ ITEM_BOMBCHUS_5,
    /* 0x97 */ ITEM_BOMBCHUS_20,
    /* 0x98 */ ITEM_STICK_UPGRADE_20,
    /* 0x99 */ ITEM_STICK_UPGRADE_30,
    /* 0x9A */ ITEM_NUT_UPGRADE_30,
    /* 0x9B */ ITEM_NUT_UPGRADE_40,
    /* 0xFC */ ITEM_LAST_USED = 0xFC,
    /* 0xFE */ ITEM_NONE_FE = 0xFE,
    /* 0xFF */ ITEM_NONE = 0xFF
} ItemID;

typedef struct EnGSwitch
{
  /* 0x0000 */ z64_actor_t actor;
  /* 0x014C */ void* actionFunc;   // EnGSwitchActionFunc
  /* 0x0150 */ int16_t type;
  /* 0x0152 */ int16_t silverCount;
  /* 0x0154 */ int16_t switchFlag;
  /* 0x0156 */ int16_t killTimer;
  /* 0x0158 */ int16_t colorIdx;
  /* 0x015A */ int16_t broken;
  /* 0x015C */ int16_t numEffects;
  /* 0x015E */ int16_t objId;
  /* 0x0160 */ int16_t index;      // first or second rupee in two-rupee patterns
  /* 0x0162 */ int16_t delayTimer; // delay between the two blue rupees appearing
  /* 0x0164 */ int16_t waitTimer;  // time rupee waits before retreating
  /* 0x0166 */ int16_t moveMode;   // Type of movement in the shooting gallery
  /* 0x0168 */ int16_t moveState;  // Appear or retreat (for blue rupees and the stationary green one)
  /* 0x016A */ int16_t noteIndex;
  /* 0x016C */ z64_xyzf_t targetPos;
  /* 0x0178 */ int8_t objIndex;
  /* 0x017C */ uint8_t collider[0x4C];  // ColliderCylinder
  /* 0x01C8 */ uint8_t effects[0x1130]; // EnGSwitchEffect[100]
} EnGSwitch; // size = 0x12F8

typedef enum {
    /*  0 */ PAUSE_STATE_OFF,
    /*  1 */ PAUSE_STATE_WAIT_LETTERBOX, // Request no letterboxing and wait for it.
    /*  2 */ PAUSE_STATE_WAIT_BG_PRERENDER, // Wait for the pause background prerender to be done.
    /*  3 */ PAUSE_STATE_INIT, // Load data and initialize/setup various things.
    /*  4 */ PAUSE_STATE_OPENING_1, // Animate the pause menu coming together with rotations and other animations.
    /*  5 */ PAUSE_STATE_OPENING_2, // Finish some animations for opening the menu.
    /*  6 */ PAUSE_STATE_MAIN, // Pause menu ready for player inputs.
    /*  7 */ PAUSE_STATE_SAVE_PROMPT,  // Save prompt in the pause menu
    /*  8 */ PAUSE_STATE_LOAD_GAME_OVER,
    /*  9 */ PAUSE_STATE_OPEN_GAME_OVER,
    /* 10 */ PAUSE_STATE_10,
    /* 11 */ PAUSE_STATE_11,
    /* 12 */ PAUSE_STATE_12,
    /* 13 */ PAUSE_STATE_13,
    /* 14 */ PAUSE_STATE_GAME_OVER,
    /* 15 */ PAUSE_STATE_SAVED,
    /* 16 */ PAUSE_STATE_OPEN_CONTINUE_QUIT,
    /* 17 */ PAUSE_STATE_CONTINUE_QUIT,
    /* 18 */ PAUSE_STATE_CLOSING, // Animate the pause menu closing
    /* 19 */ PAUSE_STATE_RESUME_GAMEPLAY // Handles returning to normal gameplay once the pause menu is visually closed
} PauseState;

// Sub-states of PAUSE_STATE_MAIN
typedef enum {
    /* 0 */ PAUSE_MAIN_STATE_IDLE,
    /* 1 */ PAUSE_MAIN_STATE_1,
    /* 2 */ PAUSE_MAIN_STATE_2,
    /* 3 */ PAUSE_MAIN_STATE_3,
    /* 4 */ PAUSE_MAIN_STATE_4,
    /* 5 */ PAUSE_MAIN_STATE_5,
    /* 6 */ PAUSE_MAIN_STATE_6,
    /* 7 */ PAUSE_MAIN_STATE_7,
    /* 8 */ PAUSE_MAIN_STATE_8,
    /* 9 */ PAUSE_MAIN_STATE_9
} PauseMainState;

typedef enum {
    /* 0 */ PAUSE_BG_PRERENDER_OFF, // Inactive, do nothing.
    /* 1 */ PAUSE_BG_PRERENDER_SETUP, // The current frame is only drawn for the purpose of serving as the pause background.
    /* 2 */ PAUSE_BG_PRERENDER_PROCESS, // The previous frame was PAUSE_BG_PRERENDER_SETUP, now apply prerender filters.
    /* 3 */ PAUSE_BG_PRERENDER_READY, // The pause background is ready to be used.
    /* 4 */ PAUSE_BG_PRERENDER_MAX
} PauseBgPreRenderState;

typedef enum {
    SUBSCREEN_ITEM,
    SUBSCREEN_MAP,
    SUBSCREEN_QUEST_STATUS,
    SUBSCREEN_EQUIPMENT,
} SubScreen;



/* helper macros */
#define LINK_IS_ADULT (z64_file.link_age == 0)
#define SLOT(item) gItemSlots[item]
#define INV_CONTENT(item) z64_file.items[SLOT(item)]



/* dram addresses */
#define z64_osSendMesg_addr                     0x80001E20
#define z64_osRecvMesg_addr                     0x80002030
#define z64_bzero_addr                          0x80002E80
#define z64_osCreateMesgQueue_addr              0x80004220
#define z64_vi_counter_addr                     0x80009E8C
#define z64_file_mq_addr                        0x80007D40
#define z64_EnItem00Action_addr                 0x800127E0
#define z64_Item_DropCollectible_addr           0x80013678
#define z64_Item_DropCollectible2_addr          0x800138B0
#define z64_GetCollectibleFlags_addr            0x800206E8
#define z64_SetCollectibleFlags_addr            0x8002071C
#define z64_ActorKill_addr                      0x80020EB4
#define z64_ActorSetLinkIncomingItemId_addr     0x80022CF4
#define z64_DrawActors_addr                     0x80024AB4
#define z64_DeleteActor_addr                    0x80024FE0
#define z64_SpawnActor_addr                     0x80025110
#define z64_RemoveActor_addr                    0x80025648
#define z64_Gfx_DrawDListOpa_addr               0x80028048
#define z64_memcopy_addr                        0x80057030
#define GetItem_Draw_addr                       0x800570C0
#define Font_LoadChar_addr                      0x8005BCE4
#define z64_Math_SinS_addr                      0x800636C4
#define PlaySFX_addr                            0x800646F0
#define z64_minimap_disable_1_addr              0x8006CD50
#define z64_minimap_disable_2_addr              0x8006D4E4
#define z64_SwitchAgeEquips_addr                0x8006F804
#define Interface_LoadItemIcon1_addr            0x8006FB50
#define z64_UpdateItemButton_addr               0x8006FB50
#define z64_GiveItem_addr                       0x8006FDCC
#define Rupees_ChangeBy_addr                    0x800721CC
#define z64_UpdateEquipment_addr                0x80079764
#define z64_LoadRoom_addr                       0x80080A3C
#define z64_UnloadRoom_addr                     0x80080C98
#define z64_ObjectSpawn_addr                    0x800812F0
#define z64_ObjectIndex_addr                    0x80081628
#define z64_ObjectIsLoaded_addr                 0x80081688
#define z64_Io_addr                             0x80091474
#define SsSram_ReadWrite_addr                   0x80091474
#define z64_entrance_offset_hook_addr           0x8009AA44
#define z64_frame_update_func_addr              0x8009AF1C
#define z64_frame_update_call_addr              0x8009CAE8
#define z64_disp_swap_1_addr                    0x800A1198
#define z64_disp_swap_2_addr                    0x800A11B0
#define z64_disp_swap_3_addr                    0x800A11C8
#define z64_disp_swap_4_addr                    0x800A11E4
#define z64_frame_input_func_addr               0x800A0BA0
#define z64_main_hook_addr                      0x800A0C3C
#define z64_frame_input_call_addr               0x800A16AC
#define z64_GetMatrixStackTop_addr              0x800AA78C
#define z64_ScalePitchAndTempo_addr             0x800C64A0
#define z64_Audio_PlayFanFare_addr              0x800C69A0
#define z64_Audio_PlaySoundGeneral_addr         0x800C806C
#define z64_Audio_GetActiveSeqId_addr           0x800CAB18
#define z64_Play_SetupRespawnPoint_addr         0x8009D94C
#define z64_Rand_ZeroOne_addr                   0x800CDCCC
#define z64_RandSeed_addr                       0x800CDCC0
#define Message_ContinueTextbox_addr            0x800DCE80
#define z64_Message_GetState_addr               0x800DD464
#define z64_DisplayTextbox_addr                 0x800DCE14
#define z64_actor_ovl_table_addr                0x800E8530
#define z64_event_state_1_addr                  0x800EF1B0
#define z64_state_ovl_tab_addr                  0x800F1340
#define gspF3DEX2_NoN_fifoTextStart             0x800E3F70
#define z64_fog_state_addr                      0x800F1640
#define z64_day_speed_addr                      0x800F1650
#define z64_light_handlers_addr                 0x800F1B40
#define z64_object_table_addr                   0x800F8FF8
#define z64_entrance_table_addr                 0x800F9C90
#define z64_scene_table_addr                    0x800FB4E0
#define z64_scene_config_table_addr             0x800FBD18
#define z64_seq_pos_addr                        0x801043B0
#define gspF3DEX2_NoN_fifoDataStart             0x801145C0
#define z64_file_addr                           0x8011A5D0
#define z64_input_direct_addr                   0x8011D730
#define z64_logo_state_addr                     0x8011F200
#define z64_stab_addr                           0x80120C38
#define z64_seq_buf_addr                        0x80124800
#define z64_ctxt_addr                           0x801C84A0
#define z64_link_addr                           0x801DAA30
#define z64_LinkInvincibility_addr              0x8038E578
#define z64_LinkDamage_addr                     0x8038E6A8

/* rom addresses */
#define z64_nes_font_static_vaddr               0x00928000
#define z64_nes_font_static_vsize               0x00004580
#define z64_icon_item_static_vaddr              0x007BD000
#define z64_icon_item_static_vsize              0x000888A0
#define z64_icon_item_24_static_vaddr           0x00846000
#define z64_icon_item_24_static_vsize           0x0000B400
#define z64_file_select_static_vaddr            0x01A02000
#define z64_file_select_static_vsize            0x000395C0
#define z64_parameter_static_vaddr              0x01A3C000
#define z64_parameter_static_vsize              0x00003B00
#define z64_icon_item_dungeon_static_vaddr      0x0085E000
#define z64_icon_item_dungeon_static_vsize      0x00001D80

/* context info */
#define z64_ctxt_filemenu_ctor                  0x80812394
#define z64_ctxt_filemenu_size                  0x0001CAD0
#define z64_ctxt_game_ctor                      0x8009A750
#define z64_ctxt_game_size                      0x00012518

/* function prototypes */
typedef void(*z64_ActorKillFunc)                        (z64_actor_t *);
typedef uint8_t(*z64_Message_GetStateFunc)              (uint8_t *);
typedef void(*z64_Flags_SetCollectibleFunc)             (z64_game_t *game, uint32_t flag);
typedef int32_t (*z64_Flags_GetCollectibleFunc)         (z64_game_t *game, uint32_t flag);
typedef void(*z64_Audio_PlaySoundGeneralFunc)           (uint16_t sfxId, void *pos, uint8_t token, float *freqScale, float *a4, uint8_t *reverbAdd);
typedef void(*z64_Audio_PlayFanFareFunc)                (uint16_t);
typedef void (*z64_DrawActors_proc)                     (z64_game_t *game, void *actor_ctxt);
typedef void (*z64_RemoveActor_proc)                    (void *actor_ctxt, z64_actor_t *actor, z64_game_t *game);
typedef void (*z64_DeleteActor_proc)                    (z64_game_t *game, void *actor_ctxt, z64_actor_t *actor);
typedef z64_actor_t* (*z64_SpawnActor_proc)             (void *actor_ctxt, z64_game_t *game, int actor_id, float x, float y, float z, uint16_t rx, uint16_t ry, uint16_t rz, uint16_t variable);
typedef void (*z64_SwitchAgeEquips_proc)                (void);
typedef void (*z64_UpdateItemButton_proc)               (z64_game_t *game, int button_index);
typedef void (*z64_UpdateEquipment_proc)                (z64_game_t *game, z64_link_t *link);
typedef void (*z64_LoadRoom_proc)                       (z64_game_t *game, void *p_ctxt_room_index, uint8_t room_index);
typedef void (*z64_UnloadRoom_proc)                     (z64_game_t *game, void *p_ctxt_room_index);
typedef void (*z64_Io_proc)                             (uint32_t dev_addr, void *dram_addr, uint32_t size, int32_t direction);
typedef void (*z64_SceneConfig_proc)                    (z64_game_t *game);
typedef void (*z64_DisplayTextbox_proc)                 (z64_game_t *game, uint16_t text_id, int unknown_);
typedef void (*z64_GiveItem_proc)                       (z64_game_t *game, uint8_t item);
typedef void(*z64_LinkDamage_proc)                      (z64_game_t *ctxt, z64_link_t *link, uint8_t damage_type, float unk_00, uint32_t unk_01, uint16_t unk_02);
typedef void(*z64_LinkInvincibility_proc)               (z64_link_t *link, uint8_t frames);
typedef float *(*z64_GetMatrixStackTop_proc)            ();
typedef void (*SsSram_ReadWrite_proc)                   (uint32_t addr, void *dramAddr, size_t size, uint32_t direction);
typedef void *(*z64_memcopy_proc)                       (void *dest, void *src, uint32_t size);
typedef void (*z64_bzero_proc)                          (void *__s, uint32_t __n);
typedef void (*z64_Gfx_DrawDListOpa_proc)               (z64_game_t *game, z64_gfx_t *dlist);
typedef float (*z64_Math_SinS_proc)                     (int16_t angle);
typedef int32_t(*z64_ObjectSpawn_proc)                  (z64_obj_ctxt_t *object_ctx, int16_t object_id);
typedef int32_t(*z64_ObjectIndex_proc)                  (z64_obj_ctxt_t *object_ctx, int16_t object_id);
typedef int32_t(*z64_ObjectIsLoaded_proc)               (z64_obj_ctxt_t *object_ctx, int32_t bank_index);
typedef int32_t(*z64_ActorSetLinkIncomingItemId_proc)   (z64_actor_t *actor, z64_game_t *game, int32_t get_item_id, float xz_range, float y_range);
typedef float (*z64_Rand_ZeroOne_proc)                  ();
typedef void(*z64_RandSeed_proc)                        (uint32_t seed);
typedef float(*z64_Rand_ZeroOne_proc)                   ();
typedef void(*Font_LoadChar_proc)                       (void* font, uint8_t character, uint16_t codePointIndex);
typedef void(*Interface_LoadItemIcon1_proc)             (z64_game_t *game, uint16_t button);
typedef void(*Rupees_ChangeBy_proc)                     (int16_t rupeeChange);
typedef void(*Message_ContinueTextbox_proc)             (z64_game_t *play, uint16_t textId);
typedef void(*PlaySFX_proc)                             (uint16_t sfxId);
typedef void(*z64_ScalePitchAndTempo_proc)              (float scaleTempoAndFreq, uint8_t duration);
typedef void(*GetItem_Draw_proc)                        (z64_game_t *game, int16_t drawId);
typedef uint16_t (*z64_Audio_GetActiveSeqId_proc)       (uint8_t seqId);
typedef void(*z64_Play_SetupRespawnPoint_proc)          (z64_game_t *game, int32_t respawnMode, int32_t playerParams);
typedef void(*z64_Actor_proc)                           (z64_actor_t *actor, z64_game_t *ctxt);

typedef struct
{
   int16_t        id;           /* 0x00 */ 
   uint8_t        type;         /* 0x02 */
   uint32_t       flags;        /* 0x04 */ 
   int16_t        objectId;     /* 0x08 */ 
   uint32_t       instanceSize; /* 0x0C */ 
   z64_Actor_proc init;         /* 0x10 */ 
   z64_Actor_proc destroy;      /* 0x14 */ 
   z64_Actor_proc update;       /* 0x18 */ 
   z64_Actor_proc draw;         /* 0x1C */ 
                                /* 0x20 */ 
} z64_actor_init_t;

typedef struct
{
   uint32_t          vrom_start;      /* 0x00 */ 
   uint32_t          vrom_end;        /* 0x04 */
   void*             vram_start;      /* 0x08 */ 
   void*             vram_end;        /* 0x0C */ 
   void*             loaded_ram_addr; /* 0x10 */ 
   z64_actor_init_t* init_info;       /* 0x14 */ 
   char*             name;            /* 0x18 */ 
   uint16_t          alloc_type;      /* 0x1C */ 
   int8_t            nb_loaded;       /* 0x1E */ 
   char              unk_01_[0x1];    /* 0x1F */ 
                                      /* 0x20 */ 
} z64_actor_ovl_t;



/* data */
#define z64_file_mq             (*(OSMesgQueue*)            z64_file_mq_addr)
#define z64_vi_counter          (*(uint32_t*)               z64_vi_counter_addr)
#define z64_stab                (*(z64_stab_t*)             z64_stab_addr)
#define z64_scene_table         ( (z64_scene_table_t*)      z64_scene_table_addr)
#define z64_fog_state           (*(uint8_t*)                z64_fog_state_addr)
#define z64_day_speed           (*(uint16_t*)               z64_day_speed_addr)
#define z64_light_handlers      ( (z64_light_handler_t*)    z64_light_handlers_addr)
#define z64_object_table        ( (z64_object_table_t*)     z64_object_table_addr)
#define z64_entrance_table      ( (z64_entrance_table_t*)   z64_entrance_table_addr)
#define z64_scene_config_table  ( (z64_SceneConfig_proc*)   z64_scene_config_table_addr)
#define z64_file                (*(z64_file_t*)             z64_file_addr)
#define z64_input_direct        (*(z64_input_t*)            z64_input_direct_addr)
#define z64_logo_state          (*(uint32_t*)               z64_logo_state_addr)
#define z64_gameinfo            (*                          z64_file.gameinfo)
#define z64_ctxt                (*(z64_ctxt_t*)             z64_ctxt_addr)
#define z64_game                (*(z64_game_t*)             &z64_ctxt)
#define z64_link                (*(z64_link_t*)             z64_link_addr)
#define z64_state_ovl_tab       (*(z64_state_ovl_t(*)[6])   z64_state_ovl_tab_addr)
#define z64_event_state_1       (*(uint32_t*)               z64_event_state_1_addr)
#define z64_actor_ovl_table     ((z64_actor_ovl_t*)         z64_actor_ovl_table_addr)



/* functions */
#define z64_ActorKill                    ((z64_ActorKillFunc)                     z64_ActorKill_addr)
#define z64_MessageGetState              ((z64_Message_GetStateFunc)              z64_Message_GetState_addr)
#define z64_SetCollectibleFlags          ((z64_Flags_SetCollectibleFunc)          z64_SetCollectibleFlags_addr)
#define z64_Flags_GetCollectible         ((z64_Flags_GetCollectibleFunc)          z64_GetCollectibleFlags_addr)
#define z64_Audio_PlaySoundGeneral       ((z64_Audio_PlaySoundGeneralFunc)        z64_Audio_PlaySoundGeneral_addr)
#define z64_Audio_PlayFanFare            ((z64_Audio_PlayFanFareFunc)             z64_Audio_PlayFanFare_addr)
#define z64_osSendMesg                   ((osSendMesg_t)                          z64_osSendMesg_addr)
#define z64_osRecvMesg                   ((osRecvMesg_t)                          z64_osRecvMesg_addr)
#define z64_osCreateMesgQueue            ((osCreateMesgQueue_t)                   z64_osCreateMesgQueue_addr)
#define z64_DrawActors                   ((z64_DrawActors_proc)                   z64_DrawActors_addr)
#define z64_RemoveActor                  ((z64_RemoveActor_proc)                  z64_RemoveActor_addr)
#define z64_DeleteActor                  ((z64_DeleteActor_proc)                  z64_DeleteActor_addr)
#define z64_SpawnActor                   ((z64_SpawnActor_proc)                   z64_SpawnActor_addr)
#define z64_SwitchAgeEquips              ((z64_SwitchAgeEquips_proc)              z64_SwitchAgeEquips_addr)
#define z64_UpdateItemButton             ((z64_UpdateItemButton_proc)             z64_UpdateItemButton_addr)
#define z64_UpdateEquipment              ((z64_UpdateEquipment_proc)              z64_UpdateEquipment_addr)
#define z64_LoadRoom                     ((z64_LoadRoom_proc)                     z64_LoadRoom_addr)
#define z64_UnloadRoom                   ((z64_UnloadRoom_proc)                   z64_UnloadRoom_addr)
#define z64_Io                           ((z64_Io_proc)                           z64_Io_addr)
#define z64_DisplayTextbox               ((z64_DisplayTextbox_proc)               z64_DisplayTextbox_addr)
#define z64_GiveItem                     ((z64_GiveItem_proc)                     z64_GiveItem_addr)
#define z64_LinkDamage                   ((z64_LinkDamage_proc)                   z64_LinkDamage_addr)
#define z64_LinkInvincibility            ((z64_LinkInvincibility_proc)            z64_LinkInvincibility_addr)
#define z64_GetMatrixStackTop            ((z64_GetMatrixStackTop_proc)            z64_GetMatrixStackTop_addr)
#define z64_RandSeed                     ((z64_RandSeed_proc)                     z64_RandSeed_addr)
#define z64_Rand_ZeroOne                 ((z64_Rand_ZeroOne_proc)                 z64_Rand_ZeroOne_addr)
#define z64_ObjectSpawn                  ((z64_ObjectSpawn_proc)                  z64_ObjectSpawn_addr)
#define z64_ObjectIndex                  ((z64_ObjectIndex_proc)                  z64_ObjectIndex_addr)
#define z64_ObjectIsLoaded               ((z64_ObjectIsLoaded_proc)               z64_ObjectIsLoaded_addr)
#define z64_ActorSetLinkIncomingItemId   ((z64_ActorSetLinkIncomingItemId_proc)   z64_ActorSetLinkIncomingItemId_addr)
#define SsSram_ReadWrite                 ((SsSram_ReadWrite_proc)                 SsSram_ReadWrite_addr)
#define z64_memcopy                      ((z64_memcopy_proc)                      z64_memcopy_addr)
#define z64_bzero                        ((z64_bzero_proc)                        z64_bzero_addr)
#define z64_Item_DropCollectible         ((z64_Item_DropCollectible_proc)         z64_Item_DropCollectible_addr)
#define z64_Item_DropCollectible2        ((z64_Item_DropCollectible_proc)         z64_Item_DropCollectible2_addr)
#define z64_Gfx_DrawDListOpa             ((z64_Gfx_DrawDListOpa_proc)             z64_Gfx_DrawDListOpa_addr)
#define z64_Math_SinS                    ((z64_Math_SinS_proc)                    z64_Math_SinS_addr)
#define z64_Rand_ZeroOne                 ((z64_Rand_ZeroOne_proc)                 z64_Rand_ZeroOne_addr)
#define Interface_LoadItemIcon1          ((Interface_LoadItemIcon1_proc)          Interface_LoadItemIcon1_addr)
#define Rupees_ChangeBy                  ((Rupees_ChangeBy_proc)                  Rupees_ChangeBy_addr)
#define Message_ContinueTextbox          ((Message_ContinueTextbox_proc)          Message_ContinueTextbox_addr)
#define z64_ScalePitchAndTempo           ((z64_ScalePitchAndTempo_proc)           z64_ScalePitchAndTempo_addr)
#define z64_Audio_GetActiveSeqId         ((z64_Audio_GetActiveSeqId_proc)         z64_Audio_GetActiveSeqId_addr)
#define z64_Play_SetupRespawnPoint       ((z64_Play_SetupRespawnPoint_proc)       z64_Play_SetupRespawnPoint_addr)
#define PlaySFX                          ((PlaySFX_proc)                          PlaySFX_addr)
#define Font_LoadChar                    ((Font_LoadChar_proc)                    Font_LoadChar_addr)
#define GetItem_Draw                     ((GetItem_Draw_proc)                     GetItem_Draw_addr)

/* macros */
#define GET_EVENTCHKINF(flag)         (z64_file.event_chk_inf[(flag) >> 4] &   (1 << ((flag) & 0xF)))
#define SET_EVENTCHKINF(flag)         (z64_file.event_chk_inf[(flag) >> 4] |=  (1 << ((flag) & 0xF)))
#define CLEAR_EVENTCHKINF(flag)       (z64_file.event_chk_inf[(flag) >> 4] &= ~(1 << ((flag) & 0xF)))
#define TOGGLE_EVENTCHKINF(flag)      (z64_file.event_chk_inf[(flag) >> 4] ^=  (1 << ((flag) & 0xF)))
#define GET_ITEMGETINF(flag)          (z64_file.item_get_inf[(flag)  >> 4] &   (1 << ((flag) & 0xF)))
#define SET_ITEMGETINF(flag)          (z64_file.item_get_inf[(flag)  >> 4] |=  (1 << ((flag) & 0xF)))
#define CLEAR_ITEMGETINF(flag)        (z64_file.item_get_inf[(flag)  >> 4] &= ~(1 << ((flag) & 0xF)))
#define TOGGLE_ITEMGETINF(flag)       (z64_file.item_get_inf[(flag)  >> 4] ^=  (1 << ((flag) & 0xF)))
#define GET_INFTABLE(flag)            (z64_file.inf_table[(flag)     >> 4] &   (1 << ((flag) & 0xF)))
#define SET_INFTABLE(flag)            (z64_file.inf_table[(flag)     >> 4] |=  (1 << ((flag) & 0xF)))
#define CLEAR_INFTABLE(flag)          (z64_file.inf_table[(flag)     >> 4] &= ~(1 << ((flag) & 0xF)))
#define TOGGLE_INFTABLE(flag)         (z64_file.inf_table[(flag)     >> 4] ^=  (1 << ((flag) & 0xF)))
#define CHECK_FLAG_ALL(flags, mask)   (((flags) & (mask)) == (mask))

/*
 *
 * SaveContext flags
 *
 */



/*
 * SaveContext.eventChkInf (0x8011B4A4)
 */

#define EVENTCHKINF_00 0x00 // Unused
#define EVENTCHKINF_01 0x01 // Unused
#define EVENTCHKINF_02 0x02
#define EVENTCHKINF_03 0x03
#define EVENTCHKINF_04 0x04
#define EVENTCHKINF_05 0x05
#define EVENTCHKINF_06 0x06 // Unused
#define EVENTCHKINF_DEKU_TREE_DIED 0x07
#define EVENTCHKINF_08 0x08 // Unused
#define EVENTCHKINF_GOT_KOKIRIS_EMERALD 0x09
#define EVENTCHKINF_0A 0x0A
#define EVENTCHKINF_0B 0x0B
#define EVENTCHKINF_0C 0x0C
#define EVENTCHKINF_0D 0x0D // Unused
#define EVENTCHKINF_0E 0x0E // Unused
#define EVENTCHKINF_0F 0x0F
#define EVENTCHKINF_TALKED_TO_MALON_FIRST_TIME     0x10
#define EVENTCHKINF_11 0x11
#define EVENTCHKINF_RECEIVED_WEIRD_EGG             0x12
#define EVENTCHKINF_TALON_WOKEN_IN_CASTLE          0x13
#define EVENTCHKINF_TALON_RETURNED_FROM_CASTLE     0x14
#define EVENTCHKINF_TALKED_TO_CHILD_MALON_AT_RANCH 0x15
#define EVENTCHKINF_CAN_LEARN_EPONAS_SONG          0x16
#define EVENTCHKINF_17 0x17 // Unused
#define EVENTCHKINF_EPONA_OBTAINED                 0x18
#define EVENTCHKINF_19 0x19 // Unused
#define EVENTCHKINF_1A 0x1A // Unused
#define EVENTCHKINF_1B 0x1B
#define EVENTCHKINF_1C 0x1C
#define EVENTCHKINF_1D 0x1D
#define EVENTCHKINF_HORSE_RACE_COW_UNLOCK 0x1E
#define EVENTCHKINF_1F 0x1F // Unused
#define EVENTCHKINF_20 0x20
#define EVENTCHKINF_21 0x21
#define EVENTCHKINF_22 0x22
#define EVENTCHKINF_23 0x23
#define EVENTCHKINF_24 0x24 // Unused
#define EVENTCHKINF_GOT_GORONS_RUBY 0x25
#define EVENTCHKINF_26 0x26 // Unused
#define EVENTCHKINF_27 0x27 // Unused
#define EVENTCHKINF_28 0x28 // Unused
#define EVENTCHKINF_29 0x29 // Unused
#define EVENTCHKINF_2A 0x2A
#define EVENTCHKINF_2B 0x2B
#define EVENTCHKINF_2C 0x2C
#define EVENTCHKINF_2D 0x2D
#define EVENTCHKINF_2F 0x2F
#define EVENTCHKINF_30 0x30
#define EVENTCHKINF_31 0x31
#define EVENTCHKINF_32 0x32
#define EVENTCHKINF_GAVE_LETTER_TO_KING_ZORA 0x33
#define EVENTCHKINF_34 0x34 // Unused
#define EVENTCHKINF_35 0x35 // Unused
#define EVENTCHKINF_36 0x36 // Unused
#define EVENTCHKINF_GOT_ZORAS_SAPPHIRE 0x37
#define EVENTCHKINF_38 0x38
#define EVENTCHKINF_39 0x39
#define EVENTCHKINF_OPENED_JABU_JABU         0x3A
#define EVENTCHKINF_STARTED_NABOORU_KNUCKLE  0x3B
#define EVENTCHKINF_DEFEATED_NABOORU_KNUCKLE 0x3C
#define EVENTCHKINF_3D 0x3D // Unused
#define EVENTCHKINF_3E 0x3E // Unused
#define EVENTCHKINF_3F 0x3F // Unused
#define EVENTCHKINF_40_INDEX 4
#define EVENTCHKINF_40_SHIFT 0
#define EVENTCHKINF_40_MASK (1 << EVENTCHKINF_40_SHIFT)
#define EVENTCHKINF_VISITED_ZELDA ((EVENTCHKINF_40_INDEX << 4) | EVENTCHKINF_40_SHIFT)
#define EVENTCHKINF_41 0x41
#define EVENTCHKINF_42 0x42
#define EVENTCHKINF_43 0x43
#define EVENTCHKINF_44 0x44 // Unused
#define EVENTCHKINF_MASTER_SWORD_CS 0x45
#define EVENTCHKINF_46 0x46 // Unused
#define EVENTCHKINF_47 0x47 // Unused
#define EVENTCHKINF_CLEANSED_KOKIRI_FOREST  0x48
#define EVENTCHKINF_CLEANSED_DEATH_MOUNTAIN 0x49
#define EVENTCHKINF_CLEANSED_LAKE_HYLIA     0x4A
#define EVENTCHKINF_OPENED_DOOR_OF_TIME     0x4B
#define EVENTCHKINF_4C 0x4C
#define EVENTCHKINF_CREATED_RAINBOW_BRIDGE              0x4D
#define EVENTCHKINF_CAUGHT_BY_CASTLE_GUARDS             0x4E
#define EVENTCHKINF_WATCHED_SHEIK_AFTER_MASTER_SWORD_CS 0x4F
#define EVENTCHKINF_50 0x50
#define EVENTCHKINF_51 0x51
#define EVENTCHKINF_52 0x52
#define EVENTCHKINF_53 0x53 // Unused
#define EVENTCHKINF_SHADOW_ATTACKS_KAKARIKO 0x54
#define EVENTCHKINF_LEARNED_PRELUDE_OF_LIGHT_CS 0x55
#define EVENTCHKINF_56 0x56 // Unused
#define EVENTCHKINF_57 0x57 // Unused
#define EVENTCHKINF_58 0x58 // Unused
#define EVENTCHKINF_59 0x59
#define EVENTCHKINF_5A 0x5A
#define EVENTCHKINF_LEARNED_SONG_OF_STORMS 0x5B
#define EVENTCHKINF_5C 0x5C
#define EVENTCHKINF_5D 0x5D // Unused
#define EVENTCHKINF_5E 0x5E // Unused
#define EVENTCHKINF_5F 0x5F // Unused
#define EVENTCHKINF_60 0x60 // Unused
#define EVENTCHKINF_61 0x61 // Unused
#define EVENTCHKINF_62 0x62 // Unused
#define EVENTCHKINF_63 0x63 // Unused
#define EVENTCHKINF_64 0x64 // Unused
#define EVENTCHKINF_FAST_WINDMILL 0x65
#define EVENTCHKINF_66 0x66 // Unused
#define EVENTCHKINF_DRAINED_WELL 0x67
#define EVENTCHKINF_68 0x68
#define EVENTCHKINF_RESTORED_LAKE_HYLIA     0x69
#define EVENTCHKINF_TALON_WOKEN_IN_KAKARIKO 0x6A

// 0x6B
#define EVENTCHKINF_TALON_RETURNED_FROM_KAKARIKO_INDEX 6
#define EVENTCHKINF_TALON_RETURNED_FROM_KAKARIKO_SHIFT 11
#define EVENTCHKINF_TALON_RETURNED_FROM_KAKARIKO_MASK (1 << EVENTCHKINF_TALON_RETURNED_FROM_KAKARIKO_SHIFT)
#define EVENTCHKINF_TALON_RETURNED_FROM_KAKARIKO ((EVENTCHKINF_TALON_RETURNED_FROM_KAKARIKO_INDEX << 4) | EVENTCHKINF_TALON_RETURNED_FROM_KAKARIKO_SHIFT)

#define EVENTCHKINF_6C 0x6C // Unused
#define EVENTCHKINF_6D 0x6D // Unused
#define EVENTCHKINF_6E 0x6E
#define EVENTCHKINF_6F 0x6F
#define EVENTCHKINF_70 0x70
#define EVENTCHKINF_71 0x71
#define EVENTCHKINF_72 0x72
#define EVENTCHKINF_73 0x73
#define EVENTCHKINF_74 0x74
#define EVENTCHKINF_75 0x75
#define EVENTCHKINF_76 0x76
#define EVENTCHKINF_77 0x77
#define EVENTCHKINF_78 0x78
#define EVENTCHKINF_79 0x79 // Unused
#define EVENTCHKINF_7A 0x7A // Unused
#define EVENTCHKINF_7B 0x7B // Unused
#define EVENTCHKINF_7C 0x7C // Unused
#define EVENTCHKINF_7D 0x7D // Unused
#define EVENTCHKINF_7E 0x7E // Unused
#define EVENTCHKINF_7F 0x7F // Unused
#define EVENTCHKINF_ZELDA_FLEED_FROM_CASTLE 0x80
#define EVENTCHKINF_81 0x81 // Unused
#define EVENTCHKINF_82 0x82
#define EVENTCHKINF_83 0x83 // Unused
#define EVENTCHKINF_84 0x84 // Unused
#define EVENTCHKINF_85 0x85 // Unused
#define EVENTCHKINF_86 0x86 // Unused
#define EVENTCHKINF_87 0x87 // Unused
#define EVENTCHKINF_88 0x88 // Unused
#define EVENTCHKINF_89 0x89 // Unused
#define EVENTCHKINF_8A 0x8A // Unused
#define EVENTCHKINF_8B 0x8B // Unused
#define EVENTCHKINF_PAID_BACK_KEATON_MASK 0x8C
#define EVENTCHKINF_PAID_BACK_SKULL_MASK  0x8D
#define EVENTCHKINF_PAID_BACK_SPOOKY_MASK 0x8E
#define EVENTCHKINF_PAID_BACK_BUNNY_HOOD  0x8F

// 0x90-0x93
// carpenters freed from the gerudo
#define EVENTCHKINF_CARPENTERS_FREE_INDEX     9
#define EVENTCHKINF_CARPENTERS_FREE_SHIFT(n)  (0 + (n))
#define EVENTCHKINF_CARPENTERS_FREE_MASK(n)   (1 << EVENTCHKINF_CARPENTERS_FREE_SHIFT(n))
#define EVENTCHKINF_CARPENTERS_FREE(n)        ((EVENTCHKINF_CARPENTERS_FREE_INDEX << 4) | EVENTCHKINF_CARPENTERS_FREE_SHIFT(n))
#define EVENTCHKINF_CARPENTERS_FREE_MASK_ALL  (EVENTCHKINF_CARPENTERS_FREE_MASK(0) | EVENTCHKINF_CARPENTERS_FREE_MASK(1) | EVENTCHKINF_CARPENTERS_FREE_MASK(2) | EVENTCHKINF_CARPENTERS_FREE_MASK(3)    )
#define GET_EVENTCHKINF_CARPENTERS_FREE_ALL() CHECK_FLAG_ALL(z64_file.event_chk_inf[EVENTCHKINF_CARPENTERS_FREE_INDEX], EVENTCHKINF_CARPENTERS_FREE_MASK_ALL)

#define EVENTCHKINF_94 0x94
#define EVENTCHKINF_95 0x95
#define EVENTCHKINF_96 0x96
#define EVENTCHKINF_97 0x97 // Unused
#define EVENTCHKINF_98 0x98 // Unused
#define EVENTCHKINF_99 0x99 // Unused
#define EVENTCHKINF_9A 0x9A // Unused
#define EVENTCHKINF_9B 0x9B // Unused
#define EVENTCHKINF_SCARECROW_ACTIVATED 0x9C
#define EVENTCHKINF_9D 0x9D // Unused
#define EVENTCHKINF_9E 0x9E // Unused
#define EVENTCHKINF_9F 0x9F // Unused
#define EVENTCHKINF_A0 0xA0
#define EVENTCHKINF_A1 0xA1
#define EVENTCHKINF_A3 0xA3
#define EVENTCHKINF_A4 0xA4
#define EVENTCHKINF_A5 0xA5
#define EVENTCHKINF_A6 0xA6
#define EVENTCHKINF_A7 0xA7
#define EVENTCHKINF_A8 0xA8
#define EVENTCHKINF_A9 0xA9
#define EVENTCHKINF_AA 0xAA
#define EVENTCHKINF_AC 0xAC
#define EVENTCHKINF_AD 0xAD
#define EVENTCHKINF_AE 0xAE // Unused
#define EVENTCHKINF_AF 0xAF // Unused
#define EVENTCHKINF_B0 0xB0
#define EVENTCHKINF_B1 0xB1
#define EVENTCHKINF_B2 0xB2
#define EVENTCHKINF_B3 0xB3
#define EVENTCHKINF_B4 0xB4
#define EVENTCHKINF_B5 0xB5
#define EVENTCHKINF_B6 0xB6
#define EVENTCHKINF_B7 0xB7
#define EVENTCHKINF_B8 0xB8
#define EVENTCHKINF_B9 0xB9
#define EVENTCHKINF_BA 0xBA
#define EVENTCHKINF_BB 0xBB
#define EVENTCHKINF_BC 0xBC
#define EVENTCHKINF_BD 0xBD
#define EVENTCHKINF_BE 0xBE
#define EVENTCHKINF_BF 0xBF
#define EVENTCHKINF_DEFEATED_NABOORU_KNUCKLE_CS 0xC0
#define EVENTCHKINF_C1 0xC1
#define EVENTCHKINF_C3 0xC3
#define EVENTCHKINF_SHEIK_REVEAL_CS 0xC4
#define EVENTCHKINF_C5 0xC5
#define EVENTCHKINF_C6 0xC6
#define EVENTCHKINF_CAUGHT_PREVIOUSLY_BY_GERUDO 0xC7
#define EVENTCHKINF_C8 0xC8
#define EVENTCHKINF_C9 0xC9
#define EVENTCHKINF_CA 0xCA // Unused
#define EVENTCHKINF_CB 0xCB // Unused
#define EVENTCHKINF_CC 0xCC // Unused
#define EVENTCHKINF_CD 0xCD // Unused
#define EVENTCHKINF_CE 0xCE // Unused
#define EVENTCHKINF_CF 0xCF // Unused

// 0xD0-0xD6
#define EVENTCHKINF_SONGS_FOR_FROGS_INDEX        13
#define EVENTCHKINF_SONGS_FOR_FROGS_CHOIR_SHIFT  0
#define EVENTCHKINF_SONGS_FOR_FROGS_ZL_SHIFT     1
#define EVENTCHKINF_SONGS_FOR_FROGS_EPONA_SHIFT  2
#define EVENTCHKINF_SONGS_FOR_FROGS_SUNS_SHIFT   3
#define EVENTCHKINF_SONGS_FOR_FROGS_SARIA_SHIFT  4
#define EVENTCHKINF_SONGS_FOR_FROGS_SOT_SHIFT    5
#define EVENTCHKINF_SONGS_FOR_FROGS_STORMS_SHIFT 6
#define EVENTCHKINF_SONGS_FOR_FROGS_CHOIR_MASK   (1 << EVENTCHKINF_SONGS_FOR_FROGS_CHOIR_SHIFT)
#define EVENTCHKINF_SONGS_FOR_FROGS_ZL_MASK      (1 << EVENTCHKINF_SONGS_FOR_FROGS_ZL_SHIFT)
#define EVENTCHKINF_SONGS_FOR_FROGS_EPONA_MASK   (1 << EVENTCHKINF_SONGS_FOR_FROGS_EPONA_SHIFT)
#define EVENTCHKINF_SONGS_FOR_FROGS_SUNS_MASK    (1 << EVENTCHKINF_SONGS_FOR_FROGS_SUNS_SHIFT)
#define EVENTCHKINF_SONGS_FOR_FROGS_SARIA_MASK   (1 << EVENTCHKINF_SONGS_FOR_FROGS_SARIA_SHIFT)
#define EVENTCHKINF_SONGS_FOR_FROGS_SOT_MASK     (1 << EVENTCHKINF_SONGS_FOR_FROGS_SOT_SHIFT)
#define EVENTCHKINF_SONGS_FOR_FROGS_STORMS_MASK  (1 << EVENTCHKINF_SONGS_FOR_FROGS_STORMS_SHIFT)
#define EVENTCHKINF_SONGS_FOR_FROGS_CHOIR        ((EVENTCHKINF_SONGS_FOR_FROGS_INDEX << 4) | EVENTCHKINF_SONGS_FOR_FROGS_CHOIR_SHIFT)
#define EVENTCHKINF_SONGS_FOR_FROGS_ZL           ((EVENTCHKINF_SONGS_FOR_FROGS_INDEX << 4) | EVENTCHKINF_SONGS_FOR_FROGS_ZL_SHIFT)
#define EVENTCHKINF_SONGS_FOR_FROGS_EPONA        ((EVENTCHKINF_SONGS_FOR_FROGS_INDEX << 4) | EVENTCHKINF_SONGS_FOR_FROGS_EPONA_SHIFT)
#define EVENTCHKINF_SONGS_FOR_FROGS_SUNS         ((EVENTCHKINF_SONGS_FOR_FROGS_INDEX << 4) | EVENTCHKINF_SONGS_FOR_FROGS_SUNS_SHIFT)
#define EVENTCHKINF_SONGS_FOR_FROGS_SARIA        ((EVENTCHKINF_SONGS_FOR_FROGS_INDEX << 4) | EVENTCHKINF_SONGS_FOR_FROGS_SARIA_SHIFT)
#define EVENTCHKINF_SONGS_FOR_FROGS_SOT          ((EVENTCHKINF_SONGS_FOR_FROGS_INDEX << 4) | EVENTCHKINF_SONGS_FOR_FROGS_SOT_SHIFT)
#define EVENTCHKINF_SONGS_FOR_FROGS_STORMS       ((EVENTCHKINF_SONGS_FOR_FROGS_INDEX << 4) | EVENTCHKINF_SONGS_FOR_FROGS_STORMS_SHIFT)

// 0xDA-0xDE
#define EVENTCHKINF_DA_DB_DC_DD_DE_INDEX 13
#define EVENTCHKINF_DA_MASK (1 << 10)
#define EVENTCHKINF_DB_MASK (1 << 11)
#define EVENTCHKINF_DC_MASK (1 << 12)
#define EVENTCHKINF_DD_MASK (1 << 13)
#define EVENTCHKINF_DE_MASK (1 << 14)



/*
 * SaveContext.itemGetInf (0x8011B4C0)
 */

#define ITEMGETINF_00 0x00 // Unused
#define ITEMGETINF_01 0x01 // Unused
#define ITEMGETINF_02 0x02
#define ITEMGETINF_03 0x03
#define ITEMGETINF_04 0x04
#define ITEMGETINF_05 0x05
#define ITEMGETINF_06 0x06
#define ITEMGETINF_07 0x07
#define ITEMGETINF_08 0x08
#define ITEMGETINF_09 0x09
#define ITEMGETINF_0A 0x0A
#define ITEMGETINF_DEKU_HEART_PIECE  0x0B
#define ITEMGETINF_BOTTLE_CUCCO_LADY 0x0C
#define ITEMGETINF_0D 0x0D
#define ITEMGETINF_0E 0x0E
#define ITEMGETINF_0F 0x0F
#define ITEMGETINF_10 0x10
#define ITEMGETINF_11 0x11
#define ITEMGETINF_12 0x12
#define ITEMGETINF_13 0x13
#define ITEMGETINF_15 0x15
#define ITEMGETINF_16 0x16
#define ITEMGETINF_17 0x17

// 0x18-0x1A
#define ITEMGETINF_18_19_1A_INDEX 1
#define ITEMGETINF_18_SHIFT 8
#define ITEMGETINF_19_SHIFT 9
#define ITEMGETINF_1A_SHIFT 10
#define ITEMGETINF_18_MASK (1 << ITEMGETINF_18_SHIFT)
#define ITEMGETINF_19_MASK (1 << ITEMGETINF_19_SHIFT)
#define ITEMGETINF_1A_MASK (1 << ITEMGETINF_1A_SHIFT)
#define ITEMGETINF_18 ((ITEMGETINF_18_19_1A_INDEX << 4) | ITEMGETINF_18_SHIFT)
#define ITEMGETINF_19 ((ITEMGETINF_18_19_1A_INDEX << 4) | ITEMGETINF_19_SHIFT)
#define ITEMGETINF_1A ((ITEMGETINF_18_19_1A_INDEX << 4) | ITEMGETINF_1A_SHIFT)

#define ITEMGETINF_1B 0x1B
#define ITEMGETINF_1C 0x1C
#define ITEMGETINF_1D 0x1D
#define ITEMGETINF_1E 0x1E
#define ITEMGETINF_1F 0x1F
#define ITEMGETINF_20 0x20 // Unused
#define ITEMGETINF_21 0x21 // Unused
#define ITEMGETINF_22 0x22 // Unused
#define ITEMGETINF_BORROWED_KEATON_MASK 0x23 // (0x8011B4C5 -> 08)
#define ITEMGETINF_BORROWED_SKULL_MASK  0x24 // (0x8011B4C5 -> 10)
#define ITEMGETINF_BORROWED_SPOOKY_MASK 0x25 // (0x8011B4C5 -> 20)
#define ITEMGETINF_BORROWED_BUNNY_HOOD  0x26 // (0x8011B4C5 -> 40)
#define ITEMGETINF_27 0x27 // Unused
#define ITEMGETINF_28 0x28 // Unused
#define ITEMGETINF_29 0x29 // Unused
#define ITEMGETINF_MASK_OF_TRUTH_LOANED 0x2A // (0x8011B4C4 -> 04)
#define ITEMGETINF_POCKET_EGG           0x2C
#define ITEMGETINF_COJIRO               0x2E
#define ITEMGETINF_2F 0x2F // Unused
#define ITEMGETINF_30 0x30
#define ITEMGETINF_31 0x31
#define ITEMGETINF_32 0x32 // Unused
#define ITEMGETINF_33 0x33 // Unused
#define ITEMGETINF_34 0x34 // Unused
#define ITEMGETINF_35 0x35 // Unused
#define ITEMGETINF_36 0x36 // Unused
#define ITEMGETINF_37 0x37 // Unused
#define ITEMGETINF_SOLD_KEATON_MASK 0x38 // (0x8011B4C6 -> 01)
#define ITEMGETINF_SOLD_SKULL_MASK  0x39 // (0x8011B4C6 -> 02)
#define ITEMGETINF_SOLD_SPOOKY_MASK 0x3A // (0x8011B4C6 -> 04)
#define ITEMGETINF_SOLD_BUNNY_HOOD  0x3B // (0x8011B4C6 -> 08)
#define ITEMGETINF_3C 0x3C // Unused
#define ITEMGETINF_3D 0x3D // Unused
#define ITEMGETINF_3E 0x3E // Unused
#define ITEMGETINF_OTHER_MASKS_AVAILABLE 0x3F // (0x8011B4C6 -> 80)



/*
 * SaveContext.infTable (0x8011B4D0)
 */

#define INFTABLE_00 0x00
#define INFTABLE_01 0x01
#define INFTABLE_02 0x02 // Unused
#define INFTABLE_03 0x03
#define INFTABLE_04 0x04 // Unused
#define INFTABLE_05 0x05
#define INFTABLE_06 0x06 // Unused
#define INFTABLE_07 0x07 // Unused
#define INFTABLE_08 0x08 // Unused
#define INFTABLE_09 0x09 // Unused
#define INFTABLE_0A 0x0A // Unused
#define INFTABLE_0B 0x0B // Unused
#define INFTABLE_0C 0x0C
#define INFTABLE_0D 0x0D // Unused
#define INFTABLE_0E 0x0E
#define INFTABLE_0F 0x0F // Unused
#define INFTABLE_10 0x10
#define INFTABLE_11 0x11 // Unused
#define INFTABLE_12 0x12 // Unused
#define INFTABLE_13 0x13 // Unused
#define INFTABLE_14 0x14 // Unused
#define INFTABLE_15 0x15
#define INFTABLE_16 0x16 // Unused
#define INFTABLE_17 0x17
#define INFTABLE_18 0x18 // Unused
#define INFTABLE_19 0x19
#define INFTABLE_1A 0x1A // Unused
#define INFTABLE_1B 0x1B // Unused
#define INFTABLE_1C 0x1C // Unused
#define INFTABLE_1D 0x1D // Unused
#define INFTABLE_1E 0x1E
#define INFTABLE_1F 0x1F // Unused
#define INFTABLE_20 0x20 // Unused
#define INFTABLE_21 0x21 // Unused
#define INFTABLE_22 0x22
#define INFTABLE_23 0x23 // Unused
#define INFTABLE_24 0x24
#define INFTABLE_25 0x25 // Unused
#define INFTABLE_26 0x26
#define INFTABLE_27 0x27 // Unused
#define INFTABLE_28 0x28
#define INFTABLE_29 0x29 // Unused
#define INFTABLE_2A 0x2A
#define INFTABLE_2B 0x2B
#define INFTABLE_2C 0x2C // Unused
#define INFTABLE_2D 0x2D // Unused
#define INFTABLE_2E 0x2E
#define INFTABLE_2F 0x2F
#define INFTABLE_30 0x30
#define INFTABLE_31 0x31 // Unused
#define INFTABLE_32 0x32 // Unused
#define INFTABLE_33 0x33 // Unused
#define INFTABLE_34 0x34 // Unused
#define INFTABLE_35 0x35 // Unused
#define INFTABLE_36 0x36 // Unused
#define INFTABLE_37 0x37 // Unused
#define INFTABLE_38 0x38 // Unused
#define INFTABLE_39 0x39 // Unused
#define INFTABLE_3A 0x3A // Unused
#define INFTABLE_3B 0x3B // Unused
#define INFTABLE_3C 0x3C // Unused
#define INFTABLE_3D 0x3D // Unused
#define INFTABLE_3E 0x3E // Unused
#define INFTABLE_3F 0x3F // Unused
#define INFTABLE_40 0x40 // Unused
#define INFTABLE_41 0x41
#define INFTABLE_42 0x42 // Unused
#define INFTABLE_43 0x43 // Unused
#define INFTABLE_44 0x44 // Unused
#define INFTABLE_45 0x45 // Unused
#define INFTABLE_46 0x46 // Unused
#define INFTABLE_47 0x47
#define INFTABLE_48 0x48 // Unused
#define INFTABLE_49 0x49 // Unused
#define INFTABLE_4A 0x4A // Unused
#define INFTABLE_4B 0x4B // Unused
#define INFTABLE_4C 0x4C // Unused
#define INFTABLE_4D 0x4D // Unused
#define INFTABLE_4E 0x4E // Unused
#define INFTABLE_4F 0x4F // Unused
#define INFTABLE_50 0x50 // Unused
#define INFTABLE_51 0x51
#define INFTABLE_52 0x52 // Unused
#define INFTABLE_53 0x53 // Unused
#define INFTABLE_54 0x54 // Unused
#define INFTABLE_55 0x55 // Unused
#define INFTABLE_56 0x56 // Unused
#define INFTABLE_57 0x57 // Unused
#define INFTABLE_58 0x58 // Unused
#define INFTABLE_59 0x59
#define INFTABLE_5A 0x5A // Unused
#define INFTABLE_5B 0x5B // Unused
#define INFTABLE_5C 0x5C // Unused
#define INFTABLE_5D 0x5D // Unused
#define INFTABLE_5E 0x5E // Unused
#define INFTABLE_5F 0x5F // Unused
#define INFTABLE_60 0x60 // Unused
#define INFTABLE_61 0x61
#define INFTABLE_62 0x62 // Unused
#define INFTABLE_63 0x63 // Unused
#define INFTABLE_64 0x64 // Unused
#define INFTABLE_65 0x65 // Unused
#define INFTABLE_66 0x66
#define INFTABLE_67 0x67 // Unused
#define INFTABLE_68 0x68 // Unused
#define INFTABLE_69 0x69 // Unused
#define INFTABLE_6A 0x6A
#define INFTABLE_6B 0x6B // Unused
#define INFTABLE_6C 0x6C
#define INFTABLE_6D 0x6D // Unused
#define INFTABLE_6E 0x6E // Unused
#define INFTABLE_6F 0x6F // Unused
#define INFTABLE_70 0x70 // Unused
#define INFTABLE_71 0x71
#define INFTABLE_72 0x72 // Unused
#define INFTABLE_73 0x73 // Unused
#define INFTABLE_74 0x74 // Unused
#define INFTABLE_75 0x75 // Unused
#define INFTABLE_GIVEN_ZELDAS_LETTER 0x76 // (0x8011B4D7 -> 40)
#define INFTABLE_GIVEN_KEATON_MASK 0x77
#define INFTABLE_78 0x78 // Unused
#define INFTABLE_79 0x79 // Unused
#define INFTABLE_7A 0x7A // Unused
#define INFTABLE_7B 0x7B // Unused
#define INFTABLE_7C 0x7C // Unused
#define INFTABLE_7D 0x7D // Unused
#define INFTABLE_TALKED_TO_TALON_IN_RANCH_HOUSE 0x7E
#define INFTABLE_7F 0x7F // Unused
#define INFTABLE_80 0x80 // Unused
#define INFTABLE_81 0x81 // Unused
#define INFTABLE_82 0x82 // Unused
#define INFTABLE_83 0x83 // Unused
#define INFTABLE_84 0x84
#define INFTABLE_TOLD_EPONA_IS_SCARED 0x85
#define INFTABLE_86 0x86 // Unused
#define INFTABLE_87 0x87 // Unused
#define INFTABLE_88 0x88 // Unused
#define INFTABLE_89 0x89 // Unused
#define INFTABLE_8A 0x8A // Unused
#define INFTABLE_MALON_SPAWNED_AT_HYRULE_CASTLE 0x8B
#define INFTABLE_8C 0x8C
#define INFTABLE_8D 0x8D
#define INFTABLE_8E 0x8E
#define INFTABLE_8F 0x8F // Unused
#define INFTABLE_90 0x90 // Unused
#define INFTABLE_91 0x91 // Unused
#define INFTABLE_92 0x92 // Unused
#define INFTABLE_93 0x93 // Unused
#define INFTABLE_94 0x94
#define INFTABLE_95 0x95 // Unused
#define INFTABLE_96 0x96 // Unused
#define INFTABLE_97 0x97
#define INFTABLE_98 0x9A // Unused
#define INFTABLE_99 0x99 // Unused
#define INFTABLE_9A 0x9A
#define INFTABLE_9B 0x9B // Unused
#define INFTABLE_9C 0x9C // Unused
#define INFTABLE_9D 0x9D // Unused
#define INFTABLE_9E 0x9E // Unused
#define INFTABLE_9F 0x9F // Unused
#define INFTABLE_A0 0xA0 // Unused
#define INFTABLE_A1 0xA1 // Unused
#define INFTABLE_A2 0xA2
#define INFTABLE_A3 0xA3 // Unused
#define INFTABLE_A4 0xA4 // Unused
#define INFTABLE_A5 0xA5 // Unused
#define INFTABLE_A6 0xA6 // Unused
#define INFTABLE_A7 0xA7 // Unused
#define INFTABLE_A8 0xA8 // Unused
#define INFTABLE_A9 0xA9 // Unused
#define INFTABLE_AA 0xAA // Unused
#define INFTABLE_AB 0xAB
#define INFTABLE_AC 0xAC // Unused
#define INFTABLE_AD 0xAD // Unused
#define INFTABLE_AE 0xAE // Unused
#define INFTABLE_AF 0xAF // Unused
#define INFTABLE_B0 0xB0
#define INFTABLE_B1 0xB1
#define INFTABLE_B2 0xB2 // Unused
#define INFTABLE_B3 0xB3 // Unused
#define INFTABLE_B4 0xB4
#define INFTABLE_B5 0xB5 // Unused
#define INFTABLE_B6 0xB6
#define INFTABLE_B7 0xB7
#define INFTABLE_B8 0xB8
#define INFTABLE_B9 0xB9
#define INFTABLE_BA 0xBA // Unused
#define INFTABLE_BB 0xBB // Unused
#define INFTABLE_BC 0xBC
#define INFTABLE_BD 0xBD // Unused
#define INFTABLE_BE 0xBE // Unused
#define INFTABLE_BF 0xBF // Unused
#define INFTABLE_C0 0xC0
#define INFTABLE_C1 0xC1
#define INFTABLE_C2 0xC2
#define INFTABLE_C3 0xC3
#define INFTABLE_C4 0xC4
#define INFTABLE_C5 0xC5
#define INFTABLE_C6 0xC6
#define INFTABLE_C7 0xC7
#define INFTABLE_C8 0xC8
#define INFTABLE_C9 0xC9
#define INFTABLE_CA 0xCA
#define INFTABLE_CB 0xCB
#define INFTABLE_CC 0xCC
#define INFTABLE_CD 0xCD
#define INFTABLE_CE 0xCE
#define INFTABLE_CF 0xCF // Unused
#define INFTABLE_D0 0xD0
#define INFTABLE_D1 0xD1 // Unused
#define INFTABLE_D2 0xD2
#define INFTABLE_D3 0xD3 // Unused
#define INFTABLE_D4 0xD4
#define INFTABLE_D5 0xD5 // Unused
#define INFTABLE_D6 0xD6
#define INFTABLE_D7 0xD7 // Unused
#define INFTABLE_D8 0xD8
#define INFTABLE_D9 0xD9
#define INFTABLE_DA 0xDA // Unused
#define INFTABLE_DB 0xDB // Unused
#define INFTABLE_DC 0xDC // Unused
#define INFTABLE_DD 0xDD // Unused
#define INFTABLE_DE 0xDE // Unused
#define INFTABLE_DF 0xDF // Unused
#define INFTABLE_E0 0xE0
#define INFTABLE_E1 0xE1 // Unused
#define INFTABLE_E2 0xE2 // Unused
#define INFTABLE_E3 0xE3
#define INFTABLE_E4 0xE4 // Unused
#define INFTABLE_E5 0xE5 // Unused
#define INFTABLE_E6 0xE6
#define INFTABLE_E7 0xE7 // Unused
#define INFTABLE_E8 0xE8 // Unused
#define INFTABLE_E9 0xE9 // Unused
#define INFTABLE_EA 0xEA // Unused
#define INFTABLE_EB 0xEB
#define INFTABLE_EC 0xEC // Unused
#define INFTABLE_ED 0xED // Unused
#define INFTABLE_EE 0xEE // Unused
#define INFTABLE_EF 0xEF // Unused
#define INFTABLE_F0 0xF0
#define INFTABLE_F1 0xF1 // Unused
#define INFTABLE_F2 0xF2 // Unused
#define INFTABLE_F3 0xF3 // Unused
#define INFTABLE_F4 0xF4
#define INFTABLE_F5 0xF5 // Unused
#define INFTABLE_F6 0xF6 // Unused
#define INFTABLE_F7 0xF7 // Unused
#define INFTABLE_F8 0xF8
#define INFTABLE_F9 0xF9 // Unused
#define INFTABLE_FA 0xFA // Unused
#define INFTABLE_FB 0xFB // Unused
#define INFTABLE_FC 0xFC
#define INFTABLE_FD 0xFD // Unused
#define INFTABLE_FE 0xFE // Unused
#define INFTABLE_FF 0xFF // Unused
#define INFTABLE_100 0x100 // Unused
#define INFTABLE_101 0x101 // Unused
#define INFTABLE_102 0x102 // Unused
#define INFTABLE_103 0x103 // Unused
#define INFTABLE_104 0x104 // Unused
#define INFTABLE_105 0x105 // Unused
#define INFTABLE_106 0x106 // Unused
#define INFTABLE_107 0x107 // Unused
#define INFTABLE_108 0x108 // Unused
#define INFTABLE_109 0x109
#define INFTABLE_10A 0x10A
#define INFTABLE_10B 0x10B
#define INFTABLE_10C 0x10C
#define INFTABLE_10D 0x10D
#define INFTABLE_10E 0x10E
#define INFTABLE_10F 0x10F
#define INFTABLE_110 0x110 // Unused
#define INFTABLE_111 0x111 // Unused
#define INFTABLE_112 0x112 // Unused
#define INFTABLE_113 0x113
#define INFTABLE_114 0x114 // Unused
#define INFTABLE_115 0x115 // Unused
#define INFTABLE_116 0x116 // Unused
#define INFTABLE_117 0x117 // Unused
#define INFTABLE_118 0x118 // Unused
#define INFTABLE_119 0x119 // Unused
#define INFTABLE_11A 0x11A
#define INFTABLE_11B 0x11B // Unused
#define INFTABLE_11C 0x11C // Unused
#define INFTABLE_11D 0x11D // Unused
#define INFTABLE_11E 0x11E
#define INFTABLE_11F 0x11F // Unused
#define INFTABLE_120 0x120 // Unused
#define INFTABLE_121 0x121 // Unused
#define INFTABLE_122 0x122 // Unused
#define INFTABLE_123 0x123 // Unused
#define INFTABLE_124 0x124
#define INFTABLE_125 0x125 // Unused
#define INFTABLE_126 0x126 // Unused
#define INFTABLE_127 0x127 // Unused
#define INFTABLE_128 0x128 // Unused
#define INFTABLE_129 0x129
#define INFTABLE_12A 0x12A
#define INFTABLE_12B 0x12B // Unused
#define INFTABLE_12C 0x12C // Unused
#define INFTABLE_12D 0x12D // Unused
#define INFTABLE_12E 0x12E // Unused
#define INFTABLE_12F 0x12F // Unused
#define INFTABLE_130 0x130 // Unused
#define INFTABLE_131 0x131 // Unused
#define INFTABLE_132 0x132 // Unused
#define INFTABLE_133 0x133 // Unused
#define INFTABLE_134 0x134 // Unused
#define INFTABLE_135 0x135 // Unused
#define INFTABLE_136 0x136 // Unused
#define INFTABLE_137 0x137 // Unused
#define INFTABLE_UNFROZEN_KING_ZORA 0x138
#define INFTABLE_139 0x139
#define INFTABLE_13A 0x13A // Unused
#define INFTABLE_13B 0x13B // Unused
#define INFTABLE_13C 0x13C // Unused
#define INFTABLE_13D 0x13D // Unused
#define INFTABLE_13E 0x13E // Unused
#define INFTABLE_13F 0x13F // Unused
#define INFTABLE_140 0x140
#define INFTABLE_141 0x141
#define INFTABLE_142 0x142
#define INFTABLE_143 0x143
#define INFTABLE_144 0x144
#define INFTABLE_145 0x145
#define INFTABLE_146 0x146
#define INFTABLE_147 0x147
#define INFTABLE_148 0x148 // Unused
#define INFTABLE_149 0x149 // Unused
#define INFTABLE_14A 0x14A // Unused
#define INFTABLE_14B 0x14B // Unused
#define INFTABLE_14C 0x14C // Unused
#define INFTABLE_14D 0x14D // Unused
#define INFTABLE_14E 0x14E // Unused
#define INFTABLE_14F 0x14F // Unused
#define INFTABLE_150 0x150 // Unused
#define INFTABLE_151 0x151 // Unused
#define INFTABLE_152 0x152 // Unused
#define INFTABLE_153 0x153 // Unused
#define INFTABLE_154 0x154 // Unused
#define INFTABLE_155 0x155 // Unused
#define INFTABLE_156 0x156 // Unused
#define INFTABLE_157 0x157 // Unused
#define INFTABLE_158 0x158 // Unused
#define INFTABLE_159 0x159 // Unused
#define INFTABLE_15A 0x15A // Unused
#define INFTABLE_15B 0x15B // Unused
#define INFTABLE_15C 0x15C // Unused
#define INFTABLE_15D 0x15D // Unused
#define INFTABLE_15E 0x15E // Unused
#define INFTABLE_15F 0x15F // Unused
#define INFTABLE_160 0x160
#define INFTABLE_161 0x161
#define INFTABLE_162 0x162
#define INFTABLE_163 0x163
#define INFTABLE_164 0x164
#define INFTABLE_165 0x165 // Unused
#define INFTABLE_166 0x166
#define INFTABLE_167 0x167 // Unused
#define INFTABLE_168 0x168 // Unused
#define INFTABLE_169 0x169 // Unused
#define INFTABLE_16A 0x16A
#define INFTABLE_16B 0x16B // Unused
#define INFTABLE_16C 0x16C
#define INFTABLE_16D 0x16D // Unused
#define INFTABLE_16E 0x16E // Unused
#define INFTABLE_16F 0x16F // Unused
#define INFTABLE_170 0x170
#define INFTABLE_171 0x171
#define INFTABLE_172 0x172
#define INFTABLE_173 0x173 // Unused
#define INFTABLE_174 0x174 // Unused
#define INFTABLE_175 0x175 // Unused
#define INFTABLE_176 0x176
#define INFTABLE_177 0x177 // Unused
#define INFTABLE_178 0x178
#define INFTABLE_179 0x179 // Unused
#define INFTABLE_17A 0x17A // Unused
#define INFTABLE_17B 0x17B // Unused
#define INFTABLE_17C 0x17C
#define INFTABLE_17F 0x17F
#define INFTABLE_180 0x180 // Unused
#define INFTABLE_181 0x181 // Unused
#define INFTABLE_182 0x182 // Unused
#define INFTABLE_183 0x183 // Unused
#define INFTABLE_184 0x184 // Unused
#define INFTABLE_185 0x185 // Unused
#define INFTABLE_186 0x186 // Unused
#define INFTABLE_187 0x187 // Unused
#define INFTABLE_188 0x188 // Unused
#define INFTABLE_189 0x189 // Unused
#define INFTABLE_18A 0x18A // Unused
#define INFTABLE_18B 0x18B // Unused
#define INFTABLE_18C 0x18C // Unused
#define INFTABLE_18D 0x18D // Unused
#define INFTABLE_18E 0x18E // Unused
#define INFTABLE_18F 0x18F // Unused
#define INFTABLE_190 0x190
#define INFTABLE_191 0x191
#define INFTABLE_HAS_DEKU_STICK_UPGRADE 0x192
#define INFTABLE_HAS_DEKU_NUT_UPGRADE 0x193
#define INFTABLE_194 0x194 // Unused
#define INFTABLE_195 0x195
#define INFTABLE_196 0x196
#define INFTABLE_197 0x197
#define INFTABLE_198 0x198

// 0x199-0x19F
#define INFTABLE_199_19A_19B_19C_19D_19E_19F_INDEX 25
#define INFTABLE_199_MASK (1 << 9)
#define INFTABLE_19A_MASK (1 << 10)
#define INFTABLE_19B_MASK (1 << 11)
#define INFTABLE_19C_MASK (1 << 12)
#define INFTABLE_19D_MASK (1 << 13)
#define INFTABLE_19E_MASK (1 << 14)
#define INFTABLE_19F_MASK (1 << 15)

// 0x1A0-0x1AF
#define INFTABLE_1AX_INDEX 26
#define INFTABLE_1A0_SHIFT 0
#define INFTABLE_1A1_SHIFT 1
#define INFTABLE_1A2_SHIFT 2
#define INFTABLE_1A3_SHIFT 3
#define INFTABLE_1A4_SHIFT 4
#define INFTABLE_1A5_SHIFT 5
#define INFTABLE_1A6_SHIFT 6
#define INFTABLE_1A7_SHIFT 7
#define INFTABLE_1A8_SHIFT 8
#define INFTABLE_1A9_SHIFT 9
#define INFTABLE_1AB_SHIFT 11
#define INFTABLE_1AD_SHIFT 13

#define INFTABLE_1B0 0x1B0 // Unused
#define INFTABLE_1B1 0x1B1 // Unused
#define INFTABLE_1B2 0x1B2 // Unused
#define INFTABLE_1B3 0x1B3 // Unused
#define INFTABLE_1B4 0x1B4 // Unused
#define INFTABLE_1B5 0x1B5 // Unused
#define INFTABLE_1B6 0x1B6 // Unused
#define INFTABLE_1B7 0x1B7 // Unused
#define INFTABLE_1B8 0x1B8 // Unused
#define INFTABLE_1B9 0x1B9 // Unused
#define INFTABLE_1BA 0x1BA // Unused
#define INFTABLE_1BB 0x1BB // Unused
#define INFTABLE_1BC 0x1BC // Unused
#define INFTABLE_1BD 0x1BD // Unused
#define INFTABLE_1BE 0x1BE // Unused
#define INFTABLE_1BF 0x1BF // Unused
#define INFTABLE_1C0 0x1C0 // Unused
#define INFTABLE_1C1 0x1C1 // Unused
#define INFTABLE_1C2 0x1C2 // Unused
#define INFTABLE_1C3 0x1C3 // Unused
#define INFTABLE_1C4 0x1C4 // Unused
#define INFTABLE_1C5 0x1C5 // Unused
#define INFTABLE_1C6 0x1C6 // Unused
#define INFTABLE_1C7 0x1C7 // Unused
#define INFTABLE_1C8 0x1C8 // Unused
#define INFTABLE_1C9 0x1C9 // Unused
#define INFTABLE_1CA 0x1CA // Unused
#define INFTABLE_1CB 0x1CB // Unused
#define INFTABLE_1CC 0x1CC // Unused
#define INFTABLE_1CD 0x1CD // Unused
#define INFTABLE_1CE 0x1CE // Unused
#define INFTABLE_1CF 0x1CF // Unused

// 0x1D0-0x1DF
#define INFTABLE_1DX_INDEX 29


#endif
