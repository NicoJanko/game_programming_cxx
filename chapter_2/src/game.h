#ifndef GAME_H
#define GAME_H

#include "actors/actor.h"
#include <SDL.h>
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

  private:
    float deltaTime;
    uint32_t tickCounts;

    bool isRunning;
    bool updatingActor;
    std::vector<Actor*> activeActors;
    std::vector<Actor*> pendingActors;
    void processInput();
    void updateGame();
    void generateOutput();

    SDL_Window* p_Window;
    SDL_Renderer* p_Render;
};

#endif
