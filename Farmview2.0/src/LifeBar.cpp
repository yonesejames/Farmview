#include "LifeBar.h"

LifeBar::LifeBar()
{
    hunger = hungerMax = 100;
    sleepy = sleepyMax = 100;
}

void LifeBar::setup(SDL_Renderer* renderer, int xHunger, int yHunger, int xSleepy, int ySleepy)
{
    this->renderer = renderer;
    this->xHunger = xHunger;
    this->yHunger = yHunger;
    this->xSleepy = xSleepy;
    this->ySleepy = ySleepy;

    std::string sleepyText = "Sleep";
    std::string hungerText = "Hunger";

    TTF_Font* font1 = TTF_OpenFont("assets/Walkway_SemiBold.ttf", 48);
    SDL_Color textColor1 = { 255, 255, 255, 255 };
    SDL_Surface* textSurface1 = TTF_RenderText_Blended(font1, sleepyText.c_str(), textColor1);
    sleepyTextTexture = SDL_CreateTextureFromSurface(renderer, textSurface1);
    SDL_FreeSurface(textSurface1);
    TTF_CloseFont(font1);

    sleepyTextRect.x = xSleepy + 2;
    sleepyTextRect.y = ySleepy + 2;

    SDL_QueryTexture(sleepyTextTexture, NULL, NULL, &sleepyTextRect.w, &sleepyTextRect.h);

    TTF_Font* font2 = TTF_OpenFont("assets/Walkway_SemiBold.ttf", 48);
    SDL_Color textColor2 = { 255, 255, 255, 255 };
    SDL_Surface* textSurface2 = TTF_RenderText_Blended(font2, hungerText.c_str(), textColor2);
    hungerTextTexture = SDL_CreateTextureFromSurface(renderer, textSurface2);
    SDL_FreeSurface(textSurface2);
    TTF_CloseFont(font2);

    hungerTextRect.x = xHunger + 2;
    hungerTextRect.y = yHunger + 2;

    SDL_QueryTexture(hungerTextTexture, NULL, NULL, &hungerTextRect.w, &hungerTextRect.h);
}

void LifeBar::draw()
{

    SDL_Rect borderHunger = { xHunger , yHunger, 302, 52 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &borderHunger);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawRect(renderer, &borderHunger);
    float hF = hunger;
    int hungerBarWidth = ( hF / hungerMax ) * 300;

    if (hungerBarWidth < 0)
    {
        hungerBarWidth = 0;
    }

    SDL_SetRenderDrawColor(renderer, 8, 43, 20, 255);
    SDL_Rect hungerColorBar = { xHunger + 1, yHunger + 1, hungerBarWidth, 50 };
    SDL_RenderFillRect(renderer, &hungerColorBar);
    SDL_RenderCopy(renderer, hungerTextTexture, NULL, &hungerTextRect);


    SDL_Rect borderSleepy = { xSleepy, ySleepy, 302, 52 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &borderSleepy);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawRect(renderer, &borderSleepy);
    float sF = sleepy;
    int sleepyBarWidth = ( sF / sleepyMax ) * 300;

    if (sleepyBarWidth < 0)
    {
        sleepyBarWidth = 0;
    }

    SDL_SetRenderDrawColor(renderer, 8, 43, 20, 255);
    SDL_Rect sleepyColorBar = { xSleepy + 1, ySleepy + 1, sleepyBarWidth, 50 };
    SDL_RenderFillRect(renderer, &sleepyColorBar);
    SDL_RenderCopy(renderer, sleepyTextTexture, NULL, &sleepyTextRect);

}
