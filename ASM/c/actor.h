#ifndef ACTOR_H
#define ACTOR_H

#include "z64.h"

#include <math.h>

#include "gfx.h"

typedef void(*actor_after_spawn_func)(z64_actor_t* actor, u8 overridden);

void         get_health(            z64_actor_t*    actor);
u8           set_health(            z64_actor_t*    actor);
void         draw_health(           z64_disp_buf_t* db);
void         restore_spawner_backup(z64_game_t*     game);
void         remove_enemy_spawner();
void         remove_falling_rocks_spawner();
void         set_actor_backup(      z64_actor_t*    actor);
void         process_enemy_health();
z64_actor_t* replace_enemy_type   ( z64_actor_t*    spawned);
z64_actor_t* Actor_SpawnEntry_Hack( void*           actorCtx, ActorEntry* actorEntry, z64_game_t* globalCtx);

/* DRAM addresses & data for enemies */
#define HP_KING_DODONGO             (*(u8*)            0x801ECB75)
#define HP_BARINADE                 (*(u8*)            0x801F9590)
#define HP_PHANTOM_GANON            (*(u8*)            0x801E71FF)
#define HP_MORPHA                   (*(u8*)            0x801F253F)
#define HP_TWINROVA_BLUE            (*(u8*)            0x801F88EF)
#define HP_TWINROVA_RED             (*(u8*)            0x801F88EF)
#define HP_TWINROVA                 (*(u8*)            0x801F7F8F)
#define HP_GANONDORF                (*(u8*)            0x8020B5CF)
#define HP_GANON                    (*(u8*)            0x801FA2DF)

#define MaxHealth(actor) ((u8*)(&actor->unk_01_[0]))

typedef struct {
    s8  scene;
    u16 id;
    s16 x;
    s16 y;
    s16 z;
    u16 xr;
    u16 yr;
    u16 zr;
    u16 var;
} actor_backup;

typedef enum {
    EN_TEST        = 0x0002,
    BOSS_DODONGO   = 0x0012, // 0x0027
    EN_FIREFLY     = 0x0013,
    EN_ARROW       = 0x0016,
    EN_TITE        = 0x001B,
    EN_REEBA       = 0x001C,
    EN_ZF          = 0x0025,
    EN_ST          = 0x0037,
    BOSS_GANONDROF = 0x0052,
    EN_AM          = 0x0054,
    EN_FLOORMAS    = 0x008E,
    EN_RD          = 0x0090,
    EN_SW          = 0x0095,
    BOSS_FD        = 0x0096,
    EN_FD          = 0x0099,
    BOSS_FD2       = 0x00A2,
    EN_ENCOUNT1    = 0x00A7,
    EN_FW          = 0x00AB,
    EN_ENCOUNT2    = 0x00B4,
    BOSS_VA        = 0x00BA,
    BOSS_MO        = 0x00C4,
    BOSS_TW        = 0x00DC,
    EN_ANUBICE     = 0x00E0,
    BOSS_GANON     = 0x00E8,
    EN_IK          = 0x0113,
    EN_FZ          = 0x0121,
    BOSS_GANON2    = 0x017A,
    EN_WF          = 0x01AF,
    EN_CROW        = 0x01C0,
} actor_id;

typedef enum {
    EN_TEST_INVISIBLE           = 0,
    EN_TEST_RISES_MINI_BOSS     = 1,
    EN_TEST_RISES_PAIRED        = 2,
    EN_TEST_CEILING             = 3,
    EN_TEST_TYPE_4              = 4,
    EN_TEST_TYPE_5              = 5,
} En_Test;

typedef enum {
    EN_FIREFLY_NORMAL_ROOST     = 3,
    EN_FIREFLY_NORMAL_FLY       = 2,
    EN_FIREFLY_FIRE_ROOST       = 1,
    EN_FIREFLY_FIRE_FLY         = 0,
    EN_FIREFLY_ICE_FLY          = 4,
    EN_FIREFLY_VISIBLE          = 0,
    EN_FIREFLY_INVISIBLE        = 0x8000,
} En_Firefly;

typedef enum {
    EN_TITE_RED                 = 0xFFFF,
    EN_TITE_BLUE                = 0xFFFE,
} En_Tite;

typedef enum {
    EN_REEBA_SMALL              = 0,
    EN_REEBA_BIG                = 1,
} En_Reeba;

typedef enum {
    EN_ZF_LIZALFOS_A            = 0,
    EN_ZF_LIZALFOS_B            = 1,
    EN_ZF_LIZALFOS              = 0x80,
    EN_ZF_DINOLFOS              = 0xFE,
    EN_ZF_DINOLFOS_DROP         = 0xFF,
} En_Zf;

typedef enum {
    EN_ST_NORMAL                = 0,
    EN_ST_BIG                   = 1,
    EN_ST_INVISIBLE             = 2,
} En_St;

typedef enum {
    EN_FLOORMAS_VISIBLE         = 0,
    EN_FLOORMAS_INVISIBLE       = 0x8000,
} En_Floormas;

typedef enum {
    EN_RD_REDEAD                = 1,
    EN_RD_REDEAD_INVISIBLE      = 3,
    EN_RD_REDEAD_CRYING         = 2,
    EN_RD_REDEAD_NO_MOURN       = 0x7F,
    EN_RD_REDEAD_NO_MOURN_WALK  = 0,
    EN_RD_GIBDO                 = 0x7E,
    EN_RD_GIBDO_RISES           = 0x7D,
} En_Rd;

typedef enum {
    EN_IK_NABOORU               = 0,
    EN_IK_WHITE_SITTING         = 1,
    EN_IK_BLACK                 = 2,
    EN_IK_WHITE                 = 3,
    EN_IK_WHITE_NO_ARMOR_DROP   = 11,
} En_Ik;

typedef enum {
    EN_WF_GRAY                  =  0,
    EN_WF_WHITE                 =  1,
} En_Wf;

typedef enum {
    EN_ENCOUNT1_LEEVER          = 0,
    EN_ENCOUNT1_RED_TEKTITE     = 0x800,
    EN_ENCOUNT1_STALCHILD       = 0x1000,
    EN_ENCOUNT1_WOLFOS          = 0x1800,
} En_Encount1;

#endif