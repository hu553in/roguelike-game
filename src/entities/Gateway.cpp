/* Copyright (C) 2018 hu553in */

#include <entities/Gateway.h>

Gateway::Gateway(Vector2<int> newPosition) {
    setStaticEntityType(typeid(Gateway));
    setPosition(newPosition);
    setSymbol('>');
    setPassability(true);
    setAbilityToBeUnderHigherLevelEntity(true);
}

Gateway::~Gateway() = default;

IStaticEntitySharedPtr Gateway::clone() const {
    return std::make_shared<Gateway>(Gateway(position));
}
