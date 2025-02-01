#include "actor.h"

extern u16 CURR_ACTOR_SPAWN_INDEX;
extern u16 play_sfx;

u8 currentHealth = 0;
u8 maxHealth     = 0;
static actor_backup actorBackup = { .scene = -1, .id = 0, .x = 0, .y = 0, .z = 0, .xr = 0, .yr = 0, .zr = 0, .var = 0 };

void get_health(z64_actor_t* actor) {
    if (actor == NULL)
        currentHealth = 0;
    else {
        currentHealth = set_health(actor);
        maxHealth     = *MaxHealth(actor);
    }
}

u8 set_health(z64_actor_t* actor) {
    u16 id  = actor->actor_id;
    
    if (actor->actor_type != ACTORTYPE_ENEMY && actor->actor_type != ACTORTYPE_BOSS && id != EN_IK)
        return 0;
    if (id == BOSS_DODONGO)
        return HP_KING_DODONGO;
    if (id == BOSS_VA)
        return HP_BARINADE;
    if (id == BOSS_GANONDROF)
        return HP_PHANTOM_GANON;
    if (id == BOSS_MO)
        return HP_MORPHA;
    if (id == BOSS_TW)
        return HP_TWINROVA;
    if (id == BOSS_GANON)
        return HP_GANONDORF;
    if (id == BOSS_GANON2)
        return HP_GANON;
    
    if (id == EN_FD) {
        if (actor->child)
            return actor->child->health;
        return 0;
    }
    
    if (id == BOSS_FD2) {
        if (actor->parent)
            return actor->parent->health;
        return 0;
    }
    
    return actor->health;
}

