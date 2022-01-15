#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <cstdlib>
#include <csignal>

#include <string>
#include <iostream>

#include <ncurses.h>

#include "draw.h"
#include "game_tick.h"
#include "misc.h"
#include "global_structs.h"

void nc_exit(int signum);
void SIGINT_handler(int sig);

void game_size_init(void);

int main();

#endif
