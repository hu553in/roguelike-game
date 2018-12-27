/* Copyright (C) 2018 hu553in */

#include <string>
#include <vector>

#include <systems/RenderSystem.h>

#include <facades/NCurses.h>

#include <entities/IItemEntity.h>
#include <entities/IStaticEntity.h>
#include <entities/IMovableEntity.h>
#include <entities/Player.h>

#include <StaticStorage.h>
#include <Statistics.h>
#include <Camera.h>

RenderSystem::RenderSystem() = default;

RenderSystem::~RenderSystem() = default;

void RenderSystem::renderStartLogo(const std::string &windowName) {
    auto curses = StaticStorage::getInstance().getEntry<NCurses>("curses");
    auto startLogo = StaticStorage::getInstance().getEntry<std::vector<std::string>>("startLogo");

    curses->clearWindow(windowName);

    for (uint8_t iter = 0; iter < startLogo->size(); iter++) {
        if (iter < startLogo->size() - 1) {
            curses->switchColorOn(windowName, ColorPairs::RED_ON_BLACK);
        }

        curses->outputStringInCenter(windowName, startLogo->at(iter),
                                     static_cast<int>(iter) - static_cast<int>(startLogo->size()) / 2, 0);

        if (iter < startLogo->size() - 1) {
            curses->switchColorOff(windowName, ColorPairs::RED_ON_BLACK);
        }
    }
}

void RenderSystem::renderMenu(const std::string &windowName) {
    auto curses = StaticStorage::getInstance().getEntry<NCurses>("curses");
    auto highlightedEntry = StaticStorage::getInstance().getEntry<uint64_t>("highlightedEntry");
    auto menuEntries = StaticStorage::getInstance().getEntry<std::vector<std::string>>("menuEntriesNamesForOutput");

    curses->clearWindow(windowName);

    int dy = -static_cast<int>(menuEntries->size() / 2);

    curses->outputStringInCenter(windowName, "Welcome to MAIN MENU, kitten!", dy, -4);

    curses->switchColorOn(windowName, ColorPairs::GREEN_ON_BLACK);
    curses->outputStringInCenter(windowName, "*(^-^)*", dy, 15);
    curses->switchColorOff(windowName, ColorPairs::GREEN_ON_BLACK);

    Vector2<int> terminalSize = curses->getSizeOfTerminal();

    for (uint32_t i = 0; i < menuEntries->size(); i++) {
        dy++;

        if (i == *highlightedEntry) {
            curses->switchColorOn(windowName, ColorPairs::YELLOW_ON_BLACK);
        }

        curses->moveCarriage(windowName, Vector2<int>(terminalSize.y / 2 + dy, terminalSize.x / 2 - 8));
        curses->outputString(windowName, std::to_string(i + 1) + ". " + menuEntries->at(i));

        if (i == *highlightedEntry) {
            curses->switchColorOff(windowName, ColorPairs::YELLOW_ON_BLACK);
        }
    }
}

void RenderSystem::renderNameInputUI(const std::string &windowName) {
    auto curses = StaticStorage::getInstance().getEntry<NCurses>("curses");

    curses->clearWindow(windowName);

    curses->outputStringInCenter(windowName, "Input your nickname (20 symbols max):", -1, 0);
    curses->outputStringInCenter(windowName, "<                    >", 1, 0);
}

