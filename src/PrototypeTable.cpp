/* Copyright (C) 2018 hu553in */

#include <utility>
#include <string>

#include <PrototypeTable.h>

PrototypeTable::PrototypeTable() = default;

PrototypeTable::~PrototypeTable() = default;

IItemEntitySharedPtr PrototypeTable::getItemEntityPrototype(const std::string &key) const {
    return itemEntityPrototypeTable.at(key)->clone();
}

IItemEntitySharedPtr PrototypeTable::getItemEntityPrototype(const char &key) const {
    std::string stringBuffer(1, key);

    return getItemEntityPrototype(stringBuffer);
}

IStaticEntitySharedPtr PrototypeTable::getStaticEntityPrototype(const std::string &key) const {
    return staticEntityPrototypeTable.at(key)->clone();
}

IStaticEntitySharedPtr PrototypeTable::getStaticEntityPrototype(const char &key) const {
    std::string stringBuffer(1, key);

    return getStaticEntityPrototype(stringBuffer);
}

IMovableEntitySharedPtr PrototypeTable::getMovableEntityPrototype(const std::string &key) const {
    return movableEntityPrototypeTable.at(key)->clone();
}

IMovableEntitySharedPtr PrototypeTable::getMovableEntityPrototype(const char &key) const {
    std::string stringBuffer(1, key);

    return getMovableEntityPrototype(stringBuffer);
}

void PrototypeTable::registerItemEntityPrototype(const std::string &key, IItemEntitySharedPtr prototype) {
    itemEntityPrototypeTable[key] = std::move(prototype);
}

void PrototypeTable::registerItemEntityPrototype(const char &key, IItemEntitySharedPtr prototype) {
    std::string stringBuffer(1, key);

    registerItemEntityPrototype(stringBuffer, std::move(prototype));
}

void PrototypeTable::registerStaticEntityPrototype(const std::string &key, IStaticEntitySharedPtr prototype) {
    staticEntityPrototypeTable[key] = std::move(prototype);
}

void PrototypeTable::registerStaticEntityPrototype(const char &key, IStaticEntitySharedPtr prototype) {
    std::string stringBuffer(1, key);

    registerStaticEntityPrototype(stringBuffer, std::move(prototype));
}

void PrototypeTable::registerMovableEntityPrototype(const std::string &key, IMovableEntitySharedPtr prototype) {
    movableEntityPrototypeTable[key] = std::move(prototype);
}

void PrototypeTable::registerMovableEntityPrototype(const char &key, IMovableEntitySharedPtr prototype) {
    std::string stringBuffer(1, key);

    registerMovableEntityPrototype(stringBuffer, std::move(prototype));
}

void PrototypeTable::removeItemEntityPrototype(const std::string &key) {
    itemEntityPrototypeTable.erase(key);
}

void PrototypeTable::removeItemEntityPrototype(const char &key) {
    std::string stringBuffer(1, key);

    itemEntityPrototypeTable.erase(stringBuffer);
}

void PrototypeTable::removeStaticEntityPrototype(const std::string &key) {
    staticEntityPrototypeTable.erase(key);
}

void PrototypeTable::removeStaticEntityPrototype(const char &key) {
    std::string stringBuffer(1, key);

    staticEntityPrototypeTable.erase(stringBuffer);
}

void PrototypeTable::removeMovableEntityPrototype(const std::string &key) {
    movableEntityPrototypeTable.erase(key);
}

void PrototypeTable::removeMovableEntityPrototype(const char &key) {
    std::string stringBuffer(1, key);

    movableEntityPrototypeTable.erase(stringBuffer);
}
