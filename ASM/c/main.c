#include "gfx.h"
#include "text.h"
#include "util.h"
#include "dpad.h"
#include "actor.h"
#include "arrow_cycle.h"
#include "misc_colors.h"
#include "hud_colors.h"
#include "z64.h"

s8 last_scene = -1;

void Gameplay_InitSkybox(z64_game_t* globalCtx, s16 skyboxId);

void c_init() {
    heap_init();
    gfx_init();
    text_init();
}

void before_game_state_update() {
    arrow_cycle_handle(&z64_link, &z64_game);
    handle_dpad();
    update_misc_colors();
    update_hud_colors();
}

void after_game_state_update() {
    get_health(z64_game.target_actor);
    process_enemy_health();
    draw_dpad();
    handle_restore_mask();
}

void before_skybox_init(z64_game_t* game, s16 skyboxId) {
    Gameplay_InitSkybox(game, skyboxId);
}

void after_scene_init() {
    last_scene = z64_game.scene_index;
}
