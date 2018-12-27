/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ENTITIES_CHEST_H_
#define INCLUDE_ENTITIES_CHEST_H_


#include <vector>

#include <entities/IStaticEntity.h>
#include <entities/IItemEntity.h>

class Chest : public IStaticEntity {
 private:
    std::vector<IItemEntitySharedPtr> container;

 public:
    explicit Chest(Vector2<int> newPosition);

    ~Chest() override;

    IStaticEntitySharedPtr clone() const override;

    void putItem(IItemEntitySharedPtr itemEntity);

    std::vector<IItemEntitySharedPtr> getAllStoredItems();
};


#endif  // INCLUDE_ENTITIES_CHEST_H_
