/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_FACADES_NCURSES_H_
#define INCLUDE_FACADES_NCURSES_H_


#include <ncurses.h>
#include <string>
#include <unordered_map>
#include <cstddef>

#include <Vector2.h>

enum class ColorPairs {
    GREEN_ON_BLACK = 1,
    RED_ON_BLACK = 2,
    YELLOW_ON_BLACK = 3,
    CYAN_ON_BLACK = 4,
    MAGENTA_ON_BLACK = 5,
    BLUE_ON_BLACK = 6,
    BLACK_ON_WHITE = 7
};

class NCurses {
 private:
    std::unordered_map<std::string, WINDOW *> windowsContainer {};

    void outputCarriage(const std::string &windowName);

    void initializeColorPair(ColorPairs pairName, int16_t foregroundColor, int16_t backgroundColor);

 public:
    NCurses();

    ~NCurses();

    void enableCursesMode();

    void disableCursesMode();

    void switchEchoModeOn();

    void switchEchoModeOff();

    void createWindow(const std::string &windowName, Vector2<int> leftCornerCoord, Vector2<int> size);

    void deleteWindow(const std::string &windowName);

    void deleteAllWindows();

    void clearWindow(const std::string &windowName);

    void refreshWindow(const std::string &windowName);

    void switchColorOn(const std::string &windowName, ColorPairs pairName);

    void switchColorOff(const std::string &windowName, ColorPairs pairName);

    void drawBox(const std::string &windowName);

    void outputString(const std::string &windowName, const std::string &string);

    void outputStringInCenter(const std::string &windowName, const std::string &string, int offsetY, int offsetX);

    void moveCarriage(const std::string &windowName, Vector2<int> coord);

    void outputChar(const std::string &windowName, char symbol);

    int getKeyCode(const std::string &windowName);

    std::string getString(const std::string &windowName, uint8_t numberOfSymbols, bool isLettersAllowed,
                          Vector2<int> coord);

    void clearToEndOfLine(const std::string &windowName);

    void deleteLine(const std::string &windowName);

    Vector2<int> getSizeOfWindow(const std::string &windowName);

    Vector2<int> getSizeOfTerminal();

    bool isTerminalResized(Vector2<int> oldSize);
};


#endif  // INCLUDE_FACADES_NCURSES_H_
