/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_SYSTEMS_MOVEMENTSYSTEM_H_
#define INCLUDE_SYSTEMS_MOVEMENTSYSTEM_H_


#include <unordered_map>
#include <string>

#include <Vector2.h>

class MovementSystem {
 public:
    MovementSystem();

    ~MovementSystem();

    void move(const std::string &direction, std::shared_ptr<Vector2<int>> position) const;
};


#endif  // INCLUDE_SYSTEMS_MOVEMENTSYSTEM_H_
