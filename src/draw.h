#pragma once

#ifndef DRAW_H
#define DRAW_H

#include <ncurses.h> // for mvprintw(), mvaddwstr(), erase(), and refresh()
#include <string> // for std::string
#include <sstream> // for std::ostringstream

#include "global_structs.h"
#include "misc.h"
#include "game_tick.h"

// define color pair aliases
#define HEAD_PAIR   1
#define BODY_PAIR   2
#define FRUIT_PAIR  3
#define BOX_PAIR    4

// section 0
#ifndef NO_UNICODE
void _w_print_head(const Game_State& current_state);
void _w_print_body(const Game_State& current_state);
void _w_print_fruit(const Game_State& current_state);
#endif
void _print_head(const Game_State& current_state);
void _print_body(const Game_State& current_state);
void _print_fruit(const Game_State& current_state);

//section 1
void _color_head(const Game_State& current_state);
void _color_body(const Game_State& current_state);
void _color_fruit(const Game_State& current_state);

// section 2
#ifndef NO_UNICODE
void _w_print_box(WINDOW* screen);
#endif
void _print_box(WINDOW* screen);
void _color_box(WINDOW* screen);

// section 3
bool draw_init(void);
void draw_frame(const Game_State& current_state);

// section 4
void print_centered_string(const Game_State& current_state, std::string msg, int y_offset);
void draw_start(const Game_State& current_state);
void draw_death(const Game_State& current_state);
void draw_win(const Game_State& current_state);

#endif
