/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ENTITIES_COIN_H_
#define INCLUDE_ENTITIES_COIN_H_


#include <entities/IItemEntity.h>

class Coin : public IItemEntity {
 public:
    Coin(Vector2<int> newPosition, Attributes newAttributes);

    ~Coin() override;

    IItemEntitySharedPtr clone() const override;
};


#endif  // INCLUDE_ENTITIES_COIN_H_
