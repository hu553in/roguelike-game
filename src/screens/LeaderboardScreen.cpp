/* Copyright (C) 2018 hu553in */

#include <string>
#include <algorithm>
#include <vector>
#include <functional>

#include <screens/LeaderboardScreen.h>

#include <StaticStorage.h>

void LeaderboardScreen::handlePressingLeftEvent() {
    leaderboardSortingSystem->sortByKillingScore();
}

void LeaderboardScreen::handlePressingRightEvent() {
    leaderboardSortingSystem->sortByNumberOfActions();
}

void LeaderboardScreen::handlePressingEnterEvent() {
    setLooping(false);
}

LeaderboardScreen::LeaderboardScreen()
    : curses {nullptr}, renderSystem {nullptr}, fileIOSystem {nullptr}, inputHandlingSystem {nullptr},
      leaderboardSortingSystem {nullptr}, leaderboard {nullptr}, windowName {} {
    setLooping(false);
}

LeaderboardScreen::~LeaderboardScreen() = default;

std::string LeaderboardScreen::update() {
    renderSystem->renderLeaderboard(windowName);

    std::string input = inputHandlingSystem->handle(windowName);
    if (pointersToMemberFunctions.find(input) != pointersToMemberFunctions.end()) {
        std::invoke(pointersToMemberFunctions[input], this);
    }

    if (looping) {
        return "looping";
    } else {
        return "menu";
    }
}

void LeaderboardScreen::onCreation() {
    curses = StaticStorage::getInstance().getEntry<NCurses>("curses");
    curses->enableCursesMode();

    renderSystem = StaticStorage::getInstance().getEntry<RenderSystem>("renderSystem");
    fileIOSystem = StaticStorage::getInstance().getEntry<FileIOSystem>("fileIOSystem");
    inputHandlingSystem = StaticStorage::getInstance().getEntry<InputHandlingSystem>("inputHandlingSystem");
    leaderboardSortingSystem = StaticStorage::getInstance().getEntry<LeaderboardSortingSystem>(
        "leaderboardSortingSystem");

    windowName = "leaderboardWindow";

    curses->createWindow(windowName, Vector2<int>(ZERO), curses->getSizeOfTerminal());

    if (StaticStorage::getInstance().containsEntry("statistics")) {
        fileIOSystem->outputNewRecordToLeaderboard();
        StaticStorage::getInstance().removeEntry("statistics");
    }

    fileIOSystem->inputLeaderboard();

    leaderboard = StaticStorage::getInstance().getEntry<std::vector<Statistics>>("leaderboard");

    if (!leaderboard->empty()) {
        StaticStorage::getInstance().registerEntry("isLeaderboardSortedInDescendingOrder",
                                                   std::make_shared<bool>(false));
        StaticStorage::getInstance().registerEntry("isLeaderboardSortedByKillingScore", std::make_shared<bool>(false));

        leaderboardSortingSystem->sortByKillingScore();

        pointersToMemberFunctions["left"] = &LeaderboardScreen::handlePressingLeftEvent;
        pointersToMemberFunctions["right"] = &LeaderboardScreen::handlePressingRightEvent;
    }

    pointersToMemberFunctions["enter"] = &LeaderboardScreen::handlePressingEnterEvent;

    setLooping(true);
}

void LeaderboardScreen::onDestruction() {
    curses->clearWindow(windowName);
    curses->refreshWindow(windowName);
    curses->deleteWindow(windowName);
    curses->disableCursesMode();

    if (!leaderboard->empty()) {
        leaderboardSortingSystem->sortByKillingScore();

        StaticStorage::getInstance().removeEntry("isLeaderboardSortedInDescendingOrder");
        StaticStorage::getInstance().removeEntry("isLeaderboardSortedByKillingScore");

        fileIOSystem->outputLeaderboard();
    }

    leaderboard = nullptr;
    StaticStorage::getInstance().removeEntry("leaderboard");

    curses = nullptr;
    renderSystem = nullptr;
    fileIOSystem = nullptr;
    windowName = "";

    setLooping(false);
}

