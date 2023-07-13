#ifndef LIFEBAR_H
#define LIFEBAR_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

class LifeBar
{
public:

    int xHunger;
    int yHunger;

    int xSleepy;
    int ySleepy;

    int hunger, hungerMax;
    int sleepy, sleepyMax;

    SDL_Renderer* renderer;
    SDL_Texture* sleepyTextTexture;
    SDL_Rect sleepyTextRect;
    SDL_Texture* hungerTextTexture;
    SDL_Rect hungerTextRect;

    LifeBar();

    void setup(SDL_Renderer* renderer, int xHunger, int yHunger, int xSleeepy, int ySleepy);
    void draw();


private:
};


#endif // !LIFEBAR_H

