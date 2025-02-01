#include "dungeon_info.h"

extern u16 play_sfx;

bool dungeon_overlay = false;
s8   dungeon_overlay_index_start;
s8   dungeon_overlay_index_end;

static dungeon_entry_t dungeons[] = {
    {  0, false, false, true,  0x0F, { Z64_ITEM_SLINGSHOT,        Z64_ITEM_NONE,          }, Z64_ITEM_KOKIRIS_EMERALD,  "Deku Tree"          },
    {  1, false, false, true,  0x1F, { Z64_ITEM_BOMB,             Z64_ITEM_NONE,          }, Z64_ITEM_GORONS_RUBY,      "Dodongo's Cavern"   },
    {  2, false, false, true,  0x0F, { Z64_ITEM_BOOMERANG,        Z64_ITEM_NONE,          }, Z64_ITEM_ZORAS_SAPPHIRE,   "Jabu-Jabu"          },
    {  3, true,  true,  true,  0x1F, { Z64_ITEM_BOW,              Z64_ITEM_NONE,          }, Z64_ITEM_MEDALLION_FOREST, "Forest Temple"      },
    {  4, true,  true,  true,  0x1F, { Z64_ITEM_HAMMER,           Z64_ITEM_NONE,          }, Z64_ITEM_MEDALLION_FIRE,   "Fire Temple"        },
    {  5, true,  true,  true,  0x1F, { Z64_ITEM_LONGSHOT,         Z64_ITEM_NONE,          }, Z64_ITEM_MEDALLION_WATER,  "Water Temple"       },
    {  7, true,  true,  true,  0x1F, { Z64_ITEM_HOVER_BOOTS,      Z64_ITEM_NONE,          }, Z64_ITEM_MEDALLION_SHADOW, "Shadow Temple"      },
    {  6, true,  true,  true,  0x1F, { Z64_ITEM_SILVER_GAUNTLETS, Z64_ITEM_MIRROR_SHIELD, }, Z64_ITEM_MEDALLION_SPIRIT, "Spirit Temple"      },
    {  9, false, false, true,  0x07, { Z64_ITEM_IRON_BOOTS,       Z64_ITEM_NONE,          }, Z64_ITEM_SERENADE,         "Ice Cavern"         },
    {  8, true,  false, true,  0x07, { Z64_ITEM_LENS,             Z64_ITEM_NONE,          }, Z64_ITEM_NONE,             "Bottom of the Well" },
    { 12, true,  false, false, 0x00, { Z64_ITEM_NONE,             Z64_ITEM_NONE,          }, Z64_ITEM_GERUDOS_CARD,     "Thieves' Hideout"   },
    { 11, true,  false, false, 0x00, { Z64_ITEM_ICE_ARROW,        Z64_ITEM_NONE,          }, Z64_ITEM_NONE,             "Training Ground"    },
    { 13, true,  true,  false, 0x00, { Z64_ITEM_GOLDEN_GAUNTLETS, Z64_ITEM_NONE,          }, Z64_ITEM_NONE,             "Ganon's Castle"     },
};
u8 dungeon_count = ARRAY_SIZE(dungeons);

static medal_color_t medal_colors[] = {
    { 0x00, 0xFF, 0x00 }, // Forest
    { 0xFF, 0x3C, 0x00 }, // Fire
    { 0x00, 0x64, 0xFF }, // Water
    { 0xFF, 0x82, 0x00 }, // Spirit
    { 0xC8, 0x32, 0xFF }, // Shadow
    { 0xC8, 0xC8, 0x00 }, // Light
};

