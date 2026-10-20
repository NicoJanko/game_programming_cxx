#ifndef COMPONENTS_ANIM_SPRITE_COMPONENT_H
#define COMPONENTS_ANIM_SPRITE_COMPONENT_H
#include "sprite_component.h"
#include <SDL.h>
#include <vector>

class AnimSpriteComponent : public SpriteComponent {
  public:
    AnimSpriteComponent(class Actor* owner, int drawOrder = 100);

    void update(const float& deltaTime) override;

    void setAnimTextures(const std::vector<SDL_Texture*>& textures);

    float getAnimeFPS() const { return animFPS; };

    void setAnimFPS(const float& fps) { animFPS = fps; };

  private:
    std::vector<SDL_Texture*> animTextures;

    float currFrame;
    float animFPS;
};

#endif
