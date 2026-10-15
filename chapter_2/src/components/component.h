#ifndef COMPONENTS_COMPONENT_H
#define COMPONENTS_COMPONENT_H
#include "actors/actor.h"

class Component {
  public:
    Component(class Actor* owner, int updateOrder = 100);

    virtual ~Component();
    virtual void Update(float deltaTime);
    int getUpdateOrder() const { return updateOrder; }

  protected:
    class Actor* owner;
    int updateOrder;
};

#endif
