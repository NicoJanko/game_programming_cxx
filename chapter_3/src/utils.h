#ifndef UTILS_H
#define UTILS_H

#include "math.h"
#include <SDL.h>
#include <random>

namespace utils {

void waitNextFrame(const uint32_t& tickCounts = 0, const uint16_t& targetFPS = 60);
void computeDeltaTime(float& deltaTime, uint32_t& tickCounts);
float getFloatRange(float min, float max);
Vector2 getRandomVector(const Vector2& min, const Vector2& max);
} // namespace utils

#endif
