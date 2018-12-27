/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ECS_ICOMPONENT_H_
#define INCLUDE_ECS_ICOMPONENT_H_


#include <cstdint>

namespace ECS {
    class IComponent {
        friend class ComponentManager;

     private:
        uint64_t componentId {};
        uint64_t ownerId {};

     public:
        virtual ~IComponent() = default;

        uint64_t getComponentId() const {
            return componentId;
        }

        uint64_t getOwnerId() const {
            return ownerId;
        }

        virtual void onCreation() = 0;
    };
}


#endif  // INCLUDE_ECS_ICOMPONENT_H_
