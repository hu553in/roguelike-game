/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ENTITIES_FLOOR_H_
#define INCLUDE_ENTITIES_FLOOR_H_


#include <entities/IStaticEntity.h>

class Floor : public IStaticEntity {
 public:
    explicit Floor(Vector2<int> newPosition);

    ~Floor() override;

    IStaticEntitySharedPtr clone() const override;
};


#endif  // INCLUDE_ENTITIES_FLOOR_H_
