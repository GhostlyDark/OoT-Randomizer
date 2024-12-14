#include "gfx.h"
#include "dpad_actions.h"
#include "fps.h"

extern bool CFG_ALLOW_KOKIRI_SWORD, CFG_ALLOW_MASTER_SWORD, CFG_ALLOW_GIANTS_KNIFE, CFG_ALLOW_DEKU_SHIELD, CFG_ALLOW_MIRROR_SHIELD, CFG_ALLOW_TUNIC, CFG_ALLOW_BOOTS;
extern u16  dpad_x, dpad_y, play_sfx;
extern u8   compare_frames;
extern bool fps_switch;

const static u16 item_buttons[8]  = { BTN_B, BTN_CLEFT, BTN_CDOWN, BTN_CRIGHT, BTN_DUP, BTN_DRIGHT, BTN_DDOWN, BTN_DLEFT };

const static s8 gPositions[4][2] = {
    {  0,  -15 },
    {  16,  0  },
    {  0,   15 },
    { -16,  0  },
};

const static s8 gPositionsBig[4][2] = {
    { -2,  -17 },
    {  14, -2  },
    { -2,   13 },
    { -18, -2  },
};

const static u8 icon_size     = 12;
const static u8 icon_size_big = 16;
const static u8 dpad_offset   = 2;

const static z64_action_parameter_t item_actions[] = {
    PLAYER_IA_DEKU_STICK,          // ITEM_DEKU_STICK
    PLAYER_IA_DEKU_NUT,            // ITEM_DEKU_NUT
    PLAYER_IA_BOMB,                // ITEM_BOMB
    PLAYER_IA_BOW,                 // ITEM_BOW
    PLAYER_IA_BOW_FIRE,            // ITEM_ARROW_FIRE
    PLAYER_IA_DINS_FIRE,           // ITEM_DINS_FIRE
    PLAYER_IA_SLINGSHOT,           // ITEM_SLINGSHOT
    PLAYER_IA_OCARINA_FAIRY,       // ITEM_OCARINA_FAIRY
    PLAYER_IA_OCARINA_OF_TIME,     // ITEM_OCARINA_OF_TIME
    PLAYER_IA_BOMBCHU,             // ITEM_BOMBCHU
    PLAYER_IA_HOOKSHOT,            // ITEM_HOOKSHOT
    PLAYER_IA_LONGSHOT,            // ITEM_LONGSHOT
    PLAYER_IA_BOW_ICE,             // ITEM_ARROW_ICE
    PLAYER_IA_FARORES_WIND,        // ITEM_FARORES_WIND
    PLAYER_IA_BOOMERANG,           // ITEM_BOOMERANG
    PLAYER_IA_LENS_OF_TRUTH,       // ITEM_LENS_OF_TRUTH
    PLAYER_IA_MAGIC_BEAN,          // ITEM_MAGIC_BEAN
    PLAYER_IA_HAMMER,              // ITEM_HAMMER
    PLAYER_IA_BOW_LIGHT,           // ITEM_ARROW_LIGHT
    PLAYER_IA_NAYRUS_LOVE,         // ITEM_NAYRUS_LOVE
    PLAYER_IA_BOTTLE,              // ITEM_BOTTLE_EMPTY
    PLAYER_IA_BOTTLE_POTION_RED,   // ITEM_BOTTLE_POTION_RED
    PLAYER_IA_BOTTLE_POTION_GREEN, // ITEM_BOTTLE_POTION_GREEN
    PLAYER_IA_BOTTLE_POTION_BLUE,  // ITEM_BOTTLE_POTION_BLUE
    PLAYER_IA_BOTTLE_FAIRY,        // ITEM_BOTTLE_FAIRY
    PLAYER_IA_BOTTLE_FISH,         // ITEM_BOTTLE_FISH
    PLAYER_IA_BOTTLE_MILK_FULL,    // ITEM_BOTTLE_MILK_FULL
    PLAYER_IA_BOTTLE_RUTOS_LETTER, // ITEM_BOTTLE_RUTOS_LETTER
    PLAYER_IA_BOTTLE_FIRE,         // ITEM_BOTTLE_BLUE_FIRE
    PLAYER_IA_BOTTLE_BUG,          // ITEM_BOTTLE_BUG
    PLAYER_IA_BOTTLE_BIG_POE,      // ITEM_BOTTLE_BIG_POE
    PLAYER_IA_BOTTLE_MILK_HALF,    // ITEM_BOTTLE_MILK_HALF
    PLAYER_IA_BOTTLE_POE,          // ITEM_BOTTLE_POE
    PLAYER_IA_WEIRD_EGG,           // ITEM_WEIRD_EGG
    PLAYER_IA_CHICKEN,             // ITEM_CHICKEN
    PLAYER_IA_ZELDAS_LETTER,       // ITEM_ZELDAS_LETTER
    PLAYER_IA_MASK_KEATON,         // ITEM_MASK_KEATON
    PLAYER_IA_MASK_SKULL,          // ITEM_MASK_SKULL
    PLAYER_IA_MASK_SPOOKY,         // ITEM_MASK_SPOOKY
    PLAYER_IA_MASK_BUNNY_HOOD,     // ITEM_MASK_BUNNY_HOOD
    PLAYER_IA_MASK_GORON,          // ITEM_MASK_GORON
    PLAYER_IA_MASK_ZORA,           // ITEM_MASK_ZORA
    PLAYER_IA_MASK_GERUDO,         // ITEM_MASK_GERUDO
    PLAYER_IA_MASK_TRUTH,          // ITEM_MASK_TRUTH
    PLAYER_IA_SWORD_MASTER,        // ITEM_SOLD_OUT
    PLAYER_IA_POCKET_EGG,          // ITEM_POCKET_EGG
    PLAYER_IA_POCKET_CUCCO,        // ITEM_POCKET_CUCCO
    PLAYER_IA_COJIRO,              // ITEM_COJIRO
    PLAYER_IA_ODD_MUSHROOM,        // ITEM_ODD_MUSHROOM
    PLAYER_IA_ODD_POTION,          // ITEM_ODD_POTION
    PLAYER_IA_POACHERS_SAW,        // ITEM_POACHERS_SAW
    PLAYER_IA_BROKEN_GORONS_SWORD, // ITEM_BROKEN_GORONS_SWORD
    PLAYER_IA_PRESCRIPTION,        // ITEM_PRESCRIPTION
    PLAYER_IA_FROG,                // ITEM_EYEBALL_FROG
    PLAYER_IA_EYEDROPS,            // ITEM_EYE_DROPS
    PLAYER_IA_CLAIM_CHECK,         // ITEM_CLAIM_CHECK
    PLAYER_IA_BOW_FIRE,            // ITEM_BOW_FIRE
    PLAYER_IA_BOW_ICE,             // ITEM_BOW_ICE
    PLAYER_IA_BOW_LIGHT,           // ITEM_BOW_LIGHT
    PLAYER_IA_SWORD_KOKIRI,        // ITEM_SWORD_KOKIRI
    PLAYER_IA_SWORD_MASTER,        // ITEM_SWORD_MASTER
    PLAYER_IA_SWORD_BIGGORON,      // ITEM_SWORD_BIGGORON
};

