/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ECS_ENTITYMANAGER_H_
#define INCLUDE_ECS_ENTITYMANAGER_H_


#include <cstdint>
#include <unordered_map>
#include <set>
#include <memory>

#include "IEntity.h"
#include "ComponentManager.h"

namespace ECS {
    class EntityManager {
        friend class SystemManager;

     private:
        std::shared_ptr<ComponentManager> componentManager;
        uint64_t currentId;

     public:
        std::unordered_map<uint64_t, std::shared_ptr<IEntity>> container {};
        std::set<uint64_t> entitiesToDestroy {};

        explicit EntityManager(const std::shared_ptr<ComponentManager> &componentManager);

        ~EntityManager();

        template <class T, class ... Args>
        uint64_t createEntity(Args &&... args) {
            auto entity = createAndGetEntity<T>(std::forward<Args>(args)...);
            return entity->getEntityId;
        }

        template<class T, class ... Args>
        std::shared_ptr<T> createAndGetEntity(Args &&... args) {
            auto entity = std::make_shared<T>(std::forward<Args>(args)...);
            entity->entityId = currentId++;
            entity->componentManager = this->componentManager;
            container[entity->entityId] = entity;
            entity->onActivation();
            return entity;
        }

        void markEntityForDestruction(uint64_t entityId);

        void destroyAllEntities();

        void destroyMarkedEntities();

        std::shared_ptr<IEntity> getEntity(uint64_t entityId);
    };
}


#endif  // INCLUDE_ECS_ENTITYMANAGER_H_
