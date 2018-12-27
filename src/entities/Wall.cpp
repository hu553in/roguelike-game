/* Copyright (C) 2018 hu553in */

#include <entities/Wall.h>

Wall::Wall(Vector2<int> newPosition) {
    setStaticEntityType(typeid(Wall));
    setPosition(newPosition);
    setSymbol('#');
    setPassability(false);
    setAbilityToBeUnderHigherLevelEntity(false);
}

Wall::~Wall() = default;

IStaticEntitySharedPtr Wall::clone() const {
    return std::make_shared<Wall>(position);
}
