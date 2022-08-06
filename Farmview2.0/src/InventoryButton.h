#ifndef INVENTORYBUTTON_H
#define INVENTORYBUTTON_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class InventoryButton
{
public:
    SDL_Renderer* renderer;
    SDL_Rect buttonRect;
    SDL_Texture* textTexture;
    SDL_Rect textRect;

    bool selected;

    void setup(SDL_Renderer* renderer, SDL_Rect buttonRect, std::string text);
    void draw();

    ~InventoryButton();

};


#endif
 