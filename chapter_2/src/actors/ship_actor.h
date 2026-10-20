#ifndef ACTORS_SHIP_ACTOR_H
#define ACTORS_SHIP_ACTOR_H

#include "actors/actor.h"

class ShipActor : public Actor {
  public:
    ShipActor(class Game* game);
    void updateActor(const float& deltaTime) override;
    void processKeyboard(const uint8_t* state);
    float getRightSpeed() const { return rightSpeed; };
    float getDownSpeed() const { return downSpeed; };

  private:
    float rightSpeed;
    float downSpeed;
};
#endif
