#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <cstdlib>
#include <csignal>

#include <string>
#include <iostream>
#include <chrono> // for std::chrono::steady_clock() and std::chrono::duration<>
#include <thread> // for std::this_thread::sleep_until()

#include <ncurses.h>

#include "draw.h"
#include "game_tick.h"
#include "misc.h"
#include "global_structs.h"

int main();

#endif
