#include "game.h"
#include "stdio.h"

Game::Game(){
    p_Window = nullptr;

    isRunning = true;

    paddlePos.x = 0;
    paddlePos.y = 768/2;
    paddleDir = 0;

    ballPos.x = 1024/2;
    ballPos.y = 768/2;

    ballVel.x = -200;
    ballVel.y = 235;

    ticksCounts = 0;

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

    p_Renderer = SDL_CreateRenderer(p_Window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!p_Renderer){
        SDL_Log("Failed to create renderer %s",SDL_GetError());
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
    SDL_DestroyRenderer(p_Renderer);
    SDL_Quit();
}

void Game::ProcessInput(){
    //process event queue
    SDL_Event event;

    while( SDL_PollEvent(&event)){
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        
        default:
            break;
        }
    }
    //esc for exit
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_ESCAPE]){
        isRunning = false;
    }

    //process direction
    state = SDL_GetKeyboardState(NULL);
    paddleDir = 0;
    if(state[SDL_SCANCODE_W]){
        paddleDir = -1;
    }
    if(state[SDL_SCANCODE_S]){
        paddleDir = 1;
    } 
}

void Game::UpdateGame(){

    while(!SDL_TICKS_PASSED(SDL_GetTicks(),ticksCounts+16));
    //determine delta time
    float deltaTime = (SDL_GetTicks()-ticksCounts);
    ticksCounts = SDL_GetTicks();
    if(deltaTime > 0.05f){
        deltaTime = 0.05f;
    }
    //update paddle position
    if (paddleDir !=0){
        paddlePos.y += paddleDir*300.0f*deltaTime;
        if(paddlePos.y < (paddleH/2.0f + thickness)){
            paddlePos.y = (paddleH/2.0f + thickness);
        } else if(paddlePos.y > ((768.0f-paddleH/2.0f) + thickness)) {
                paddlePos.y = ((768.0f-paddleH/2.0f) + thickness);
        }
    }

    //update ball position
    ballPos.x += ballVel.x * deltaTime;
    ballPos.y += ballVel.y * deltaTime;
    //check if ball touch the top wall
    if ((ballPos.y <= thickness)&&(ballVel.y < 0.0f)) {
        ballVel.y *= -1;
    }
    //check if ball touch the bottom wall
    if((ballPos.y >= 768-thickness)&&(ballVel.y>0.0f)){
        ballVel.y *= -1;
    }
    //check if ball touch the right wall
    if((ballPos.x >= 1024-thickness)&&(ballVel.x >0.0f)){
        ballVel.x *= -1;
    }
    //check if ball touch the paddle
    bool sameXasPaddle = (ballPos.x <= (paddlePos.x+thickness/2)&&(ballVel.x<0.0f));
    bool betweenYPaddle = (ballPos.y >= (paddlePos.y-paddleH/2))&&(ballPos.y <= (paddlePos.y + paddleH/2));
    if(sameXasPaddle && betweenYPaddle){
        ballVel.x *= -1;
    }

}

void Game::GenerateOutput(){
    //first clear the backbuffer
    SDL_SetRenderDrawColor(
        p_Renderer,
        0,
        0,
        255,
        255
    );
    SDL_RenderClear(p_Renderer);
    

    //draw rectangle
    SDL_SetRenderDrawColor(
        p_Renderer,
        255,
        255,
        255,
        255
    );
    
    //topwall
    SDL_Rect t_wall{
        0,
        0,
        1024,
        thickness
    };
    SDL_RenderFillRect(p_Renderer, &t_wall);

    //bottomwall
    
    SDL_Rect b_wall{
        0,
        768-thickness,
        1024,
        thickness
    };
    SDL_RenderFillRect(p_Renderer, &b_wall);
    //rightwall
    
    SDL_Rect r_wall{
        1024-thickness,
        0,
        thickness,
        768
    };
    SDL_RenderFillRect(p_Renderer, &r_wall);


    //ball
    SDL_Rect ball{
        static_cast<int>(ballPos.x - thickness/2),
        static_cast<int>(ballPos.y - thickness/2),
        thickness,
        thickness
    };
    SDL_RenderFillRect(p_Renderer, &ball);
    //ball
    paddleH = 10*thickness;
    SDL_Rect paddle{
        static_cast<int>(paddlePos.x - thickness/2),
        static_cast<int>(paddlePos.y - paddleH/2),
        thickness,
        paddleH
    };
    SDL_RenderFillRect(p_Renderer, &paddle);





    //swap
    SDL_RenderPresent(p_Renderer);
    return;
}

