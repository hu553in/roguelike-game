/* Copyright (C) 2018 hu553in */

#include <string>

#include <systems/MovementSystem.h>

MovementSystem::MovementSystem() = default;

MovementSystem::~MovementSystem() = default;

void MovementSystem::move(const std::string &direction, std::shared_ptr<Vector2<int>> position) const {
    Vector2<int> vectorOfMove {direction};
    *position += vectorOfMove;
}
