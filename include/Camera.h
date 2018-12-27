/* Copyright (C) 2018 hu553in */

#ifndef INCLUDE_CAMERA_H_
#define INCLUDE_CAMERA_H_


#include <cstdint>
#include <vector>

#include <entities/IItemEntity.h>
#include <entities/IMovableEntity.h>
#include <entities/IStaticEntity.h>

class Camera {
 public:
    Camera();

    ~Camera();

    std::vector<std::vector<char>> getPicture(const Vector2<int> &pictureSize, const Vector2<int> &playerCoord,
                                              const std::shared_ptr<std::vector<std::vector<char>>> &fullPicture);
};


#endif  // INCLUDE_CAMERA_H_
