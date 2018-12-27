/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ECS_COMPONENTMANAGER_H_
#define INCLUDE_ECS_COMPONENTMANAGER_H_


#include <unordered_map>
#include <utility>
#include <typeindex>
#include <memory>

#include "IComponent.h"

namespace ECS {
    struct HashOfPair {
        template<typename T1, typename T2>
        uint32_t operator()(const std::pair<T1, T2> &pair) const {
            uint32_t hash1 = std::hash<T1>()(pair.first);
            uint32_t hash2 = std::hash<T2>()(pair.second);
            return hash1 ^ (hash2 << 1);
        }
    };

    class ComponentManager {
     private:
        std::unordered_map<std::pair<uint64_t, std::type_index>,
                          std::shared_ptr<IComponent>, HashOfPair> container {};
        uint64_t currentId = 0;

     public:
        ComponentManager();

        ~ComponentManager();

        template<class T, class ... Args>
        void addComponent(const uint64_t entityId, Args &&... args) {
            auto component = new T(std::forward<Args>(args)...);
            auto key = std::make_pair(entityId, std::type_index(typeid(T)));
            component->ownerId = entityId;
            component->componentId = currentId++;
            container[key] = std::shared_ptr<T>(component);
            component->onCreation();
        }

        template<class T>
        std::shared_ptr<T> getComponent(uint64_t entityId) {
            auto key = std::make_pair(entityId, std::type_index(typeid(T)));
            return std::dynamic_pointer_cast<T>(container[key]);
        }

        template<class T>
        void destroyComponent(uint64_t entityId) {
            auto key = std::make_pair(entityId, std::type_index(typeid(T)));
            container.erase(key);
        }

        void destroyAllComponentsByOwnerId(uint64_t entityId);

        void destroyAllComponents();
    };
}


#endif  // INCLUDE_ECS_COMPONENTMANAGER_H_
