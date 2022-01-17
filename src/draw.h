#pragma once

#ifndef DRAW_H
#define DRAW_H

#include <ncurses.h> // for mvprintw(), mvaddwstr(), erase(), and refresh()
#include <string>
#include <sstream> // for std::ostringstream

#include "global_structs.h"
#include "misc.h"
#include "game_tick.h"

extern WINDOW *stdscr;

void w_print_point(const Point2d_int& point, const wchar_t* wstr);
void print_point(const Point2d_int& point, const char* str_print);
void print_centered_string(std::string);

void w_draw_frame(const Game_State& current_state);
void draw_frame(const Game_State& current_state);

void draw_start(const Game_State& current_state);
void draw_death(const Game_State& current_state);

#endif