void change_sword(z64_game_t *game, z64_link_t *link, u8 sword) {
    z64_file.equip_sword            = sword;
    if (z64_file.link_age)
        z64_file.child_equip_sword  = sword;
    else z64_file.adult_equip_sword = sword;
    
    if (z64_file.equip_sword == 3 && z64_file.broken_giants_knife)
        z64_file.button_items[0] = 0x55;
    else z64_file.button_items[0] = z64_file.equip_sword == 0 ? Z64_ITEM_NONE : z64_file.equip_sword + 0x3A;
    
    z64_file.sword_flag = z64_file.equip_sword == 0 ? 1 : 0;
    change_equipment(game, link);
    
    if (z64_file.equip_sword != 0)
        Interface_LoadItemIcon1(game, 0);
}

void change_shield(z64_game_t* game, z64_link_t* link, u8 shield) {
    z64_file.equip_shield            = shield;
    if (z64_file.link_age)
        z64_file.child_equip_shield  = shield;
    else z64_file.adult_equip_shield = shield;
    change_equipment(game, link);
}

void change_tunic(z64_game_t* game, z64_link_t* link, u8 tunic) {
    z64_file.equip_tunic            = tunic;
    if (z64_file.link_age)
        z64_file.child_equip_tunic  = tunic;
    else z64_file.adult_equip_tunic = tunic;
    change_equipment(game, link);
}

void change_boots(z64_game_t* game, z64_link_t* link, u8 boots) {
    z64_file.equip_boots            = boots;
    if (z64_file.link_age)
        z64_file.child_equip_boots  = boots;
    else z64_file.adult_equip_boots = boots;
    change_equipment(game, link);
}

void change_equipment(z64_game_t* game, z64_link_t* link) {
    z64_UpdateEquipment(game, link);
    play_sfx = 0x835;
}

void draw_dpad_actions(z64_disp_buf_t* db, u8 alpha) {
    if (z64_game.common.input[0].raw.pad.l && OPTION_ACTIVE(1, SAVE_30_FPS, CFG_DEFAULT_30_FPS) ) { // FPS Counter Top-Left
        gDPSetPrimColor(db->p++, 0, 0, fps_switch ? 0 : 255, fps_switch ? 255 : 0, 0, 255);
        sprite_load_and_draw(db, &ammo_digit_sprite, compare_frames / 10, dpad_x - 11 - dpad_offset, dpad_y - 8 - dpad_offset, 8, 8);
        sprite_load_and_draw(db, &ammo_digit_sprite, compare_frames % 10, dpad_x - 4  - dpad_offset, dpad_y - 8 - dpad_offset, 8, 8);
    }
                                       
    for (u8 i=0; i<4; i++)
        draw_action(db, DPAD_SET_BUTTON_INDEX(i), gPositions[i][0], gPositions[i][1], gPositionsBig[i][0], gPositionsBig[i][1], alpha);
}

