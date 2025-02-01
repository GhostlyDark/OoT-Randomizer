#include "text.h"

#include "gfx.h"
#include "util.h"
#include "z64.h"

#define text_max_chars 256
#define text_bucket_count 6
#define text_bucket_size 18

typedef struct {
    uint32_t c     : 8;
    uint32_t left  : 12;
    uint32_t top   : 12;
    uint8_t width  : 8;
    uint8_t height : 8;
    colorRGBA8_t color;
} text_char_t;

static text_char_t *text_end = NULL;
static text_char_t *text_buf = NULL;

uint8_t text_font_width  = 8;
uint8_t text_font_height = 14;

void text_set_size(uint8_t width, uint8_t height) {
    text_font_width  = width;
    text_font_height = height;
}

void text_init() {
    text_buf = heap_alloc(text_max_chars * sizeof(text_char_t));
    text_end = text_buf;
}

int text_print_color(const char *s, int left, int top, colorRGBA8_t color) {
    char c;
    int count = 0;
    while (c = *(s++)) {
        if (text_end >= text_buf + text_max_chars) break;
        text_end->c      = c;
        text_end->left   = left;
        text_end->top    = top;
        text_end->width  = text_font_width;
        text_end->height = text_font_height;
        text_end->color  = color;
        text_end++;
        left += text_font_width;
        count++;
    }
    return count;
}

int text_print(const char* s, int left, int top) {
    colorRGBA8_t color = { 0xFF, 0xFF, 0xFF, 0xFF };
    return text_print_color(s, left, top, color);
}

int draw_int(z64_disp_buf_t* db, int32_t number, int16_t left, int16_t top, colorRGBA8_t color) {
    draw_int_size(db, number, left, top, color, 8, 16);
}

int draw_int_size(z64_disp_buf_t* db, int32_t number, int16_t left, int16_t top, colorRGBA8_t color, int16_t width, int16_t height) {
    int isNegative = 0;
    if (number < 0) {
        number    *= -1;
        isNegative =  1;
    }

    uint8_t digits[10];
    uint8_t j = 0;
    
    do {
        digits[j] = number % 10;
        number    = number / 10;
        j++;
    } while (number > 0);
    
    gDPSetCombineLERP(db->p++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);

    gDPSetPrimColor(db->p++, 0, 0, color.r, color.g, color.b, color.a);
    if (isNegative)
        text_print("-", left - counter_digit_sprite.tile_w, top);
    
    for (uint8_t c = j; c > 0; c--) {
        sprite_texture(db, &counter_digit_sprite, digits[c-1], left, top, width, height);
        left += width;
    }
    return j;
}

void text_flush(z64_disp_buf_t *db) {
    for (int i=0; i < text_bucket_count; i++) {
        sprite_load(db, &font_sprite, i * text_bucket_size, text_bucket_size);

        text_char_t *text_p = text_buf;
        while (text_p < text_end) {
            char c             = text_p->c;
            int left           = text_p->left;
            int top            = text_p->top;
            int width          = text_p->width;
            int height         = text_p->height;
            colorRGBA8_t color = text_p->color;
            text_p++;

            int bucket = (c - 32) / text_bucket_size;
            if (bucket != i) continue;
            
            // Apply text color.
            gDPSetPrimColor(db->p++, 0, 0, color.r, color.g, color.b, color.a);

            int tile_index = (c - 32) % text_bucket_size;
            sprite_draw(db, &font_sprite, tile_index, left, top, width, height);
        }
    }

    text_end = text_buf;
    text_set_size(8, 14);
}