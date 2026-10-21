#ifndef COMPONENTS_INPUT_COMPONENT_H
#define COMPONENTS_INPUT_COMPONENT_H

#include "components/move_component.h"

class InputComponent : public MoveComponent {
  public:
    InputComponent(class Actor* owner, int updateOrder = 10);

    void processInput(const uint8_t* keyState) override;

    float getMaxForwardSpeed() const { return maxForwardSpeed; }
    void setMaxForwardSpeed(float speed) { maxForwardSpeed = speed; }

    float getMaxAngularSpeed() const { return maxAngularSpeed; }
    void setMaxAngularSpeed(float value) { maxAngularSpeed = value; }

    int getBackKey() const { return backKey; }
    void setBackKey(int value) { backKey = value; }

    int getForwardKey() const { return forwardKey; }
    void setForwardKey(int value) { forwardKey = value; }

    int getClockwiseKey() const { return clockwiseKey; }
    void setClockwiseKey(int value) { clockwiseKey = value; }

    int getCounterClockwiseKey() const { return counterClockwiseKey; }
    void setCounterClockwiseKey(int value) { counterClockwiseKey = value; }

  private:
    float maxForwardSpeed;
    float maxAngularSpeed;

    int forwardKey;
    int backKey;

    int clockwiseKey;
    int counterClockwiseKey;
};
#endif
