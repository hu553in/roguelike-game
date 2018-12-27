/* Copyright (C) 2018 hu553in */

#include <string>
#include <cstdint>

#include <Statistics.h>

Statistics::Statistics() : nickname {""}, killingScore {0}, numberOfActions {0} {}

Statistics::Statistics(std::string nickname, int64_t killingScore, int64_t numberOfActions)
    : nickname {std::move(nickname)}, killingScore {killingScore}, numberOfActions {numberOfActions} {}

Statistics::~Statistics() = default;
