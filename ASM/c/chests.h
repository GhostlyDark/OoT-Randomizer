#ifndef CHESTS_H
#define CHESTS_H

#include "z64.h"

struct EnBox;

typedef void (*EnBoxActionFunc)(struct EnBox *, z64_game_t *);

typedef struct EnBox {
    /* 0x0000 */ DynaPolyActor   dyna;
    /* 0x0154 */ u8              skelanime[0x44];
    /* 0x0198 */ s32             unk_198;
    /* 0x019C */ s32             sub_cam_id;
    /* 0x01A0 */ float           unk_1A0;
    /* 0x01A4 */ EnBoxActionFunc action_func;
    /* 0x01A8 */ z64_xyz_t       joint_table[5];
    /* 0x01C6 */ z64_xyz_t       morph_table[5];
    /* 0x01E4 */ s16             unk_1E4;
    /* 0x01E6 */ u8              movement_flags;
    /* 0x01E7 */ u8              alpha;
    /* 0x01E8 */ u8              switch_flag;
    /* 0x01E9 */ u8              type;
    /* 0x01EA */ u8              ice_smoke_timer;
    /* 0x01EB */ u8              unk_1EB;
} EnBox; // size = 0x01EC

void draw_chest(z64_game_t *game, s32 part, void *unk, void *unk2, z64_actor_t *actor, Gfx **opa_ptr);

#endif
