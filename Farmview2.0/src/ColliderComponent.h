#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <string>
#include <SDL.h>
#include "Components.h"
#include "TextureManager.h"

class ColliderComponent : public Component
{
public: 
    SDL_Rect collider;
    std::string tag;

    SDL_Texture* texture;
    SDL_Rect sourceRect;
    SDL_Rect destinationRect;

    TransformComponent* transform;

    ColliderComponent(std::string t)
    {
        tag = t;
    }

    ColliderComponent(std::string t, int xpos, int ypos, int size)
    {
        tag = t;
        collider.x = xpos;
        collider.y = ypos;

        collider.h = size;
        collider.w = size;
    }

    void init() override
    {
        if (!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent <TransformComponent>();
        }

        transform = &entity->getComponent<TransformComponent>();

        texture = TextureManager::loadTexture("assets/collisionTexture2.png");
        sourceRect = { 0, 0, 16, 16 };
        destinationRect = { collider.x, collider.y, collider.w, collider.h };

    }

    void update() override
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
    {
        TextureManager::draw(texture, sourceRect, destinationRect, SDL_FLIP_NONE);
    }


};

#endif

