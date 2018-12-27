/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_SYSTEMS_FILEIOSYSTEM_H_
#define INCLUDE_SYSTEMS_FILEIOSYSTEM_H_


#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <utility>

#include <entities/IItemEntity.h>
#include <entities/IMovableEntity.h>
#include <entities/IStaticEntity.h>

#include <Vector2.h>

class FileIOSystem {
 private:
    void inputStaticEntities(const std::string &levelName);

    void inputItemEntities(const std::string &levelName);

    void inputMovableEntities(const std::string &levelName);

 public:
    FileIOSystem();

    ~FileIOSystem();

    void inputMap(const std::string &levelName);

    void inputStartLogo();

    void inputExitLogo();

    void inputLeaderboard();

    void outputNewRecordToLeaderboard();

    void outputLeaderboard();
};


#endif  // INCLUDE_SYSTEMS_FILEIOSYSTEM_H_
