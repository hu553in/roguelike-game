/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ENTITIES_IENTITY_H_
#define INCLUDE_ENTITIES_IENTITY_H_


#include <memory>

#include <Vector2.h>

class IEntity {
 protected:
    Vector2<int> position {};
    char symbol {};

 public:
    virtual ~IEntity() = default;

    Vector2<int> getPosition() const {
        return position;
    }

    void setPosition(Vector2<int> newPosition) {
        position = newPosition;
    }

    char getSymbol() {
        return symbol;
    }

    void setSymbol(const char &newSymbol) {
        symbol = newSymbol;
    }
};

using IEntitySharedPtr = std::shared_ptr<IEntity>;


#endif  // INCLUDE_ENTITIES_IENTITY_H_
