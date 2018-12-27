/* Copyright (C) 2018 hu553in */

#include "../../include/ECS/EntityManager.h"

ECS::EntityManager::EntityManager(const std::shared_ptr<ComponentManager> &componentManager) {
    this->componentManager = componentManager;
}

ECS::EntityManager::~EntityManager() = default;

void ECS::EntityManager::markEntityForDestruction(uint64_t entityId) {
    entitiesToDestroy.emplace(entityId);
}

void ECS::EntityManager::destroyAllEntities() {
    entitiesToDestroy.clear();
    container.clear();
}

void ECS::EntityManager::destroyMarkedEntities() {
    for (auto iterator : entitiesToDestroy) {
        auto entity = container[iterator];

        if (!entity) {
            continue;
        }

        entity->removeAllComponents();
        container.erase(iterator);
    }

    entitiesToDestroy.clear();
}

std::shared_ptr<ECS::IEntity> ECS::EntityManager::getEntity(uint64_t entityId) {
    return container[entityId];
}
