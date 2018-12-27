/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_STATICSTORAGE_H_
#define INCLUDE_STATICSTORAGE_H_


#include <unordered_map>
#include <memory>
#include <string>
#include <typeinfo>

#include <Exceptions.h>

class StaticStorage;

class StaticStorageDestroyer {
 private:
    StaticStorage *instance = nullptr;

 public:
    ~StaticStorageDestroyer();

    void initialize(StaticStorage *instanceToDestroy);
};

class StaticStorage {
    friend class StaticStorageDestroyer;

 private:
    std::unordered_map<std::string, std::shared_ptr<void>> storage;
    static StaticStorage *instance;
    static StaticStorageDestroyer destroyer;

    StaticStorage() = default;

    ~StaticStorage() = default;

 public:
    StaticStorage(const StaticStorage &) = delete;

    StaticStorage &operator=(StaticStorage &) = delete;

    static StaticStorage &getInstance();

    template<class T>
    void registerEntry(std::shared_ptr<T> objectPtr) {
        const std::type_info *typeId = &typeid(T);

        registerEntry(typeId->name(), objectPtr);
    }

    template<class T>
    void registerEntry(const std::type_info *typeId, std::shared_ptr<T> objectPtr) {
        if (!typeId) {
            throw Exceptions::StorageExceptions::InvalidTypeIDException();
        }

        registerEntry(typeId->name(), objectPtr);
    }

    template<class T>
    void registerEntry(const std::string &id, std::shared_ptr<T> objectPtr) {
        auto iterator = storage.find(id);

        if (iterator != storage.end()) {
            throw Exceptions::StorageExceptions::EntryAlreadyExistsException();
        }

        storage[id] = objectPtr;
    }

    template<class T>
    std::shared_ptr<T> getEntry() const {
        const std::type_info *typeId = &typeid(T);

        return getEntry<T>(typeId->name());
    }

    template<class T>
    std::shared_ptr<T> getEntry(const std::type_info *typeId) const {
        if (!typeId) {
            throw Exceptions::StorageExceptions::InvalidTypeIDException();
        }

        return getEntry<T>(typeId->name());
    }

    template<class T>
    std::shared_ptr<T> getEntry(const std::string &id) const {
        auto iterator = storage.find(id);

        if (iterator != storage.end()) {
            return std::static_pointer_cast<T>(iterator->second);
        }

        throw Exceptions::StorageExceptions::EntryNotFoundException();
    }

    void removeEntry(const std::string &id);

    bool containsEntry(const std::string &id);

    void clear();
};


#endif  // INCLUDE_STATICSTORAGE_H_
