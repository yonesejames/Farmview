#include "loadScreen.h"

int* LoadScreen::loadScreen(const char* filePath, int time)
/* 
    Function that takes in a filePath to create a texture and render 
    to the screen and a time to allow an amout of milliseconds 
    to delay the texture on screen.
*/
{

    SDL_Surface* mainScreen = SDL_LoadBMP(filePath);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, mainScreen);

    SDL_RenderCopy(Game::renderer, texture, NULL, NULL);

    SDL_RenderPresent(Game::renderer);

    SDL_Delay(time);

    return 0;

}


// Old way of loading screen:
/*
int* LoadScreen::loadScreen(const char* filePath, SDL_Window* window, int time)
{

    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    SDL_Surface* mainScreen = SDL_LoadBMP(filePath);

    //Apply the image
    SDL_BlitSurface(mainScreen, NULL, screenSurface, NULL);

    //Update the surface
    SDL_UpdateWindowSurface(window);

    // Delay for three seconds:
    SDL_Delay(time);

    return 0;

}
*/

