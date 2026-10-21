#ifndef ACTORS_SHIP_H
#define ACTORS_SHIP_H

#include "actors/actor.h"

class ShipActor : public Actor {
  public:
    ShipActor(class Game* game);
    void actorInput(const uint8_t* keyState) override;
    void updateActor(const float& deltaTime) override;

  private:
    float lazerCooldown = 0.0f;
};

#endif
