bool Game::checkPossibilityOfMoveAndPrepareForIt(Coord coord, bool *isLevelSuccessfullyFinished,
                                                 bool *gameplayLooping, int *remainingNumberOfMoves,
                                                 const int *numberOfMovesGivenForEachCoin, Map *map) {
    bool isTargetCellNotWall = true;

    switch (map->getFieldByCoords(coord)) {
        case '#':
            isTargetCellNotWall = false;
            break;

        case '$':
            *remainingNumberOfMoves += *numberOfMovesGivenForEachCoin;
            map->setFieldByCoords(coord, '.');
            break;

        case '>':
            *gameplayLooping = false;
            *isLevelSuccessfullyFinished = true;
            break;

        default:
            break;
    }

    return isTargetCellNotWall;
}

void Game::startMenuLoop(bool *mainLooping, int *numberOfMovesGivenForEachCoin, size_t *level, Map *map,
                         bool *automaticallyGoToNextLevel, NCurses *mainWindow, Coord *startCoord) {
    bool menuLooping = true;
    const std::vector<std::string> PATHS_TO_MAPS {"resources/maps/map_01.txt",
                                                  "resources/maps/map_02.txt",
                                                  "resources/maps/map_03.txt",
                                                  "resources/maps/map_04.txt",
                                                  "resources/maps/map_05.txt"};
    size_t numberOfLevels = PATHS_TO_MAPS.size();

    std::vector<std::string> levelNames;

    for (size_t i = 0; i < PATHS_TO_MAPS.size(); i++) {
        levelNames.push_back("Level " + std::to_string(i + 1));
    }

    Menu menu(numberOfLevels, levelNames);

    if (!*automaticallyGoToNextLevel || *level == numberOfLevels - 1) {
        while (menuLooping) {
            menuLooping = false;

            mainWindow->clearScreen();
            menu.render(mainWindow);

            bool selectActionLooping = true;

            while (selectActionLooping) {
                switch (mainWindow->getChar()) {
                    case 'd':
                        if (menu.getHighlightPosition() < menu.getNumberOfLevels() - 1) {
                            menu.setHighlightPosition(menu.getHighlightPosition() + 1);
                        } else {
                            menu.setHighlightPosition(0);
                        }
                        break;

                    case 'u':
                        if (menu.getHighlightPosition() > 0) {
                            menu.setHighlightPosition(menu.getHighlightPosition() - 1);
                        } else {
                            menu.setHighlightPosition(menu.getNumberOfLevels() - 1);
                        }
                        break;

                    case 10:
                        *level = menu.getHighlightPosition();
                        selectActionLooping = false;
                        break;

                    case '\b':
                        *mainLooping = false;
                        return;

                    default:
                        break;
                }

                if (selectActionLooping) {
                    mainWindow->clearScreen();
                    menu.render(mainWindow);
                }
            }

            if (!*mainLooping) {
                return;
            }

            try {
                map->load(&menuLooping, PATHS_TO_MAPS[*level], automaticallyGoToNextLevel);
                *startCoord = map->getStartCoordOfCharacter();
            } catch (Exceptions::FileCantBeOpenException &fileCantBeOpenException) {
                throw Exceptions::FileCantBeOpenException();
            } catch (Exceptions::CorruptedFileException &corruptedFileException) {
                throw Exceptions::CorruptedFileException();
            }
        }

    } else {
        while (menuLooping) {
            menuLooping = false;
            (*level)++;

            try {
                map->load(&menuLooping, PATHS_TO_MAPS[*level], automaticallyGoToNextLevel);
                *startCoord = map->getStartCoordOfCharacter();
            } catch (Exceptions::FileCantBeOpenException &fileCantBeOpenException) {
                throw Exceptions::FileCantBeOpenException();
            } catch (Exceptions::CorruptedFileException &corruptedFileException) {
                throw Exceptions::CorruptedFileException();
            }
        }
    }

    *numberOfMovesGivenForEachCoin = getNumberOfMovesGivenForEachCoin(mainWindow);
}

