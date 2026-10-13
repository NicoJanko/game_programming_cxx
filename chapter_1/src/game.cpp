#include "game.h"
#include "stdio.h"

Game::Game(){
    p_Window = nullptr;

    isRunning = true;
}


bool Game::Initialize(){
    int sdlResults = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResults != 0) {
        SDL_Log("Failed to initialize sdl with error %s",SDL_GetError());
        return false;
    } else {
        SDL_Log("SDL Initialiazation successfull");
    }
    p_Window = SDL_CreateWindow("Pong",100,100,1024,768,0);
    //if creation failed create window will return a nullptr
    if (!p_Window){
        SDL_Log("Failed to create window with error %s", SDL_GetError());
        return false;
    }
    return true;

}

void Game::RunLoop(){
    while (isRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
    return;
}


void Game::Shutdown(){
    SDL_DestroyWindow(p_Window);
    SDL_Quit();
}

void Game::ProcessInput(){

}

void Game::UpdateGame(){

}

void Game::GenerateOutput(){

}

