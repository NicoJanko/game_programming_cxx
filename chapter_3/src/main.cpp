#include "game.h"
#include <SDL.h>


int main(int /*argc*/, char* /*argv*/[]) {
    Game game;
    if (game.initialize()) {
        game.runLoop();
    }
    game.shutdown();
    return 0;
}
