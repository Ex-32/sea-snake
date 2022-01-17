# Sea-Snake
Sea-Snake is a command-line implementation of the classic game "snake" written in C++ using the ncurses library, the name is a play on the language name as it was created as approachable project for me to start to learn C++.

It should compile with no issue on linux and mac assuming you have `cmake` and `ncurses` installed, i got it to compile on windows with cygwin, but that's up to you.

## compilation instructions:
Ensure you have ncurses and cmake installed, if not:
```bash
# install with apt (Ubuntu/Debian):
sudo apt-get install libncurses-dev cmake

# install with Homebrew (Mac):
brew install ncurses cmake

# or some other way...
```

Then download or clone the code, and compile with cmake:
```bash
# from .../sea-snake
mkdir build
cd build
cmake ..
make
```
then run:
```bash
./sea-snake    # for normal ascii mode,
./sea-snake -u # for unicode mode, or
./sea-snake -h # for additional instructions
```
