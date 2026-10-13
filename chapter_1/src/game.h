#ifndef GAME_H
#define GAME_H

#include <SDL.h>


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

        bool isRunning;


};



#endif


