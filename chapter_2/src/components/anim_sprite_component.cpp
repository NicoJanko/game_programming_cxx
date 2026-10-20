#include "anim_sprite_component.h"

AnimSpriteComponent::AnimSpriteComponent(class Actor* owner, int drawOrder)
    : SpriteComponent(owner, drawOrder), currFrame(0.0f), animFPS(24.0f) {}

void AnimSpriteComponent::update(const float& deltaTime) {

    SpriteComponent::update(deltaTime);
    if (!animTextures.empty()) {
        // updat the current frame based on frame rate and delta time
        currFrame += animFPS * deltaTime;

        while (currFrame >= animTextures.size()) {
            currFrame -= animTextures.size();
        }
        // set current texture
        setTexture(animTextures[static_cast<int>(currFrame)]);
    }
}

void AnimSpriteComponent::setAnimTextures(const std::vector<SDL_Texture*>& textures) {
    this->animTextures = textures;
    currFrame = 0.0;
    // set first frame
    setTexture(animTextures[0]);
}
