#ifndef ACTORS_LAZER_ACTOR_H
#define ACTORS_LAZER_ACTOR_H

#include "actors/actor.h"
#include "components/circle_component.h"

class LazerActor : public Actor {
  public:
    LazerActor(class Game* game);
    void updateActor(const float& deltaTime) override;

  private:
    CircleComponent* cc;
};

#endif
