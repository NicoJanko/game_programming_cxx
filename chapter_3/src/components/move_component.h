#ifndef COMPONENTS_MOVE_COMPONENT_H
#define COMPONENTS_MOVE_COMPONENT_H

#include "components/component.h"

class MoveComponent : public Component {

  public:
    MoveComponent(class Actor* owner, int updateOrder = 10);

    void update(const float& deltaTime) override;

    float getAngularSpeed() const { return angularSpeed; };
    float getForwardSpeed() const { return forwardSpeed; };
    void setAngularSpeed(float speed) { angularSpeed = speed; };
    void setForwardSpeed(float speed) { forwardSpeed = speed; };

  private:
    float angularSpeed;
    float forwardSpeed;
};

#endif
