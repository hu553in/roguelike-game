# roguelike-game

## Table of contents

* [Description](#description)
* [Tech stack](#tech-stack)
* [Code style](#code-style)
* [Required dependencies](#required-dependencies)
* [Launch game](#launch-game)
* [Additional commands](#additional-commands)

## Description

This project is the terminal-based roguelike-like game.

The main purposes of creating this game are:
* making lulz xd
* improving programming skills

It's WIP so it does not work at the moment, but don't worry!

## Tech stack

* C++
* ncurses

## Code style

This project _partially_ uses
[Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
with [cpplint](https://google.github.io/styleguide/cppguide.html#cpplint).

## Required dependencies

* NCurses
* CMake
* GNU Make
* GCC
* ClangFormat (for the formatting)
* Python 2 (for the linting)

## How to run

**Note:** in case if you don't want to install ClangFormat and/or Python 2,
you should edit `./Makefile` and `./CMakeLists.txt` so that they don't use
these tools.

1) Install dependencies
2) Run `make`

## Additional `GNU Make` rules

* Remove the `cmake-build-debug` folder: `make clean`
* Reset the leaderboard file: `make reset_leaderboard`
* Run the project with rebuilding only modified files and without linting: `make run`

Also you can find more commands in `Makefile`. Enjoy! ;)
