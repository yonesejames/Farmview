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
    SDL_Texture* seed;
    SDL_Texture* cancel;
    int x;
    int y;
    int selectedItemIndex;
    int Inventory[10];

    bool visible = false;

    ~ItemMenu();

    void setup(SDL_Renderer* renderer, int* items, int x, int y);
    void moveUp();
    void moveDown();
    void draw();


private:
    SDL_Texture* generateTextTexture(TTF_Font* font, SDL_Color color, std::string text);
};

#endif
