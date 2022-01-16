#pragma once

#ifndef GAME_TICK_H
#define GAME_TICK_H

#include <list>

#include <ncurses.h>

#include "misc.h"
#include "global_structs.h"

extern WINDOW *stdscr;

int key_from_queue(void);
Game_State game_state_init(void);
Game_State do_game_tick(Game_State current_state);

#endif
