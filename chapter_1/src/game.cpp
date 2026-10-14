#include "game.h"
#include <cmath>

Game::Game(){
    p_Window = nullptr;

    isRunning = true;

    paddle1.position.x = 0;
    paddle1.position.y = 768/2;
    paddle1.direction = 0;
    paddle1.height = 10*thickness;

    paddle2.position.x = 1024;
    paddle2.position.y = 768/2;
    paddle2.direction = 0;
    paddle2.height = 10*thickness;


    Ball ball1{
        {1024/2,768/2},
        {200,235}
    };
    Ball ball2{
        {1024/2,768/2},
        {-200,-235}
    };

    ballVector.push_back(ball1);
    ballVector.push_back(ball2);


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
    paddle1.direction = 0;
    if(state[SDL_SCANCODE_W]){
        paddle1.direction = -1;
    }
    if(state[SDL_SCANCODE_S]){
        paddle1.direction = 1;
    } 
}

void Game::UpdateGame(){

    while(!SDL_TICKS_PASSED(SDL_GetTicks(),ticksCounts+16));
    //determine delta time
    deltaTime = (SDL_GetTicks()-ticksCounts);
    ticksCounts = SDL_GetTicks();
    if(deltaTime > 0.05f){
        deltaTime = 0.05f;
    }
    //update paddle position
    if (paddle1.direction !=0){
        paddle1.position.y += paddle1.direction*300.0f*deltaTime;
        if(paddle1.position.y < (paddle1.height/2.0f + thickness)){
            paddle1.position.y = (paddle1.height/2.0f + thickness);
        } else if(paddle1.position.y > ((768.0f-paddle1.height/2.0f) + thickness)) {
                paddle1.position.y = ((768.0f-paddle1.height/2.0f) + thickness);
        }
    }
    //check closest ball
    int32_t previousDist = 1024;
    for(int i = 0; i<ballVector.size();i++){
        int32_t Xdist = paddle2.position.x - ballVector.at(i).postion.x;
        if(Xdist<previousDist){
            closetBall = i;
            previousDist = Xdist;
        }
    }
    //check if the ball is up ro down from the paddle
    paddle2.direction =0;
    if(ballVector.at(closetBall).postion.y - (paddle2.position.y - paddle2.height)<0){
        paddle2.direction = -1; // go up
    }
    if(ballVector.at(closetBall).postion.y - (paddle2.position.y + paddle2.height)>0){
        paddle2.direction = 1;
    }

    //update second paddle position automatically 
    if (paddle2.direction !=0){
        paddle2.position.y += paddle2.direction*300.0f*deltaTime;
        if(paddle2.position.y < (paddle2.height/2.0f + thickness)){
            paddle2.position.y = (paddle2.height/2.0f + thickness);
        } else if(paddle2.position.y > ((768.0f-paddle2.height/2.0f) + thickness)) {
                paddle2.position.y = ((768.0f-paddle2.height/2.0f) + thickness);
        }
    }

    //update ball position
    //check if ball touch the paddle
    for(auto& thisBall: ballVector){
        updateBallPos(thisBall);
        checkBallPaddleColision(thisBall, paddle1);
        checkBallPaddleColision(thisBall, paddle2);
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
    

    //ball
    for(auto& thisBall: ballVector){
        SDL_Rect ball{
        static_cast<int>(thisBall.postion.x - thickness/2),
        static_cast<int>(thisBall.postion.y - thickness/2),
        thickness,
        thickness
    };
    SDL_RenderFillRect(p_Renderer, &ball);
    }
    
    //paddle1
    
    SDL_Rect paddleRect1{
        static_cast<int>(paddle1.position.x - thickness/2),
        static_cast<int>(paddle1.position.y - paddle1.height/2),
        thickness,
        paddle1.height
    };
    SDL_RenderFillRect(p_Renderer, &paddleRect1);
    //paddle2
    SDL_Rect paddleRect2{
        static_cast<int>(paddle2.position.x - thickness/2),
        static_cast<int>(paddle2.position.y - paddle2.height/2),
        thickness,
        paddle2.height
    };
    SDL_RenderFillRect(p_Renderer, &paddleRect2);





    //swap
    SDL_RenderPresent(p_Renderer);
    return;
}


void Game::updateBallPos(Ball& ball){
    //update ball position
    ball.postion.x += ball.velocity.x * deltaTime;
    ball.postion.y += ball.velocity.y * deltaTime;
    //check if ball touch the top wall
    if ((ball.postion.y <= thickness)&&(ball.velocity.y < 0.0f)) {
        ball.velocity.y *= -1;
    }
    //check if ball touch the bottom wall
    if((ball.postion.y >= 768-thickness)&&(ball.velocity.y>0.0f)){
        ball.velocity.y *= -1;
    }
    
}

void Game::checkBallPaddleColision(Ball& ball,const Paddle& paddle){
    float yDiff = std::abs(ball.postion.y - paddle.position.y);
    bool betweenPaddle = yDiff <= paddle.height / 2.0f;

    bool collideOnX = std::abs(ball.postion.x - paddle.position.x) <= thickness;

    bool movingToward = (paddle.position.x - ball.postion.x) * ball.velocity.x > 0.0f;
    
    if(betweenPaddle &&collideOnX&&movingToward){
        ball.velocity.x *= -1;
    }
}
