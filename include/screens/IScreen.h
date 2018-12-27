/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_SCREENS_ISCREEN_H_
#define INCLUDE_SCREENS_ISCREEN_H_


#include <memory>
#include <string>

class IScreen {
 protected:
    bool looping {};

 public:
    virtual ~IScreen() = default;

    virtual std::string update() = 0;

    virtual void onCreation() = 0;

    virtual void onDestruction() = 0;

    void setLooping(bool newValue) {
        looping = newValue;
    }
};

using IScreenSharedPtr = std::shared_ptr<IScreen>;


#endif  // INCLUDE_SCREENS_ISCREEN_H_
