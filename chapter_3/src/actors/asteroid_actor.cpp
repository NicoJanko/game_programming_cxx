#include "actors/asteroid_actor.h"
#include "components/move_component.h"
#include "components/sprite_component.h"
#include "game.h"
#include "math.h"
#include "utils.h"


AsteroidActor::AsteroidActor(class Game* game) : Actor(game) {
    game->addActor(this);
    // init to random position/orientation
    Vector2 randPos = utils::getRandomVector(Vector2(0.0, 0.0f), Vector2(1024.0f, 768.0f));

    setPosition(randPos);
    setRotation(utils::getFloatRange(0.0f, Math::twoPi));

    // TODO change this to a tilemap
    SpriteComponent* sc = new SpriteComponent(this);
    sc->setTexture(game->loadTexture("Asteroid.png"));

    MoveComponent* mv = new MoveComponent(this);
    mv->setForwardSpeed(150.0f);
}
