/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ROUTINGMACHINE_H_
#define INCLUDE_ROUTINGMACHINE_H_


#include <string>
#include <unordered_map>

#include <screens/IScreen.h>

class RoutingMachine {
 private:
    std::unordered_map<std::string, IScreenSharedPtr> screenDictionary {};
    std::unordered_map<std::string, IScreenSharedPtr>::iterator screenDictionaryIterator {};

 public:
    RoutingMachine();

    ~RoutingMachine();

    bool update();

    template <class T>
    void addScreen(const std::string &screenName, const T &screen) {
        screenDictionary[screenName] = std::make_shared<T>(screen);
    }

    void executeRendering();

    void setIterator(const std::string &screenName);
};


#endif  // INCLUDE_ROUTINGMACHINE_H_