int Game::getNumberOfMovesGivenForEachCoin(NCurses *mainWindow) {
    int64_t numberOfMoves = 0;
    int numberOfSymbols = 3;

    while (numberOfMoves == 0) {
        Coord offset {-2, 0};

        showMessage(mainWindow,
                    "Input the number of moves that will be given for picking up a coin (1..999):", offset.y, false);

        Size sizeBuffer = mainWindow->getSizeOfWorkspace();
        Coord coord {static_cast<int>(sizeBuffer.y / 2), static_cast<int>(sizeBuffer.x / 2 - numberOfSymbols / 2)};
        char *buffer = mainWindow->getCharArray(numberOfSymbols, false, coord);

        numberOfMoves = std::strtol(buffer, nullptr, 10);
    }

    return static_cast<int>(numberOfMoves);
}

bool Game::startGameplayLoop(Map *map, int *numberOfMovesGivenForEachCoin, int *numberOfMoves,
                             Character *mainCharacter, size_t *level, const int *STARTER_REMAINING_NUMBER_OF_MOVES,
                             NCurses *gameplayWindow, NCurses *statisticsWindow) {
    bool gameplayLooping = true;
    bool isLevelSuccessfullyFinished = false;
    int remainingNumberOfMoves = *STARTER_REMAINING_NUMBER_OF_MOVES;

    while (gameplayLooping) {
        Coord bufferForCoord = mainCharacter->getCoord();
        Coord mainCharacterCoord {bufferForCoord.y, bufferForCoord.x};
        char direction = gameplayWindow->getChar();

        switch (direction) {
            case 'd':
                mainCharacterCoord.y++;
                break;

            case 'u':
                mainCharacterCoord.y--;
                break;

            case 'l':
                mainCharacterCoord.x--;
                break;

            case 'r':
                mainCharacterCoord.x++;
                break;

            case 'e':
                gameplayLooping = false;
                break;

            default:
                continue;
        }

        if (gameplayLooping) {
            if (checkPossibilityOfMoveAndPrepareForIt(mainCharacterCoord, &isLevelSuccessfullyFinished,
                    &gameplayLooping, &remainingNumberOfMoves, numberOfMovesGivenForEachCoin, map)) {
                remainingNumberOfMoves--;
                (*numberOfMoves)++;
                mainCharacter->move(direction);
            }
        }

        if (remainingNumberOfMoves == 0) {
            gameplayLooping = false;
        } else {
            render(map, mainCharacter, remainingNumberOfMoves, level, gameplayWindow, statisticsWindow);
        }
    }

    return isLevelSuccessfullyFinished;
}

void Game::render(Map *map, Character *mainCharacter, int remainingNumberOfMoves, const size_t *level,
                  NCurses *gameplayWindow, NCurses *statisticsWindow) {
    Size sizeOfWorkspace = gameplayWindow->getSizeOfWorkspace();
    Size sizeOfMap = map->getSizeOfMap();
    Coord offset {static_cast<int>(sizeOfWorkspace.y / 2 - sizeOfMap.y / 2),
                  static_cast<int>(sizeOfWorkspace.x / 2 - sizeOfMap.x / 2)};

    map->render(gameplayWindow, offset);
    mainCharacter->render(gameplayWindow, offset);

    gameplayWindow->refreshScreen();

    statisticsWindow->clearScreen();
    statisticsWindow->drawBox();

    int offsetY = 0;
    statisticsWindow->renderStringInCenter("Level: " + std::to_string(*level + 1), offsetY);

    offsetY = 1;
    statisticsWindow->renderStringInCenter("Remaining number of moves: " + std::to_string(remainingNumberOfMoves),
            offsetY);

    statisticsWindow->refreshScreen();
}

