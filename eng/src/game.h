#ifndef GAME_H
#define GAME_H

#include "actors/actor.h"
#include "actors/ship_actor.h"

#include "components/sprite_component.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <unordered_map>
#include <vector>

class Game {
  public:
    Game();
    ~Game();

    bool initialize();
    void runLoop();

    void shutdown();

    void addActor(Actor* actor);
    void removeActor(Actor* actor);

    void addSprite(SpriteComponent* sprite);
    SDL_Texture* loadTexture(const char* fileName);
    SDL_Texture* getTexture(const char* fileName);

  private:
    float deltaTime;
    uint32_t tickCounts;

    bool isRunning;
    bool updatingActor;
    std::vector<Actor*> activeActors;
    std::vector<Actor*> pendingActors;
    void loadData();

    void processInput();
    void updateGame();
    void generateOutput();

    SDL_Window* p_Window;
    SDL_Renderer* p_Renderer;

    std::unordered_map<std::string, SDL_Texture*> textureMap;

    std::vector<SpriteComponent*> sprites;

    ShipActor* ship;
    Actor* backGround;
};

#endif
