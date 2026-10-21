#include "sprite_component.h"
#include "actors/actor.h"
#include "game.h"
#include "math.h"
#include "utils.h"

SpriteComponent::SpriteComponent(class Actor* owner, int drawOrder)
    : Component(owner), drawOrder(drawOrder) {
    owner->getGame()->addSprite(this);
}

SpriteComponent::~SpriteComponent() {}

void SpriteComponent::draw(SDL_Renderer* renderer) {
    if (texture) {
        SDL_Rect r;
        // scale with the owner scale
        r.w = static_cast<int>(texWidth * owner->getScale());
        r.h = static_cast<int>(texHeight * owner->getScale());
        // center the position around the owner's position
        r.x = static_cast<int>(owner->getPosition().x - (r.w / 2));
        r.y = static_cast<int>(owner->getPosition().y - (r.h / 2));

        SDL_RenderCopyEx(renderer, texture, nullptr, &r, Math::toDegrees(owner->getRotation()),
                         nullptr, SDL_FLIP_NONE);
    }
}

void SpriteComponent::setTexture(SDL_Texture* texture) {
    this->texture = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);
}
