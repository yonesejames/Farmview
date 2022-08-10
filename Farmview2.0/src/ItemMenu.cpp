#include "ItemMenu.h"

ItemMenu::~ItemMenu()
{
    SDL_DestroyTexture(noItem);
    SDL_DestroyTexture(carrot);
    SDL_DestroyTexture(carrotGrowth);
    SDL_DestroyTexture(tomato);
    SDL_DestroyTexture(tomatoGrowth);
    SDL_DestroyTexture(strawberry);
    SDL_DestroyTexture(strawberryGrowth);
    SDL_DestroyTexture(pumpkin);
    SDL_DestroyTexture(pumpkinGrowth);
    SDL_DestroyTexture(corn);
    SDL_DestroyTexture(cornGrowth);
    SDL_DestroyTexture(potato);
    SDL_DestroyTexture(potatoGrowth);
    SDL_DestroyTexture(watermelon);
    SDL_DestroyTexture(watermelonGrowth);
    SDL_DestroyTexture(radish);
    SDL_DestroyTexture(radishGrowth);
    SDL_DestroyTexture(lettuce);
    SDL_DestroyTexture(lettuceGrowth);
    SDL_DestroyTexture(wheat);
    SDL_DestroyTexture(wheatGrowth);
    SDL_DestroyTexture(plum);
    SDL_DestroyTexture(plumGrowth);
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

    carrot = generateTextTexture(font, textColor, "Carrot");
    carrotGrowth = generateTextTexture(font, textColor, "Carrot Seed");

    tomato = generateTextTexture(font, textColor, "Tomato");
    tomatoGrowth = generateTextTexture(font, textColor, "Tomato Seed");

    strawberry = generateTextTexture(font, textColor, "Strawberry");
    strawberryGrowth = generateTextTexture(font, textColor, "Strawberry Seed");

    pumpkin = generateTextTexture(font, textColor, "Pumpkin");
    pumpkinGrowth = generateTextTexture(font, textColor, "Pumpkin Seed");

    corn = generateTextTexture(font, textColor, "Corn");
    cornGrowth = generateTextTexture(font, textColor, "Corn Seed");

    potato = generateTextTexture(font, textColor, "Potato");
    potatoGrowth = generateTextTexture(font, textColor, "Potato Seed");

    watermelon = generateTextTexture(font, textColor, "Watermelon");
    watermelonGrowth = generateTextTexture(font, textColor, "Watermelon Seed");

    radish = generateTextTexture(font, textColor, "Radish");
    radishGrowth = generateTextTexture(font, textColor, "Radish Seed");

    lettuce = generateTextTexture(font, textColor, "Lettuce");
    lettuceGrowth = generateTextTexture(font, textColor, "Lettuce Seed");

    wheat = generateTextTexture(font, textColor, "Wheat");
    wheatGrowth = generateTextTexture(font, textColor, "Wheat Seed");

    plum = generateTextTexture(font, textColor, "Plum");
    plumGrowth = generateTextTexture(font, textColor, "Plum Seed");

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
            tempTexture = carrot;
        }
        if (items[i] == 2)
        {
            tempTexture = carrotGrowth;
        }
        if (items[i] == 3)
        {
            tempTexture = tomato;
        }
        if (items[i] == 4)
        {
            tempTexture = tomatoGrowth;
        }
        if (items[i] == 5)
        {
            tempTexture = strawberry;
        }
        if (items[i] == 6)
        {
            tempTexture = strawberryGrowth;
        }
        if (items[i] == 7)
        {
            tempTexture = pumpkin;
        }
        if (items[i] == 8)
        {
            tempTexture = pumpkinGrowth;
        }
        if (items[i] == 9)
        {
            tempTexture = corn;
        }
        if (items[i] == 10)
        {
            tempTexture = cornGrowth;
        }
        if (items[i] == 11)
        {
            tempTexture = potato;
        }
        if (items[i] == 12)
        {
            tempTexture = potatoGrowth;
        }
        if (items[i] == 13)
        {
            tempTexture = watermelon;
        }
        if (items[i] == 14)
        {
            tempTexture = watermelonGrowth;
        }
        if (items[i] == 15)
        {
            tempTexture = radish;
        }
        if (items[i] == 16)
        {
            tempTexture = radishGrowth;
        }
        if (items[i] == 17)
        {
            tempTexture = lettuce;
        }
        if (items[i] == 18)
        {
            tempTexture = lettuceGrowth;
        }
        if (items[i] == 19)
        {
            tempTexture = wheat;
        }
        if (items[i] == 20)
        {
            tempTexture = wheatGrowth;
        }
        if (items[i] == 21)
        {
            tempTexture = plum;
        }
        if (items[i] == 22)
        {
            tempTexture = plumGrowth;
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
