#include <SDL.h>
#include "game.h"

int main(int /*argc*/, char* /*argv*/[]){
    Game game;
    bool initResult = game.Initialize();
    if (initResult){
        game.RunLoop();
    }
    game.Shutdown();
    return 0;
}
