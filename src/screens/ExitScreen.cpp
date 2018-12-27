/* Copyright (C) 2018 hu553in */

#include <string>

#include <screens/ExitScreen.h>

#include <systems/FileIOSystem.h>

#include <Vector2.h>
#include <StaticStorage.h>

ExitScreen::ExitScreen() : curses {nullptr}, renderSystem {nullptr}, inputHandlingSystem {nullptr}, windowName {} {
    setLooping(false);
}

ExitScreen::~ExitScreen() = default;

std::string ExitScreen::update() {
    renderSystem->renderExitLogo(windowName);

    if ((inputHandlingSystem->handle(windowName)) == "enter") {
        setLooping(false);
    }

    if (looping) {
        return "looping";
    } else {
        return "end";
    }
}

void ExitScreen::onCreation() {
    curses = StaticStorage::getInstance().getEntry<NCurses>("curses");
    curses->enableCursesMode();

    renderSystem = StaticStorage::getInstance().getEntry<RenderSystem>("renderSystem");

    inputHandlingSystem = StaticStorage::getInstance().getEntry<InputHandlingSystem>("inputHandlingSystem");

    windowName = "exitWindow";
    curses->createWindow(windowName, Vector2<int> {0, 0}, curses->getSizeOfTerminal());

    auto fileIOSystem = StaticStorage::getInstance().getEntry<FileIOSystem>("fileIOSystem");
    fileIOSystem->inputExitLogo();

    setLooping(true);
}

void ExitScreen::onDestruction() {
    curses->clearWindow(windowName);
    curses->refreshWindow(windowName);
    curses->deleteWindow(windowName);
    curses->disableCursesMode();

    curses = nullptr;
    renderSystem = nullptr;
    inputHandlingSystem = nullptr;
    windowName = "";

    StaticStorage::getInstance().removeEntry("exitLogo");

    setLooping(false);
}

