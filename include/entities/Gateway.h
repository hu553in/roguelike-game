/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ENTITIES_GATEWAY_H_
#define INCLUDE_ENTITIES_GATEWAY_H_


#include <entities/IStaticEntity.h>

class Gateway : public IStaticEntity {
 public:
    explicit Gateway(Vector2<int> newPosition);

    ~Gateway() override;

    IStaticEntitySharedPtr clone() const override;
};


#endif  // INCLUDE_ENTITIES_GATEWAY_H_
