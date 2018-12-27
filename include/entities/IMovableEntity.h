/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ENTITIES_IMOVABLEENTITY_H_
#define INCLUDE_ENTITIES_IMOVABLEENTITY_H_


#include <memory>
#include <string>
#include <typeindex>
#include <vector>
#include <unordered_map>

#include <entities/IEntity.h>
#include <entities/IItemEntity.h>

#include <Attributes.h>

class IMovableEntity : public IEntity {
 protected:
    std::shared_ptr<std::type_index> movableEntityType {};
    Attributes attributes {};
    std::unordered_map<std::type_index, IItemEntitySharedPtr> inventory {};

 public:
    ~IMovableEntity() override = default;

    uint32_t getVelocity() const {
        return attributes.velocity;
    }

    void setVelocity(uint32_t newVelocity) {
        attributes.velocity = newVelocity;
    }

    uint32_t getHealthPoints() const {
        return attributes.healthPoints;
    }

    void setHealthPoints(uint32_t newHealthPoints) {
        attributes.healthPoints = newHealthPoints;
    }

    uint32_t getAttackPower() const {
        return attributes.attackPower;
    }

    void setAttackPower(uint32_t newAttackPower) {
        attributes.attackPower = newAttackPower;
    }

    uint32_t getArmorRate() const {
        return attributes.armorRate;
    }

    void setArmorRate(uint32_t newArmorRate) {
        attributes.armorRate = newArmorRate;
    }

    void setWorth(uint32_t newWorth) {
        attributes.worth = newWorth;
    }

    uint32_t getWorth() {
        return attributes.worth;
    }

    Attributes getAttributes() const {
        return attributes;
    }

    void setAttributes(const Attributes &newAttributes) {
        attributes = newAttributes;
    }

    void putItemToInventory(const IItemEntitySharedPtr &itemObject) {
        inventory[itemObject->getItemEntityType()] = itemObject;
        attributes += itemObject->getAttributes();
    }

    IItemEntitySharedPtr getItemFromInventory(const std::type_index &itemEntityType) {
        return inventory.at(itemEntityType);
    }

    void destroyItemInInventory(const std::type_index &itemEntityType) {
        attributes -= inventory.at(itemEntityType)->getAttributes();
        inventory.erase(itemEntityType);
    }

    std::unordered_map<std::type_index, IItemEntitySharedPtr> getInventory() {
        return inventory;
    }

    std::type_index getMovableEntityType() const {
        return *movableEntityType;
    }

    void setMovableEntityType(const std::type_index &newMovableEntityType) {
        movableEntityType = std::make_shared<std::type_index>(newMovableEntityType);
    }

    virtual std::shared_ptr<IMovableEntity> clone() const = 0;

    virtual void move(std::string direction) = 0;
};

using IMovableEntitySharedPtr = std::shared_ptr<IMovableEntity>;


#endif  // INCLUDE_ENTITIES_IMOVABLEENTITY_H_
