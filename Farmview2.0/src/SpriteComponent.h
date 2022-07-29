#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H


#include <SDL.h>
#include "Components.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>

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

private:
    // Creates "TransformComponent" object:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect sourceRectangle, destinationRectangle;

    bool animated = false;
    int frames = 0;
    // Delay between frames in milliseconds:
    int speed = 100;

    int xpos;
    int ypos;
};


#endif

