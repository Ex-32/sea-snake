#pragma once

#ifndef DRAW_H
#define DRAW_H

#include <ncurses.h> // for mvprintw(), mvaddwstr(), erase(), and refresh()
#include <string> // for std::string
#include <sstream> // for std::ostringstream

#include "global_structs.h"
#include "misc.h"
#include "game_tick.h"

extern WINDOW *stdscr;

void print_centered_string(const Game_State& current_state, std::string msg, int y_offset);

#ifndef NO_UNICODE
void _w_print_head(const Game_State& current_state);
void _w_print_body(const Game_State& current_state);
void _w_print_fruit(const Game_State& current_state);
#endif
void _print_head(const Game_State& current_state);
void _print_body(const Game_State& current_state);
void _print_fruit(const Game_State& current_state);

void _color_head(const Game_State& current_state);
void _color_body(const Game_State& current_state);
void _color_fruit(const Game_State& current_state);

void _color_box(WINDOW* screen);

void _no_color(WINDOW* screen);

#ifndef NO_UNICODE
void _w_print_box(WINDOW* screen);
#endif
void _print_box(WINDOW* screen);

bool draw_init(void);

void draw_frame(const Game_State& current_state);

void draw_start(const Game_State& current_state);
void draw_death(const Game_State& current_state);
void draw_win(const Game_State& current_state);

#endif
