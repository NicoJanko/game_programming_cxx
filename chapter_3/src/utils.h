#ifndef UTILS_H
#define UTILS_H

#include "math.h"
#include <SDL.h>
#include <numbers>

namespace utils {
void waitNextFrame(const uint32_t& tickCounts = 0, const uint16_t& targetFPS = 60);
void computeDeltaTime(float& deltaTime, uint32_t& tickCounts);
} // namespace utils
namespace math {
float toDegrees(float radians) { return radians * 180.0f / Math::pi; }
float toRadians(float degrees) { return degrees * Math::pi / 180.0f; }
} // namespace math
#endif
