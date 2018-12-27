/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ENTITIES_WALL_H_
#define INCLUDE_ENTITIES_WALL_H_


#include <entities/IStaticEntity.h>

#include <Attributes.h>

class Wall : public IStaticEntity {
 public:
    explicit Wall(Vector2<int> newPosition);

    ~Wall() override;

    IStaticEntitySharedPtr clone() const override;
};


#endif  // INCLUDE_ENTITIES_WALL_H_
