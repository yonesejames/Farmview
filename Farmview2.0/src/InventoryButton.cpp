#include "InventoryButton.h"

void InventoryButton::setup(SDL_Renderer* renderer, SDL_Rect buttonRect, std::string text)
{
    this->renderer = renderer;
    this->buttonRect = buttonRect;

    TTF_Font* font = TTF_OpenFont("assets/Walkway_SemiBold.ttf", 48);
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    textRect.x = buttonRect.x + 2;
    textRect.y = buttonRect.y + 2;

    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

    selected = false;
    
}

void InventoryButton::draw()
{
    if (selected)
    {
        SDL_SetRenderDrawColor(renderer, 0, 80, 37, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 8, 43, 20, 255);
    }

    SDL_RenderFillRect(renderer, &buttonRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &buttonRect);

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}

InventoryButton::~InventoryButton()
{
    if (textTexture != NULL)
    {
        SDL_DestroyTexture(textTexture);
    }
}
