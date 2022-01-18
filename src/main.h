#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <csignal> // for std::signal()
#include <iostream> // for std::cout and std::endl
#include <chrono> // for std::chrono::steady_clock() and std::chrono::duration<>
#include <thread> // for std::this_thread::sleep_until()
#include <cstdlib> // for std::exit

// for setlocale, initscr(), curs_set(), keypad(), noecho(), and nodelay()
#include <ncurses.h>

// for parsing command line arguments
#include "tclap/CmdLine.h"

#include "draw.h"
#include "game_tick.h"
#include "misc.h"
#include "global_structs.h"

int main(int argc, char *argv[]);

#endif
