/* Copyright (C) 2018 hu553in */

#include <vector>

#include <entities/Chest.h>

Chest::Chest(Vector2<int> newPosition) {
    setStaticEntityType(typeid(Chest));
    setPosition(newPosition);
    setSymbol('X');
    setPassability(false);
    setAbilityToBeUnderHigherLevelEntity(false);
}

Chest::~Chest() = default;

IStaticEntitySharedPtr Chest::clone() const {
    return std::make_shared<Chest>(Chest(position));
}

void Chest::putItem(IItemEntitySharedPtr itemEntity) {
    container.emplace_back(itemEntity);
}

std::vector<IItemEntitySharedPtr> Chest::getAllStoredItems() {
    return container;
}
