#include "utils.h"
#include <algorithm>

namespace {
std::mt19937 sGenerator;
}

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

float utils::getFloatRange(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(sGenerator);
}

Vector2 utils::getRandomVector(const Vector2& min, const Vector2& max) {
    Vector2 r = Vector2(getFloatRange(0.0f, 1.0f), getFloatRange(0.0f, 1.0f));
    return min + (max - min) * r;
}
