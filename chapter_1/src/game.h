#ifndef GAME_H
#define GAME_H

#include <SDL.h>

struct Vector2
    {
        float x;
        float y;
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
        void GenerateOutput();

        SDL_Window* p_Window;
        SDL_Renderer* p_Renderer;

        bool isRunning;
        const int thickness = 15;
        Vector2 paddlePos;
        int8_t paddleDir;
        uint16_t paddleH;

        Vector2 ballPos;
        Vector2 ballVel;

        Uint32 ticksCounts;


};



#endif


