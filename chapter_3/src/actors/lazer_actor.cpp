#include "actors/lazer_actor.h"
#include "components/move_component.h"
#include "game.h"

LazerActor::LazerActor(class Game* game) : Actor(game) {
    cc = new CircleComponent(this);
    cc->setRadius(2.0f);

    SpriteComponent* sc = new SpriteComponent(this, 120);
    sc->setTexture(game->getTexture("Laser.png"));

    MoveComponent* mc = new MoveComponent(this);
    mc->setForwardSpeed(150.0f);
}

void LazerActor::updateActor(const float& deltaTime) {
    // check for intersect with ennemi
    for (auto* ast : game->getAsteroidActors()) {
        if (intersect(*cc, *ast->getCircle())) {
            // set both dead
            setState(Dead);
            ast->setState(Dead);
        }
    }
}
