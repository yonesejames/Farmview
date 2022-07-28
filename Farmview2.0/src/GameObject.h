#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "Game.h"

class GameObject
/* 
    GameObject creates inherited methods and attributes -- 
    Not supported anymore, so may delete later.
*/
{
public:
    GameObject(const char* textureSheet, int x, int y);
    ~GameObject();

    void update();
    void render();

private:
    int xpos;
    int ypos;

    SDL_Texture* objectTexture;
    SDL_Rect sourceRect, destinationRect;


};


#endif

