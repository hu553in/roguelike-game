/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_PROTOTYPETABLE_H_
#define INCLUDE_PROTOTYPETABLE_H_


#include <unordered_map>
#include <string>
#include <memory>
#include <typeindex>
#include <typeinfo>

#include <entities/IStaticEntity.h>
#include <entities/IMovableEntity.h>
#include <entities/IItemEntity.h>

#include <Exceptions.h>

class PrototypeTable {
 private:
    std::unordered_map<std::string, IItemEntitySharedPtr> itemEntityPrototypeTable;
    std::unordered_map<std::string, IStaticEntitySharedPtr> staticEntityPrototypeTable;
    std::unordered_map<std::string, IMovableEntitySharedPtr> movableEntityPrototypeTable;

 public:
    PrototypeTable();

    ~PrototypeTable();

    IItemEntitySharedPtr getItemEntityPrototype(const std::string &key) const;

    IItemEntitySharedPtr getItemEntityPrototype(const char &key) const;

    IStaticEntitySharedPtr getStaticEntityPrototype(const std::string &key) const;

    IStaticEntitySharedPtr getStaticEntityPrototype(const char &key) const;

    IMovableEntitySharedPtr getMovableEntityPrototype(const std::string &key) const;

    IMovableEntitySharedPtr getMovableEntityPrototype(const char &key) const;

    void registerItemEntityPrototype(const std::string &key, IItemEntitySharedPtr prototype);

    void registerItemEntityPrototype(const char &key, IItemEntitySharedPtr prototype);

    void registerStaticEntityPrototype(const std::string &key, IStaticEntitySharedPtr prototype);

    void registerStaticEntityPrototype(const char &key, IStaticEntitySharedPtr prototype);

    void registerMovableEntityPrototype(const std::string &key, IMovableEntitySharedPtr prototype);

    void registerMovableEntityPrototype(const char &key, IMovableEntitySharedPtr prototype);

    void removeItemEntityPrototype(const std::string &key);

    void removeItemEntityPrototype(const char &key);

    void removeStaticEntityPrototype(const std::string &key);

    void removeStaticEntityPrototype(const char &key);

    void removeMovableEntityPrototype(const std::string &key);

    void removeMovableEntityPrototype(const char &key);
};

using PrototypeTablePtr = std::shared_ptr<PrototypeTable>;


#endif  // INCLUDE_PROTOTYPETABLE_H_
