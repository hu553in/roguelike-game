/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_ATTRIBUTES_H_
#define INCLUDE_ATTRIBUTES_H_


#include <cstdint>

class Attributes {
 public:
    uint32_t velocity {}, healthPoints {}, attackPower {}, armorRate {}, worth {};

    Attributes() = default;

    Attributes(uint32_t _velocity, uint32_t _healthPoints, uint32_t _attackPower, uint32_t _armorRate,
               uint32_t _worth) :
            velocity {_velocity}, healthPoints {_healthPoints}, attackPower {_attackPower}, armorRate {_armorRate},
            worth {_worth} {};

    ~Attributes() = default;

    bool operator==(const Attributes &other) const {
        return velocity == other.velocity && healthPoints == other.healthPoints && attackPower == other.attackPower &&
               armorRate == other.armorRate && worth == other.armorRate;
    }

    bool operator!=(const Attributes &other) const {
        return !(other == *this);
    }
};

inline Attributes operator+(Attributes a, Attributes b) {
    Attributes buffer {a.velocity + b.velocity, a.healthPoints + b.healthPoints, a.attackPower + b.attackPower,
                       a.armorRate + b.armorRate, a.worth + b.worth};
    return buffer;
}

inline Attributes operator-(Attributes a, Attributes b) {
    Attributes buffer {a.velocity - b.velocity, a.healthPoints - b.healthPoints, a.attackPower - b.attackPower,
                       a.armorRate - b.armorRate, a.worth - b.worth};
    return buffer;
}

inline Attributes operator+=(Attributes a, Attributes b) {
    Attributes buffer {a.velocity + b.velocity, a.healthPoints + b.healthPoints, a.attackPower + b.attackPower,
                       a.armorRate + b.armorRate, a.worth + b.worth};
    return buffer;
}

inline Attributes operator-=(Attributes a, Attributes b) {
    Attributes buffer {a.velocity - b.velocity, a.healthPoints - b.healthPoints, a.attackPower - b.attackPower,
                       a.armorRate - b.armorRate, a.worth - b.worth};
    return buffer;
}


#endif  // INCLUDE_ATTRIBUTES_H_
