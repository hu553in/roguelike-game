/* Copyright (C) 2018 hu553in */

#include <string>
#include <memory>
#include <sstream>
#include <vector>
#include <iostream>

#include <systems/FileIOSystem.h>

#include <entities/Coin.h>
#include <entities/Gateway.h>
#include <entities/Wall.h>
#include <entities/Floor.h>
#include <entities/Player.h>

#include <Exceptions.h>
#include <Statistics.h>
#include <StaticStorage.h>
#include <PrototypeTable.h>

void FileIOSystem::inputItemEntities(const std::string &levelName) {
    auto staticEntitiesVector = StaticStorage::getInstance().getEntry<std::vector<std::vector<IStaticEntitySharedPtr>>>(
        "staticEntities");

    auto itemEntitiesVector = std::make_shared<std::vector<std::vector<IItemEntitySharedPtr>>>();

    itemEntitiesVector->resize(staticEntitiesVector->size());

    for (uint64_t i = 0; i < itemEntitiesVector->size(); i++) {
        itemEntitiesVector->at(i).resize(staticEntitiesVector->at(i).size());
    }

    std::ifstream itemEntitiesFile("resources/maps/" + levelName + "/ItemEntities.txt");

    if (!itemEntitiesFile.is_open()) {
        throw Exceptions::FileExceptions::FileCantBeOpenException();
    } else {
        auto prototypeTable = StaticStorage::getInstance().getEntry<PrototypeTable>("prototypeTable");

        while (!itemEntitiesFile.eof()) {
            std::string buffer {};
            std::getline(itemEntitiesFile, buffer);

            char entitySymbol;
            int y, x;

            std::stringstream stringstream(buffer);
            stringstream >> entitySymbol >> y >> x;

            IItemEntitySharedPtr itemEntityBuffer {};

            try {
                itemEntityBuffer = prototypeTable->getItemEntityPrototype(entitySymbol);
                itemEntityBuffer->setPosition(Vector2<int>(y, x));
            } catch (std::out_of_range &out_of_range) {
                itemEntityBuffer = nullptr;
            }

            itemEntitiesVector->at(static_cast<uint32_t>(y)).at(static_cast<uint32_t>(x)) = itemEntityBuffer;
        }

        StaticStorage::getInstance().registerEntry<std::vector<std::vector<IItemEntitySharedPtr>>>(
            "itemEntities", itemEntitiesVector);

        itemEntitiesFile.close();
    }
}

void FileIOSystem::inputMovableEntities(const std::string &levelName) {
    auto staticEntitiesVector = StaticStorage::getInstance().getEntry<std::vector<std::vector<IStaticEntitySharedPtr>>>(
        "staticEntities");

    auto movableEntitiesVector = std::make_shared<std::vector<std::vector<IMovableEntitySharedPtr>>>();

    movableEntitiesVector->resize(staticEntitiesVector->size());

    for (uint64_t i = 0; i < movableEntitiesVector->size(); i++) {
        movableEntitiesVector->at(i).resize(staticEntitiesVector->at(i).size());
    }

    std::ifstream movableEntitiesFile("resources/maps/" + levelName + "/MovableEntities.txt");

    if (!movableEntitiesFile.is_open()) {
        throw Exceptions::FileExceptions::FileCantBeOpenException();
    } else {
        auto prototypeTablePtr = StaticStorage::getInstance().getEntry<PrototypeTable>("prototypeTable");

        while (!movableEntitiesFile.eof()) {
            std::string buffer {};
            std::getline(movableEntitiesFile, buffer);

            char whatEntity;
            int y, x;

            std::stringstream stringstream(buffer);
            stringstream >> whatEntity >> y >> x;

            IMovableEntitySharedPtr movableEntityBuffer {};

            try {
                movableEntityBuffer = prototypeTablePtr->getMovableEntityPrototype(whatEntity);
                movableEntityBuffer->setPosition(Vector2<int>(y, x));
            } catch (std::out_of_range &out_of_range) {
                movableEntityBuffer = nullptr;
            }

            if (whatEntity == '@') {
                StaticStorage::getInstance().registerEntry<IMovableEntity>("player", movableEntityBuffer);
            } else {
                movableEntitiesVector->at(static_cast<uint32_t>(y)).at(static_cast<uint32_t>(x)) = movableEntityBuffer;
            }
        }

        StaticStorage::getInstance().registerEntry<std::vector<std::vector<IMovableEntitySharedPtr>>>(
            "movableEntities", movableEntitiesVector);

        movableEntitiesFile.close();
    }
}

