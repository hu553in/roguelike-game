/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_SYSTEMS_INPUTHANDLINGSYSTEM_H_
#define INCLUDE_SYSTEMS_INPUTHANDLINGSYSTEM_H_


#include <unordered_map>
#include <string>

class InputHandlingSystem {
 private:
    std::unordered_map<int, std::string> keyCodeMap;

 public:
    InputHandlingSystem();

    ~InputHandlingSystem();

    std::string handle(const std::string &windowName);
};


#endif  // INCLUDE_SYSTEMS_INPUTHANDLINGSYSTEM_H_
