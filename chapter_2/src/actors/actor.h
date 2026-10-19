#ifndef ACTORS_ACTOR_H
#define ACTORS_ACTOR_H

#include "object/vectors.h"
#include <SDL.h>

class Actor {
  public:
    enum State { Active, Paused, Dead };

    Actor(class Game* game);
    virtual ~Actor();

    void update(const float& deltaTime);
    void updateComponents(const float& deltaTime);

    virtual void updateActor(const float& deltaTime);

    void addComponent(class Component* component);
    void removeComponent(class Component* component);

    State getState();

  private:
    State state;

    Vector2 position;
    float scale;
};

#endif
