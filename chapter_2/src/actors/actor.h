#ifndef ACTORS_ACTOR_H
#define ACTORS_ACTOR_H

#include "object/vectors.h"
#include <SDL.h>

class Actor {
  public:
    enum State { Active, Paused, Dead };

    Actor(class Game* game);
    virtual ~Actor();

    void update(float deltaTime);
    void updateComponents(float deltaTime);

    virtual void updateActor(float deltaTime);

    void addComponent(class Component* component);
    void removeComponent(class Component* component);

  private:
    State state;

    Vector2 position;
    float scale;
};

#endif
