#include "utils.h"
#include <algorithm>

void utils::waitNextFrame(const uint32_t& tickCounts, const uint16_t& targetFPS) {
    if (targetFPS <= 0) {
        return;
    }
    const uint32_t timeMs = 1000 / targetFPS;

    while (!SDL_TICKS_PASSED(SDL_GetTicks(), tickCounts + timeMs))
        ;
}

void utils::computeDeltaTime(float& deltaTime, uint32_t& tickCounts) {
    deltaTime = std::min((SDL_GetTicks() - tickCounts) / 1000.0f, 0.05f);
    tickCounts = SDL_GetTicks();
}
