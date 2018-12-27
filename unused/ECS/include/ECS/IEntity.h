/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ECS_IENTITY_H_
#define INCLUDE_ECS_IENTITY_H_


#include <cstdint>
#include <memory>

#include "ComponentManager.h"

namespace ECS {
    class IEntity {
        friend class EntityManager;

    private:
        std::shared_ptr<ComponentManager> componentManager;

    protected:
        uint64_t entityId {};

    public:
        virtual ~IEntity() = default;

        template <class T>
        std::shared_ptr<T> getComponent() const {
            return componentManager->getComponent<T>(entityId);
        }

        template<class T>
        bool hasComponent() const {
            return componentManager->getComponent<T>(entityId) != nullptr;
        }

        template <class T, class ...Args>
        std::shared_ptr<T> addComponent(Args &&... args) {
            return componentManager->addComponent<T>(entityId, std::forward<Args>(args)...);
        }

        template<class T>
        void removeComponent() {
            componentManager->destroyComponent<T>(entityId);
        }

        void removeAllComponents() {
            componentManager->destroyAllComponentsByOwnerId(entityId);
        }

        inline bool operator==(const IEntity &other) const {
            return entityId == other.entityId;
        }

        inline bool operator!=(const IEntity &other) const {
            return entityId != other.entityId;
        }

        inline bool operator==(const std::shared_ptr<IEntity> &other) const {
            return entityId == other->entityId;
        }

        inline bool operator!=(const std::shared_ptr<IEntity> &other) const {
            return entityId != other->entityId;
        }

        uint64_t getEntityId() const {
            return entityId;
        }

        virtual void onCreation() = 0;
    };
}


#endif  // INCLUDE_ECS_IENTITY_H_
