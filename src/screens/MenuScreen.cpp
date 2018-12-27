/* Copyright (C) 2018 hu553in */

#include <string>
#include <vector>
#include <functional>

#include <screens/MenuScreen.h>

#include <StaticStorage.h>

void MenuScreen::handlePressingUpEvent() {
    if (highlightedEntry == 0) {
        highlightedEntry = menuEntries.size() - 1;
    } else {
        highlightedEntry--;
    }
}

void MenuScreen::handlePressingDownEvent() {
    if (highlightedEntry == menuEntries.size() - 1) {
        highlightedEntry = 0;
    } else {
        highlightedEntry++;
    }
}

void MenuScreen::handlePressingEnterEvent() {
    setLooping(false);
}

MenuScreen::MenuScreen()
    : windowName {}, highlightedEntry {}, pointersToMemberFunctions {}, menuEntries {},
      menuEntriesNamesForOutput {nullptr}, curses {nullptr}, renderSystem {nullptr}, inputHandlingSystem {nullptr} {
    setLooping(false);
}

MenuScreen::~MenuScreen() = default;

std::string MenuScreen::update() {
    StaticStorage::getInstance().registerEntry<uint64_t>("highlightedEntry",
                                                         std::make_shared<uint64_t>(highlightedEntry));

    StaticStorage::getInstance().registerEntry<std::vector<std::string>>("menuEntriesNamesForOutput",
                                                                         menuEntriesNamesForOutput);

    renderSystem->renderMenu(windowName);

    StaticStorage::getInstance().removeEntry("highlightedEntry");
    StaticStorage::getInstance().removeEntry("menuEntriesNamesForOutput");

    std::string input = inputHandlingSystem->handle(windowName);
    if (pointersToMemberFunctions.find(input) != pointersToMemberFunctions.end()) {
        std::invoke(pointersToMemberFunctions[input], this);
    }

    if (looping) {
        return "looping";
    } else {
        return menuEntries.at(static_cast<int>(highlightedEntry));
    }
}

void MenuScreen::onCreation() {
    curses = StaticStorage::getInstance().getEntry<NCurses>("curses");
    curses->enableCursesMode();

    renderSystem = StaticStorage::getInstance().getEntry<RenderSystem>("renderSystem");
    inputHandlingSystem = StaticStorage::getInstance().getEntry<InputHandlingSystem>("inputHandlingSystem");

    pointersToMemberFunctions.insert({"up", &MenuScreen::handlePressingUpEvent});
    pointersToMemberFunctions.insert({"down", &MenuScreen::handlePressingDownEvent});
    pointersToMemberFunctions.insert({"enter", &MenuScreen::handlePressingEnterEvent});

    menuEntries.insert({0, "nameInput"});
    menuEntries.insert({1, "leaderboard"});
    menuEntries.insert({2, "exit"});

    menuEntriesNamesForOutput = std::make_shared<std::vector<std::string>>();

    menuEntriesNamesForOutput->emplace_back("Play game");
    menuEntriesNamesForOutput->emplace_back("Leaderboard");
    menuEntriesNamesForOutput->emplace_back("Quit game");

    windowName = "menuWindow";
    curses->createWindow(windowName, Vector2<int> {0, 0}, curses->getSizeOfTerminal());

    setLooping(true);
}

void MenuScreen::onDestruction() {
    curses->clearWindow(windowName);
    curses->refreshWindow(windowName);
    curses->deleteWindow(windowName);
    curses->disableCursesMode();

    pointersToMemberFunctions.clear();

    menuEntries.clear();
    menuEntriesNamesForOutput->clear();
    menuEntriesNamesForOutput = nullptr;

    if (highlightedEntry != 0) {
        highlightedEntry = 0;
    }

    curses = nullptr;
    renderSystem = nullptr;
    inputHandlingSystem = nullptr;
    windowName = "";

    setLooping(false);
}

