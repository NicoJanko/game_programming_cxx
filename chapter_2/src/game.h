#ifndef GAME_H
#define GAME_H

#include <SDL.h>

class Game {
    public:
        Game();
        ~Game();

        bool initialize();
        void runLoop();

        void shutdown();
    
        private:
            void processInput();
            void updateGame();
            void generateOutput();

};


#endif
