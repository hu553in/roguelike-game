/* Copyright (C) 2018 hu553in */

#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <string>

#include <systems/LeaderboardSortingSystem.h>

#include <Statistics.h>
#include <StaticStorage.h>

LeaderboardSortingSystem::LeaderboardSortingSystem() = default;

LeaderboardSortingSystem::~LeaderboardSortingSystem() = default;

void LeaderboardSortingSystem::sortByKillingScore() {
    auto leaderboard = StaticStorage::getInstance().getEntry<std::vector<Statistics>>("leaderboard");

    auto isLeaderboardSortedInDescendingOrder = StaticStorage::getInstance().getEntry<bool>(
            "isLeaderboardSortedInDescendingOrder");
    auto isLeaderboardSortedByKillingScore = StaticStorage::getInstance().getEntry<bool>(
            "isLeaderboardSortedByKillingScore");

    for (size_t i = 0; i < leaderboard->size() - 1; i++) {
        for (size_t j = i + 1; j < leaderboard->size(); j++) {
            if (*isLeaderboardSortedInDescendingOrder &&
                *isLeaderboardSortedByKillingScore &&
                leaderboard->at(j).killingScore < leaderboard->at(i).killingScore) {
                    std::swap<Statistics>(leaderboard->at(i), leaderboard->at(j));
            } else if (leaderboard->at(j).killingScore > leaderboard->at(i).killingScore) {
                std::swap<Statistics>(leaderboard->at(i), leaderboard->at(j));
            }
        }
    }

    if (!*isLeaderboardSortedByKillingScore) {
        *isLeaderboardSortedInDescendingOrder = true;
        *isLeaderboardSortedByKillingScore = true;
    } else {
        *isLeaderboardSortedInDescendingOrder = !*isLeaderboardSortedInDescendingOrder;
    }
}

void LeaderboardSortingSystem::sortByNumberOfActions() {
    auto leaderboard = StaticStorage::getInstance().getEntry<std::vector<Statistics>>("leaderboard");

    auto isLeaderboardSortedInDescendingOrder = StaticStorage::getInstance().getEntry<bool>(
            "isLeaderboardSortedInDescendingOrder");
    auto isLeaderboardSortedByKillingScore = StaticStorage::getInstance().getEntry<bool>(
            "isLeaderboardSortedByKillingScore");

    for (size_t i = 0; i < leaderboard->size() - 1; i++) {
        for (size_t j = i + 1; j < leaderboard->size(); j++) {
            if (*isLeaderboardSortedInDescendingOrder &&
                !*isLeaderboardSortedByKillingScore &&
                leaderboard->at(j).numberOfActions < leaderboard->at(i).numberOfActions) {
                    std::swap<Statistics>(leaderboard->at(i), leaderboard->at(j));
            } else if (leaderboard->at(j).numberOfActions > leaderboard->at(i).numberOfActions) {
                std::swap<Statistics>(leaderboard->at(i), leaderboard->at(j));
            }
        }
    }

    if (*isLeaderboardSortedByKillingScore) {
        *isLeaderboardSortedInDescendingOrder = true;
        *isLeaderboardSortedByKillingScore = false;
    } else {
        *isLeaderboardSortedInDescendingOrder = !*isLeaderboardSortedInDescendingOrder;
    }
}
