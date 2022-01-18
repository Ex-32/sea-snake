#include "game_tick.h"

// holds the program in blocks of 200ms until a key is pressed
void await_key(void) {
    // clear char queue
    int keycode{};
    while (keycode >= 0) {
        keycode = key_from_queue();
    }
    // while no keystroke new keycode every 200ms, return on keystroke
    while (true) {
        keycode = key_from_queue();
        if (keycode >= 0) return;
        sleep_milli(200);
    }
}

// gets key code from the queue, returns keycode if there is one, otherwise -1
int key_from_queue(void) {
    int keycode {getch()};
    if (keycode != ERR) {
        return keycode;
    } else {
        return -1;
    }
}

Game_State game_state_init(void) {

    Game_State current_state;

    if (g_console_width % 2 == 0) {
       current_state.game_window = newwin(g_console_hight, g_console_width, 0, 0);
    } else {
        current_state.game_window = newwin(g_console_hight, (g_console_width-1), 0, 0);
    }

    // initialize size of game field from window size
    // 2 less than window size to account for window border
    {
        int x{};
        int y{};
        getmaxyx(current_state.game_window,y,x);
        current_state.game_height = y-2;
        current_state.game_width = (x/2)-2;
    }

    current_state.game_size = current_state.game_height * current_state.game_width;

    current_state.facing = random_int(0,3);

    // initialize the snake body so that it's at least 5 "tiles" away from the edge
    Point2d_int snake_start{
        random_int(6,(current_state.game_width-5)),
        random_int(6,(current_state.game_height-5))
    };
    current_state.snake_body.emplace_front(snake_start);

    // snake has starting length of one
    current_state.snake_length = 1;

    // initialize first fruit
    current_state.fruit = {
        // start from 1 instead of 0 because of window border
        random_int(1,current_state.game_width),
        random_int(1,current_state.game_height)
    };

    // set the starting game speed to stating speed (one frame per 200ms by default)
    current_state.speed = g_arg_speed;

    return current_state;

}

void do_game_tick(Game_State& current_state) {

    // gets direction that snake is facing from keystrokes
    // loops though keystrokes from the queue until there are no keycodes in
    // queue and uses them to set the direction the snake is facing
    int new_facing{current_state.facing};
    for (int keycode{key_from_queue()}; keycode >= 0; keycode = key_from_queue()) {
        switch (keycode) {
            case 258: // down arrow key
                // if not facing up, now facing down
                if (current_state.facing != 1) new_facing = 0;
                break;
            case 259: // up arrow key
                // if not facing down, now facing up
                if (current_state.facing != 0) new_facing = 1;
                break;
            case 260: // left arrow key
                // if not facing right, now facing left
                if (current_state.facing != 3) new_facing = 2;
                break;
            case 261: // right arrow key
                // if not facing left, now facing right
                if (current_state.facing != 2) new_facing = 3;
                break;
        }
    }
    current_state.facing = new_facing;

    // get current location of head, create new snake segment that's moved one
    // tile in the direction that it's facing then add that to the front of the
    // snake, effectively moving the snake forward one tile
    Point2d_int old_head = current_state.snake_body.front();
    Point2d_int new_head{old_head};
    switch(current_state.facing) {
        case 0: // move head down one tile
            ++new_head.y;
            break;
        case 1: // move head up one tile
            --new_head.y;
            break;
        case 2: // move head left one tile
            --new_head.x;
            break;
        case 3: // move head right one tile
            ++new_head.x;
            break;
    }

    // check if the head of the snake is on the fruit, if it is,
    // increase the snake length by one and sets the flag to spawn a new fruit
    bool new_fruit_needed{false};
    if ( same_point2d_int(new_head,current_state.fruit) ) {
        ++current_state.snake_length;
        if (current_state.snake_length >= current_state.game_size) {
            if (g_arg_skip_menu) win(current_state.snake_length);
            else draw_win(current_state);
        }
        new_fruit_needed = true;
        if (current_state.speed > g_arg_max_speed) {
            current_state.speed -= g_arg_increment;
        }
    }

    // compares actual size of snake to to correct snake length and pops body
    // segments off the end until it's the correct length.
    // (std::list.size() returns unsigned integral type, so
    // current_state.snake_length and snake_length_actual are unsigned ints)
    for (
        long unsigned int snake_length_actual{current_state.snake_body.size()};
        snake_length_actual > current_state.snake_length-1;
        // -1 because we haven't added the new head yet ^^
        snake_length_actual = current_state.snake_body.size()
    ) {
        current_state.snake_body.pop_back();
    }

    // if the new head should be where the snake body already is,
    // the snake is dead
    for (const auto& snake_segment : (current_state.snake_body)) {
        if (same_point2d_int(new_head,snake_segment)) {
        if (g_arg_skip_menu) death(current_state.snake_length); //print and final score and exit
        else draw_death(current_state);

        }
    }
    // if the new head is outside the bounds, the snake is dead
    if (
        // < 1 instead of < 0 because of window border
        new_head.x > current_state.game_width ||
        new_head.x < 1 ||
        new_head.y > current_state.game_height ||
        new_head.y < 1
    ) {
        if (g_arg_skip_menu) death(current_state.snake_length); //print and final score and exit
        else draw_death(current_state);

    }

    // attach the new head to the front of the snake
    current_state.snake_body.emplace_front(new_head);

    while (new_fruit_needed) {
        // define a new fruit
        current_state.fruit = {
            // start from 1 instead of 0 because of window border
            random_int(1,current_state.game_width),
            random_int(1,current_state.game_height)
        };
        // new fruit no longer needed
        new_fruit_needed = false;
        // check if that spot is part of the snake
        for (const auto& snake_segment : (current_state.snake_body)) {
            // if it is, we need a new, new fruit
            if (same_point2d_int(current_state.fruit, snake_segment)) {
                new_fruit_needed = true;
                break;
            }
        }
    }
}
