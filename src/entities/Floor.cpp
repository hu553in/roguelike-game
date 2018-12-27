/* Copyright (C) 2018 hu553in */

#include <entities/Floor.h>

Floor::Floor(Vector2<int> newPosition) {
    setStaticEntityType(typeid(Floor));
    setPosition(newPosition);
    setSymbol('.');
    setPassability(true);
    setAbilityToBeUnderHigherLevelEntity(true);
}

Floor::~Floor() = default;

IStaticEntitySharedPtr Floor::clone() const {
    return std::make_shared<Floor>(Floor(position));
}