bool draw_dungeon_info(z64_disp_buf_t* db) {
    if (z64_game.pause_ctxt.state != PAUSE_STATE_MAIN || z64_game.pause_ctxt.debugState != 0 || z64_game.pause_ctxt.pageIndex != SUBSCREEN_MAP || z64_game.pause_ctxt.mainState || !(OPTION_ACTIVE(1, SAVE_SHOW_OVERLAY, CFG_DEFAULT_SHOW_OVERLAY))) {
        dungeon_overlay = false;
        return false;
    }
    
    pad_t pad_pressed = z64_game.common.input[0].pad_pressed;
    
    if (pad_pressed.a) {
        dungeon_overlay            ^= 1;
        dungeon_overlay_index_start = 0;
        play_sfx = dungeon_overlay ? 0x4813 : 0x4814;
    }
    
    if (!dungeon_overlay)
        return false;
    
     if (pad_pressed.dr || pad_pressed.cr) {
        dungeon_overlay_index_start += DUNGEON_OVERLAY_RANGE;
        play_sfx = 0x4839;
    }
    else if (pad_pressed.dl || pad_pressed.cl) {
        dungeon_overlay_index_start -= DUNGEON_OVERLAY_RANGE;
        play_sfx = 0x4839;
    }
    
    if (dungeon_overlay_index_start > dungeon_count)
        dungeon_overlay_index_start = 0;
    else if (dungeon_overlay_index_start < 0)
        dungeon_overlay_index_start = dungeon_count - (dungeon_count % DUNGEON_OVERLAY_RANGE);
    
    dungeon_overlay_index_end = dungeon_overlay_index_start + DUNGEON_OVERLAY_RANGE;
    if (dungeon_overlay_index_end > dungeon_count)
        dungeon_overlay_index_end = dungeon_count;

    u16 bg_width  = 220;
    u16 bg_height = (DUNGEON_OVERLAY_RANGE * DUNGEON_OVERLAY_ICON_SIZE) + ((DUNGEON_OVERLAY_RANGE + 1) * DUNGEON_OVERLAY_ICON_PADDING) + 20;
    u16 bg_left   =   (Z64_SCREEN_WIDTH  - bg_width)  / 2;
    u16 bg_top    = ( (Z64_SCREEN_HEIGHT - bg_height) / 2) + 15;
    u16 start_top = bg_top  + DUNGEON_OVERLAY_ICON_PADDING;
    
    gDPSetCombineMode(db->p++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(db->p++, 0, 0, 0x00, 0x00, 0x00, 0xD0);
    gSPTextureRectangle(db->p++, bg_left<<2, bg_top<<2, (bg_left + bg_width)<<2, (bg_top + bg_height)<<2, 0, 0, 0, 1<<10, 1<<10);
    
    u16 left = bg_left + DUNGEON_OVERLAY_ICON_PADDING + DUNGEON_OVERLAY_TITLE_WIDTH + (DUNGEON_OVERLAY_ICON_SIZE + DUNGEON_OVERLAY_ICON_PADDING);
    u16 top  = start_top - 20;
    gSPTextureRectangle(db->p++, (left - 2)<<2, (top - 2)<<2, (left + (DUNGEON_OVERLAY_ICON_SIZE + DUNGEON_OVERLAY_ICON_PADDING) * 7 + 4)<<2, (top + DUNGEON_OVERLAY_ICON_SIZE + DUNGEON_OVERLAY_ICON_PADDING + 1)<<2, 0, 0, 0, 1<<10, 1<<10);
    
    gDPSetCombineMode(db->p++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    text_set_size(5, 9);
    
    gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
    sprite_load_and_draw(db, &quest_items_sprite, 17,                 left + (DUNGEON_OVERLAY_ICON_SIZE + DUNGEON_OVERLAY_ICON_PADDING) * 0, top, DUNGEON_OVERLAY_ICON_SIZE, DUNGEON_OVERLAY_ICON_SIZE);
    sprite_load_and_draw(db, &quest_items_sprite, 14,                 left + (DUNGEON_OVERLAY_ICON_SIZE + DUNGEON_OVERLAY_ICON_PADDING) * 1, top, DUNGEON_OVERLAY_ICON_SIZE, DUNGEON_OVERLAY_ICON_SIZE);
    sprite_load_and_draw(db, &quest_items_sprite, 16,                 left + (DUNGEON_OVERLAY_ICON_SIZE + DUNGEON_OVERLAY_ICON_PADDING) * 2, top, DUNGEON_OVERLAY_ICON_SIZE, DUNGEON_OVERLAY_ICON_SIZE);
    sprite_load_and_draw(db, &quest_items_sprite, 15,                 left + (DUNGEON_OVERLAY_ICON_SIZE + DUNGEON_OVERLAY_ICON_PADDING) * 3, top, DUNGEON_OVERLAY_ICON_SIZE, DUNGEON_OVERLAY_ICON_SIZE);
    sprite_load_and_draw(db, &items_sprite,       Z64_ITEM_SLINGSHOT, left + (DUNGEON_OVERLAY_ICON_SIZE + DUNGEON_OVERLAY_ICON_PADDING) * 4, top, DUNGEON_OVERLAY_ICON_SIZE, DUNGEON_OVERLAY_ICON_SIZE);
    sprite_load_and_draw(db, &quest_items_sprite, 11,                 left + (DUNGEON_OVERLAY_ICON_SIZE + DUNGEON_OVERLAY_ICON_PADDING) * 6, top, DUNGEON_OVERLAY_ICON_SIZE, DUNGEON_OVERLAY_ICON_SIZE);
    
    start_top = bg_top + DUNGEON_OVERLAY_ICON_PADDING;
    
    for (u8 i=dungeon_overlay_index_start; i<dungeon_overlay_index_end; i++) {
        dungeon_entry_t *d = &(dungeons[i]);
        left               = bg_left   +   DUNGEON_OVERLAY_ICON_PADDING;
        top                = start_top + ((DUNGEON_OVERLAY_ICON_SIZE + DUNGEON_OVERLAY_ICON_PADDING) * (i - dungeon_overlay_index_start));
        
        gDPPipeSync(db->p++);
        if (d->reward >= Z64_ITEM_MEDALLION_FOREST && d->reward <= Z64_ITEM_MEDALLION_LIGHT && has_quest_reward(d->reward)) {
            medal_color_t *c = &(medal_colors[d->reward - Z64_ITEM_MEDALLION_FOREST]);
            gDPSetPrimColor(db->p++, 0, 0, c->r, c->g, c->b, 0xFF);
            sprite_load_and_draw(db, &medals_sprite, d->reward - Z64_ITEM_MEDALLION_FOREST, left, top, DUNGEON_OVERLAY_ICON_SIZE, DUNGEON_OVERLAY_ICON_SIZE);
        }
        if (d->reward == Z64_ITEM_SERENADE && z64_file.serenade_of_water) {
            medal_color_t *c = &(medal_colors[Z64_ITEM_MEDALLION_WATER - Z64_ITEM_MEDALLION_FOREST]);
            gDPSetPrimColor(db->p++, 0, 0, c->r, c->g, c->b, 0xFF);
            u8 size   =        (u8)round((double) DUNGEON_OVERLAY_ICON_SIZE / 24 * 16);
            u8 offset = left + (u8)round((double)(DUNGEON_OVERLAY_ICON_SIZE - size) / 2);
            sprite_load_and_draw(db, &song_note_sprite, 0, offset, top, size, DUNGEON_OVERLAY_ICON_SIZE);
        }
        
        gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        if (d->reward >= Z64_ITEM_KOKIRIS_EMERALD && d->reward <= Z64_ITEM_ZORAS_SAPPHIRE && has_quest_reward(d->reward))
            sprite_load_and_draw(db, &stones_sprite, d->reward - Z64_ITEM_KOKIRIS_EMERALD, left, top, DUNGEON_OVERLAY_ICON_SIZE, DUNGEON_OVERLAY_ICON_SIZE);
        if (d->reward == Z64_ITEM_GERUDOS_CARD && z64_file.gerudos_card)
            sprite_load_and_draw(db, &quest_items_sprite, 10, left, top, DUNGEON_OVERLAY_ICON_SIZE, DUNGEON_OVERLAY_ICON_SIZE);
        
        left += DUNGEON_OVERLAY_ICON_SIZE + DUNGEON_OVERLAY_ICON_PADDING;
        
        text_print(d->name, left, top + 3);
        left += DUNGEON_OVERLAY_TITLE_WIDTH;
        
        s8 keys = z64_file.dungeon_keys[d->index];
        if (keys >= 0) {
            if (keys > 99)
                keys = 99;
            
            char count[2] = "0";
            count[0] = '0' + keys / 10;
            if (keys > 9)
                count[1] = '0' + keys % 10;
            text_print(count, left, top + 3);
        }
        left += DUNGEON_OVERLAY_ICON_SIZE + DUNGEON_OVERLAY_ICON_PADDING;
        
        if (d->has_boss_key && z64_file.dungeon_items[(d->index == 13) ? 10 : d->index].boss_key)
            sprite_load_and_draw(db, &quest_items_sprite, 14, left, top, DUNGEON_OVERLAY_ICON_SIZE, DUNGEON_OVERLAY_ICON_SIZE);
        left += DUNGEON_OVERLAY_ICON_SIZE + DUNGEON_OVERLAY_ICON_PADDING;
        
        if (d->has_map && z64_file.dungeon_items[d->index].map)
            sprite_load_and_draw(db, &quest_items_sprite, 16, left, top, DUNGEON_OVERLAY_ICON_SIZE, DUNGEON_OVERLAY_ICON_SIZE);
        left += DUNGEON_OVERLAY_ICON_SIZE + DUNGEON_OVERLAY_ICON_PADDING;
        
        if (d->has_map && z64_file.dungeon_items[d->index].compass)
            sprite_load_and_draw(db, &quest_items_sprite, 15, left, top, DUNGEON_OVERLAY_ICON_SIZE, DUNGEON_OVERLAY_ICON_SIZE);
        left += DUNGEON_OVERLAY_ICON_SIZE + DUNGEON_OVERLAY_ICON_PADDING;
        
        for (u8 j=0; j<2; j++) {
            if (d->item[j] != Z64_ITEM_NONE && has_item(d->item[j]))
                sprite_load_and_draw(db, &items_sprite, d->item[j], left, top, DUNGEON_OVERLAY_ICON_SIZE, DUNGEON_OVERLAY_ICON_SIZE);
            left += DUNGEON_OVERLAY_ICON_SIZE + DUNGEON_OVERLAY_ICON_PADDING;
        }
        
        if (d->skulltulas && z64_file.gs_flags[d->index ^ 3] == d->skulltulas)
            sprite_load_and_draw(db, &quest_items_sprite, 11, left, top, DUNGEON_OVERLAY_ICON_SIZE, DUNGEON_OVERLAY_ICON_SIZE);
    }
    
    char page[9] = "Page: 1/1";
    page[6] = '0' + dungeon_overlay_index_start / DUNGEON_OVERLAY_RANGE + 1;
    page[8] = '0' + dungeon_count               / DUNGEON_OVERLAY_RANGE + 1;
    text_set_size(4, 7);
    text_print(page, bg_left + bg_width - 40, bg_top + bg_height - 10);
    
    gDPSetPrimColor(db->p++, 0, 0, 0xD0, 0xD0, 0xD0, 0xFF);
    sprite_load_and_draw(db, &button_sprite, 2, Z64_SCREEN_WIDTH / 2 - 20, bg_top + bg_height - 20, 16, 16);
    sprite_load_and_draw(db, &button_sprite, 4, Z64_SCREEN_WIDTH / 2 + 20, bg_top + bg_height - 20, 16, 16);
    
    text_flush(db);
    gDPFullSync(db->p++);
    gSPEndDisplayList(db->p++);
    return true;
}

bool has_item(u8 item) {
    if ( (z64_file.iron_boots && item == Z64_ITEM_IRON_BOOTS) || (z64_file.hover_boots && item == Z64_ITEM_HOVER_BOOTS) || (z64_file.mirror_shield && item == Z64_ITEM_MIRROR_SHIELD) || (z64_file.strength_upgrade > 1 && item == Z64_ITEM_SILVER_GAUNTLETS) || (z64_file.strength_upgrade > 2 && item == Z64_ITEM_GOLDEN_GAUNTLETS) )
        return true;
    
    for (u8 i=0; i<24; i++)
        if (z64_file.items[i] == item)
            return true;
    return false;
}

bool has_quest_reward(u8 reward) {
    if ( (z64_file.kokiris_emerald && reward == Z64_ITEM_KOKIRIS_EMERALD) || (z64_file.gorons_ruby      && reward == Z64_ITEM_GORONS_RUBY)      || (z64_file.zoras_sapphire   && reward == Z64_ITEM_ZORAS_SAPPHIRE)   || \
         (z64_file.light_medallion && reward == Z64_ITEM_MEDALLION_LIGHT) || (z64_file.forest_medallion && reward == Z64_ITEM_MEDALLION_FOREST) || (z64_file.fire_medallion   && reward == Z64_ITEM_MEDALLION_FIRE)   || \
         (z64_file.water_medallion && reward == Z64_ITEM_MEDALLION_WATER) || (z64_file.shadow_medallion && reward == Z64_ITEM_MEDALLION_SHADOW) || (z64_file.spirit_medallion && reward == Z64_ITEM_MEDALLION_SPIRIT) )
        return true;
    return false;
}