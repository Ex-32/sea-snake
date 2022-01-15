
#define VERSION 0.0.0
#include "main.h"

void nc_exit(int exitcode) {
    endwin(); // deallocates memory and ends ncurses
    std::exit(exitcode);
}

void SIGINT_handler(int sig) {
    nc_exit(sig);
}

void game_size_init(void) {
    int x{};
    int y{};
    getmaxyx(stdscr,y,x);
    g_game_hight = y;
    if (g_game_width % 2 == 0) {
        g_game_width = (x/2);
    } else {
        g_game_width = ((x-1)/2);
    }
}

int main() {
    std::signal(SIGINT, SIGINT_handler);

    // init screen and sets up screen
    initscr();
    //curs_set(0);
    keypad(stdscr, TRUE);
    game_size_init();

    // pause the screen output
    getch();

    int keycode{};
    while (1) {
        keycode = key_from_queue();
        if (keycode > 0) {
            printw("Key pressed! It was: %d\n", keycode);
            refresh();
        } else {
            printw("No key pressed yet...\n");
            refresh();
            sleep(1);
        }
    }

    nc_exit(0);
    return EXIT_FAILURE;
}
