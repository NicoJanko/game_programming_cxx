#include "input_component.h"
#include "actors/actor.h"
InputComponent::InputComponent(class Actor* owner, int updateOrder)
    : MoveComponent(owner, updateOrder) {}

void InputComponent::processInput(const uint8_t* keyState) {
    float forwardSpeed = 0.0f;
    if (keyState[forwardKey]) {
        forwardSpeed += maxForwardSpeed;
    }
    if (keyState[backKey]) {
        forwardSpeed -= maxForwardSpeed;
    }

    float angularSpeed = 0.0f;
    if (keyState[clockwiseKey]) {
        angularSpeed += maxAngularSpeed;
    }
    if (keyState[counterClockwiseKey]) {
        angularSpeed -= maxAngularSpeed;
    }

    setForwardSpeed(forwardSpeed);
    setAngularSpeed(angularSpeed);
}
