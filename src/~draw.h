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

#ifndef NO_UNICODE
void w_print_point(WINDOW* screen, const Point2d_int& point, const wchar_t* wstr);
#endif
void print_point(WINDOW* screen, const Point2d_int& point, const char* str_print);
void print_centered_string(std::string);

#ifndef NO_UNICODE
void draw_window_box(WINDOW* screen);
#endif
void draw_window_box(WINDOW* screen);

#ifndef NO_UNICODE
void w_draw_frame(const Game_State& current_state);
#endif
void draw_frame(const Game_State& current_state);

void draw_start(const Game_State& current_state);
void draw_death(const Game_State& current_state);
void draw_win(const Game_State& current_state);

#endif
