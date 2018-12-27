/* Copyright (C) 2018 hu553in */

#include <memory>
#include <vector>
#include <string>

#include <screens/GameScreen.h>

#include <StaticStorage.h>

GameScreen::GameScreen() : curses {nullptr}, renderSystem {nullptr}, fileIOSystem {nullptr}, windowName {} {
    setLooping(false);
}

GameScreen::~GameScreen() = default;

std::string GameScreen::update() {
    renderSystem->renderGameplay(windowName);

    curses->getKeyCode(windowName);

    setLooping(false);

    if (looping) {
        return "looping";
    } else {
        return "exit";
    }
}

void GameScreen::onCreation() {
    curses = StaticStorage::getInstance().getEntry<NCurses>("curses");
    curses->enableCursesMode();

    renderSystem = StaticStorage::getInstance().getEntry<RenderSystem>("renderSystem");

    fileIOSystem = StaticStorage::getInstance().getEntry<FileIOSystem>("fileIOSystem");
    fileIOSystem->inputMap("level_1");

    windowName = "gameplayWindow";
    curses->createWindow(windowName, Vector2<int> {0, 0}, curses->getSizeOfTerminal() - Vector2<int>(ONE));

    setLooping(true);
}

void GameScreen::onDestruction() {
    curses->clearWindow(windowName);
    curses->refreshWindow(windowName);
    curses->deleteWindow(windowName);
    curses->disableCursesMode();

    curses = nullptr;
    renderSystem = nullptr;
    fileIOSystem = nullptr;
    windowName = "";

    setLooping(false);
}

