#ifndef ITEMMENU_H
#define ITEMMENU_H


#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class ItemMenu
{
public:
    SDL_Renderer* renderer;
    int* items;
    SDL_Texture* noItem;
    SDL_Texture* carrot;
    SDL_Texture* carrotGrowth;
    SDL_Texture* tomato;
    SDL_Texture* tomatoGrowth;
    SDL_Texture* strawberry;
    SDL_Texture* strawberryGrowth;
    SDL_Texture* pumpkin;
    SDL_Texture* pumpkinGrowth;
    SDL_Texture* corn;
    SDL_Texture* cornGrowth;
    SDL_Texture* potato;
    SDL_Texture* potatoGrowth;
    SDL_Texture* watermelon;
    SDL_Texture* watermelonGrowth;
    SDL_Texture* radish;
    SDL_Texture* radishGrowth;
    SDL_Texture* lettuce;
    SDL_Texture* lettuceGrowth;
    SDL_Texture* wheat;
    SDL_Texture* wheatGrowth;
    SDL_Texture* plum;
    SDL_Texture* plumGrowth;
    SDL_Texture* cancel;
    int x;
    int y;
    int selectedItemIndex;
    int Inventory[10];

    bool visible = false;

    ItemMenu(){};
    ~ItemMenu();

    void setup(SDL_Renderer* renderer, int* items, int x, int y);
    void moveUp();
    void moveDown();
    void draw();


private:
    SDL_Texture* generateTextTexture(TTF_Font* font, SDL_Color color, std::string text);
};

#endif
