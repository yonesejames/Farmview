#include "GameObject.h"
#include "TextureManager.h"

GameObject::~GameObject()
{

}


GameObject::GameObject(const char* textureSheet, int x, int y)
/* Creates game objects out of textures */
{
    objectTexture = TextureManager::loadTexture(textureSheet);

    xpos = x;
    ypos = y;
}

void GameObject::update()
/* 
    Updates game objects based on size (w and h) and placement (x and y) with 
    destination on screen and the source (the object itself)
*/
{
    xpos++;
    ypos++;

    sourceRect.h = 16;
    sourceRect.w = 16;
    sourceRect.x = 0;
    sourceRect.y = 0;

    destinationRect.h = sourceRect.h;
    destinationRect.w = sourceRect.w;
    destinationRect.x = xpos;
    destinationRect.y = ypos;

}

void GameObject::render()
/* Renders game objects */
{
    SDL_RenderCopy(Game::renderer, objectTexture, &sourceRect, &destinationRect);
}