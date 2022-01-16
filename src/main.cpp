
#define VERSION "1.1.0"
#include "main.h"

bool g_arg_wide_mode{};
bool g_arg_menu{};
int g_arg_speed{};
int g_arg_increment{};
int g_arg_max_speed{};

int main(int argc, char *argv[]) {

    // catch ^C and cleanly exit
    std::signal(SIGINT, nc_exit);

    //parse command line arguments
    try {
        TCLAP::CmdLine cmd(
            "The game of snake (in ncurses)", //command description
            ' ', //charater between flags and arguments
            VERSION //version
        );

        TCLAP::SwitchArg wide_mode(
            "u", //short flag
            "unicode", //long flag
            "Draw snake using unicode characters", //description
            false //default
        );
        cmd.add(wide_mode);

        TCLAP::SwitchArg menu(
            "n", //short flag
            "no-menu", //long flag
            "Skip the start and death menu, score will be printed to stdout", //description
            false //default
        );
        cmd.add(menu);

        TCLAP::ValueArg<int> speed(
            "s", //short flag
            "speed", //long flag
            "How fast to start the game, in milliseconds per frame", //description
            false, //required?
            250, //default
            "milliseconds" //human readable description of type
        );
        cmd.add(speed);

        TCLAP::ValueArg<int> increment(
            "i", //short flag
            "incremnet", //long flag
            "how much to increase the speed of each frame by when a fruit is eaten", //description
            false, //required?
            10, //default
            "milliseconds" //human readable description of type
        );
        cmd.add(increment);

        TCLAP::ValueArg<int> max_speed(
            "m", //short flag
            "min-speed", //long flag
            "The minimum time per frame, lower values increase maximum speed of snake", //description
            false, //required?
            80, //default
            "milliseconds" //human readable description of type
        );
        cmd.add(max_speed);

        cmd.parse( argc, argv );

        //store parsed command line args in global variables
        g_arg_wide_mode = wide_mode.getValue();
        g_arg_menu = menu.getValue();
        g_arg_speed = speed.getValue();
        g_arg_increment = increment.getValue();
        g_arg_max_speed = max_speed.getValue();

    } catch (TCLAP::ArgException &e) {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    }

    // politely explaining to the program that milliseconds do, in fact,
    // exist and a duration of them should be called "millisec_type"
    typedef std::chrono::duration<int,std::milli> millisec_type;

    // init screen and set up screen
    if (g_arg_wide_mode) setlocale(LC_ALL, ""); // if in unicode mode, enable unicode support
    initscr();             // initialize screen
    curs_set(0);           // hide cursor
    keypad(stdscr, TRUE);  // enable keypad (arrow key) support
    cbreak();              // disable line buffering
    noecho();              // disable echoing back input
    nodelay(stdscr, TRUE); // make getch() calls non-blocking

    if (!g_arg_menu) {
        // TODO display start menu
    }

    // initialize the game state
    Game_State current_state = game_state_init();

    // select wide mode loop or ascii loop
    if (g_arg_wide_mode) {
        while (true) {
            // get current time plus frame durration
            auto end_time{std::chrono::steady_clock::now() +
                        millisec_type(current_state.speed)};
            // get user input and update state
            do_game_tick(current_state);
            // draw the game state in the window
            // (wide mode uses unicode chars)
            w_draw_frame(current_state);
            // Zzz... (sleep for remainder of duration)
            std::this_thread::sleep_until(end_time);
        }
    } else {
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
    }

    nc_exit(0);
    return EXIT_FAILURE;
}
