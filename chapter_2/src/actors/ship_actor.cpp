#include "ship_actor.h"
#include "components/anim_sprite_component.h"
#include "game.h"

ShipActor::ShipActor(class Game* game) : Actor(game), rightSpeed(0.0f), downSpeed(0.0f) {
    auto* asc = new AnimSpriteComponent(this);
    std::vector<SDL_Texture*> anims = {
        game->getTexture("Ship01.png"),
        game->getTexture("Ship02.png"),
        game->getTexture("Ship03.png"),
        game->getTexture("Ship04.png"),
    };
    asc->setAnimTextures(anims);
}

void ShipActor::updateActor(const float& deltaTime) {
    Actor::updateActor(deltaTime);

    Vector2 pos = getPosition();
    pos.x += rightSpeed * deltaTime;
    pos.y += downSpeed * deltaTime;
    if (pos.x < 25.0f) {
        pos.x = 25.0f;
    } else if (pos.x > 500.0f) {
        pos.x = 500.0f;
    }
    if (pos.y < 25.0f) {
        pos.y = 25.0f;
    } else if (pos.y > 743.0f) {
        pos.y = 743.0f;
    }
    setPosition(pos);
}

void ShipActor::processKeyboard(const uint8_t* state) {
    rightSpeed = 0.0f;
    downSpeed = 0.0f;

    if (state[SDL_SCANCODE_W]) {
        downSpeed += -300.0f;
    }
    if (state[SDL_SCANCODE_S]) {
        downSpeed += 300.0f;
    }
    if (state[SDL_SCANCODE_D]) {
        rightSpeed += 300.0f;
    }
    if (state[SDL_SCANCODE_A]) {
        rightSpeed += -300.0f;
    }
}
