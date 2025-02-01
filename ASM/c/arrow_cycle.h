#ifndef ARROW_CYCLE_H
#define ARROW_CYCLE_H

#include "z64.h"

bool              actor_helper_does_actor_exist(z64_actor_t*     target, z64_game_t* ctxt, u8 actorCategory);
z64_actor_t*      arrow_cycle_find_arrow(       z64_link_t*      player, z64_game_t* ctxt);
void              arrow_cycle_handle(           z64_link_t*      player, z64_game_t* ctxt);
void*             reloc_resolve_actor_overlay(  z64_actor_ovl_t* ovl,    u32         vram);
z64_actor_init_t* reloc_resolve_actor_init(     z64_actor_ovl_t* ovl);


#endif
