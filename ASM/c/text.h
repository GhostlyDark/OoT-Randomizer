#ifndef TEXT_H
#define TEXT_H

#include "z64.h"

void text_set_size(uint8_t width, uint8_t height);
void text_init();
int text_print_color(const char *s, int left, int top, colorRGBA8_t color);
int text_print(const char *s, int left, int top);
int draw_int(z64_disp_buf_t* db, int32_t number, int16_t left, int16_t top, colorRGBA8_t color);
int draw_int_size(z64_disp_buf_t* db, int32_t number, int16_t left, int16_t top, colorRGBA8_t color, int16_t width, int16_t height);
void text_flush(z64_disp_buf_t *db);

#endif
