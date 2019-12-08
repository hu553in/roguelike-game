# roguelike-game (WIP)

This game was created just for lulz and studying at development courses :)

## Technology stack

* Linux
* C++
* NCurses library
* Some other utils described below

## Required dependencies

* [NCurses](https://www.gnu.org/software/ncurses)
* [CMake](https://cmake.org)
* [Make](https://www.gnu.org/software/make)
* [GCC](https://gcc.gnu.org)
* [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html)
* [Python](https://www.python.org)

## Code style

This project _partially_ uses [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) and [cpplint](https://google.github.io/styleguide/cppguide.html#cpplint).

## Launch game

After installing dependencies, just run `make` in the project root folder.

## Additional commands

* Remove `cmake-build-debug` folder: `make clean`
* Reset leaderboard file: `make reset_leaderboard`
* Run project with only modified files rebuilding and without linting: `make run`
* Also you can find more commands in `Makefile`. Enjoy! ;)
