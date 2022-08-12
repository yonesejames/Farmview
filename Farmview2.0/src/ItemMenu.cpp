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

        if (buttonVisible == true)
        {
            if (items[i] == 1 || items[i] == 3 || items[i] == 5
                || items[i] == 7 || items[i] == 9 || items[i] == 11 || items[i] == 13
                || items[i] == 15 || items[i] == 17 || items[i] == 19 || items[i] == 21)
            {
                TTF_Font* font = TTF_OpenFont("assets/Walkway_SemiBold.ttf", 48);
                SDL_Color textColor = { 255, 255, 255, 255 };
                SDL_Texture* eat;
                SDL_Rect eatTextRect;
                eat = generateTextTexture(font, textColor, "Eat");
                SDL_Rect eatButton = { x + 700, y, 200, 50 };

                eatTextRect.x = eatButton.x + 2;
                eatTextRect.y = eatButton.y + 2;

                SDL_QueryTexture(eat, NULL, NULL, &eatTextRect.w, &eatTextRect.h);

                SDL_RenderCopy(renderer, eat, NULL, &eatTextRect);

                SDL_RenderFillRect(renderer, &eatButton);

                eatTextRect.x = eatButton.x + 2;
                eatTextRect.y = eatButton.y + 2;

                SDL_QueryTexture(eat, NULL, NULL, &eatTextRect.w, &eatTextRect.h);

                SDL_RenderCopy(renderer, eat, NULL, &eatTextRect);

                if (Game::event.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x = Game::event.button.x;
                    int y = Game::event.button.y;

                    if (x >= eatButton.x && x <= eatButton.x + eatButton.w && y >= eatButton.y && eatButton.y + eatButton.h)
                    {
                        Game* game = new Game();
                        game->eatCrop(items[i]);
                    }
                }

            }

            if (items[i] == 2 || items[i] == 4 || items[i] == 6
                || items[i] == 8 || items[i] == 10 || items[i] == 12 || items[i] == 14
                || items[i] == 16 || items[i] == 18 || items[i] == 20 || items[i] == 22)
            {
                TTF_Font* font = TTF_OpenFont("assets/Walkway_SemiBold.ttf", 48);
                SDL_Color textColor = { 255, 255, 255, 255 };
                SDL_Texture* plant;
                SDL_Rect plantTextRect;
                plant = generateTextTexture(font, textColor, "Plant");
                SDL_Rect plantButton = { x + 700, y, 200, 50 };

                plantTextRect.x = plantButton.x + 2;
                plantTextRect.y = plantButton.y + 2;

                SDL_QueryTexture(plant, NULL, NULL, &plantTextRect.w, &plantTextRect.h);

                SDL_RenderCopy(renderer, plant, NULL, &plantTextRect);

                SDL_RenderFillRect(renderer, &plantButton);

                plantTextRect.x = plantButton.x + 2;
                plantTextRect.y = plantButton.y + 2;

                SDL_QueryTexture(plant, NULL, NULL, &plantTextRect.w, &plantTextRect.h);

                SDL_RenderCopy(renderer, plant, NULL, &plantTextRect);

                if (Game::event.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x = Game::event.button.x;
                    int y = Game::event.button.y;

                    if (x >= plantButton.x && x <= plantButton.x + plantButton.w && y >= plantButton.y && plantButton.y + plantButton.h)
                    {
                        Game* game = new Game();
                        game->useItem();
                    }
                }
            }

            if (items[i] == 1 || items[i] == 3 || items[i] == 5
                || items[i] == 7 || items[i] == 9 || items[i] == 11 || items[i] == 13
                || items[i] == 15 || items[i] == 17 || items[i] == 19 || items[i] == 21
                || items[i] == 2 || items[i] == 4 || items[i] == 6
                || items[i] == 8 || items[i] == 10 || items[i] == 12 || items[i] == 14
                || items[i] == 16 || items[i] == 18 || items[i] == 20 || items[i] == 22)
            {
                TTF_Font* font = TTF_OpenFont("assets/Walkway_SemiBold.ttf", 48);
                SDL_Color textColor = { 255, 255, 255, 255 };
                SDL_Texture* drop;
                SDL_Rect dropTextRect;
                drop = generateTextTexture(font, textColor, "Drop");
                SDL_Rect dropButton = { x + 900, y, 200, 50 };

                dropTextRect.x = dropButton.x + 2;
                dropTextRect.y = dropButton.y + 2;

                SDL_QueryTexture(drop, NULL, NULL, &dropTextRect.w, &dropTextRect.h);

                SDL_RenderCopy(renderer, drop, NULL, &dropTextRect);

                SDL_RenderFillRect(renderer, &dropButton);

                dropTextRect.x = dropButton.x + 2;
                dropTextRect.y = dropButton.y + 2;

                SDL_QueryTexture(drop, NULL, NULL, &dropTextRect.w, &dropTextRect.h);

                SDL_RenderCopy(renderer, drop, NULL, &dropTextRect);

                if (Game::event.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x = Game::event.button.x;
                    int y = Game::event.button.y;

                    if (x >= dropButton.x && x <= dropButton.x + dropButton.w && y >= dropButton.y && dropButton.y + dropButton.h)
                    {
                        Game* game = new Game();
                        game->useItem();

                    }
                }
            }

        }        
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


SDL_Texture* ItemMenu::generateTextTexture(TTF_Font* font, SDL_Color color, std::string t)
{
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, t.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    return textTexture;
}