bool can_use_child_trade() {
    if (z64_file.items[Z64_SLOT_CHILD_TRADE] >= Z64_ITEM_KEATON_MASK && z64_file.items[Z64_SLOT_CHILD_TRADE] <= Z64_ITEM_MASK_OF_TRUTH && OPTION_ACTIVE(1, SAVE_MASK_ABILITIES, CFG_DEFAULT_MASK_ABILITIES))
        return  (!z64_game.pause_ctxt.state && !(z64_link.state_flags_1 & BLOCK_ITEMS_BUT_SWIMMING) && !z64_game.restriction_flags.trade_items);
    else return (!z64_game.pause_ctxt.state && !(z64_link.state_flags_1 & BLOCK_ITEMS)              && !z64_game.restriction_flags.trade_items);
}

bool can_use_hookshot() {
    return (!z64_game.pause_ctxt.state && !z64_game.restriction_flags.all && (!(z64_link.state_flags_1 & BLOCK_ITEMS) || (!(z64_link.state_flags_1 & BLOCK_ITEMS_BUT_SWIMMING) && Player_GetEnvironmentalHazard(&z64_game) == PLAYER_ENV_HAZARD_UNDERWATER_FLOOR)));
}

bool can_use_adult_trade()     { return (!z64_game.pause_ctxt.state && !(z64_link.state_flags_1 & BLOCK_ITEMS) &&  !z64_game.restriction_flags.trade_items                          ); }
bool can_use_items()           { return (!z64_game.pause_ctxt.state && !(z64_link.state_flags_1 & BLOCK_ITEMS) &&  !z64_game.restriction_flags.all                                  ); }
bool can_use_ocarina()         { return (!z64_game.pause_ctxt.state && !(z64_link.state_flags_1 & BLOCK_ITEMS) &&  !z64_game.restriction_flags.ocarina                              ); }
bool can_use_lens()            { return (!z64_game.pause_ctxt.state && !(z64_link.state_flags_1 & BLOCK_ITEMS) && (!z64_game.restriction_flags.all || z64_game.scene_index == 0x10) ); }
bool can_use_farores_wind()    { return (!z64_game.pause_ctxt.state && !(z64_link.state_flags_1 & BLOCK_ITEMS) &&  !z64_game.restriction_flags.farores_wind                         ); }
bool is_semi_alpha(u8 alpha)   { return (!z64_game.pause_ctxt.state && alpha >= 0x46); }

void run_equipment_action(z64_game_t* game, z64_link_t* link, u8 action) {
    if (action >= Z64_SLOT_KOKIRI_SWORD && action <= Z64_SLOT_GIANTS_KNIFE)
        toggle_sword(game, link);
    else if (action >= Z64_SLOT_DEKU_SHIELD && action <= Z64_SLOT_MIRROR_SHIELD)
        toggle_shield(game, link);
    else if (action == Z64_SLOT_KOKIRI_TUNIC)
        toggle_tunic(game, link);
    else if (action == Z64_SLOT_GORON_TUNIC)
        swap_tunic(game, link, 6, 2);
    else if (action == Z64_SLOT_ZORA_TUNIC)
        swap_tunic(game, link, 5, 3);
    else if (action == Z64_SLOT_KOKIRI_BOOTS)
        toggle_boots(game, link);
    else if (action == Z64_SLOT_IRON_BOOTS)
        swap_boots(game, link, 2, 2);
    else if (action == Z64_SLOT_HOVER_BOOTS)
        swap_boots(game, link, 1, 3);
}

