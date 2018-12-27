/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_FACADES_LINUX_H_
#define INCLUDE_FACADES_LINUX_H_


#include <asm/ioctls.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <Vector2.h>

namespace Linux {
    void getSizeOfTerminal(Vector2<int> *sizeOfTerminal) {
        struct winsize windowSize {};
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowSize);

        *sizeOfTerminal = {windowSize.ws_row, windowSize.ws_col};
    }
}


#endif  // INCLUDE_FACADES_LINUX_H_
