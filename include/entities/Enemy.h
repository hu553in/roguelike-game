/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ENTITIES_ENEMY_H_
#define INCLUDE_ENTITIES_ENEMY_H_


#include <string>

#include <entities/IMovableEntity.h>

class Enemy : public IMovableEntity {
 public:
    Enemy(Vector2<int> startPosition, Attributes startAttributes);

    ~Enemy() override;

    void move(std::string direction) override;

    IMovableEntitySharedPtr clone() const override;
};


#endif  // INCLUDE_ENTITIES_ENEMY_H_
