#include "bg_sprite_component.h"

BGSpriteComponent::BGSpriteComponent(class Actor* owner, int drawOrder)
    : SpriteComponent(owner, drawOrder) {}

void BGSpriteComponent::update(const float& deltaTime) {
    SpriteComponent::update(deltaTime);
    for (auto& bg : bgTextures) {
        // update x offset
        bg.offset.x += scrollSpeed * deltaTime;
        // if completly offscreen reset
        if (bg.offset.x < -screenSize.x) {
            bg.offset.x = (bgTextures.size() - 1) * screenSize.x - 1;
        }
    }
}

void BGSpriteComponent::setBGTextures(const std::vector<SDL_Texture*>& textures) {
    int count = 0;
    for (auto* tex : textures) {
        BGTexture temp;
        temp.texture = tex;

        temp.offset.x = count * screenSize.x;
        temp.offset.y = 0;
        bgTextures.emplace_back(temp);
        count++;
    }
}
