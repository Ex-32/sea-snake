#include "game_tick.h"

// gets key code from the queue, returns keycode if there is one, otherwise -1
int key_from_queue(void) {
    int keycode = getch();
    if (keycode != ERR) {
        return keycode;
    } else {
        return -1;
    }
}
