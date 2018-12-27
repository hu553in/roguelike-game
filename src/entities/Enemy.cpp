/* Copyright (C) 2018 hu553in */

#include <string>

#include <entities/Enemy.h>

#include <systems/MovementSystem.h>

#include <StaticStorage.h>

Enemy::Enemy(Vector2<int> startPosition, Attributes startAttributes) {
    setMovableEntityType(typeid(Enemy));
    setPosition(startPosition);
    setAttributes(startAttributes);
    setSymbol('E');
}

Enemy::~Enemy() = default;

void Enemy::move(std::string direction) {
    auto positionPtr = std::make_shared<Vector2<int>>(position);
    StaticStorage::getInstance().getEntry<MovementSystem>("movementSystem")->move(direction, positionPtr);
}

IMovableEntitySharedPtr Enemy::clone() const {
    return std::make_shared<Enemy>(Enemy(position, attributes));
}
