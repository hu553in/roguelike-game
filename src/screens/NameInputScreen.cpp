/* Copyright (C) 2018 hu553in */

#include <string>

#include <screens/NameInputScreen.h>

#include <StaticStorage.h>
#include <Statistics.h>

NameInputScreen::NameInputScreen() : curses {nullptr}, renderSystem {nullptr}, windowName {} {
    setLooping(false);
}

NameInputScreen::~NameInputScreen() = default;

std::string NameInputScreen::update() {
    renderSystem->renderNameInputUI(windowName);

    auto statistics = std::make_shared<Statistics>(Statistics());

    auto windowSize = curses->getSizeOfWindow(windowName);
    const int maxLengthOfNickname = 20;
    auto coordForGettingString = Vector2<int>(windowSize.y / 2 + 1, windowSize.x / 2 - maxLengthOfNickname / 2);

    statistics->nickname = curses->getString(windowName, maxLengthOfNickname, true, coordForGettingString);

    if (!statistics->nickname.empty()) {
        StaticStorage::getInstance().registerEntry<Statistics>("statistics", statistics);

        setLooping(false);
    }

    if (looping) {
        return "looping";
    } else {
        return "game";
    }
}

void NameInputScreen::onCreation() {
    curses = StaticStorage::getInstance().getEntry<NCurses>("curses");
    curses->enableCursesMode();

    renderSystem = StaticStorage::getInstance().getEntry<RenderSystem>("renderSystem");

    windowName = "nameInputWindow";

    curses->createWindow(windowName, Vector2<int>(ZERO), curses->getSizeOfTerminal());

    setLooping(true);
}

void NameInputScreen::onDestruction() {
    curses->clearWindow(windowName);
    curses->refreshWindow(windowName);
    curses->deleteWindow(windowName);
    curses->disableCursesMode();

    curses = nullptr;
    renderSystem = nullptr;
    windowName = "";

    setLooping(false);
}

