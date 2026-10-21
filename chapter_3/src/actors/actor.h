#ifndef ACTORS_ACTOR_H
#define ACTORS_ACTOR_H

#include "math.h"
#include <SDL.h>
#include <vector>

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
    void setScale(const float scal) { scale = scal; };
    Vector2 getPosition() const { return position; }
    void setPosition(const Vector2& pos) { position = pos; };
    float getRotation() const { return rotation_r; }

  private:
    State state;

    Vector2 position;
    float scale;
    float rotation_r;

    class Game* game;
    std::vector<class Component*> components;
};

#endif
