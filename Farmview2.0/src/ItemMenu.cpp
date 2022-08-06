#include "ItemMenu.h"

ItemMenu::~ItemMenu()
{
    SDL_DestroyTexture(noItem);
    SDL_DestroyTexture(seed);
    SDL_DestroyTexture(cancel);
}

void ItemMenu::setup(SDL_Renderer* renderer, int* items, int x, int y)
{

    this->renderer = renderer;
    this->items = items;
    this->x = x;
    this->y = y;

    TTF_Font* font = TTF_OpenFont("assets/Walkway_SemiBold.ttf", 48);
    SDL_Color textColor = { 255, 255, 255, 255 };

    noItem = generateTextTexture(font, textColor, "--");
    seed = generateTextTexture(font, textColor, "Seed");
    cancel = generateTextTexture(font, textColor, "Cancel");

    TTF_CloseFont(font);
}

void ItemMenu::moveUp()
{
    selectedItemIndex--;
    if (selectedItemIndex < 0)
    {
        selectedItemIndex = 0;
    }
}

void ItemMenu::moveDown()
{
    selectedItemIndex++;
    if (selectedItemIndex > 10)
    {
        selectedItemIndex = 10;
    }
}

void ItemMenu::draw()
{
    if (!visible)
    {
        return;
    }

    SDL_Rect itemButton = { x, y, 700, 50 };
    for (int i = 0; i < 10; i++)
    {
        itemButton.y = y + (i * itemButton.h);

        if (selectedItemIndex == i)
        {
            SDL_SetRenderDrawColor(renderer, 0, 80, 37, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 8, 43, 20, 255);
        }

        SDL_RenderFillRect(renderer, &itemButton);

        SDL_Texture* tempTexture = noItem;
        if (items[i] == 1)
        {
            tempTexture = seed;
        }

        SDL_Rect textRect;
        textRect.x = itemButton.x + 2;
        textRect.y = itemButton.y + 2;

        SDL_QueryTexture(tempTexture, NULL, NULL, &textRect.w, &textRect.h);

        SDL_RenderCopy(renderer, tempTexture, NULL, &textRect);
    }

    if (selectedItemIndex == 10)
    {
        SDL_SetRenderDrawColor(renderer, 0, 80, 37, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 8, 43, 20, 255);
    }

    itemButton.y = y + (10 * itemButton.h);
    SDL_RenderFillRect(renderer, &itemButton);

    SDL_Rect textRect;
    textRect.x = itemButton.x + 2;
    textRect.y = itemButton.y + 2;

    SDL_QueryTexture(cancel, NULL, NULL, &textRect.w, &textRect.h);

    SDL_RenderCopy(renderer, cancel, NULL, &textRect);

}


SDL_Texture* ItemMenu::generateTextTexture(TTF_Font* font, SDL_Color color, std::string text)
{
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    return textTexture;
}
