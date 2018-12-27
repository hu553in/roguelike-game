/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_SCREENS_MENUSCREEN_H_
#define INCLUDE_SCREENS_MENUSCREEN_H_


#include <string>
#include <vector>
#include <memory>
#include <utility>

#include <screens/IScreen.h>

#include <facades/NCurses.h>

#include <systems/RenderSystem.h>
#include <systems/InputHandlingSystem.h>

class MenuScreen : public IScreen {
    typedef void (MenuScreen::*MenuScreenMemberFunctionPtr)();

 private:
    std::string windowName;
    uint64_t highlightedEntry;
    std::unordered_map<std::string, MenuScreenMemberFunctionPtr> pointersToMemberFunctions;
    std::unordered_map<int, std::string> menuEntries;
    std::shared_ptr<std::vector<std::string>> menuEntriesNamesForOutput;
    std::shared_ptr<NCurses> curses;
    std::shared_ptr<RenderSystem> renderSystem;
    std::shared_ptr<InputHandlingSystem> inputHandlingSystem;

    void handlePressingUpEvent();

    void handlePressingDownEvent();

    void handlePressingEnterEvent();

 public:
    MenuScreen();

    ~MenuScreen() override;

    std::string update() override;

    void onCreation() override;

    void onDestruction() override;
};


#endif  // INCLUDE_SCREENS_MENUSCREEN_H_
