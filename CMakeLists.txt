cmake_minimum_required(VERSION 3.8)

# if turned on with the argument `-D NO_UNICODE=ON` sea-snake it will compile
# without unicode support using the non-unicode version of ncurses,
# if you're getting a error saying NCURSES_LIB is set to NOTFOUND
# try enabling this flag.
option(NO_UNICODE "compiles without unicode support" OFF)

# enable debug flags (overrules OPTIMIZATIONS)
option(DEBUG "compiles in debug mode" OFF)
# enables optimization flags (overruled by DEBUG)
option(OPTIMIZATIONS "enables compiler optimization" ON)
# if you turn this off you're on your own
option(WARNINGS "enables exteneded compiler warnings; turn off at your own peril" ON)

# define project
project("sea-snake")

# C++17 is required, this enforces that
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED)

if(NO_UNICODE)
  # find nucurses library on system
  find_library(NCURSES_LIB ncurses)
else(NO_UNICODE)
  # find unicode nucurses library on system depending on platform
  if(APPLE)
    find_library(NCURSES_LIB ncurses)
  else(APPLE)
    find_library(NCURSES_LIB ncursesw)
  endif(APPLE)
endif(NO_UNICODE)

# add sea-snake executable
add_executable(sea-snake "./src/main.cpp" "./src/draw.cpp" "./src/game_tick.cpp" "./src/misc.cpp")

# add local include folder to target
# this contains the tclap
target_include_directories(sea-snake PRIVATE "./include")

# must be defined for unicode ncurses to work on certain platforms
# (looking at you apple)
if (NOT NO_UNICODE)
  target_compile_options(sea-snake PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>: /D_XOPEN_SOURCE_EXTENDED >
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -D_XOPEN_SOURCE_EXTENDED >
  )
endif(NOT NO_UNICODE)

# define NO_UNICODE in preprocessor,
# this will exclude unicode mode parts of the code at compile-time
if(NO_UNICODE)
  add_compile_definitions(NO_UNICODE)
endif(NO_UNICODE)

# add ncurses library to sea-snake
target_link_libraries(sea-snake PRIVATE "${NCURSES_LIB}")

# add warning flags
if(WARNINGS)
  target_compile_options(sea-snake PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>: /W4 >
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -Wall -Wextra -Wpedantic >
  )
endif(WARNINGS)

# add debug flags
if(DEBUG)
  target_compile_options(sea-snake PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>: /Od >
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -Og >
  )
endif(DEBUG)

# add optimization flags
if(OPTIMIZATIONS AND NOT DEBUG)
  target_compile_options(sea-snake PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>: /O2 >
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>: -O2 >
  )
endif(OPTIMIZATIONS AND NOT DEBUG)
