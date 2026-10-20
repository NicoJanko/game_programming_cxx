#include "actor.h"
#include "game.h"

Actor::Actor(class Game* game) : game(game) { game->addActor(this); }

Actor::~Actor() {}

void Actor::update(const float& deltaTime) {}

void Actor::updateComponents(const float& deltaTime) {}

void Actor::updateActor(const float& deltaTime) {}

void Actor::addComponent(class Component* component) {}

void Actor::removeComponent(class Component* component) {}
