#include "actor.h"
#include "game.h"

Actor::Actor(class Game* game)
    : game(game), state(Active), position(Vector2(0.0f, 0.0f)), scale(1.0f), rotation_r(0.0f) {
    game->addActor(this);
}

Actor::~Actor() {
    game->removeActor(this);
    while (!components.empty()) {
        delete components.back();
    }
}

void Actor::update(const float& deltaTime) {
    if (state == Active) {
        updateActor(deltaTime);
        updateComponents(deltaTime);
    }
}

void Actor::updateComponents(const float& deltaTime) {
    for (auto* iter : components) {
        iter->update(deltaTime);
    }
}

void Actor::updateActor(const float& deltaTime) {}

void Actor::addComponent(class Component* component) {
    // Find the insertion point in the sorted vector
    // (The first element with a order higher than me)
    int myOrder = component->getUpdateOrder();
    auto iter = components.begin();
    for (; iter != components.end(); ++iter) {
        if (myOrder < (*iter)->getUpdateOrder()) {
            break;
        }
    }

    // Inserts element before position of iterator
    components.insert(iter, component);
}

void Actor::removeComponent(class Component* component) {
    auto iter = std::ranges::find(components, component);
    if (iter != components.end()) {
        components.erase(iter);
    }
}

void Actor::processInput(const uint8_t* keyState) {
    // first process inputs for components
    if (state == Active) {
        for (auto* comp : components) {
            comp->processInput(keyState);
        }
        actorInput(keyState);
    }
}

void Actor::actorInput(const uint8_t* keyState) {}
