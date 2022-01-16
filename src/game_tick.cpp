#include "game_tick.h"

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

    // initialize size of game field from console size
    {
        int x{};
        int y{};
        getmaxyx(stdscr,y,x);
        current_state.game_height = y;
        if (x % 2 == 0) {
            current_state.game_width = (x/2);
        } else {
            current_state.game_width  = ((x-1)/2);
        }
    }

    current_state.facing = random_int(0,3);

    // initialize the snake body so that it's at least 5 "tiles" away from the edge
    Point2d_int snake_start{
        random_int(5,(current_state.game_width-6)),
        random_int(5,(current_state.game_height-6))
    };
    current_state.snake_body.emplace_front(snake_start);

    // snake has starting length of one
    current_state.snake_length = 1;

    // initialize first fruit
    current_state.fruit = {
        random_int(0,current_state.game_width-1),
        random_int(0,current_state.game_height-1)
    };

    // set the starting game speed to one frame per 350ms
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

    // check if the head of the snake is on the fruit,
    // if it is, increase the snake length by one and spawn a new fruit
    if ( same_point2d_int(new_head,current_state.fruit) ) {
        ++current_state.snake_length;
        current_state.fruit = {
            random_int(0,current_state.game_width-1),
            random_int(0,current_state.game_height-1)
        };
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
            // TODO: go to death screen instead
            death(current_state.snake_length); //print and final score and exit
        }
    }
    // if the new head is outside the bounds, the snake is dead
    if (
        new_head.x > current_state.game_width-1 ||
        new_head.x < 0 ||
        new_head.y > current_state.game_height-1 ||
        new_head.y < 0
    ) {
        // TODO: go to death screen instead
        death(current_state.snake_length); //print and final score and exit
    }

    // attach the new head to the front of the snake
    current_state.snake_body.emplace_front(new_head);

}
