/* Copyright (C) 2018 hu553in */

#include <memory>

#include <facades/NCurses.h>

#include <entities/Wall.h>
#include <entities/Floor.h>
#include <entities/Gateway.h>
#include <entities/Coin.h>
#include <entities/Player.h>
#include <entities/Chest.h>
#include <entities/Enemy.h>

#include <screens/TitleScreen.h>
#include <screens/MenuScreen.h>
#include <screens/NameInputScreen.h>
#include <screens/GameScreen.h>
#include <screens/LeaderboardScreen.h>
#include <screens/ExitScreen.h>

#include <systems/MovementSystem.h>
#include <systems/RenderSystem.h>
#include <systems/FileIOSystem.h>
#include <systems/InputHandlingSystem.h>
#include <systems/LeaderboardSortingSystem.h>

#include <StaticStorage.h>
#include <PrototypeTable.h>
#include <RoutingMachine.h>
#include <Camera.h>

void fillStaticStorage() {
    auto movementSystem = std::make_shared<MovementSystem>();
    StaticStorage::getInstance().registerEntry<MovementSystem>("movementSystem", movementSystem);

    auto renderSystem = std::make_shared<RenderSystem>();
    StaticStorage::getInstance().registerEntry<RenderSystem>("renderSystem", renderSystem);

    auto inputHandlingSystem = std::make_shared<InputHandlingSystem>();
    StaticStorage::getInstance().registerEntry<InputHandlingSystem>("inputHandlingSystem", inputHandlingSystem);

    auto fileIOSystem = std::make_shared<FileIOSystem>();
    StaticStorage::getInstance().registerEntry<FileIOSystem>("fileIOSystem", fileIOSystem);

    auto leaderboardSortingSystem = std::make_shared<LeaderboardSortingSystem>();
    StaticStorage::getInstance().registerEntry<LeaderboardSortingSystem>("leaderboardSortingSystem",
                                                                         leaderboardSortingSystem);

    auto curses = std::make_shared<NCurses>();
    StaticStorage::getInstance().registerEntry<NCurses>("curses", curses);

    auto camera = std::make_shared<Camera>();
    StaticStorage::getInstance().registerEntry<Camera>("camera", camera);

    auto prototypeTable = std::make_shared<PrototypeTable>();

    prototypeTable->registerStaticEntityPrototype('#', std::make_shared<Wall>(Wall(Vector2<int>(ZERO))));
    prototypeTable->registerStaticEntityPrototype('.', std::make_shared<Floor>(Floor(Vector2<int>(ZERO))));
    prototypeTable->registerStaticEntityPrototype('>', std::make_shared<Gateway>(Gateway(Vector2<int>(ZERO))));
    prototypeTable->registerStaticEntityPrototype('X', std::make_shared<Chest>(Chest(Vector2<int>(ZERO))));

    prototypeTable->registerItemEntityPrototype('$', std::make_shared<Coin>(Coin(Vector2<int>(ZERO),
                                                Attributes {0, 0, 0, 0, 10})));

    prototypeTable->registerMovableEntityPrototype('@', std::make_shared<Player>(Player(Vector2<int>(ZERO),
                                                   Attributes {1, 100, 10, 5, 0})));
    prototypeTable->registerMovableEntityPrototype('E', std::make_shared<Enemy>(Enemy(Vector2<int>(ZERO),
                                                   Attributes {1, 50, 5, 3, 0})));

    StaticStorage::getInstance().registerEntry<PrototypeTable>("prototypeTable", prototypeTable);

    auto routingMachine = std::make_shared<RoutingMachine>();

    routingMachine->addScreen<TitleScreen>("title", TitleScreen());
    routingMachine->addScreen<MenuScreen>("menu", MenuScreen());
    routingMachine->addScreen<NameInputScreen>("nameInput", NameInputScreen());
    routingMachine->addScreen<GameScreen>("game", GameScreen());
    routingMachine->addScreen<LeaderboardScreen>("leaderboard", LeaderboardScreen());
    routingMachine->addScreen<ExitScreen>("exit", ExitScreen());

    routingMachine->setIterator("title");

    StaticStorage::getInstance().registerEntry<RoutingMachine>("routingMachine", routingMachine);
}

int main() {
    fillStaticStorage();

    auto routingMachine = StaticStorage::getInstance().getEntry<RoutingMachine>("routingMachine");

    while (routingMachine->update()) {}

    StaticStorage::getInstance().clear();

    return 0;
}
