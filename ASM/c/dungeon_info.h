#ifndef DUNGEON_INFO_H
#define DUNGEON_INFO_H

#include "z64.h"

#include <math.h>

#include "gfx.h"
#include "text.h"
#include "util.h"

#define DUNGEON_OVERLAY_RANGE        3
#define DUNGEON_OVERLAY_TITLE_WIDTH  95
#define DUNGEON_OVERLAY_ICON_SIZE    14
#define DUNGEON_OVERLAY_ICON_PADDING 1

typedef struct {
    u8   index;
    struct {
        u8 has_keys     : 1;
        u8 has_boss_key : 1;
        u8 has_map      : 1;
    };
    u8   skulltulas;
    u8   item[2];
    u8   reward;
    char name[18];
} dungeon_entry_t;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
} medal_color_t;

bool draw_dungeon_info(z64_disp_buf_t* db);
bool has_item(         u8              item);
bool has_quest_reward( u8              reward);

#endif
