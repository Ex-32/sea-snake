#pragma once

#ifndef DRAW_H
#define DRAW_H

#include <ncurses.h>

#include "global_structs.h"

extern WINDOW *stdscr;

void print_point(Point2d_int point, const char* str_print);

void draw_frame(const Game_State& current_state);

// // TODO: add start and death screens
// void draw_start();
// void draw_death();

#endif