void draw_action(z64_disp_buf_t* db, z64_slot_t action, s8 icon_x, s8 icon_y, s8 icon_big_x, s8 icon_big_y, u8 alpha) {
    if (action >= Z64_SLOT_KOKIRI_SWORD && action <= Z64_SLOT_GIANTS_KNIFE)
        draw_sword_icon( db, icon_x, icon_y, alpha);
    else if (action >= Z64_SLOT_DEKU_SHIELD && action <= Z64_SLOT_MIRROR_SHIELD)  
        draw_shield_icon(db, icon_x, icon_y, alpha);
    else if (action == Z64_SLOT_KOKIRI_TUNIC)
        draw_tunic_icon( db, icon_x, icon_y, alpha);
    else if (action == Z64_SLOT_GORON_TUNIC)
        draw_equipment_icon(db, icon_x, icon_y, icon_big_x, icon_big_y, alpha, 66, z64_file.goron_tunic, z64_file.equip_tunic == 2);
    else if (action == Z64_SLOT_ZORA_TUNIC)
        draw_equipment_icon(db, icon_x, icon_y, icon_big_x, icon_big_y, alpha, 67, z64_file.zora_tunic,  z64_file.equip_tunic == 3);
    else if (action == Z64_SLOT_KOKIRI_BOOTS)
        draw_boots_icon( db, icon_x, icon_y, alpha);
    else if (action == Z64_SLOT_IRON_BOOTS)
        draw_equipment_icon(db, icon_x, icon_y, icon_big_x, icon_big_y, alpha, 69, z64_file.iron_boots,  z64_file.equip_boots == 2);
    else if (action == Z64_SLOT_HOVER_BOOTS)
        draw_equipment_icon(db, icon_x, icon_y, icon_big_x, icon_big_y, alpha, 70, z64_file.hover_boots, z64_file.equip_boots == 3);
    else if (action <= Z64_SLOT_CHILD_TRADE) {
        u8 item = z64_file.items[action];
        
        if (item >= Z64_ITEM_WEIRD_EGG && item <= Z64_ITEM_MASK_OF_TRUTH)
            draw_child_trade_icon(db, item, icon_x, icon_y, icon_big_x, icon_big_y, alpha);
        else if (item >= Z64_ITEM_POCKET_EGG && item <= Z64_ITEM_CLAIM_CHECK)
            draw_adult_trade_icon(db, item, icon_x, icon_y, alpha);
        else if (item == Z64_ITEM_FAIRY_OCARINA || item == Z64_ITEM_OCARINA_OF_TIME)
            draw_item_icon(db, item, action, icon_x, icon_y, can_use_ocarina(), alpha);
        else if (item == Z64_ITEM_HOOKSHOT || item == Z64_ITEM_LONGSHOT)
            draw_item_icon(db, item, action, icon_x, icon_y, can_use_hookshot(), alpha);
        else if (item == Z64_ITEM_LENS)
            draw_item_icon(db, Z64_ITEM_LENS, Z64_SLOT_LENS, icon_x, icon_y, can_use_lens(), alpha);
        else if (item == Z64_ITEM_FARORES_WIND)
            draw_item_icon(db, Z64_ITEM_FARORES_WIND, Z64_SLOT_FARORES_WIND, icon_x, icon_y, can_use_farores_wind(), alpha);
        else if (item == Z64_ITEM_FIRE_ARROW || item == Z64_ITEM_ICE_ARROW || item == Z64_ITEM_LIGHT_ARROW)
            draw_arrow_icon(db, item, action, icon_x, icon_y, can_use_items(), alpha);
        else if (item == Z64_ITEM_SOLD_OUT)
            draw_item_icon(db, item, action, icon_x, icon_y, false, alpha);
        else if (item != Z64_ITEM_NONE)
            draw_item_icon(db, item, action, icon_x, icon_y, can_use_items(), alpha);
        
        if (item != Z64_ITEM_NONE)
            draw_ammo(db, item, dpad_x + icon_x + dpad_offset, dpad_y + icon_y + dpad_offset + 8, 4, -1, (!can_use_items() && is_semi_alpha(alpha)) ? 0x46 : alpha, false);
    }
}

void draw_ammo(z64_disp_buf_t* db, u8 item, u16 x, u16 y, u8 size, s8 spacing, u8 alpha, bool b_button) {
    s8 ammo     = -1;
    u8 capacity =  0;
    
    if (item == z64_file.items[Z64_SLOT_SLINGSHOT] && item == Z64_ITEM_SLINGSHOT && !b_button) {
        ammo     = z64_file.ammo[Z64_SLOT_SLINGSHOT];
        capacity = z64_capacity.bullet_bag[z64_file.bullet_bag];
    }
    else if ( (item == z64_file.items[Z64_SLOT_BOW] && !b_button) || item == z64_file.items[Z64_SLOT_FIRE_ARROW] || item == z64_file.items[Z64_SLOT_ICE_ARROW] || item == z64_file.items[Z64_SLOT_LIGHT_ARROW]) {
        ammo     = z64_file.ammo[Z64_SLOT_BOW];
        capacity = z64_capacity.quiver[z64_file.quiver];
    }
    else if (item == z64_file.items[Z64_SLOT_BOMB]) {
        ammo     = z64_file.ammo[Z64_SLOT_BOMB];
        capacity = z64_capacity.bomb_bag[z64_file.bomb_bag];
    }
    else if (item == z64_file.items[Z64_SLOT_BOMBCHU]) {
        ammo     = z64_file.ammo[Z64_SLOT_BOMBCHU];
        capacity = 50;
    }
    else if (item == z64_file.items[Z64_SLOT_STICK]) {
        ammo     = z64_file.ammo[Z64_SLOT_STICK];
        capacity = z64_capacity.stick_upgrade[z64_file.stick_upgrade];
    }
    else if (item == z64_file.items[Z64_SLOT_NUT]) {
        ammo     = z64_file.ammo[Z64_SLOT_NUT];
        capacity = z64_capacity.nut_upgrade[z64_file.nut_upgrade];
    }
    else if (item == z64_file.items[Z64_SLOT_BEANS] && item == Z64_ITEM_BEANS) {
        ammo     = z64_file.ammo[Z64_SLOT_BEANS];
        capacity = 10;
    }
        
    if (ammo >= 0) {
        if (ammo == capacity)
            gDPSetPrimColor(db->p++, 0, 0, 120, 255, 0, alpha);
        else if (ammo == 0)
            gDPSetPrimColor(db->p++, 0, 0, 100, 100, 100, alpha);
        else gDPSetPrimColor(db->p++, 0, 0, 255, 255, 255, alpha);
        
        if (ammo >= 10)
            sprite_load_and_draw(db, &ammo_digit_sprite, ammo / 10, x, y, size, size);
        sprite_load_and_draw(db, &ammo_digit_sprite, ammo % 10, x + size + spacing, y, size, size);
    }
}

