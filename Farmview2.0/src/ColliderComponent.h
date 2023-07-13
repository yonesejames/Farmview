#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H


#include <string>
#include <SDL2/SDL.h>>
#include "Components.h"
#include "TextureManager.h"
#include <iostream>

class ColliderComponent : public Component
/*
    ColliderComponent has inherited Component class public parts and creates 
    collider objects with source and destination rectangles and texture. 
    Adds "TranformComponent" to colliders
*/
{
public: 
    // Create rectangle collider:
    SDL_Rect collider;

    // Create string tag:
    std::string tag;

    SDL_Texture* texture;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;

    // Creates "TransformComponent" object:
    TransformComponent* transform;

    // Overloaded constructors:
    ColliderComponent(std::string t)
    /* Constructor that takes in one argument to tag a collider. */
    {
        tag = t;
    }

    ColliderComponent(std::string t, int xpos, int ypos, int size)
    /*
        Constructor that takes an argument to tag a collider, 
        int x and y position of the collider and size of the collider.
    */

    {
        tag = t;
        collider.x = xpos;
        collider.y = ypos;

        collider.h = size;
        collider.w = size;
    }

    void init() override
    /* 
        Function that overrides "init" function by adding the "TransformComponent" if entity does not have it
        then allocates the "TransformComponent" to transform variable with "getComponent" function. 
        Add texture to collision (currently black space) and adding a rectangle to the collision starting from
        (0,0) x and y axis and adding width of 16 pixels and height of 16 pixels.
        Finally, assigning x and y coordinates and size of the collider to SDL_Rect destination rectangle 
    
    */
    {
        if (!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }

        transform = &entity->getComponent<TransformComponent>();

        texture = TextureManager::loadTexture("assets/collisionTexture2.png");

        // Magic numbers (may optimize at a later date to have input instead)
        // currently map is in 16 x 16 pixels:
        sourceRect = { 0, 0, 16, 16 };
        destinationRect = { collider.x, collider.y, collider.w, collider.h };
    }

    void update() override
    /*
        Function that overrides the "update" function by re-assigning position of
        collider using x and y coordinates and width and height of the collider 
        if the tag is not "terrain". If the tag is terrain then reassigning destination
        rectangles x and y coordinates.
    */
    {
        if (tag != "terrain")
        {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
        }

        destinationRect.x = collider.x - Game::camera.x;

        destinationRect.y = collider.y - Game::camera.y;
    }

    void draw() override
    /* Function that overrides the "draw" function by drawing texture of colliders */
    {
        TextureManager::draw(texture, sourceRect, destinationRect, SDL_FLIP_NONE);
    }


};


#endif

