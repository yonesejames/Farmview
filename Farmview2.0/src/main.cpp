#include <SDL.h>
#include "Game.h"

Game* game = { nullptr };

int main(int argc, char* argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    Uint32 delay = (33 / 10) * 10;
    
    game = new Game();

    game->init("Farmview", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 880, false);

    while (game->running())
    {        
        frameStart = SDL_GetTicks(); 
        game->time();

        game->handleEvents();
        game->update();
        game->render();


        // Capping frame rate:
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }

    }

    game->close();

    return 0;
}

