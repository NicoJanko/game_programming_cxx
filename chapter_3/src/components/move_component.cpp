#include "components/move_component.h"
#include "actors/actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
    : Component(owner, updateOrder), angularSpeed(0.0f), forwardSpeed(0.0f) {}

void MoveComponent::update(const float& deltaTime) {
    if (!Math::nearZero(angularSpeed)) {
        float rot = owner->getRotation();
        rot += angularSpeed * deltaTime;
        owner->setRotation(rot);
    }
    if (!Math::nearZero(forwardSpeed)) {
        Vector2 pos = owner->getPosition();
        pos += owner->getForwardVector() * forwardSpeed * deltaTime;
        owner->setPosition(pos);
    }
}
