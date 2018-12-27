/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_STATISTICS_H_
#define INCLUDE_STATISTICS_H_


#include <string>
#include <cstdint>
#include <iostream>

class Statistics {
 public:
    std::string nickname {};
    int64_t killingScore {};
    int64_t numberOfActions {};

    Statistics();

    Statistics(std::string nickname, int64_t killingScore, int64_t numberOfActions);

    ~Statistics();
};

inline std::ostream &operator<<(std::ostream &os, const Statistics &statistics) {
    os << statistics.nickname << " " << statistics.killingScore << " " << statistics.numberOfActions;
    return os;
}


#endif  // INCLUDE_STATISTICS_H_
