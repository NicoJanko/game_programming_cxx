#include "actors/ship_actor.h"
#include "actors/lazer_actor.h"
#include "components/input_component.h"
#include "components/sprite_component.h"
#include "game.h"
#include "math.h"
#include "utils.h"

ShipActor::ShipActor(class Game* game) : Actor(game) {
    // init to random position/orientation
    Vector2 randPos = utils::getRandomVector(Vector2(0.0, 0.0f), Vector2(1024.0f, 768.0f));

    setPosition(randPos);
    // setRotation(utils::getFloatRange(0.0f, Math::twoPi));

    // TODO change this to a tilemap
    SpriteComponent* sc = new SpriteComponent(this, 120);
    sc->setTexture(game->getTexture("Ship.png"));

    InputComponent* ic = new InputComponent(this);
    ic->setMaxForwardSpeed(100.0f);
    ic->setMaxAngularSpeed(Math::twoPi);
    ic->setForwardKey(SDL_SCANCODE_W);
    ic->setBackKey(SDL_SCANCODE_S);
    ic->setClockwiseKey(SDL_SCANCODE_A);
    ic->setCounterClockwiseKey(SDL_SCANCODE_D);
}

void ShipActor::updateActor(const float& deltaTime) { lazerCooldown -= deltaTime; }

void ShipActor::actorInput(const uint8_t* keyState) {
    if ((keyState[SDL_SCANCODE_SPACE]) && (lazerCooldown <= 0.0f)) {
        LazerActor* laz = new LazerActor(game);
        laz->setPosition(getPosition());
        laz->setRotation(getRotation());
        lazerCooldown = 0.5f;
    }
}
