#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>
#include <numbers>

namespace utils {
void waitNextFrame(const uint32_t& tickCounts = 0, const uint16_t& targetFPS = 60);
void computeDeltaTime(float& deltaTime, uint32_t& tickCounts);
} // namespace utils
namespace math {
constexpr float toDegrees(float radians) { return radians * 180.0f / std::numbers::pi_v<float>; }
constexpr float toRadians(float degrees) { return degrees * std::numbers::pi_v<float> / 180.0f; }
} // namespace math
#endif