void toggle_sword(z64_game_t* game, z64_link_t* link) {
    if (!z64_file.kokiri_sword && !z64_file.master_sword && !z64_file.giants_knife)
        return;
    
    u8 sword = z64_file.equip_sword;
    sword++;
    
    if (sword > 3) {
        sword = 0;
        if (!OPTION_ACTIVE(2, SAVE_UNEQUIP_GEAR, CFG_DEFAULT_UNEQUIP_GEAR))
            sword++;
    }
    
    if (sword == 1 && (!z64_file.kokiri_sword || (!z64_file.link_age && !CFG_ALLOW_KOKIRI_SWORD) ) )
        sword++;
    if (sword == 2 && (!z64_file.master_sword || ( z64_file.link_age && !CFG_ALLOW_MASTER_SWORD) ) )
        sword++;
    if (sword == 3 && (!z64_file.giants_knife || ( z64_file.link_age && !CFG_ALLOW_GIANTS_KNIFE) ) ) {
        if (OPTION_ACTIVE(2, SAVE_UNEQUIP_GEAR, CFG_DEFAULT_UNEQUIP_GEAR))
            sword = 0;
        else if (z64_file.kokiri_sword && ( z64_file.link_age || CFG_ALLOW_KOKIRI_SWORD) )
            sword = 1;
        else if (z64_file.master_sword && (!z64_file.link_age || CFG_ALLOW_MASTER_SWORD) )
            sword = 2;
        else sword = 0;
    }
            
    if (sword != z64_file.equip_sword)
        change_sword(game, link, sword);
}

void toggle_shield(z64_game_t* game, z64_link_t* link) {
    if (!z64_file.deku_shield && !z64_file.hylian_shield && !z64_file.mirror_shield)
        return;
    
    u8 shield = z64_file.equip_shield;
    shield++;
    
    if (shield > 3) {
        shield = 0;
        if (!OPTION_ACTIVE(2, SAVE_UNEQUIP_GEAR, CFG_DEFAULT_UNEQUIP_GEAR))
            shield++;
    }
    
    if (shield == 1 && (!z64_file.deku_shield || (!z64_file.link_age && !CFG_ALLOW_DEKU_SHIELD) ) )
        shield++;
    if (shield == 2 && !z64_file.hylian_shield)
        shield++;
    if (shield == 3 && (!z64_file.mirror_shield || (z64_file.link_age && !CFG_ALLOW_MIRROR_SHIELD) ) ) {
        if (OPTION_ACTIVE(2, SAVE_UNEQUIP_GEAR, CFG_DEFAULT_UNEQUIP_GEAR))
            shield = 0;
        else if (z64_file.deku_shield && (z64_file.link_age || CFG_ALLOW_DEKU_SHIELD) )
            shield = 1;
        else if (z64_file.hylian_shield)
            shield = 2;
        else shield = 0;
    }
    
    if (shield != z64_file.equip_shield)
        change_shield(game, link, shield);
}

void toggle_tunic(z64_game_t* game, z64_link_t* link) {
    if (!z64_file.kokiri_tunic && !z64_file.goron_tunic && !z64_file.zora_tunic)
        return;
    
    bool not_allowed = z64_file.link_age && !CFG_ALLOW_TUNIC;
    bool can_unequip = OPTION_ACTIVE(2, SAVE_UNEQUIP_GEAR, CFG_DEFAULT_UNEQUIP_GEAR) || OPTION_ACTIVE(2, SAVE_EXTRA_ABILITIES, CFG_DEFAULT_EXTRA_ABILITIES);
    u8   tunic       = z64_file.equip_tunic;
    tunic++;
    
    if (tunic > 3) {
        tunic = 0;
        if (!can_unequip)
            tunic++;
    }
    
    if (tunic == 1 &&  !z64_file.kokiri_tunic)
        tunic++;
    if (tunic == 2 && (!z64_file.goron_tunic || not_allowed) )
        tunic++;
    if (tunic == 3 && (!z64_file.zora_tunic  || not_allowed) ) {
        if (can_unequip)
            tunic = 0;
        else if (z64_file.kokiri_tunic)
            tunic = 1;
        else if (z64_file.goron_tunic && (!z64_file.link_age || !CFG_ALLOW_TUNIC) )
            tunic = 2;
        else tunic = 0;
    }
    
    if (tunic != z64_file.equip_tunic)
        change_tunic(game, link, tunic);
}

void toggle_boots(z64_game_t* game, z64_link_t* link) {
    if (z64_file.link_age && !CFG_ALLOW_BOOTS)
        return;
    if (!z64_file.kokiri_boots || (!z64_file.iron_boots && !z64_file.hover_boots) )
        return;
    
    u8 boots = z64_file.equip_boots;
    boots++;
    if (boots > 3)
        boots = 1;
    
    if (boots == 2 && !z64_file.iron_boots)
        boots++;
    if (boots == 3 && !z64_file.hover_boots)
        boots = 1;
    
    if (boots != z64_file.equip_boots)
        change_boots(game, link, boots);
}

