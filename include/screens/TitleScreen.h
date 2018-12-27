/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_SCREENS_TITLESCREEN_H_
#define INCLUDE_SCREENS_TITLESCREEN_H_


#include <string>
#include <memory>

#include <screens/IScreen.h>

#include <facades/NCurses.h>

#include <systems/RenderSystem.h>
#include <systems/InputHandlingSystem.h>

class TitleScreen : public IScreen {
 private:
    std::shared_ptr<NCurses> curses;
    std::shared_ptr<RenderSystem> renderSystem;
    std::shared_ptr<InputHandlingSystem> inputHandlingSystem;
    std::string windowName;

 public:
    TitleScreen();

    ~TitleScreen() override;

    std::string update() override;

    void onCreation() override;

    void onDestruction() override;
};


#endif  // INCLUDE_SCREENS_TITLESCREEN_H_
