/* Copyright (C) 2018 hu553in */

#include <string>
#include <memory>

#include <RoutingMachine.h>

RoutingMachine::RoutingMachine() = default;

RoutingMachine::~RoutingMachine() {
    screenDictionary.clear();
}

bool RoutingMachine::update() {
    std::string input = screenDictionaryIterator->second->update();

    if (input != "looping") {
        screenDictionaryIterator->second->onDestruction();

        if (input == "end") {
            return false;
        } else {
            setIterator(input);
            return true;
        }
    }

    return true;
}

void RoutingMachine::setIterator(const std::string &screenName) {
    if (!screenDictionary.empty()) {
        screenDictionaryIterator = screenDictionary.find(screenName);

        if (screenDictionaryIterator != screenDictionary.end()) {
            screenDictionaryIterator->second->onCreation();
        } else {
            throw std::runtime_error("Can not find screen with that name!");
        }
    } else {
        throw std::runtime_error("The screen dictionary is empty!");
    }
}

void RoutingMachine::executeRendering() {
//    screenDictionaryIterator->second->render();
}
