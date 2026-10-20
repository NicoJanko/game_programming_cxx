#include "game.h"
#include "utils.h"
#include <algorithm>
#include <filesystem>

namespace {
const std::filesystem::path asset_dir{ASSET_DIR};
}

Game::Game() {}

Game::~Game() {}

bool Game::initialize() {
    // init SDL
    int sdlResults = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResults != 0) {
        SDL_Log("Failed to initialize sdl with error %s", SDL_GetError());
        return false;
    }

    sdlResults = IMG_Init(IMG_INIT_PNG);
    if (sdlResults != 0) {
        SDL_Log("Failed to initialize sdl_image with error %s", IMG_GetError());
        return false;
    }

    SDL_Log("SDL Initialiazation successfull");

    p_Window = SDL_CreateWindow("Space", 100, 100, 1024, 768, 0);

    if (!p_Window) {
        SDL_Log("Failed to create window with error %s", SDL_GetError());
        return false;
    }

    p_Render =
        SDL_CreateRenderer(p_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!p_Render) {
        SDL_Log("Failed to create renderer with error %s", SDL_GetError());
        return false;
    }

    // init members
    deltaTime = 0.0f;
    tickCounts = 0;
    updatingActor = false;
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
    SDL_DestroyRenderer(p_Render);
    SDL_Quit();
}

void Game::processInput() {}

void Game::updateGame() {
    utils::waitNextFrame(tickCounts);
    utils::computeDeltaTime(deltaTime, tickCounts);

    // update actors
    updatingActor = true;
    for (auto* actor : activeActors) {
        actor->updateActor(deltaTime);
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

void Game::generateOutput() {}

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

SDL_Texture* Game::loadTexture(const char* fileName) {
    // load from file
    const std::string full_path = (asset_dir / fileName).string();
    SDL_Surface* surf = IMG_Load(full_path.c_str()); // need to be char*
    if (!surf) {
        SDL_Log("Failed to load texture file %s", fileName);
        return nullptr;
    }
    // create texture from surface
    SDL_Texture* text = SDL_CreateTextureFromSurface(p_Render, surf);
    SDL_FreeSurface(surf);
    if (!text) {
        SDL_Log("Failed to convert surface to texture for %s", fileName);
        return nullptr;
    }
    return text;
}

void Game::loadData() { textureMap["Ship01.png"] = loadTexture("Ship01.png"); }
