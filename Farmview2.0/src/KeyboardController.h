#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "Item.h"
#include "InfoBox.h"


class KeyboardController : public Component
/* 
    KeyboardController has inherited Component class public parts and 
    controls what happens when a key is selected on keyboard. 
*/
{
public:
    // Creates "TransformComponent" object:
    TransformComponent* transform;
    SpriteComponent* sprite;

    void init() override
    /*
        Function that overrides "init" function by grabbing the entity components 
        from both transform and sprite. 
    */
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override
    /*
        Function that overrides the "update" function by transforming sprite to 
        a direction by changing velocity when selecting az key and 
        showing an image to the screen based on position.
    */
    { 
        int selectedItemNumber = 0;
        // When key is pressed:
        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = -1.0;
                sprite->Play("walkBackward");
                break;
            case SDLK_s:
                transform->velocity.y = 1.0;
                sprite->Play("walkForward");
                break;
            case SDLK_a:
                transform->velocity.x = -1.0;
                sprite->Play("walkLeft");
                // Optional if you have one image facing one way, you can flip the image:
                //sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                break;
            case SDLK_d:
                transform->velocity.x = 1.0;
                sprite->Play("walkRight");
                // Optional if you have one image facing one way, you can flip the image:
                //sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                break;
            case SDLK_e:
                sprite->Play("wateringForward");
                break;
            default:
                break;
            }
        }

        // When key is not pressed:
        if (Game::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform->velocity.y = 0;
                sprite->Play("idleBackward");
                break;
            case SDLK_s:
                transform->velocity.y = 0;
                sprite->Play("idleForward");
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                sprite->Play("idleLeft");
                // Optional if you have one image facing one way, you can reset the 
                // flipped the image:
                //sprite->spriteFlip = SDL_FLIP_NONE;
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                sprite->Play("idleRight");
                // Optional if you have one image facing one way, you can reset the 
                // flipped the image:
                //sprite->spriteFlip = SDL_FLIP_NONE;
                break;
            case SDLK_e:
                sprite->Play("idleForward");
                break;
            default:
                break;
            }
        }

        if (Game::event.type == SDL_KEYDOWN)
        {
            if (Game::event.key.keysym.scancode == SDLK_w)
            {
                if (Game::event.key.keysym.scancode == SDLK_e)
                {
                    sprite->Play("wateringBackward");
                }
            }

            if (Game::event.key.keysym.scancode == SDLK_s)
            {
                if (Game::event.key.keysym.scancode == SDLK_e)
                {
                    sprite->Play("wateringForward");
                }
            }

            if (Game::event.key.keysym.scancode == SDLK_a)
            {
                if (Game::event.key.keysym.scancode == SDLK_e)
                {
                    sprite->Play("wateringLeft");
                }
            }

            if (Game::event.key.keysym.scancode == SDLK_d)
            {
                if (Game::event.key.keysym.scancode == SDLK_e)
                {
                    sprite->Play("wateringRight");
                }
            }
        }




    }

};


#endif

