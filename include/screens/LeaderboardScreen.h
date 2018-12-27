/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_SCREENS_LEADERBOARDSCREEN_H_
#define INCLUDE_SCREENS_LEADERBOARDSCREEN_H_


#include <string>
#include <unordered_map>
#include <vector>

#include <screens/IScreen.h>

#include <facades/NCurses.h>

#include <systems/RenderSystem.h>
#include <systems/FileIOSystem.h>
#include <systems/InputHandlingSystem.h>
#include <systems/LeaderboardSortingSystem.h>

#include <Statistics.h>

class LeaderboardScreen : public IScreen {
    typedef void (LeaderboardScreen::*LeaderboardScreenMemberFunctionPtr)();

 private:
    std::shared_ptr<NCurses> curses;
    std::shared_ptr<RenderSystem> renderSystem;
    std::shared_ptr<FileIOSystem> fileIOSystem;
    std::shared_ptr<InputHandlingSystem> inputHandlingSystem;
    std::shared_ptr<LeaderboardSortingSystem> leaderboardSortingSystem;
    std::shared_ptr<std::vector<Statistics>> leaderboard;
    std::unordered_map<std::string, LeaderboardScreenMemberFunctionPtr> pointersToMemberFunctions;
    std::string windowName;

    void handlePressingLeftEvent();

    void handlePressingRightEvent();

    void handlePressingEnterEvent();

 public:
    LeaderboardScreen();

    ~LeaderboardScreen() override;

    std::string update() override;

    void onCreation() override;

    void onDestruction() override;
};


#endif  // INCLUDE_SCREENS_LEADERBOARDSCREEN_H_
