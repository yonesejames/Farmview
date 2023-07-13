#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H


#include <SDL2/SDL.h>
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
    int wateringIndex = 0;
    int item = 0;
    bool readyToPick = false;

    int firstGrowth = SDL_GetTicks() + 10000;
    int secondGrowth = SDL_GetTicks() + 20000;
    int thirdGrowth = SDL_GetTicks() + 30000;
    int fourthGrowth = SDL_GetTicks() + 40000;
    int fifthGrowth = SDL_GetTicks() + 50000;
    int sixthGrowth = SDL_GetTicks() + 60000;

    //PlantKeyboardController* pKC;
    //ItemMenu* itemMenu;

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

        Animation wateringForward = Animation(8, 2, 300);
        Animation wateringBackward = Animation(9, 2, 300);
        Animation wateringRight = Animation(10, 2, 300);
        Animation wateringLeft = Animation(11, 2, 300);

        animations.emplace("wateringForward", wateringForward);
        animations.emplace("wateringBackward", wateringBackward);
        animations.emplace("wateringRight", wateringRight);
        animations.emplace("wateringLeft", wateringLeft);

        // When game starts the sprite will show up like this:
        Play("idleForward");

        setTexture(filePath);

        sizeWidth = sizeW;
        sizeHeight = sizeH;

    }

    SpriteComponent(const char* filePath, bool isGrowing, int i)
    /*
        Constructor that takes in a filepath to render the sprite on screen,
        isAnimated will allow the sprite to animate, int sizeW and sizeH for size of the
        sprite.
    */
    {
        grow = isGrowing;

        if (i == 2)
        {
            Animation carrotGrowth = Animation(0, 6, 500);

            growth.emplace("carrotGrowth", carrotGrowth);

            // When game starts the sprite will show up like this:
            playGrowth("carrotGrowth");

            setTexture(filePath);
            
        }
        if (i == 4)
        {
            Animation tomatoGrowth = Animation(0, 6, 500);

            growth.emplace("tomatoGrowth", tomatoGrowth);

            // When game starts the sprite will show up like this:
            playGrowth("tomatoGrowth");

            setTexture(filePath);

        }
        if (i == 6)
        {
            Animation strawberryGrowth = Animation(0, 6, 500);

            growth.emplace("strawberryGrowth", strawberryGrowth);

            // When game starts the sprite will show up like this:
            playGrowth("strawberryGrowth");

            setTexture(filePath);

        }
        if (i == 8)
        {
            Animation pumpkinGrowth = Animation(0, 6, 500);

            growth.emplace("pumpkinGrowth", pumpkinGrowth);

            // When game starts the sprite will show up like this:
            playGrowth("pumpkinGrowth");

            setTexture(filePath);
        }
        if (i == 10)
        {
            Animation cornGrowth = Animation(0, 6, 500);

            growth.emplace("cornGrowth", cornGrowth);

            // When game starts the sprite will show up like this:
            playGrowth("cornGrowth");

            setTexture(filePath);
        }
        if (i == 12)
        {
            Animation potatoGrowth = Animation(0, 6, 500);

            growth.emplace("potatoGrowth", potatoGrowth);

            // When game starts the sprite will show up like this:
            playGrowth("potatoGrowth");

            setTexture(filePath);
        }
        if (i == 14)
        {
            Animation watermelonGrowth = Animation(0, 6, 500);

            growth.emplace("watermelonGrowth", watermelonGrowth);

            // When game starts the sprite will show up like this:
            playGrowth("watermelonGrowth");

            setTexture(filePath);
        }
        if (i == 16)
        {
            Animation radishGrowth = Animation(0, 6, 500);

            growth.emplace("radishGrowth", radishGrowth);

            // When game starts the sprite will show up like this:
            playGrowth("radishGrowth");

            setTexture(filePath);
        }
        if (i == 18)
        {
            Animation lettuceGrowth = Animation(0, 6, 500);

            growth.emplace("lettuceGrowth", lettuceGrowth);

            // When game starts the sprite will show up like this:
            playGrowth("lettuceGrowth");

            setTexture(filePath);
        }
        if (i == 20)
        {
            Animation wheatGrowth = Animation(0, 6, 500);

            growth.emplace("wheatGrowth", wheatGrowth);

            // When game starts the sprite will show up like this:
            playGrowth("wheatGrowth");

            setTexture(filePath);
        }
        if (i == 22)
        {
            Animation plumGrowth = Animation(0, 6, 500);

            growth.emplace("plumGrowth", plumGrowth);

            // When game starts the sprite will show up like this:
            playGrowth("plumGrowth");

            setTexture(filePath);
        }

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


        if (grow)
        {
            auto currentTime = SDL_GetTicks();

            if (currentTime > firstGrowth)
            {
                sourceRectangle.x = sourceRectangle.w * 0;
                readyToPick = false;
            }
            if (currentTime > secondGrowth)
            {
                sourceRectangle.x = sourceRectangle.w * 1;
                readyToPick = false;
            }
            if (currentTime > thirdGrowth)
            {
                sourceRectangle.x = sourceRectangle.w * 2;
                readyToPick = false;
            }
            if (currentTime > fourthGrowth)
            {
                sourceRectangle.x = sourceRectangle.w * 3;
                readyToPick = false;
            }
            if (currentTime > fifthGrowth)
            {
                sourceRectangle.x = sourceRectangle.w * 4;
                readyToPick = false;
            }
            if (currentTime > sixthGrowth)
            {
                sourceRectangle.x = sourceRectangle.w * 5;
                checkReady();
                
            }

            //sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
            
            sourceRectangle.y = animationIndex * transform->height;

            destinationRectangle.x = static_cast<int>(transform->position.x) - Game::camera.x;
            destinationRectangle.y = static_cast<int>(transform->position.y) - Game::camera.y;
            destinationRectangle.w = transform->width * transform->scale;
            destinationRectangle.h = transform->height * transform->scale;
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

    void checkReady()
    {
        if (sourceRectangle.x == sourceRectangle.w * 5)
        {
            readyToPick = true;
        }
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

