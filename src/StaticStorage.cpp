/* Copyright (C) 2018 hu553in */

#include <string>

#include <StaticStorage.h>

StaticStorageDestroyer::~StaticStorageDestroyer() {
    delete instance;
}

void StaticStorageDestroyer::initialize(StaticStorage* instanceToDestroy) {
    instance = instanceToDestroy;
}

StaticStorage *StaticStorage::instance = nullptr;

StaticStorageDestroyer StaticStorage::destroyer {};

StaticStorage &StaticStorage::getInstance() {
    if (instance == nullptr) {
        instance = new StaticStorage();
        destroyer.initialize(instance);
    }

    return *instance;
}

void StaticStorage::removeEntry(const std::string &id) {
    storage.erase(id);
}

bool StaticStorage::containsEntry(const std::string &id) {
    return storage.find(id) != storage.end();
}

void StaticStorage::clear() {
    storage.clear();
}
