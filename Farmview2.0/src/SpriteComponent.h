#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL.h>
#include "Components.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>
#include <iostream>

class SpriteComponent : public Component
/* Sprites are images that represent game assets. */
{
public:
    int animationIndex = 0;

    // Sorted associative container that contains key-value pairs with unique keys.
    // Implemented by red–black trees (self-balancing binary search tree. 
    // Each node stores an extra bit representing "color" ("red" or "black"), 
    // used to ensure that the tree remains balanced during insertions and deletions):
    std::map<const char*, Animation> animations;

    // Flips image:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    int sizeWidth;
    int sizeHeight;

    ~SpriteComponent()
    /* Deconstructor that destroys the sprite */
    {
        SDL_DestroyTexture(texture);
    }

    // Default constructor:
    SpriteComponent() = default;

    //Overloaded Constructors:
    SpriteComponent(const char* filePath)
    /*
        Constructor that takes in 
    */
    {
        setTexture(filePath);
    }

    SpriteComponent(const char* filePath, bool isAnimated, int sizeW, int sizeH)
    /*
        Constructor that takes in 
    */
    {
        animated = isAnimated;

        Animation idleForward = Animation(0, 3, 400);
        Animation idleBackward = Animation(1, 3, 400);
        Animation idleRight = Animation(2, 3, 400);
        Animation idleLeft = Animation(3, 3, 400);

        Animation walkForward = Animation(4, 3, 300);
        Animation walkBackward = Animation(5, 3, 300);
        Animation walkRight = Animation(6, 3, 300);
        Animation walkLeft = Animation(7, 3, 300);

        animations.emplace("idleForward", idleForward);
        animations.emplace("idleBackward", idleBackward);
        animations.emplace("idleRight", idleRight);
        animations.emplace("idleLeft", idleLeft);

        animations.emplace("walkForward", walkForward);
        animations.emplace("walkBackward", walkBackward);
        animations.emplace("walkRight", walkRight);
        animations.emplace("walkLeft", walkLeft);

        Play("idleForward");

        setTexture(filePath);

        sizeWidth = sizeW;
        sizeHeight = sizeH;

    }

    void setTexture(const char* filePath)
    /*
        Function that 
    */
    {
        texture = TextureManager::loadTexture(filePath);
    }


    void init() override
    /*
        Function that overrides the "init" function by 
    */
    {
        // Position references the entity that this component belongs to 
        // and uses PositionComponent: 
        transform = &entity->getComponent<TransformComponent>();
    
        // Initializing source size and positon:
        sourceRectangle.x = 0;
        sourceRectangle.y = 0;
        sourceRectangle.w = transform->width;
        sourceRectangle.h = transform->height;

        // Initializing destination size for the source:
        destinationRectangle.w = sizeWidth;
        destinationRectangle.h = sizeHeight;

        std::cout << sizeWidth << ", " << sizeHeight << std::endl;
        std::cout << destinationRectangle.w << ", " << destinationRectangle.h << std::endl;

    }

    void update() override
    /*
        Function that overrides the "update" function by 
    */
    {

        if (animated)
        {
            sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }

        sourceRectangle.y = animationIndex * transform->height;

        destinationRectangle.x = static_cast<int>(transform->position.x) - Game::camera.x;
        destinationRectangle.y = static_cast<int>(transform->position.y) - Game::camera.y;
        destinationRectangle.w = transform->width * transform->scale;
        destinationRectangle.h = transform->height * transform->scale;
    }

    void draw() override
    /*
        Function that overrides the "draw" function by 
    */
    {
        TextureManager::draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
    }

    void Play(const char* animationName)
    /*
        Function that 
    */
    {
        frames = animations[animationName].frames;
        animationIndex = animations[animationName].index;
        speed = animations[animationName].speed;
    }

private:
    //
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect sourceRectangle, destinationRectangle;

    bool animated = false;
    int frames = 0;
    // Delay between frames in milliseconds:
    int speed = 100;
};


#endif