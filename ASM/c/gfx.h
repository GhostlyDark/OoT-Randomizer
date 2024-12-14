#ifndef GFX_H
#define GFX_H

#include "z64.h"

extern Gfx setup_db[];
extern Gfx empty_dlist[];

typedef struct {
    uint8_t *buf;
    uint16_t tile_w;
    uint16_t tile_h;
    uint16_t tile_count;
    uint8_t im_fmt;
    uint8_t im_siz;
    uint8_t bytes_per_texel;
} sprite_t;

extern sprite_t stones_sprite;
extern sprite_t medals_sprite;
extern sprite_t items_sprite;
extern sprite_t quest_items_sprite;
extern sprite_t font_sprite;
extern sprite_t dpad_sprite;
extern sprite_t triforce_sprite;
extern sprite_t l_button_pause_screen_sprite;
extern sprite_t song_note_sprite;
extern sprite_t key_rupee_clock_sprite;
extern sprite_t item_digit_sprite;
extern sprite_t linkhead_skull_sprite;
extern sprite_t heart_sprite;
extern sprite_t button_sprite;
extern sprite_t counter_digit_sprite;
extern sprite_t ammo_digit_sprite;
extern sprite_t subscreen_sprite;
extern sprite_t title_sprite;
extern sprite_t title_text_sprite;
extern sprite_t name_panel_sprite;
extern sprite_t magic_meter_end;
extern sprite_t magic_meter_mid;
extern sprite_t magic_meter_fill;

void gfx_init();

void sprite_load(                  z64_disp_buf_t *db, sprite_t *sprite, int start_tile, int     tile_count);
void sprite_draw(                  z64_disp_buf_t *db, sprite_t *sprite, int tile_index, int     left, int     top, int     width, int     height);
void sprite_load_and_draw(         z64_disp_buf_t *db, sprite_t *sprite, int index,      int16_t x,    int16_t y,   uint8_t w,     uint8_t h);
void sprite_texture(               z64_disp_buf_t* db, sprite_t* sprite, int tile_index, int16_t left, int16_t top, int16_t width, int16_t height);
void sprite_texture_4b(            z64_disp_buf_t* db, sprite_t* sprite, int tile_index, int16_t left, int16_t top, int16_t width, int16_t height);

void display_buffer_init();
void display_buffer_reset();

#endif
