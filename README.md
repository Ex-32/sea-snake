# Sea-Snake
## !! currently WIP, not functional yet !!
Sea-Snake is a command-line implementation of the classic game "snake" written in C++ using the ncurses library, the name is a play on the language name as it was created as approachable project for me to start to learn C++. It should compile on linux and mac assuming you have `cmake` and `ncurses` installed (it might compile on windows through cygwin or mingw).

## compilation instructions:
Ensure you have ncurses installed, if not:
```bash
# install with apt (Ubuntu/Debian):
sudo apt-get install libncurses5-dev libncursesw5-dev

# install with Homebrew (Mac):
brew install ncurses

# or some other way...
```

Then compile with cmake:
```bash
# from .../sea-snake
mkdir build
cd build
cmake ..
make
```
