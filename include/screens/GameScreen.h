/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_SCREENS_GAMESCREEN_H_
#define INCLUDE_SCREENS_GAMESCREEN_H_


#include <string>

#include <screens/IScreen.h>

#include <facades/NCurses.h>

#include <systems/RenderSystem.h>
#include <systems/FileIOSystem.h>

class GameScreen : public IScreen {
 private:
    std::shared_ptr<NCurses> curses;
    std::shared_ptr<RenderSystem> renderSystem;
    std::shared_ptr<FileIOSystem> fileIOSystem;
    std::string windowName;

 public:
    GameScreen();

    ~GameScreen() override;

    std::string update() override;

    void onCreation() override;

    void onDestruction() override;
};


#endif  // INCLUDE_SCREENS_GAMESCREEN_H_
