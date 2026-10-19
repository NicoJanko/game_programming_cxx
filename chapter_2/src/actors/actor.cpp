#include "actor.h"

Actor::Actor(class Game* game) {}

Actor::~Actor() {}

Actor::State Actor::getState() { return state; }

void Actor::update(const float& deltaTime) {}

void Actor::updateComponents(const float& deltaTime) {}

void Actor::updateActor(const float& deltaTime) {}

void Actor::addComponent(class Component* component) {}

void Actor::removeComponent(class Component* component) {}
