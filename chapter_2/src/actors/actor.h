#ifndef ACTORS_ACTOR_H
#define ACTORS_ACTOR_H

#include "object/vectors.h"
#include <SDL.h>

class Actor {
  public:
    enum State { Active, Paused, Dead };

    Actor(class Game* game);
    virtual ~Actor();

    class Game* getGame() const { return game; }

    void update(const float& deltaTime);
    void updateComponents(const float& deltaTime);

    virtual void updateActor(const float& deltaTime);

    void addComponent(class Component* component);
    void removeComponent(class Component* component);

    State getState() const { return state; }
    float getScale() const { return scale; }
    Vector2 getPosition() const { return position; }
    float getRotation() const { return rotation_r; }

  private:
    State state;

    Vector2 position;
    float scale;
    float rotation_r;

    class Game* game;
};

#endif