void RenderSystem::renderGameplay(const std::string &windowName) {
    auto staticEntities = StaticStorage::getInstance().getEntry<std::vector<std::vector<IStaticEntitySharedPtr>>>(
        "staticEntities");
    auto itemEntities = StaticStorage::getInstance().getEntry<std::vector<std::vector<IItemEntitySharedPtr>>>(
        "itemEntities");
    auto movableEntities = StaticStorage::getInstance().getEntry<std::vector<std::vector<IMovableEntitySharedPtr>>>(
        "movableEntities");

    Vector2<int> playerCoord = StaticStorage::getInstance().getEntry<IMovableEntity>("player")->getPosition();

    auto fullPicture = std::make_shared<std::vector<std::vector<char>>>(staticEntities->size());

    for (uint64_t row = 0; row < staticEntities->size(); row++) {
        for (uint64_t cell = 0; cell < staticEntities->at(row).size(); cell++) {
            char symbol {' '};

            if (staticEntities->at(row).at(cell) != nullptr) {
                symbol = staticEntities->at(row).at(cell)->getSymbol();
            }

            if (itemEntities->at(row).at(cell) != nullptr) {
                symbol = itemEntities->at(row).at(cell)->getSymbol();
            }

            if (movableEntities->at(row).at(cell) != nullptr) {
                symbol = movableEntities->at(row).at(cell)->getSymbol();
            }

            fullPicture->at(row).push_back(symbol);
        }
    }

    fullPicture->at(static_cast<uint64_t>(playerCoord.y)).at(static_cast<uint64_t>(playerCoord.x)) = '@';

    auto camera = StaticStorage::getInstance().getEntry<Camera>("camera");
    auto curses = StaticStorage::getInstance().getEntry<NCurses>("curses");

    auto clippedPicture = camera->getPicture(curses->getSizeOfTerminal() - Vector2<int>(ONE), playerCoord, fullPicture);

    curses->clearWindow(windowName);

    for (const auto &_row : clippedPicture) {
        for (const auto &_cell : _row) {
            curses->outputChar(windowName, _cell);
        }
    }
}