void draw_health(z64_disp_buf_t *db) {
    if (OPTION_ACTIVE(1, SAVE_MASK_ABILITIES, CFG_DEFAULT_MASK_ABILITIES)) {
        if (z64_link.current_mask != PLAYER_MASK_TRUTH && !z64_game.actor_ctxt.lens_active)
            return;
    }
    else if (!OPTION_ACTIVE(1, SAVE_SHOW_HEALTH, CFG_DEFAULT_SHOW_HEALTH))
        return;
    if (z64_file.hud_visibility_mode == HUD_VISIBILITY_NOTHING || !CAN_DRAW_HUD || !CAN_CONTROL_LINK || z64_textbox != 0 || currentHealth == 0 || maxHealth == 0)
        return;
    
    u16 x       = z64_file.rupees > 9999 ? 90 : (z64_file.rupees > 999 ? 80 : 70);
    u16 y       = 205;
    u8 length   = 30;
    u8 division = currentHealth * length / maxHealth;
    
    gDPSetCombineMode(db->p++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    sprite_load_and_draw(db, &linkhead_skull_sprite, 1, x, y, 16, 16);
    
    x += 15;
    y += 3;
    
    gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    sprite_load_and_draw(db, &magic_meter_mid, 0, x+8, y, length, 16);
    sprite_load_and_draw(db, &magic_meter_end, 0, x,   y, 8,      16);
    
    gDPLoadTextureBlock(db->p++, magic_meter_end.buf + (0 * (8 * 16 * magic_meter_end.bytes_per_texel)), G_IM_FMT_IA, G_IM_SIZ_8b, 8, 16, 0, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 3, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(db->p++, (x+length+8)<<2, y<<2, (x+length+16)<<2, (y+16)<<2, G_TX_RENDERTILE, 256, 0, 1<<10, 1<<10);
    
    gDPSetPrimColor(db->p++, 0, 0, 200, 0, 0, 0xFF);
    gDPLoadMultiBlock_4b(db->p++, magic_meter_fill.buf + (0 * (8 * 8 * magic_meter_fill.bytes_per_texel)), 0x0000, G_TX_RENDERTILE, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle(db->p++, (x+8)<<2, (y+3)<<2, (x+division+8)<<2, (y+10)<<2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
}

void restore_spawner_backup(z64_game_t *game) {
    if (actorBackup.scene < 0 || z64_link.current_mask == PLAYER_MASK_SKULL || z64_link.current_mask == PLAYER_MASK_GORON)
        return;
    else if (actorBackup.scene != z64_game.scene_index)
        actorBackup.scene = -1;
    else {
        z64_SpawnActor(&game->actor_ctxt, game, actorBackup.id, actorBackup.x, actorBackup.y, actorBackup.z, actorBackup.xr, actorBackup.yr, actorBackup.zr, actorBackup.var);
        actorBackup.scene = -1;
    }
}

void remove_enemy_spawner() {
    if (actorBackup.scene >= 0 || z64_link.current_mask != PLAYER_MASK_SKULL)
        return;
    
    z64_actor_t *actor = z64_game.actor_list[ACTORTYPE_PROP].first;
    while (actor != NULL) {
        if (actor->actor_id == EN_ENCOUNT1) {
            set_actor_backup(actor);
            break;
        }
        actor = actor->next;
    }
}

void remove_falling_rocks_spawner() {
    if (actorBackup.scene >= 0 || z64_link.current_mask != PLAYER_MASK_GORON)
        return;
    
    z64_actor_t *actor = z64_game.actor_list[ACTORTYPE_ENEMY].first;
    while (actor != NULL) {
        if (actor->actor_id == EN_ENCOUNT2) {
            set_actor_backup(actor);
            break;
        }
        actor = actor->next;
    }
}

void set_actor_backup(z64_actor_t *actor) {
    actorBackup.scene = z64_game.scene_index;
    actorBackup.id    = actor->actor_id;
    actorBackup.x     = actor->pos_init.x;
    actorBackup.y     = actor->pos_init.y;
    actorBackup.z     = actor->pos_init.z;
    actorBackup.xr    = actor->rot_init.x;
    actorBackup.yr    = actor->rot_init.y;
    actorBackup.zr    = actor->rot_init.z;
    actorBackup.var   = actor->variable;
    z64_ActorKill(actor);
}

void process_enemy_health() {
    if (!CAN_CONTROL_LINK)
        return;
    
    z64_actor_t *enemy = z64_game.actor_list[ACTORTYPE_ENEMY].first;
    while (enemy != NULL) {
        if (*MaxHealth(enemy) == 0) {
            u16 id = enemy->actor_id;
            
            if (OPTION_ACTIVE(2, SAVE_RANDOM_ENEMIES, CFG_DEFAULT_RANDOM_ENEMIES) && id != EN_ST && id != EN_ANUBICE && id != EN_FZ && enemy->health > 1) {
                float rand = z64_Rand_ZeroOne();
                if (rand >= 0.4) {
                    float factor = 1.5;
                    if (rand <= 0.8)
                        factor = 1.75;
                    else if (rand <= 1.0)
                        factor = 2;
                    
                    u8 add = (enemy->health & 20) * factor;
                    if (factor == 1.5 && add < 1)
                        add = 1;
                    else if (factor == 1.75 && add < 2)
                        add = 2;
                    else if (factor == 2 && add < 3)
                        add = 3;
                    enemy->health += add;
                }
            }
            
            *MaxHealth(enemy) = set_health(enemy);
        }
        enemy = enemy->next;
    }
}

z64_actor_t* replace_enemy_type(z64_actor_t* spawned) {
    if (!OPTION_ACTIVE(2, SAVE_RANDOM_ENEMIES, CFG_DEFAULT_RANDOM_ENEMIES) || spawned->actor_type != ACTORTYPE_ENEMY)
        return spawned;
        
    float rand = z64_Rand_ZeroOne();
    if (rand < 0.65)
        return spawned;
    
    switch (spawned->actor_id) {
        case EN_TEST:
            if (spawned->variable == EN_TEST_CEILING)
                spawned->variable == EN_TEST_INVISIBLE;
            break;
        
        case EN_FIREFLY:
            if (spawned->variable & 4 == EN_FIREFLY_NORMAL_FLY) {
                rand = z64_Rand_ZeroOne();
                if (rand >= 0.5)
                    spawned->variable = ( ( (spawned->variable >> 8) & 0xFF) << 8) + EN_FIREFLY_FIRE_FLY;
                else spawned->variable = ( ( (spawned->variable >> 8) & 0xFF) << 8) + EN_FIREFLY_ICE_FLY;
            }
            else if (spawned->variable & 4 == EN_FIREFLY_NORMAL_ROOST)
                spawned->variable = ( ( (spawned->variable >> 8) & 0xFF) << 8) + EN_FIREFLY_FIRE_ROOST;
            
            if (spawned->variable >> 8 & 0x80 == EN_FIREFLY_VISIBLE) {
                rand = z64_Rand_ZeroOne();
                if (rand >= 0.5)
                    spawned->variable = EN_FIREFLY_INVISIBLE + spawned->variable & 4;
            }
            break;
        
        case EN_TITE:
            if (spawned->variable == EN_TITE_RED)
                spawned->variable = EN_TITE_BLUE;
            spawned->damage += 0x10;
            break;
        
        case EN_REEBA:
            if (spawned->variable == EN_REEBA_SMALL)
                spawned->variable = EN_REEBA_BIG;
            break;
        
        case EN_ZF:
            if (spawned->variable & 0xFF == EN_ZF_LIZALFOS)
                spawned->variable = ( ( (spawned->variable >> 8) & 0xFF) << 8) + EN_ZF_DINOLFOS;
            break;
        
        case EN_ST:
            if (spawned->variable == EN_ST_NORMAL)
                spawned->variable = EN_ST_INVISIBLE;
            break;
        
        case EN_FLOORMAS:
            if (spawned->variable == EN_FLOORMAS_VISIBLE)
                spawned->variable = EN_FLOORMAS_INVISIBLE;
            break;
        
        case EN_RD:
            if (spawned->variable & 0xFF == EN_RD_REDEAD)
                spawned->variable = ( ( (spawned->variable >> 8) & 0xFF) << 8) + EN_RD_GIBDO;
            break;
        
        case EN_IK:
            if (spawned->variable & 0xFF == EN_IK_BLACK)
                spawned->variable = ( ( (spawned->variable >> 8) & 0xFF) << 8) + EN_IK_WHITE;
            break;
        
        default:
            break;
    }
    
    return spawned;
}

z64_actor_t* Actor_SpawnEntry_Hack(void *actorCtx, ActorEntry *actorEntry, z64_game_t *globalCtx) {
    z64_actor_t* spawned = z64_SpawnActor(actorCtx, globalCtx, actorEntry->id, actorEntry->pos.x, actorEntry->pos.y, actorEntry->pos.z, actorEntry->rot.x, actorEntry->rot.y, actorEntry->rot.z, actorEntry->params);
    
    if (spawned)
        spawned = replace_enemy_type(spawned);
    return spawned;
}