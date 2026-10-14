#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>

struct Vector2
    {
        float x;
        float y;
    };

struct Ball {
    Vector2 postion;
    Vector2 velocity;
};

struct Paddle{
    Vector2 position;
    int8_t direction;
    uint16_t height;
};

class Game {
    public:
        Game();

        bool Initialize();
        void RunLoop();

        void Shutdown();

    private:
        void ProcessInput();
        void UpdateGame();
        float deltaTime;
        void GenerateOutput();
        void updateBallPos(Ball& ball);
        void checkBallPaddleColision(Ball& ball,const Paddle& paddle);

        SDL_Window* p_Window;
        SDL_Renderer* p_Renderer;

        bool isRunning;
        const int thickness = 15;
        Paddle paddle1;
        Paddle paddle2;
        uint8_t closetBall;
        


        std::vector<Ball> ballVector;

        Vector2 ballPos;
        Vector2 ballVel;

        Uint32 ticksCounts;


};



#endif


