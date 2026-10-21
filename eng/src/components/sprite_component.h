#ifndef COMPONENTS_SPRITE_COMPONENT_H
#define COMPONENTS_SPRITE_COMPONENT_H

#include "component.h"
#include <SDL.h>

class SpriteComponent : public Component {
  public:
    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();
    virtual void draw(SDL_Renderer* renderer);
    virtual void setTexture(SDL_Texture* texture);

    int getDrawOrder() const { return drawOrder; }
    int getTexWidth() const { return texWidth; }
    int getTexHeight() const { return texHeight; }

  protected:
    SDL_Texture* texture;
    int drawOrder;
    int texWidth;
    int texHeight;
};

#endif
