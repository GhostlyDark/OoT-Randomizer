#ifndef DEBUG_H
#define DEBUG_H

#include "z64.h"

#include "gfx.h"
#include "text.h"
#include "options.h"

#define BG_WIDTH      240
#define BG_HEIGHT     150
#define PADDING       1
#define ICON_SIZE     12
#define ROWS          10

#define EVENT         0xF9
#define ITEM          0xFA
#define INFTABLE      0xFB
#define SCENE_CLEAR   0xFC
#define CARPENTERS    0xFD
#define NABOORU       0xFE
#define MASK          0xFF

#define WARPS         0
#define UPGRADES      1
#define PROGRESSIONS  2

typedef struct {
    u8        main_index;
    u8        sub_menu_index;
    u8        dungeon_index;
    u8        room_index;
    u8        overworld_index;
    u8        boss_index;
    u8        upgrade_index;
    u8        progression_index;
} menu_index_t;

typedef struct {
    char*     name;
} menu_category_t;

typedef struct {
    u16       entrance_index;
    char*     name;
} warp_t;

typedef struct {
    z64_xyz_t pos;
    u16       yaw;
    char*     name;
} room_t;

typedef struct {
    u8        number_of_rooms;
    room_t*   room;
} rooms_t;

typedef struct {
    char*     name;
} upgrade_t;

typedef struct {
    char*     name;
    u8        type;
    u16       flag;
} progression_t;

static menu_index_t current_menu_indexes = { 0, 0, 0, 0, 0, 0, 0, 0 };

void reset_map_select();
void execute_warp();
void handle_map_select();
bool draw_map_select(  z64_disp_buf_t* db);
void draw_page_counter(u8              index,          u16 elements);
void draw_items(       void*           items,          u8  index, u16 elements, u8 type);
void draw_timeofday(   z64_disp_buf_t* db);

#endif
