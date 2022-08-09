#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H


#include <SDL.h>
#include "Components.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>
#include <string>

class SpriteComponent : public Component
/* Sprites are images that represent game assets. */
{
public:
    int animationIndex = 0;
    int growthIndex = 0;

    // Sorted associative container that contains key-value pairs with unique keys.
    // Implemented by red–black trees (self-balancing binary search tree. 
    // Each node stores an extra bit representing "color" ("red" or "black"), 
    // used to ensure that the tree remains balanced during insertions and deletions):
    std::map<const char*, Animation> animations;
    std::map<const char*, Animation> growth;

    // Flips image:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    int sizeWidth;
    int sizeHeight;

    SDL_Rect sourceRectangle, destinationRectangle;

    ~SpriteComponent()
    /* Destructor that destroys the sprite */
    {
        SDL_DestroyTexture(texture);
    }

    // Default constructor:
    SpriteComponent() = default;

    // Overloaded constructors:
    SpriteComponent(const char* filePath)
    /* Constructor that takes in in a filepath to render the sprite on screen */
    {
        setTexture(filePath);
    }

    SpriteComponent(const char* filePath, int x, int y)
    /* Constructor that takes in in a filepath to render the sprite on screen */
    {
        setTexture(filePath);
        xpos = x;
        ypos = y;
    }

    SpriteComponent(const char* filePath, bool isAnimated, int sizeW, int sizeH)
    /*
        Constructor that takes in a filepath to render the sprite on screen, 
        isAnimated will allow the sprite to animate, int sizeW and sizeH for size of the
        sprite.
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

        // When game starts the sprite will show up like this:
        Play("idleForward");

        setTexture(filePath);

        sizeWidth = sizeW;
        sizeHeight = sizeH;

    }

    SpriteComponent(const char* filePath, bool isGrowing)
        /*
            Constructor that takes in a filepath to render the sprite on screen,
            isAnimated will allow the sprite to animate, int sizeW and sizeH for size of the
            sprite.
        */
    {
        grow = isGrowing;

        /*
        Animation growing1 = Animation(0, 1, 500);
        Animation growing2= Animation(1, 1, 500);
        Animation growing3 = Animation(2, 1, 500);
        Animation growing4 = Animation(3, 1, 500);
        Animation growing5 = Animation(4, 1, 500);
        Animation growing6 = Animation(5, 1, 500);

        growth.emplace("growing1", growing1);
        growth.emplace("growing2", growing2);
        growth.emplace("growing3", growing3);
        growth.emplace("growing4", growing4);
        growth.emplace("growing5", growing5);
        growth.emplace("growing6", growing6);
        */

        Animation growing1 = Animation(0, 6, 500);
        
        growth.emplace("growing1", growing1);

        // When game starts the sprite will show up like this:
        playGrowth("growing1");

        setTexture(filePath);

    }

    void setTexture(const char* filePath)
    /* Function that creates a texture from filePath */
    {
        texture = TextureManager::loadTexture(filePath);
    }

    void init() override
    /*
        Function that overrides the "init" function by creating a transform object, 
        initializing the source's size and position of the sprite and the size of 
        the destination.
    */
    {
        // Transform assigns a referenced entity to the TransformComponent:
        transform = &entity->getComponent<TransformComponent>();
    
        // Initializing source size:
        sourceRectangle.x = 0;
        sourceRectangle.y = 0;
        sourceRectangle.w = transform->width;
        sourceRectangle.h = transform->height;

        // Initializing destination size for the source:
        destinationRectangle.w = sizeWidth;
        destinationRectangle.h = sizeHeight;

    }

    void update() override
    /*
        Function that overrides the "update" function by animating sprite if animated is
        true and updated sprite by movement using transform.
    */
    {

        if (animated)
        {
            sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }

        if (animated)
        {
            sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }

        if (grow)
        {
            sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }

        if (grow)
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
        Function that overrides the "draw" function by drawing sprite from texture.
    */
    {
        TextureManager::draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
    }

    void Play(const char* animationName)
    /* Function that plays the animation based on frames, index, and speed */
    {
        frames = animations[animationName].frames;
        animationIndex = animations[animationName].index;
        speed = animations[animationName].speed;
    }

    void playGrowth(const char* growthName)
    /* Function that plays the animation based on frames, index, and speed */
    {
        frames = growth[growthName].frames;
        growthIndex = growth[growthName].index;
        speed = growth[growthName].speed;
    }


private:
    // Creates "TransformComponent" object:
    TransformComponent* transform;
    SDL_Texture* texture;

    bool animated = false;
    bool grow = false;
    int frames = 0;
    // Delay between frames in milliseconds:
    int speed = 100;

    int xpos;
    int ypos;
};


#endif