void swap_tunic(z64_game_t* game, z64_link_t* link, u8 shift, u8 equip) {
    if (!z64_file.equipment & (1 < shift) || (z64_file.link_age && !CFG_ALLOW_TUNIC) )
        return;
    z64_file.equip_tunic = z64_file.equip_tunic == equip ? 1 : equip;
    change_equipment(game, link);
}

void swap_boots(z64_game_t* game, z64_link_t* link, u8 shift, u8 equip) {
    if (!z64_file.equipment & (1 < shift) || (z64_file.link_age && !CFG_ALLOW_BOOTS) )
        return;
    z64_file.equip_boots = z64_file.equip_boots == equip ? 1 : equip;
    change_equipment(game, link);
}

void draw_sword_icon(z64_disp_buf_t* db, s8 icon_x, s8 icon_y, u8 alpha) {
    if (z64_file.equip_sword == 0)
        return;
    gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    draw_dpad_icon(db, &items_sprite, z64_file.equip_sword == 3 && z64_file.broken_giants_knife ? 85 : 58 + z64_file.equip_sword, icon_x, icon_y, icon_size);
}

void draw_shield_icon(z64_disp_buf_t* db, s8 icon_x, s8 icon_y, u8 alpha) {
    if (z64_file.equip_shield == 0)
        return;
    gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    draw_dpad_icon(db, &items_sprite, 61 + z64_file.equip_shield, icon_x, icon_y, icon_size);
}

void draw_tunic_icon(z64_disp_buf_t* db, s8 icon_x, s8 icon_y, u8 alpha) {
    if (z64_file.equip_tunic == 0)
        return;
    gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    draw_dpad_icon(db, &items_sprite, 64 + z64_file.equip_tunic, icon_x, icon_y, icon_size);
}


void draw_boots_icon(z64_disp_buf_t* db, s8 icon_x, s8 icon_y, u8 alpha) {
    if (z64_file.equip_boots == 0)
        return;
    gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
    draw_dpad_icon(db, &items_sprite, 67 + z64_file.equip_boots, icon_x, icon_y, icon_size);
}

void draw_equipment_icon(z64_disp_buf_t* db, s8 icon_x, s8 icon_y, s8 icon_big_x, s8 icon_big_y, u8 alpha, u8 icon, bool has_item, bool is_equipped) {
    if (has_item) {
        gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, alpha);
        draw_dpad_icon(db, &items_sprite, icon, is_equipped ? icon_big_x : icon_x, is_equipped ? icon_big_y : icon_y, is_equipped ? icon_size_big : icon_size);
    }
}

void draw_child_trade_icon(z64_disp_buf_t* db, z64_item_t item, s8 icon_x, s8 icon_y, s8 icon_big_x, s8 icon_big_y, u8 alpha) {
    bool mask = (z64_link.current_mask == item - Z64_ITEM_KEATON_MASK + 1);
    gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, (!can_use_child_trade() && is_semi_alpha(alpha)) ? 0x46 : alpha);
    draw_dpad_icon(db, &items_sprite, z64_file.items[Z64_SLOT_CHILD_TRADE], mask ? icon_big_x : icon_x, mask ? icon_big_y : icon_y, mask ? icon_size_big : icon_size);
}

void draw_adult_trade_icon(z64_disp_buf_t* db, z64_item_t item, s8 icon_x, s8 icon_y, u8 alpha) {
    gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, (!can_use_adult_trade() && is_semi_alpha(alpha)) ? 0x46 : alpha);
    draw_dpad_icon(db, &items_sprite, z64_file.items[Z64_SLOT_ADULT_TRADE], icon_x, icon_y, icon_size);
}

void draw_arrow_icon(z64_disp_buf_t* db, z64_item_t item, z64_slot_t slot, s8 icon_x, s8 icon_y, bool usability, u8 alpha) {
    z64_item_t compare = z64_file.items[slot];
    if (compare == item) {
        switch (compare) {
            case Z64_ITEM_FIRE_ARROW:
                compare = Z64_ITEM_BOW_FIRE_ARROW;
                break;
            case Z64_ITEM_ICE_ARROW:
                compare = Z64_ITEM_BOW_ICE_ARROW;
                break;
            case Z64_ITEM_LIGHT_ARROW:
                compare = Z64_ITEM_BOW_LIGHT_ARROW;
                break;
        }
        gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, (!usability && is_semi_alpha(alpha)) ? 0x46 : alpha);
        draw_dpad_icon(db, &items_sprite, compare, icon_x, icon_y, icon_size);
    }
}

void draw_item_icon(z64_disp_buf_t* db, z64_item_t item, z64_slot_t slot, s8 icon_x, s8 icon_y, bool usability, u8 alpha) {
    gDPSetPrimColor(db->p++, 0, 0, 0xFF, 0xFF, 0xFF, (!usability && is_semi_alpha(alpha)) ? 0x46 : alpha);
    draw_dpad_icon(db, &items_sprite, z64_file.items[slot], icon_x, icon_y, icon_size);
}

