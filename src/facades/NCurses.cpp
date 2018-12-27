/* Copyright (C) 2018 hu553in */

#include <ncurses.h>
#include <string>
#include <cstddef>
#include <cassert>
#include <cstdint>

#include <facades/NCurses.h>

void NCurses::switchEchoModeOn() {
    curs_set(1);
    echo();
}

void NCurses::switchEchoModeOff() {
    curs_set(0);
    noecho();
}

NCurses::NCurses() = default;

NCurses::~NCurses() {
    disableCursesMode();
}

void NCurses::enableCursesMode() {
    initscr();
    curs_set(0);
    noecho();
    cbreak();

    start_color();

    initializeColorPair(ColorPairs::GREEN_ON_BLACK, COLOR_GREEN, COLOR_BLACK);
    initializeColorPair(ColorPairs::YELLOW_ON_BLACK, COLOR_YELLOW, COLOR_BLACK);
    initializeColorPair(ColorPairs::RED_ON_BLACK, COLOR_RED, COLOR_BLACK);
    initializeColorPair(ColorPairs::CYAN_ON_BLACK, COLOR_CYAN, COLOR_BLACK);
    initializeColorPair(ColorPairs::MAGENTA_ON_BLACK, COLOR_MAGENTA, COLOR_BLACK);
    initializeColorPair(ColorPairs::BLUE_ON_BLACK, COLOR_BLUE, COLOR_BLACK);
    initializeColorPair(ColorPairs::BLACK_ON_WHITE, COLOR_BLACK, COLOR_WHITE);
}

void NCurses::disableCursesMode() {
    deleteAllWindows();
    endwin();
}

void NCurses::initializeColorPair(ColorPairs pairName, int16_t foregroundColor, int16_t backgroundColor) {
    init_pair(static_cast<int16_t>(pairName), foregroundColor, backgroundColor);
}

void NCurses::createWindow(const std::string &windowName, Vector2<int> leftCornerCoord, Vector2<int> size) {
    if (windowsContainer.find(windowName) != windowsContainer.end()) {
        throw std::runtime_error("Window called " + windowName + " already exists!");
    }

    WINDOW *window = newwin(size.y, size.x, leftCornerCoord.y, leftCornerCoord.x);

    keypad(window, TRUE);

    windowsContainer[windowName] = window;
}

void NCurses::deleteWindow(const std::string &windowName) {
    if (windowsContainer.find(windowName) == windowsContainer.end()) {
        throw std::runtime_error("Window called " + windowName + " does not exist!");
    }

    delwin(windowsContainer.at(windowName));
    windowsContainer.erase(windowName);
}

void NCurses::deleteAllWindows() {
    for (auto iterator : windowsContainer) {
        delwin(iterator.second);
    }

    windowsContainer.clear();
}

void NCurses::clearWindow(const std::string &windowName) {
    wclear(windowsContainer.at(windowName));
}

void NCurses::refreshWindow(const std::string &windowName) {
    wrefresh(windowsContainer.at(windowName));
}

void NCurses::switchColorOn(const std::string &windowName, ColorPairs pairName) {
    wattron(windowsContainer.at(windowName), COLOR_PAIR(static_cast<int16_t>(pairName)));
}

void NCurses::switchColorOff(const std::string &windowName, ColorPairs pairName) {
    wattroff(windowsContainer.at(windowName), COLOR_PAIR(static_cast<int16_t>(pairName)));
}

void NCurses::drawBox(const std::string &windowName) {
    box(windowsContainer.at(windowName), ACS_VLINE, ACS_HLINE);
}

void NCurses::outputCarriage(const std::string &windowName) {
    switchColorOn(windowName, ColorPairs::BLACK_ON_WHITE);
    outputChar(windowName, ' ');
    switchColorOff(windowName, ColorPairs::BLACK_ON_WHITE);
}

void NCurses::outputString(const std::string &windowName, const std::string &string) {
    wprintw(windowsContainer.at(windowName), string.c_str());
}

void NCurses::outputStringInCenter(const std::string &windowName, const std::string &string, int offsetY, int offsetX) {
    offsetY -= 1;

    Vector2<int> sizeOfWorkspace = getSizeOfWindow(windowName);
    Vector2<int> coordForMovingCarriage = {sizeOfWorkspace.y / 2 + offsetY,
                                           static_cast<int>(sizeOfWorkspace.x / 2 - string.size() / 2 + offsetX)};

    moveCarriage(windowName, coordForMovingCarriage);
    wprintw(windowsContainer.at(windowName), string.c_str());
}

void NCurses::moveCarriage(const std::string &windowName, Vector2<int> coord) {
    wmove(windowsContainer.at(windowName), coord.y, coord.x);
}

void NCurses::outputChar(const std::string &windowName, char symbol) {
    waddch(windowsContainer.at(windowName), static_cast<chtype>(symbol));
}

int NCurses::getKeyCode(const std::string &windowName) {
    return wgetch(windowsContainer.at(windowName));
}

std::string NCurses::getString(const std::string &windowName, uint8_t numberOfSymbols, bool isLettersAllowed,
                               Vector2<int> coord) {
    assert(numberOfSymbols != 0);

    std::string buffer;
    char keyCode = 0;
    int counterOfSymbols = 0;

    coord.y--;

    moveCarriage(windowName, coord);
    outputCarriage(windowName);

    refreshWindow(windowName);

    while ((buffer.empty() || keyCode != 10) && counterOfSymbols < numberOfSymbols) {
        keyCode = static_cast<char>(getKeyCode(windowName));

        wrefresh(windowsContainer.at(windowName));

        bool check = (((keyCode >= 'A' && keyCode <= 'Z') || (keyCode >= 'a' && keyCode <= 'z')) && isLettersAllowed) ||
                     (keyCode >= '0' && keyCode <= '9') ||
                     (keyCode == 7);

        Vector2<int> currentCoord = coord;

        if (check) {
            if (keyCode == 7) {
                if (counterOfSymbols > 0) {
                    counterOfSymbols--;
                    buffer.pop_back();

                    currentCoord.x += counterOfSymbols;

                    moveCarriage(windowName, currentCoord + Vector2<int>(RIGHT));
                    outputChar(windowName, ' ');

                    moveCarriage(windowName, currentCoord);
                    outputCarriage(windowName);
                }

                moveCarriage(windowName, currentCoord);
            } else {
                buffer.push_back(keyCode);

                currentCoord.x += counterOfSymbols;
                moveCarriage(windowName, currentCoord);
                outputChar(windowName, keyCode);

                counterOfSymbols++;

                if (counterOfSymbols < numberOfSymbols) {
                    outputCarriage(windowName);
                }
            }
        }
    }

    return buffer;
}

void NCurses::clearToEndOfLine(const std::string &windowName) {
    wclrtoeol(windowsContainer.at(windowName));
}

void NCurses::deleteLine(const std::string &windowName) {
    wdeleteln(windowsContainer.at(windowName));
}

Vector2<int> NCurses::getSizeOfWindow(const std::string &windowName) {
    Vector2<int> size {};
    getmaxyx(windowsContainer.at(windowName), size.y, size.x);
    return size;
}

Vector2<int> NCurses::getSizeOfTerminal() {
    Vector2<int> size {};
    getmaxyx(stdscr, size.y, size.x);
    return size;
}

bool NCurses::isTerminalResized(Vector2<int> oldSize) {
    auto currentSize = getSizeOfTerminal();

    return currentSize.y != oldSize.y || currentSize.x != oldSize.x;
}
