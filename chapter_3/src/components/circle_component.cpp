#include "components/circle_component.h"

CircleComponent::CircleComponent(class Actor* owner, int updateOrder)
    : Component(owner, updateOrder) {}

Vector2 CircleComponent::getCenter() const { return owner->getPosition(); }

bool intersect(const CircleComponent& a, const CircleComponent& b) {
    // distance squared
    Vector2 diff = a.getCenter() - b.getCenter();
    float diffSq = diff.lenghtSeq();

    float radiiSq = a.getRadius() + b.getRadius();
    radiiSq *= radiiSq;

    return diffSq <= radiiSq;
}
