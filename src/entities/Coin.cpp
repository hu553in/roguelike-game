/* Copyright (C) 2018 hu553in */

#include <entities/Coin.h>

Coin::Coin(Vector2<int> newPosition, Attributes newAttributes) {
    setItemEntityType(typeid(Coin));
    setPosition(newPosition);
    setAttributes(newAttributes);
    setSymbol('$');
    setItemEntityKind("usable");
}

Coin::~Coin() = default;

IItemEntitySharedPtr Coin::clone() const {
    return std::make_shared<Coin>(Coin(position, attributes));
}
