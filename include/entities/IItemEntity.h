/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ENTITIES_IITEMENTITY_H_
#define INCLUDE_ENTITIES_IITEMENTITY_H_


#include <memory>
#include <string>
#include <typeindex>

#include <entities/IEntity.h>

#include <Attributes.h>

class IItemEntity : public IEntity {
 protected:
    std::shared_ptr<std::type_index> itemEntityType {};
    std::string itemEntityKind {};
    Attributes attributes {};

 public:
    ~IItemEntity() override = default;

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

    std::string getItemEntityKind() const {
        return itemEntityKind;
    }

    void setItemEntityKind(const std::string &newItemEntityKind) {
        itemEntityKind = newItemEntityKind;
    }

    std::type_index getItemEntityType() const {
        return *itemEntityType;
    }

    void setItemEntityType(const std::type_index &newItemEntityType) {
        itemEntityType = std::make_shared<std::type_index>(newItemEntityType);
    }

    virtual std::shared_ptr<IItemEntity> clone() const = 0;
};

using IItemEntitySharedPtr = std::shared_ptr<IItemEntity>;


#endif  // INCLUDE_ENTITIES_IITEMENTITY_H_
