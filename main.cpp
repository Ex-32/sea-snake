
#define VERSION 1.0.0
#include "main.h"

int main() {
    // catch ^C and cleanly exit
    std::signal(SIGINT, nc_exit);

    // init screen and set up screen
    initscr();             // initialize screen
    curs_set(0);           // hide cursor
    keypad(stdscr, TRUE);  // enable keypad (arrow key) support
    cbreak();              // disable line buffering
    noecho();              // disable echoing back input
    nodelay(stdscr, TRUE); // make getch() calls non-blocking

    // initialize the game state
    Game_State current_state = game_state_init();


    while (true) {
        // get user input and update state
        do_game_tick(current_state);
        // draw the game state in the window
        draw_frame(current_state);
        // Zzz...
        sleep_milli(current_state.speed);
    }

    nc_exit(0);
    return EXIT_FAILURE;
}
