/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ENTITIES_ISTATICENTITY_H_
#define INCLUDE_ENTITIES_ISTATICENTITY_H_


#include <memory>
#include <string>
#include <typeindex>

#include <entities/IEntity.h>

class IStaticEntity : public IEntity {
 protected:
    std::shared_ptr<std::type_index> staticEntityType {};
    bool isPassable {}, canBeUnderHigherLevelEntity {};

 public:
    ~IStaticEntity() override = default;

    std::type_index getStaticEntityType() const {
        return *staticEntityType;
    }

    void setStaticEntityType(const std::type_index &newStaticEntityType) {
        staticEntityType = std::make_shared<std::type_index>(newStaticEntityType);
    }

    void setPassability(const bool &value) {
        isPassable = value;
    }

    void setAbilityToBeUnderHigherLevelEntity(const bool &value) {
        canBeUnderHigherLevelEntity = value;
    }

    virtual std::shared_ptr<IStaticEntity> clone() const = 0;
};

using IStaticEntitySharedPtr = std::shared_ptr<IStaticEntity>;


#endif  // INCLUDE_ENTITIES_ISTATICENTITY_H_
