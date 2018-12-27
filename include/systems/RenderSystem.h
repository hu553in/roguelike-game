/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_SYSTEMS_RENDERSYSTEM_H_
#define INCLUDE_SYSTEMS_RENDERSYSTEM_H_


#include <string>
#include <vector>

class RenderSystem {
 public:
    RenderSystem();

    ~RenderSystem();

    void renderStartLogo(const std::string &windowName);

    void renderMenu(const std::string &windowName);

    void renderNameInputUI(const std::string &windowName);

    void renderGameplay(const std::string &windowName);

    void renderLeaderboard(const std::string &windowName);

    void renderExitLogo(const std::string &windowName);
};


#endif  // INCLUDE_SYSTEMS_RENDERSYSTEM_H_
