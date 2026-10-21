#ifndef ACTORS_ASTEROID_H
#define ACTORS_ASTEROID_H
#include "actors/actor.h"
#include "components/circle_component.h"

class AsteroidActor : public Actor {
  public:
    AsteroidActor(class Game* game);
    ~AsteroidActor() override;
    CircleComponent* getCircle() const { return cc; }

  private:
    CircleComponent* cc;
};

#endif
