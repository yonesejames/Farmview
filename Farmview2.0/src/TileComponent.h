#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <SDL.h>

class TileComponent : public Component
{
public:

    SDL_Texture* texture;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;
    Vector position;

    TileComponent() = default;


    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    TileComponent(int sourceX, int sourceY, int xpos, int ypos, int tileSize, int tileScale, const char* filePath)
    {
        texture = TextureManager::loadTexture(filePath);

        position.x = xpos;
        position.y = ypos;

        sourceRect.x = sourceX;
        sourceRect.y = sourceY;
        // 16 px:
        sourceRect.w = tileSize;
        sourceRect.h = tileSize;

        destinationRect.x = xpos;
        destinationRect.y = ypos;
        // 32 px:
        destinationRect.w = tileSize * tileScale;
        destinationRect.h = tileSize * tileScale;

    }

    void update() override
    {
        destinationRect.x = position.x - Game::camera.x;
        destinationRect.y = position.y - Game::camera.y;

    }

    void draw() override
    {
        TextureManager::draw(texture, sourceRect, destinationRect, SDL_FLIP_NONE);
    }

};


#endif

