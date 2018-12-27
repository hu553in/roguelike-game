/* Copyright (C) 2018 hu553in */

#include <vector>
#include <cstddef>
#include <cassert>
#include <string>

#include <Camera.h>

Camera::Camera()= default;

Camera::~Camera() = default;

std::vector<std::vector<char>> Camera::getPicture(const Vector2<int> &pictureSize, const Vector2<int> &playerCoord,
                                                  const std::shared_ptr<std::vector<std::vector<char>>> &fullPicture) {
    assert(pictureSize.y % 2 != 0 && pictureSize.x % 2 != 0);

    std::vector<std::vector<char>> clippedPicture(static_cast<uint32_t>(pictureSize.y),
                                                  std::vector<char>(static_cast<uint32_t>(pictureSize.x)));

    Vector2<int> centerCoord {pictureSize.y / 2, pictureSize.x / 2};
    Vector2<int> difference = centerCoord - playerCoord;

    for (uint32_t row = 0; row < clippedPicture.size(); row++) {
        for (uint32_t column = 0; column < clippedPicture.at(row).size(); column++) {
            auto rowForComparing = static_cast<int>(row),
                 columnForComparing = static_cast<int>(column);

            if (rowForComparing - difference.y >= 0 &&
                columnForComparing - difference.x >= 0 &&
                rowForComparing - difference.y < static_cast<int>(fullPicture->size()) &&
                columnForComparing - difference.x < static_cast<int>(fullPicture->at(row - difference.y).size())) {
                clippedPicture.at(row).at(column) = fullPicture->at(row - difference.y).at(column - difference.x);
            } else {
                clippedPicture.at(row).at(column) = ' ';
            }
        }
    }

    return clippedPicture;
}