void Game::updateAndShowLeaderboard(size_t level, const int *numberOfMoves, NCurses *mainWindow) {
    const std::vector<std::string> PATHS_TO_TABLES {
            "resources/leaderboards/leaderboard_01.txt",
            "resources/leaderboards/leaderboard_02.txt",
            "resources/leaderboards/leaderboard_03.txt",
            "resources/leaderboards/leaderboard_04.txt",
            "resources/leaderboards/leaderboard_05.txt"
    };

    char *newNickname;
    int offsetY = -2;
    showMessage(mainWindow, "Input your nickname (nickname longer than 20 chars will be shortened):", offsetY, false);

    int numberOfSymbols = 20;

    Size sizeOfWorkspace = mainWindow->getSizeOfWorkspace();
    Coord coordForMovingCarriage = {static_cast<int>(sizeOfWorkspace.y / 2),
                                    static_cast<int>(sizeOfWorkspace.x / 2 - numberOfSymbols / 2)};

    newNickname = mainWindow->getCharArray(numberOfSymbols, true, coordForMovingCarriage);

    Leaderboard leaderboard;

    try {
        leaderboard.update(PATHS_TO_TABLES[level], newNickname, *numberOfMoves);
    } catch (Exceptions::FileCantBeOpenException &fileCantBeOpenException) {
        showMessage(mainWindow, "Leaderboard file can't be opened!", 0);
        return;
    } catch (Exceptions::CorruptedFileException &corruptedFileException) {
        showMessage(mainWindow, "Leaderboard file is corrupted!", 0);
        return;
    }

    leaderboard.render(mainWindow, &level);
}

void Game::showMessage(NCurses *mainWindow, const std::string &messageText, int offsetY,
                       bool waitAfterMessage) {
    mainWindow->clearScreen();
    mainWindow->renderStringInCenter(messageText, offsetY);
    mainWindow->refreshScreen();

    if (waitAfterMessage) {
        while (mainWindow->getKeyCode() != 10) {}
    }
}

Game::Game() = default;

void Game::startMainLoop() {
    bool mainLooping = true;
    bool isPreviousGameWon = false;
    bool automaticallyGoToNextLevel;
    size_t level {};
    const int STARTER_REMAINING_NUMBER_OF_MOVES = 150;

    NCurses mainWindow(0, 0, 0, 0);

    while (mainLooping) {
        int numberOfMovesGivenForEachCoin;
        int numberOfMoves = 0;

        Size sizeOfWorkspace = mainWindow.getSizeOfTerminal();
        Size margins = {6, 4};

        sizeOfWorkspace = sizeOfWorkspace - margins;

        Map map(sizeOfWorkspace);

        Coord startCoord {};

        try {
            automaticallyGoToNextLevel = isPreviousGameWon;
            startMenuLoop(&mainLooping, &numberOfMovesGivenForEachCoin, &level,
                          &map, &automaticallyGoToNextLevel, &mainWindow, &startCoord);
        } catch (Exceptions::FileCantBeOpenException &fileCantBeOpenException) {
            showMessage(&mainWindow, "Map file can't be opened!", 0);
            continue;
        } catch (Exceptions::CorruptedFileException &corruptedFileException) {
            showMessage(&mainWindow, "Map file is corrupted!", 0);
            continue;
        }

        if (mainLooping) {
            Character mainCharacter(startCoord, '@');

            mainWindow.clearScreen();
            mainWindow.refreshScreen();

            Size sizeOfTerminal {};
            sizeOfTerminal = mainWindow.getSizeOfTerminal();

            NCurses statisticsWindow(0, static_cast<int>(sizeOfTerminal.y - 4), 2, 2);
            NCurses gameplayWindow(4, 0, 2, 2);

            if (mainLooping) {
                render(&map, &mainCharacter, STARTER_REMAINING_NUMBER_OF_MOVES, &level, &gameplayWindow,
                       &statisticsWindow);

                isPreviousGameWon = startGameplayLoop(&map, &numberOfMovesGivenForEachCoin, &numberOfMoves,
                        &mainCharacter, &level, &STARTER_REMAINING_NUMBER_OF_MOVES, &gameplayWindow, &statisticsWindow);

                if (isPreviousGameWon) {
                    updateAndShowLeaderboard(level, &numberOfMoves, &mainWindow);
                } else {
                    showMessage(&mainWindow, "It's a fail, but don't worry. See you soon!", 0);
                }
            }
        }
    }

    showMessage(&mainWindow, "It's the end of main loop. Bye! <3", 0);
}

Game::~Game() = default;