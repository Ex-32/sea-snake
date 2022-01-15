#pragma once

#ifndef DRAW_H
#define DRAW_H

#include <ncurses.h>

#include "misc.h"
#include "global_structs.h"

extern WINDOW *stdscr;

void reset_screen(void);

void print_point(Point2d_int point, const char* str_print);

void draw_frame(Game_State* current_game_state);
void draw_start();
void draw_death();

#endif
