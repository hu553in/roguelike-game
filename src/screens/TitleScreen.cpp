/* Copyright (C) 2018 hu553in */

#include <string>
#include <vector>

#include <screens/TitleScreen.h>

#include <systems/FileIOSystem.h>

#include <StaticStorage.h>

TitleScreen::TitleScreen() : curses {nullptr}, renderSystem {nullptr}, inputHandlingSystem {nullptr}, windowName {} {
    setLooping(false);
}

TitleScreen::~TitleScreen() = default;

std::string TitleScreen::update() {
    renderSystem->renderStartLogo(windowName);

    if ((inputHandlingSystem->handle(windowName)) == "enter") {
        setLooping(false);
    }

    if (looping) {
        return "looping";
    } else {
        return "menu";
    }
}

void TitleScreen::onCreation() {
    curses = StaticStorage::getInstance().getEntry<NCurses>("curses");
    curses->enableCursesMode();

    renderSystem = StaticStorage::getInstance().getEntry<RenderSystem>("renderSystem");

    inputHandlingSystem = StaticStorage::getInstance().getEntry<InputHandlingSystem>("inputHandlingSystem");

    windowName = "titleWindow";
    curses->createWindow(windowName, Vector2<int> {0, 0}, curses->getSizeOfTerminal());

    auto fileIOSystem = StaticStorage::getInstance().getEntry<FileIOSystem>("fileIOSystem");
    fileIOSystem->inputStartLogo();

    setLooping(true);
}

void TitleScreen::onDestruction() {
    curses->clearWindow(windowName);
    curses->refreshWindow(windowName);
    curses->deleteWindow(windowName);
    curses->disableCursesMode();

    curses = nullptr;
    renderSystem = nullptr;
    inputHandlingSystem = nullptr;
    windowName = "";

    StaticStorage::getInstance().removeEntry("startLogo");

    setLooping(false);
}

