/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_VECTOR2_H_
#define INCLUDE_VECTOR2_H_


#define ZERO ("zero")
#define ONE ("one")
#define UP ("up")
#define DOWN ("down")
#define LEFT ("left")
#define RIGHT ("right")

#include <string>
#include <unordered_map>
#include <memory>
#include <ostream>

template <typename T>
class Vector2 {
 public:
    T y {}, x {};

    Vector2() = default;

    Vector2(T _y, T _x) : y {_y}, x {_x} {}

    explicit Vector2(const std::string &type) {
        bool check = std::is_signed<T>::value;

        std::unordered_map<std::string, Vector2<int>> _signed {
                std::make_pair("up", Vector2<int> {-1, 0}),
                std::make_pair("down", Vector2<int> {1, 0}),
                std::make_pair("left", Vector2<int> {0, -1}),
                std::make_pair("right", Vector2<int> {0, 1}),
                std::make_pair("zero", Vector2<int> {0, 0}),
                std::make_pair("one", Vector2<int> {1, 1})
        };

        std::unordered_map<std::string, Vector2<size_t>> _unsigned {
                std::make_pair("zero", Vector2<size_t> {0, 0}),
                std::make_pair("one", Vector2<size_t> {1, 1})
        };

        if (check) {
            y = _signed.at(type).y;
            x = _signed.at(type).x;
        } else {
            y = _unsigned.at(type).y;
            x = _unsigned.at(type).x;
        }
    }

    ~Vector2() = default;

    bool operator==(const Vector2<T> &other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2<T> &other) const {
        return !(other == *this);
    }

    bool operator<(const Vector2<T> &other) const {
        return y < other.y && x < other.x;
    }

    bool operator>(const Vector2<T> &other) const {
        return y > other.y && x > other.x;
    }

    bool operator<=(const Vector2<T> &other) const {
        return y <= other.y && x <= other.x;
    }

    bool operator>=(const Vector2<T> &other) const {
        return y >= other.y && x >= other.x;
    }

    Vector2<T> &operator=(Vector2<T> other) {
        this->y = other.y;
        this->x = other.x;
        return *this;
    }
};

template <typename T>
inline Vector2<T> operator+(Vector2<T> a, Vector2<T> b) {
    Vector2<T> buffer {a.y + b.y, a.x + b.x};
    return buffer;
}

template <typename T>
inline Vector2<T> operator-(Vector2<T> a, Vector2<T> b) {
    Vector2<T> buffer {a.y - b.y, a.x - b.x};
    return buffer;
}

template <typename T>
inline Vector2<T> operator+=(Vector2<T> a, Vector2<T> b) {
    Vector2<T> buffer {a.y + b.y, a.x + b.x};
    return buffer;
}

template <typename T>
inline Vector2<T> operator-=(Vector2<T> a, Vector2<T> b) {
    Vector2<T> buffer {a.y - b.y, a.x - b.x};
    return buffer;
}

template <typename T>
inline std::ostream &operator<<(std::ostream &os, const Vector2<T> &vector2) {
    os << vector2.y << " " << vector2.x;
    return os;
}


#endif  // INCLUDE_VECTOR2_H_
