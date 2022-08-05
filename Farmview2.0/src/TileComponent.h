#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H


#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <SDL.h>

class TileComponent : public Component
/*
    TileComponent has inherited Component class public parts and creates 
    tiles for the map.
*/
{
public:

    SDL_Texture* texture;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;
    Vector position;

    ~TileComponent()
    /* Destructor that destroys the tile */
    {
        SDL_DestroyTexture(texture);
    }

    // Default constructor:
    TileComponent() = default;

    // Overloaded constructor: 
    TileComponent(int sourceX, int sourceY, int xpos, int ypos, int tileSize, int tileScale, const char* filePath)
    /*
        Constructor that takes in x and y axis for rectangle source of the component, 
        x and y position for the position of the tile, tile size and scale of the tile to 
        also get destination of the tile.
    */
    {
        texture = TextureManager::loadTexture(filePath);

        // Set Vector position to the x and y position arguments:
        position.x = xpos;
        position.y = ypos;

        // Set the SDL_Rect source rectangle to the sourcex and source y arguments:
        sourceRect.x = sourceX;
        sourceRect.y = sourceY;

        // Set rectangle's width and height to tileSize (16px):
        sourceRect.w = tileSize;
        sourceRect.h = tileSize;

        // Set rectangle's destination x and y to xpos and ypos arguments:
        destinationRect.x = xpos;
        destinationRect.y = ypos;

        // Set rectangle's width and height to tileSize * tileScale to get scaled size:
        destinationRect.w = tileSize * tileScale;
        destinationRect.h = tileSize * tileScale;



    }

    void update() override
    /* Function that overrides the "update" function by updatin based on camera view */
    {
        destinationRect.x = position.x - Game::camera.x;
        destinationRect.y = position.y - Game::camera.y;

    }

    void draw() override
    /* Function that overrides the "draw" function by drawing through TextureManager */
    {
        TextureManager::draw(texture, sourceRect, destinationRect, SDL_FLIP_NONE);
    }

    SDL_Rect getTile(int xpos, int ypos)
    {
        position.x = xpos;
        position.y = ypos;

        return destinationRect;
    }

};


#endif

