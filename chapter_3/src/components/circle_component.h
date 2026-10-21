#ifndef COMPONENT_CIRCLE_COMPONENT_H
#define COMPONENT_CIRCLE_COMPONENT_H

#include "components/component.h"

class CircleComponent : public Component {
  public:
    CircleComponent(class Actor* owner, int updateOrder = 10);

    float getRadius() const { return Radius; }
    void setRadius(float value) { Radius = value; }

    Vector2 getCenter() const;

  private:
    float Radius;
};

bool intersect(const CircleComponent& a, const CircleComponent& b);

#endif
