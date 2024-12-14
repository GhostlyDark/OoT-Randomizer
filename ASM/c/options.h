#ifndef OPTIONS_H
#define OPTIONS_H

#include "z64.h"
#include "gfx.h"
#include "text.h"
#include "buttons.h"
#include "dpad_paused.h"
#include "fps.h"
#include "debug.h"

#include <string.h>
#include <stdio.h>

void handle_options_menu();
void handle_options_menu_input(pad_t           pad_pressed);
void write_option(             u8              index, u8 shift, pad_t pad_pressed, u16 save);
bool draw_settings_menu(       z64_disp_buf_t* db);
bool draw_abilities_info(      z64_disp_buf_t* db);
void handle_item_editor();
void return_to_options_menu();

#endif
