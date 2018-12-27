/* Copyright (C) 2018 hu553in */

#include "../../include/ECS/ComponentManager.h"

ECS::ComponentManager::ComponentManager() = default;

ECS::ComponentManager::~ComponentManager() = default;

void ECS::ComponentManager::destroyAllComponentsByOwnerId(uint64_t entityId) {
    for (auto iterator : container) {
        if (iterator.first.first == entityId) {
            container.erase(iterator.first);
        }
    }
}

void ECS::ComponentManager::destroyAllComponents() {
    container.clear();
}
