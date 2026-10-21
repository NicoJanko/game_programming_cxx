#ifndef COMPONENTS_BG_SPRITE_H
#define COMPONENTS_BG_SPRITE_H

#include "sprite_component.h"
#include <SDL.h>
#include <vector>

class BGSpriteComponent : public SpriteComponent {
  public:
    BGSpriteComponent(class Actor* owner, int drawOrder = 10);

    void update(const float& deltaTime) override;
    void draw(SDL_Renderer* renderer) override;

    void setBGTextures(const std::vector<SDL_Texture*>& textures);

    void setScrollSpeed(float speed) { scrollSpeed = speed; };
    float getScrollSpeed() const { return scrollSpeed; };

    void setScreenSize(const Vector2& size) { screenSize = size; };
    Vector2 getScreenSize() { return screenSize; };

  private:
    struct BGTexture {
        SDL_Texture* texture;
        Vector2 offset;
    };
    std::vector<BGTexture> bgTextures;

    float scrollSpeed;
    Vector2 screenSize;
};

#endif
