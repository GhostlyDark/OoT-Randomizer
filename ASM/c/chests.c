#include "chests.h"
#include "n64.h"
#include "gfx.h"

#define BROWN_FRONT_TEXTURE        0x06001798
#define BROWN_BASE_TEXTURE         0x06002798
#define GOLD_FRONT_TEXTURE         0x06002F98
#define GOLD_BASE_TEXTURE          0x06003798

#define CHEST_BASE                 1
#define CHEST_LID                  3

#define LARGE_CHEST                0
#define LARGE_CHEST_APPEARS_CLEAR  1
#define BOSS_CHEST                 2
#define LARGE_CHEST_FALLING_SWITCH 3
#define LARGE_CHEST_INVISIBLE      4
#define SMALL_CHEST                5
#define SMALL_CHEST_INVISIBLE      6
#define SMALL_CHEST_APPEARS_CLEAR  7
#define SMALL_CLEAR_FALLING_SWITCH 8
#define LARGE_CHEST_ZELDAS_LULLABY 9
#define LARGE_CHEST_SUNS_SONG      10
#define LARGE_CHEST_APPEARS_SWITCH 11

#define IS_LARGE_CHEST (chest_type == LARGE_CHEST || chest_type == LARGE_CHEST_APPEARS_CLEAR || chest_type == LARGE_CHEST_FALLING_SWITCH || chest_type == LARGE_CHEST_INVISIBLE || chest_type == LARGE_CHEST_ZELDAS_LULLABY || chest_type == LARGE_CHEST_SUNS_SONG || chest_type == LARGE_CHEST_APPEARS_SWITCH)

extern void* LEATHER_CHEST_FRONT_TEXTURE;
extern void* LEATHER_CHEST_BASE_TEXTURE;
extern void* LEATHER_SYEO_CHEST_FRONT_TEXTURE;
extern void* LEATHER_SYEO_CHEST_BASE_TEXTURE;
extern void* KEY_CHEST_FRONT_TEXTURE;
extern void* KEY_CHEST_BASE_TEXTURE;

extern Mtx_t* write_matrix_stack_top(z64_gfx_t* gfx);
asm(".equ write_matrix_stack_top, 0x800AB900");

u8 get_chest_type(z64_actor_t *actor) {
    return ((EnBox *)actor)->type;
}

void set_chest_texture(z64_gfx_t *gfx, u8 chest_type, u8 chest_item, Gfx **opa_ptr) {
    void* frontTexture = (void*)BROWN_FRONT_TEXTURE;
    void* baseTexture  = (void*)BROWN_BASE_TEXTURE;
    u8 id              = chest_item;

    if (OPTION_ACTIVE(1, SAVE_CHEST_CONTENTS, CFG_DEFAULT_CHEST_CONTENTS)) {
        if (IS_LARGE_CHEST) {
            if ( (id >= CHEST_FAIRY_BOW && id <= CHEST_BOOMERANG) || (id >= CHEST_HOOKSHOT && id <= CHEST_LENS_OF_TRUTH) || (id >= CHEST_IRON_BOOTS && id <= CHEST_GOLDEN_SCALE) || (id >= CHEST_FIRE_ARROW && id <= CHEST_LIGHT_ARROW) || (id >= CHEST_DINS_FIRE && id <= CHEST_NAYRUS_LOVE)
                    || id == CHEST_MEGATON_HAMMER || id == CHEST_FAIRY_OCARINA || id == CHEST_MIRROR_SHIELD || id == CHEST_DUNGEON_MAP || id == CHEST_COMPASS) {
                frontTexture = &LEATHER_CHEST_FRONT_TEXTURE;
                baseTexture  = &LEATHER_CHEST_BASE_TEXTURE;
            }
        }
        else if (id == CHEST_SMALL_KEY) { 
            frontTexture = &KEY_CHEST_FRONT_TEXTURE;
            baseTexture  = &KEY_CHEST_BASE_TEXTURE;
        }
    }

    gfx->poly_opa.d -= 4;
    gDPSetTextureImage(gfx->poly_opa.d, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, frontTexture);
    gSPEndDisplayList(gfx->poly_opa.d + 1);
    gDPSetTextureImage(gfx->poly_opa.d + 2, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, baseTexture);
    gSPEndDisplayList(gfx->poly_opa.d + 3);
    gSPSegment((*opa_ptr)++, 0x09, gfx->poly_opa.d);
}

void draw_chest_base(z64_game_t *game, z64_actor_t *actor, Gfx **opa_ptr) {
    z64_gfx_t *gfx = game->common.gfx;
    u8 chest_type  = get_chest_type(actor);
    u8 chest_item  = (actor->variable & 0x0FE0) >> 5;
    
    gSPMatrix((*opa_ptr)++, write_matrix_stack_top(gfx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    
    if (chest_type != BOSS_CHEST) {
        set_chest_texture(gfx, chest_type, chest_item, opa_ptr);
        gSPDisplayList((*opa_ptr)++, 0x060006F0);
    }
    else gSPDisplayList((*opa_ptr)++, 0x06000AE8);
}

void draw_chest_lid(z64_game_t *game, z64_actor_t *actor, Gfx **opa_ptr) {
    z64_gfx_t *gfx = game->common.gfx;
    u8 chest_type  = get_chest_type(actor);
    u8 chest_item  = (actor->variable & 0x0FE0) >> 5;
    
    gSPMatrix((*opa_ptr)++, write_matrix_stack_top(gfx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    
    if (chest_type != BOSS_CHEST) {
        set_chest_texture(gfx, chest_type, chest_item, opa_ptr);
        gSPDisplayList((*opa_ptr)++, 0x060010C0);
    }
    else gSPDisplayList((*opa_ptr)++, 0x06001678);
}

void draw_chest(z64_game_t *game, s32 part, void *unk, void *unk2, z64_actor_t *actor, Gfx **opa_ptr) {
    if (part == CHEST_BASE)
        draw_chest_base(game, actor, opa_ptr);
    else if (part == CHEST_LID) draw_chest_lid(game, actor, opa_ptr);
}