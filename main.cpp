
#define VERSION 1.0.0
#include "main.h"

int main() {
    // catch ^C and cleanly exit
    std::signal(SIGINT, nc_exit);

    // politely explaining to the program that milliseconds do, in fact,
    // exist and a duration of them should be called "millisec_type"
    typedef std::chrono::duration<int,std::milli> millisec_type;

    // init screen and set up screen
    //setlocale(LC_ALL, ""); // enable unicode support
    initscr();             // initialize screen
    curs_set(0);           // hide cursor
    keypad(stdscr, TRUE);  // enable keypad (arrow key) support
    cbreak();              // disable line buffering
    noecho();              // disable echoing back input
    nodelay(stdscr, TRUE); // make getch() calls non-blocking

    // initialize the game state
    Game_State current_state = game_state_init();

    while (true) {
        // get current time plus frame durration
        auto end_time{std::chrono::steady_clock::now() +
                      millisec_type(current_state.speed)};
        // get user input and update state
        do_game_tick(current_state);
        // draw the game state in the window
        draw_frame(current_state);
        // Zzz... (sleep for remainder of duration)
        std::this_thread::sleep_until(end_time);
    }

    nc_exit(0);
    return EXIT_FAILURE;
}
