#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
    TransformComponent* transform;
    SpriteComponent* sprite;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override
    {
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
            default:
                break;
            }

        }

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
            default:
                break;
            }
        }
        

    }

};


#endif

