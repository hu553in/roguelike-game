/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_SCREENS_EXITSCREEN_H_
#define INCLUDE_SCREENS_EXITSCREEN_H_


#include <string>

#include <screens/IScreen.h>

#include <facades/NCurses.h>

#include <systems/RenderSystem.h>
#include <systems/InputHandlingSystem.h>

class ExitScreen : public IScreen {
 private:
    std::shared_ptr<NCurses> curses;
    std::shared_ptr<RenderSystem> renderSystem;
    std::shared_ptr<InputHandlingSystem> inputHandlingSystem;
    std::string windowName;

 public:
    ExitScreen();

    ~ExitScreen() override;

    std::string update() override;

    void onCreation() override;

    void onDestruction() override;
};


#endif  // INCLUDE_SCREENS_EXITSCREEN_H_
