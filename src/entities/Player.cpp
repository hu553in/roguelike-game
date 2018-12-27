/* Copyright (C) 2018 hu553in */

#include <string>

#include <entities/Player.h>

#include <systems/MovementSystem.h>

#include <StaticStorage.h>

Player::Player(Vector2<int> startPosition, Attributes startAttributes) {
    setMovableEntityType(typeid(Player));
    setPosition(startPosition);
    setAttributes(startAttributes);
    setSymbol('@');
}

Player::~Player() = default;

void Player::move(std::string direction) {
    auto positionPtr = std::make_shared<Vector2<int>>(position);
    StaticStorage::getInstance().getEntry<MovementSystem>("movementSystem")->move(direction, positionPtr);
}

IMovableEntitySharedPtr Player::clone() const {
    return std::make_shared<Player>(Player(position, attributes));
}
