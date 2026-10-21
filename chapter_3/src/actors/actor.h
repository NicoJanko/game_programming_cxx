#ifndef ACTORS_ACTOR_H
#define ACTORS_ACTOR_H

#include "math.h"
#include <SDL.h>
#include <cmath>
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
    void setState(State stat) { state = stat; }
    float getScale() const { return scale; }
    void setScale(const float scal) { scale = scal; };
    Vector2 getPosition() const { return position; }
    void setPosition(const Vector2& pos) { position = pos; };
    float getRotation() const { return rotation_r; }
    void setRotation(const float rot) { rotation_r = rot; };
    Vector2 getForwardVector() const {
        return Vector2(std::cos(rotation_r), -std::sin(rotation_r));
    }

    void processInput(const uint8_t* keyState);
    virtual void actorInput(const uint8_t* keyState);

  private:
    State state;

    Vector2 position;
    float scale;
    float rotation_r;

    std::vector<class Component*> components;

  protected:
    class Game* game;
};

#endif
