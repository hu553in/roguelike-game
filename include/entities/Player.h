/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ENTITIES_PLAYER_H_
#define INCLUDE_ENTITIES_PLAYER_H_


#include <string>

#include <entities/IMovableEntity.h>

class Player : public IMovableEntity {
 public:
    Player(Vector2<int> startPosition, Attributes startAttributes);

    ~Player() override;

    void move(std::string direction) override;

    IMovableEntitySharedPtr clone() const override;
};


#endif  // INCLUDE_ENTITIES_PLAYER_H_
