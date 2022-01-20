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
void _w_print_head(WINDOW* screen, const Point2d_int& point);
void _w_print_body(WINDOW* screen, const Point2d_int& point);
void _w_print_fruit(WINDOW* screen, const Point2d_int& point);
#endif
void _print_head(WINDOW* screen, const Point2d_int& point);
void _print_body(WINDOW* screen, const Point2d_int& point);
void _print_fruit(WINDOW* screen, const Point2d_int& point);

void _print_back(WINDOW* screen, const Point2d_int& point);

void _color_head(WINDOW* screen, const Point2d_int& point);
void _color_body(WINDOW* screen, const Point2d_int& point);
void _color_fruit(WINDOW* screen, const Point2d_int& point);

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
