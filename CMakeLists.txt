cmake_minimum_required(VERSION 3.8)

# if run with the argument `-D NO_UNICODE=ON` sea-snake it will compile
# without unicode support using the non-unicode version of ncurses,
# if you're getting a error saying NCURSES_LIB is set to NOTFOUND
# try enabling this flag.
option(NO_UNICODE "compiles without unicode support" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -pipe")

set(CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}          -g ")
set(CMAKE_CXX_FLAGS_RELEASE        "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}        -O2")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_MINSIZEREL}     -Os")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -Og")

project("sea-snake")

# C++17 is required, this enforces that
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED)

set(CURSES_NEED_NCURSES TRUE)
if(NOT NO_UNICODE AND NOT APPLE)
  set(CURSES_NEED_WIDE TRUE)
endif(NOT NO_UNICODE AND NOT APPLE)
find_package(Curses REQUIRED)

# add sea-snake executable
add_executable(
  sea-snake
  "./src/main.cpp"
  "./src/draw.cpp"
  "./src/game_tick.cpp"
  "./src/misc.cpp"
)

# add local include folder to target
# this contains the tclap library
target_include_directories(sea-snake PRIVATE "./include")

if(NO_UNICODE)
  # define NO_UNICODE in the preprocessor,
  # this will exclude unicode mode parts of the code at compile-time
  target_compile_definitions(sea-snake PUBLIC NO_UNICODE)
else(NO_UNICODE)
  # must be defined for unicode ncurses to work on certain platforms
  # (looking at you apple)
  target_compile_definitions(sea-snake PUBLIC _XOPEN_SOURCE_EXTENDED)
endif(NO_UNICODE)

target_include_directories(sea-snake PRIVATE ${CURSES_INCLUDE_DIRS})
#target_include_directories(sea-snake PRIVATE ${CURSES_INCLUDE_PATH})
target_link_libraries(sea-snake PRIVATE ${CURSES_LIBRARIES})