void FileIOSystem::inputStaticEntities(const std::string &levelName) {
    auto staticEntitiesVector = std::make_shared<std::vector<std::vector<IStaticEntitySharedPtr>>>();

    std::ifstream staticEntitiesFile("resources/maps/" + levelName + "/StaticEntities.txt");

    if (!staticEntitiesFile.is_open()) {
        throw Exceptions::FileExceptions::FileCantBeOpenException();
    } else {
        int numberOfRows = 0,
            numberOfColumns = 0,
            currentRow = 0,
            currentColumn = 0;

        auto prototypeTablePtr = StaticStorage::getInstance().getEntry<PrototypeTable>("prototypeTable");

        while (staticEntitiesFile) {
            std::string buffer {};

            std::getline(staticEntitiesFile, buffer);

            std::vector<IStaticEntitySharedPtr> staticEntityBufferForOneLine;

            for (auto iterator : buffer) {
                Vector2<int> currentCoord {currentRow, currentColumn};

                IStaticEntitySharedPtr staticEntityBuffer {};

                try {
                    staticEntityBuffer = prototypeTablePtr->getStaticEntityPrototype(iterator);
                    staticEntityBuffer->setPosition(currentCoord);
                } catch (std::out_of_range &out_of_range) {
                    staticEntityBuffer = nullptr;
                }

                staticEntityBufferForOneLine.push_back(staticEntityBuffer);

                currentColumn++;
            }

            if (currentColumn > numberOfColumns) {
                numberOfColumns = currentColumn;
            }

            if (staticEntitiesFile) {
                staticEntitiesVector->push_back(staticEntityBufferForOneLine);
                currentRow++;
                currentColumn = 0;
            } else {
                currentRow--;
            }
        }

        numberOfRows = currentRow;
        auto mapSize = std::make_shared<Vector2<int>>(Vector2<int>(numberOfRows, numberOfColumns));
        StaticStorage::getInstance().registerEntry<Vector2<int>>("mapSize", mapSize);

        StaticStorage::getInstance().registerEntry<std::vector<std::vector<IStaticEntitySharedPtr>>>(
            "staticEntities", staticEntitiesVector);

        staticEntitiesFile.close();
    }
}

FileIOSystem::FileIOSystem() = default;

FileIOSystem::~FileIOSystem() = default;

void FileIOSystem::inputMap(const std::string &levelName) {
    inputStaticEntities(levelName);
    inputItemEntities(levelName);
    inputMovableEntities(levelName);
}

void FileIOSystem::inputStartLogo() {
    std::ifstream logoFile("resources/startLogo.txt");

    auto logoVector = std::make_shared<std::vector<std::string>>();

    if (logoFile.is_open()) {
        while (!logoFile.eof()) {
            std::string buffer {};
            std::getline(logoFile, buffer);
            logoVector->push_back(buffer);
        }
    } else {
        throw Exceptions::FileExceptions::FileCantBeOpenException();
    }

    StaticStorage::getInstance().registerEntry<std::vector<std::string>>("startLogo", logoVector);
}

void FileIOSystem::inputExitLogo() {
    std::ifstream logoFile("resources/exitLogo.txt");

    auto logoVector = std::make_shared<std::vector<std::string>>();

    if (logoFile.is_open()) {
        while (!logoFile.eof()) {
            std::string buffer {};
            std::getline(logoFile, buffer);
            logoVector->push_back(buffer);
        }
    } else {
        throw Exceptions::FileExceptions::FileCantBeOpenException();
    }

    StaticStorage::getInstance().registerEntry<std::vector<std::string>>("exitLogo", logoVector);
}

void FileIOSystem::inputLeaderboard() {
    std::ifstream leaderboardFile("resources/leaderboard.txt");

    auto membersVector = std::make_shared<std::vector<Statistics>>();

    if (!leaderboardFile.is_open()) {
        throw Exceptions::FileExceptions::FileCantBeOpenException();
    } else {
        leaderboardFile.get();

        while (!leaderboardFile.eof()) {
            std::string buffer {};

            std::getline(leaderboardFile, buffer);

            Statistics statistics {};

            std::stringstream stream(buffer);

            stream >> statistics.nickname >> statistics.killingScore >> statistics.numberOfActions;
            membersVector->emplace_back(statistics);
        }
    }

    StaticStorage::getInstance().registerEntry<std::vector<Statistics>>("leaderboard", membersVector);
}

void FileIOSystem::outputNewRecordToLeaderboard() {
    std::ofstream leaderboardFile;
    leaderboardFile.open("resources/leaderboard.txt", std::ios_base::app);

    auto record = StaticStorage::getInstance().getEntry<Statistics>("statistics");

    if (!leaderboardFile.is_open()) {
        throw Exceptions::FileExceptions::FileCantBeOpenException();
    } else {
        leaderboardFile << "\n" << *record;
        leaderboardFile.close();
    }
}

void FileIOSystem::outputLeaderboard() {
    std::ofstream leaderboardFile;
    leaderboardFile.open("resources/leaderboard.txt");

    auto members = StaticStorage::getInstance().getEntry<std::vector<Statistics>>("leaderboard");

    if (!leaderboardFile.is_open()) {
        throw Exceptions::FileExceptions::FileCantBeOpenException();
    } else {
        for (auto &member : *members) {
            leaderboardFile << "\n" << member;
        }

        leaderboardFile.close();
    }
}
