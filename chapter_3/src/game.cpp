#include "game.h"
#include "actors/actor.h"
#include "actors/asteroid_actor.h"
#include "actors/ship_actor.h"
#include "components/bg_sprite_component.h"
#include "utils.h"
#include <algorithm>
#include <filesystem>

namespace {
const std::filesystem::path asset_dir{ASSET_DIR};
}

Game::Game() {
    p_Window = nullptr;

    isRunning = true;

    tickCounts = 0;
}

Game::~Game() {}

bool Game::initialize() {
    // init SDL
    int sdlResults = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResults != 0) {
        SDL_Log("Failed to initialize sdl with error %s", SDL_GetError());
        return false;
    }

    sdlResults = IMG_Init(IMG_INIT_PNG);
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0) {
        SDL_Log("Failed to initialize sdl_image with error %s", IMG_GetError());
        return false;
    }

    SDL_Log("SDL Initialiazation successfull");

    p_Window = SDL_CreateWindow("Space", 100, 100, 1024, 768, 0);

    if (!p_Window) {
        SDL_Log("Failed to create window with error %s", SDL_GetError());
        return false;
    }

    p_Renderer =
        SDL_CreateRenderer(p_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!p_Renderer) {
        SDL_Log("Failed to create renderer with error %s", SDL_GetError());
        return false;
    }

    // init members
    deltaTime = 0.0f;
    tickCounts = 0;
    updatingActor = false;

    loadData();

    return true;
}

void Game::runLoop() {
    while (isRunning) {
        processInput();
        updateGame();
        generateOutput();
    }
}

void Game::shutdown() {
    SDL_DestroyWindow(p_Window);
    SDL_DestroyRenderer(p_Renderer);
    SDL_Quit();
}

void Game::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        isRunning = false;
    }

    // Process actor input
    updatingActor = true;
    for (auto* act : activeActors) {
        act->processInput(state);
    }
    updatingActor = false;
}

void Game::updateGame() {
    utils::waitNextFrame(tickCounts);
    utils::computeDeltaTime(deltaTime, tickCounts);

    // update actors
    updatingActor = true;
    for (auto* actor : activeActors) {
        actor->update(deltaTime);
    }
    updatingActor = false;

    for (auto* actor : pendingActors) {
        activeActors.emplace_back(actor);
    }
    pendingActors.clear();
    std::vector<Actor*> deadActor;
    for (auto* actor : activeActors) {
        if (actor->getState() == Actor::Dead) {
            deadActor.emplace_back(actor);
        }
    }

    for (auto* actor : deadActor) {
        delete actor;
    }
}

void Game::generateOutput() {
    SDL_SetRenderDrawColor(p_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(p_Renderer);

    // Draw all sprite components
    for (auto* sprite : sprites) {
        sprite->draw(p_Renderer);
    }

    SDL_RenderPresent(p_Renderer);
}

void Game::addActor(Actor* actor) {
    if (updatingActor) {
        pendingActors.emplace_back(actor);
    } else {
        activeActors.emplace_back(actor);
    }
}

void Game::removeActor(Actor* actor) {
    // check if it's in actor
    auto it = std::ranges::find(activeActors, actor);
    if (it != activeActors.end()) {
        it = activeActors.erase(it);
        return;
    }
    it = std::ranges::find(pendingActors, actor);
    if (it != pendingActors.end()) {
        it = pendingActors.erase(it);
        return;
    }
    // throw an error that the actor was not found
}

void Game::addSprite(SpriteComponent* sprite) {
    // find the insertion point
    int thisDrawOrder = sprite->getDrawOrder();
    auto iter = sprites.begin();

    for (; iter != sprites.end(); ++iter) {
        if (thisDrawOrder < (*iter)->getDrawOrder()) {
            break;
        }
    }

    sprites.insert(iter, sprite);
}

void Game::removeSprite(SpriteComponent* sprite) {
    auto iter = std::ranges::find(sprites, sprite);
    if (iter != sprites.end()) {
        sprites.erase(iter);
    }
}

SDL_Texture* Game::loadTexture(const char* fileName) {
    // load from file
    const std::string full_path = (asset_dir / fileName).string();
    SDL_Surface* surf = IMG_Load(full_path.c_str()); // need to be char*
    if (!surf) {
        SDL_Log("Failed to load texture file %s", fileName);
        return nullptr;
    }
    // create texture from surface
    SDL_Texture* text = SDL_CreateTextureFromSurface(p_Renderer, surf);
    SDL_FreeSurface(surf);
    if (!text) {
        SDL_Log("Failed to convert surface to texture for %s", fileName);
        return nullptr;
    }
    return text;
}

SDL_Texture* Game::getTexture(const char* fileName) {
    auto iter = textureMap.find(fileName);
    if (iter != textureMap.end()) {
        return iter->second;
    }
    return nullptr;
}

void Game::loadData() {
    // load all textures

    textureMap["Farback01.png"] = loadTexture("Farback01.png");
    textureMap["Asteroid.png"] = loadTexture("Asteroid.png");
    textureMap["Ship.png"] = loadTexture("Ship.png");
    textureMap["Laser.png"] = loadTexture("Laser.png");
    backGround = new Actor(this);
    backGround->setPosition(Vector2(512.0f, 384.0f));
    auto* bg = new BGSpriteComponent(backGround, 50);
    bg->setScreenSize(Vector2(1024.0f, 768.0f));
    std::vector<SDL_Texture*> bgtex = {getTexture("Farback01.png")};
    bg->setBGTextures(bgtex);

    // TODO : use a tile map
    const int numAsteroid = 20;
    for (int i = 0; i < numAsteroid; i++) {
        asteroidActors.emplace_back(new AsteroidActor(this));
    }

    ShipActor* ship = new ShipActor(this);
}

void Game::removeAsteroid(AsteroidActor* ast) { std::erase(asteroidActors, ast); }
