#include "component.h"

Component::Component(class Actor* owner, int updateOrder)
    : owner(owner), updateOrder(updateOrder) {}

Component::~Component() {}

void Component::update(const float& deltaTime) {}
