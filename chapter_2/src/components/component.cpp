#include "component.h"

Component::Component(class Actor* owner, int updateOrder) : owner(owner), updateOrder(updateOrder) {
    owner->addComponent(this);
}

Component::~Component() { owner->removeComponent(this); }

void Component::update(const float& deltaTime) {}
