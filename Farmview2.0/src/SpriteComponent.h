#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL.h>
#include "Components.h"
#include "TextureManager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component
{
public:
    int animationIndex = 0;

    std::map<const char*, Animation> animations;

    SpriteComponent() = default;

    // Flips image:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }

    SpriteComponent(const char* filePath)
    {
        setTexture(filePath);
    }

    SpriteComponent(const char* filePath, bool isAnimated)
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
    }

    void setTexture(const char* filePath)
    {
        texture = TextureManager::loadTexture(filePath);
    }


    void init() override
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
        destinationRectangle.w = 100;
        destinationRectangle.h = 100;
    }

    void update() override
    {

        if (animated)
        {
            sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }

        sourceRectangle.y = animationIndex * transform->height;

        destinationRectangle.x = static_cast<int>(transform->position.x);
        destinationRectangle.y = static_cast<int>(transform->position.y);
        destinationRectangle.w = transform->width * transform->scale;
        destinationRectangle.h = transform->height * transform->scale;
    }

    void draw() override
    {
        TextureManager::draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
    }

    void Play(const char* animationName)
    {
        frames = animations[animationName].frames;
        animationIndex = animations[animationName].index;
        speed = animations[animationName].speed;
    }

private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect sourceRectangle, destinationRectangle;

    bool animated = false;
    int frames = 0;
    // Delay between frames in milliseconds:
    int speed = 100;
};


#endif