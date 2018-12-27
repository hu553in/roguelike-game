/* Copyright (C) 2018 hu553in */

#include <string>

#include <systems/InputHandlingSystem.h>

#include <facades/NCurses.h>

#include <StaticStorage.h>

InputHandlingSystem::InputHandlingSystem() {    // key codes are in the octal numeric system
    keyCodeMap.insert({0403, "up"});
    keyCodeMap.insert({0402, "down"});
    keyCodeMap.insert({0404, "left"});
    keyCodeMap.insert({0405, "right"});
    keyCodeMap.insert({0407, "backspace"});
    keyCodeMap.insert({0550, "end"});
    keyCodeMap.insert({0012, "enter"});
}

InputHandlingSystem::~InputHandlingSystem() {
    keyCodeMap.clear();
}

std::string InputHandlingSystem::handle(const std::string &windowName) {
    auto curses = StaticStorage::getInstance().getEntry<NCurses>("curses");

    auto keyCodeMapIterator = keyCodeMap.end();

    while (keyCodeMapIterator == keyCodeMap.end()) {
        int keyCode = curses->getKeyCode(windowName);
        keyCodeMapIterator = keyCodeMap.find(keyCode);
    }

    return keyCodeMapIterator->second;
}
