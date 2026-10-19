#ifndef UTILS_H
#define UTILS_H

#include <SDL.h>

namespace utils {
void waitNextFrame(const uint32_t& tickCounts = 0, const uint16_t& targetFPS = 60);
void computeDeltaTime(float& deltaTime, uint32_t& tickCounts);
} // namespace utils

#endif