void RenderSystem::renderLeaderboard(const std::string &windowName) {
    auto curses = StaticStorage::getInstance().getEntry<NCurses>("curses");
    auto leaderboard = StaticStorage::getInstance().getEntry<std::vector<Statistics>>("leaderboard");

    curses->clearWindow(windowName);

    if (leaderboard->empty()) {
        curses->outputStringInCenter(windowName, "Leaderboard is empty!", -1, 0);
        curses->outputStringInCenter(windowName, "Press ENTER to show main menu", 1, 0);
    } else {
        int heightOfRenderablePartOfLeaderboard {};

        if (leaderboard->size() >= 10) {
            heightOfRenderablePartOfLeaderboard = 10;
        } else {
            heightOfRenderablePartOfLeaderboard = static_cast<int>(leaderboard->size());
        }

        int dy = -((heightOfRenderablePartOfLeaderboard + 10) / 2);

        curses->switchColorOn(windowName, ColorPairs::GREEN_ON_BLACK);
        curses->outputStringInCenter(windowName, "LEADERBOARD (TOP 10 PLAYERS):", dy, 0);
        curses->switchColorOff(windowName, ColorPairs::GREEN_ON_BLACK);

        Vector2<int> sizeOfTerminal = curses->getSizeOfTerminal();

        dy += 2;
        int dxForNumber = -23,
            dxForNickname = -18,
            dxForKillingScore = 7,
            dxForNumberOfActions = 17;

        auto isLeaderboardSortedInDescendingOrder = StaticStorage::getInstance().getEntry<bool>(
            "isLeaderboardSortedInDescendingOrder");
        auto isLeaderboardSortedByKillingScore = StaticStorage::getInstance().getEntry<bool>(
            "isLeaderboardSortedByKillingScore");

        char sortingOrderSymbol = *isLeaderboardSortedInDescendingOrder ? 'D' : 'A';
        int dxForSortingOrderSymbol = *isLeaderboardSortedByKillingScore ? 13 : 25;

        curses->moveCarriage(windowName,
                             Vector2<int>(sizeOfTerminal.y / 2 + dy, sizeOfTerminal.x / 2 + dxForSortingOrderSymbol));
        curses->outputChar(windowName, sortingOrderSymbol);

        curses->moveCarriage(windowName,
                             Vector2<int>(sizeOfTerminal.y / 2 + dy, sizeOfTerminal.x / 2 + dxForNumber));
        curses->outputString(windowName, "N");

        curses->moveCarriage(windowName,
                             Vector2<int>(sizeOfTerminal.y / 2 + dy, sizeOfTerminal.x / 2 + dxForNickname));
        curses->outputString(windowName, "NICKNAME");

        curses->moveCarriage(windowName,
                             Vector2<int>(sizeOfTerminal.y / 2 + dy, sizeOfTerminal.x / 2 + dxForKillingScore));
        curses->outputString(windowName, "SCORE");

        curses->moveCarriage(windowName,
                             Vector2<int>(sizeOfTerminal.y / 2 + dy, sizeOfTerminal.x / 2 + dxForNumberOfActions));
        curses->outputString(windowName, "ACTIONS");

        dy += 2;
        for (int i = 0; i < heightOfRenderablePartOfLeaderboard; i++, dy++) {
            std::string buffer {};

            if (i < 9) {
                buffer = "0" + std::to_string(i + 1);
            } else {
                buffer = std::to_string(i + 1);
            }

            curses->moveCarriage(windowName,
                                 Vector2<int>(sizeOfTerminal.y / 2 + dy, sizeOfTerminal.x / 2 + dxForNumber));
            curses->outputString(windowName, buffer);

            curses->moveCarriage(windowName,
                                 Vector2<int>(sizeOfTerminal.y / 2 + dy, sizeOfTerminal.x / 2 + dxForNickname));
            curses->outputString(windowName, leaderboard->at(static_cast<uint64_t>(i)).nickname);

            curses->moveCarriage(windowName,
                                 Vector2<int>(sizeOfTerminal.y / 2 + dy, sizeOfTerminal.x / 2 + dxForKillingScore));
            curses->outputString(windowName, std::to_string(leaderboard->at(static_cast<uint64_t>(i)).killingScore));

            curses->moveCarriage(windowName,
                                 Vector2<int>(sizeOfTerminal.y / 2 + dy, sizeOfTerminal.x / 2 + dxForNumberOfActions));
            curses->outputString(windowName, std::to_string(leaderboard->at(static_cast<uint64_t>(i)).numberOfActions));
        }

        curses->switchColorOn(windowName, ColorPairs::GREEN_ON_BLACK);

        dy += 3;
        curses->outputStringInCenter(windowName, "Press LEFT to sort leaderboard by KILLING SCORE", dy, 0);

        dy++;
        curses->outputStringInCenter(windowName, "Press RIGHT to sort leaderboard by NUMBER OF ACTIONS", dy, 0);

        dy++;
        curses->outputStringInCenter(windowName, "Press the same key again to change sorting order", dy, 0);

        dy++;
        curses->outputStringInCenter(windowName, R"(D means "descending order", A means "ascending order")", dy, 0);

        dy++;
        curses->outputStringInCenter(windowName, "Press ENTER to show main menu", dy, 0);

        curses->switchColorOff(windowName, ColorPairs::GREEN_ON_BLACK);
    }
}

void RenderSystem::renderExitLogo(const std::string &windowName) {
    auto curses = StaticStorage::getInstance().getEntry<NCurses>("curses");
    auto exitLogo = StaticStorage::getInstance().getEntry<std::vector<std::string>>("exitLogo");

    curses->clearWindow(windowName);

    for (uint8_t iter = 0; iter < exitLogo->size(); iter++) {
        if (iter < exitLogo->size() - 1) {
            curses->switchColorOn(windowName, ColorPairs::RED_ON_BLACK);
        }

        curses->outputStringInCenter(windowName, exitLogo->at(iter),
                                     static_cast<int>(iter) - static_cast<int>(exitLogo->size()) / 2, 0);

        if (iter < exitLogo->size() - 1) {
            curses->switchColorOff(windowName, ColorPairs::RED_ON_BLACK);
        }
    }
}