void draw_dpad_icon(z64_disp_buf_t* db, sprite_t *sprite, u8 icon, s8 x, s8 y, u8 size) {
    sprite_load_and_draw(db, sprite, icon, dpad_x + x + dpad_offset, dpad_y + y + dpad_offset, size, size);
}

void player_update_bottle_item(z64_game_t* game, z64_item_t item, u8 button) {
    if (z64_file.items[button < 4 ? z64_file.c_button_slots[button - 1] : DPAD_SET_BUTTON_INDEX(button - 4)] == Z64_ITEM_MILK_FULL && item == Z64_ITEM_BOTTLE)
            item = Z64_ITEM_MILK_HALF;
    
    if (button < 4)
        update_c_button_bottle_item(game, item, button);
    else {
        for (u8 index=1; index<4; index++)
            if (z64_file.button_items[index] == z64_file.items[DPAD_SET_BUTTON_INDEX(button - 4)]) {
                update_c_button_bottle_item(game, item, index);
                break;
            }
    }
    
    z64_file.items[button < 4 ? z64_file.c_button_slots[button - 1] : DPAD_SET_BUTTON_INDEX(button - 4)] = item;
    game->pause_ctxt.cursorItem[PAUSE_ITEM] = item;
}

void update_c_button_bottle_item(z64_game_t* game, z64_item_t item, z64_item_button_t button) {
    z64_file.button_items[button]  = item;
    z64_file.button_status[button] = BTN_ENABLED;
    Interface_LoadItemIcon1(game, button);
}

void player_process_item_buttons(z64_link_t* link, z64_game_t* game) {
    u8 index = 0;
    
    if (link->current_mask != PLAYER_MASK_NONE && !(link->state_flags_1 & (PLAYER_STATE1_CLIMBING | PLAYER_STATE1_SWIMMING) ) ) {
        u8 mask_item_action = link->current_mask - 1 + PLAYER_IA_MASK_KEATON;
        if (!player_item_is_item_action(C_BTN_ITEM(0), mask_item_action)        && !player_item_is_item_action(C_BTN_ITEM(1), mask_item_action)        && !player_item_is_item_action(C_BTN_ITEM(2), mask_item_action)        && \
            !player_item_is_item_action(get_dpad_btn_item(0), mask_item_action) && !player_item_is_item_action(get_dpad_btn_item(1), mask_item_action) && !player_item_is_item_action(get_dpad_btn_item(2), mask_item_action) && !player_item_is_item_action(get_dpad_btn_item(3), mask_item_action))
            link->current_mask = PLAYER_MASK_NONE;
    }
    
    z64_throw_check_1 = z64_throw_check_2 = z64_throw_check_3 = z64_throw_check_4 = OPTION_ACTIVE(1, SAVE_DPAD, CFG_DEFAULT_DPAD) ? 0xCF : 0xC0;
    if (has_lens_on_dpad_button())
        z64_dpad_lens_1 = z64_dpad_lens_2 = z64_dpad_lens_3 = 0x1000;
    else {
        z64_dpad_lens_1 = 0x504E;
        z64_dpad_lens_2 = 0x504F;
        z64_dpad_lens_3 = 0x5458;
    }

    if (!(link->state_flags_1 & (PLAYER_STATE1_HOLDING_ABOVE_HEAD | PLAYER_STATE1_NO_CONTROL)) && !((link->held_item_action == PLAYER_IA_HOOKSHOT || link->held_item_action == PLAYER_IA_LONGSHOT) && link->held_actor == NULL)) {
        if (link->item_action >= PLAYER_IA_FISHING_POLE)
            if (!player_item_is_in_use(link, B_BTN_ITEM)           && !player_item_is_in_use(link, C_BTN_ITEM(0))        && !player_item_is_in_use(link, C_BTN_ITEM(1))        && !player_item_is_in_use(link, C_BTN_ITEM(2)) && \
                !player_item_is_in_use(link, get_dpad_btn_item(0)) && !player_item_is_in_use(link, get_dpad_btn_item(1)) && !player_item_is_in_use(link, get_dpad_btn_item(2)) && !player_item_is_in_use(link, get_dpad_btn_item(3))) {
                Player_UseItem(game, link, Z64_ITEM_NONE);
                use_item_check = 0x10C0;
                return;
            }

        for (index=0; index<ARRAY_SIZE(item_buttons); index++)
            if (CHECK_BTN_ALL(game->common.input[0].pad_pressed.pad, item_buttons[index])) {
                if (index >= 4 && OPTION_ACTIVE(1, SAVE_DPAD, CFG_DEFAULT_DPAD))
                    if (DPAD_SET_BUTTON_INDEX(index - 4) >= Z64_SLOT_KOKIRI_SWORD)
                        run_equipment_action(game, link, DPAD_SET_BUTTON_INDEX(index - 4));
                break;
            }
    
        z64_item_t item = player_get_item_on_button(game, index);
        if (item >= Z64_ITEM_NONE_FE) {
            for (index=0; index<ARRAY_SIZE(item_buttons); index++)
                if (CHECK_BTN_ALL(game->common.input[0].raw.pad.pad, item_buttons[index]))
                    break;
                
            item = player_get_item_on_button(game, index);
            if (item < Z64_ITEM_NONE_FE && player_item_to_item_action(item) == link->held_item_action)
                z64_held_item_button_is_held_down = true;
        }
        else {
            link->held_item_button = index;
            if (item >= Z64_ITEM_KEATON_MASK && item <= Z64_ITEM_MASK_OF_TRUTH && OPTION_ACTIVE(1, SAVE_MASK_ABILITIES, CFG_DEFAULT_MASK_ABILITIES))
                use_item_check = 0x1500;
            Player_UseItem(game, link, item);
            use_item_check = 0x10C0;
        }
    }
}

z64_action_parameter_t player_item_to_item_action(z64_item_t item) {
    if (item >= Z64_ITEM_NONE_FE)
        return PLAYER_IA_NONE;
    else if (item == Z64_ITEM_SWORD_CS)
        return PLAYER_IA_SWORD_CS;
    else if (item == ITEM_FISHING_POLE)
        return PLAYER_IA_FISHING_POLE;
    else return item_actions[item];
}

bool player_item_is_in_use(z64_link_t* link, z64_item_t item) {
    if ((item < Z64_ITEM_NONE_FE) && (player_item_to_item_action(item) == link->item_action))
        return true;
    else return false;
}

bool player_item_is_item_action(z64_item_t item, z64_action_parameter_t item_action) {
    if (item < 0xFD && player_item_to_item_action(item) == item_action)
        return true;
    else return false;
}

z64_item_t player_get_item_on_button(z64_game_t* game, u8 index) {
    if (index >= 8)
        return Z64_ITEM_NONE;
    else if (game->bombchuBowlingStatus != 0)
        return (game->bombchuBowlingStatus > 0) ? Z64_ITEM_BOMBCHU : Z64_ITEM_NONE;
    else if (index == 0)
        return B_BTN_ITEM;
    else if (index == 1)
        return C_BTN_ITEM(0);
    else if (index == 2)
        return C_BTN_ITEM(1);
    else if (index == 3)
        return C_BTN_ITEM(2);
    else return get_dpad_btn_item(index - 4);
}

z64_item_t get_dpad_btn_item(u8 button) {
    if (!(OPTION_ACTIVE(1, SAVE_DPAD, CFG_DEFAULT_DPAD)) || DPAD_SET_BUTTON_INDEX(button) >= Z64_SLOT_KOKIRI_SWORD || z64_file.items[DPAD_SET_BUTTON_INDEX(button)] == Z64_ITEM_SOLD_OUT)
        return Z64_ITEM_NONE;
    else if (z64_file.items[DPAD_SET_BUTTON_INDEX(button)] == Z64_ITEM_FAIRY_OCARINA || z64_file.items[DPAD_SET_BUTTON_INDEX(button)] == Z64_ITEM_OCARINA_OF_TIME) {
        if (can_use_ocarina())
            return z64_file.items[DPAD_SET_BUTTON_INDEX(button)];
    }
    else if (z64_file.items[DPAD_SET_BUTTON_INDEX(button)] >= Z64_ITEM_WEIRD_EGG && z64_file.items[DPAD_SET_BUTTON_INDEX(button)] <= Z64_ITEM_MASK_OF_TRUTH) {
        if (can_use_child_trade())
            return z64_file.items[DPAD_SET_BUTTON_INDEX(button)];
    }
    else if (z64_file.items[DPAD_SET_BUTTON_INDEX(button)] >= Z64_ITEM_POCKET_EGG && z64_file.items[DPAD_SET_BUTTON_INDEX(button)] <= Z64_ITEM_CLAIM_CHECK) {
        if (can_use_adult_trade())
            return z64_file.items[DPAD_SET_BUTTON_INDEX(button)];
    }
    else if (z64_file.items[DPAD_SET_BUTTON_INDEX(button)] == Z64_ITEM_HOOKSHOT || z64_file.items[DPAD_SET_BUTTON_INDEX(button)] == Z64_ITEM_LONGSHOT) {
        if (can_use_hookshot())
            return z64_file.items[DPAD_SET_BUTTON_INDEX(button)];
    }
    else if (z64_file.items[DPAD_SET_BUTTON_INDEX(button)] == Z64_ITEM_LENS) {
        if (can_use_lens())
            return z64_file.items[DPAD_SET_BUTTON_INDEX(button)];
    }
    else if (z64_file.items[DPAD_SET_BUTTON_INDEX(button)] == Z64_ITEM_FARORES_WIND) {
        if (can_use_farores_wind())
            return z64_file.items[DPAD_SET_BUTTON_INDEX(button)];
    }
    else if (can_use_items())
        return z64_file.items[DPAD_SET_BUTTON_INDEX(button)];
    
    return Z64_ITEM_NONE;
}

bool has_lens_on_dpad_button() {
    for (u8 i=1; i<4; i++)
        if (z64_file.button_items[i] == Z64_ITEM_LENS)
            return false;
    for (u8 i=0; i<4; i++)
        if (z64_file.items[DPAD_SET_BUTTON_INDEX(i)] == Z64_ITEM_LENS)
            return true;
    return false;
}