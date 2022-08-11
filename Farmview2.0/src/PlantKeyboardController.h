#ifndef PLANTKEYBOARDCONTROLLER_H
#define PLANTKEYBOARDCONTROLLER_H

#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "ItemMenu.h"

class PlantKeyboardController : public Component
/*
    PlantKeyboardController has inherited Component class public parts and
    controls what happens when a key is selected on keyboard.
*/
{
public:
    TransformComponent* transform;
    SpriteComponent* sprite;
    ItemMenu* itemMenu;
    Game* game;

    int xpos;
    int ypos;
    int width;
    int height;
    int scale;
    int item;

    PlantKeyboardController()
    {

    }

    PlantKeyboardController(int i, ItemMenu* im)
    {
        item = i;
        itemMenu = im;
         
    }

    PlantKeyboardController(int x, int y, int w, int h, int s, int i, ItemMenu* im)
    {
        transform->position.x = x;
        transform->position.y = y;
        transform->width = w;
        transform->height = h;
        transform->scale = s;

        item = i;
        itemMenu = im;

    }

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
        if (Game::event.type == SDL_MOUSEBUTTONDOWN)
        {
            int x = Game::event.button.x;
            int y = Game::event.button.y;
            auto spriteRect = sprite->destinationRectangle;

            if (x >= spriteRect.x && x <= spriteRect.x + spriteRect.w && y >= spriteRect.y && spriteRect.y + spriteRect.h)
            {
                std::cout << "Plant clicked" << std::endl;

                bool freeSlotFound = false;

                for (int i = 0; i < 10; i++)
                { 
                    if (itemMenu->Inventory[i] == 0)
                    {
                        if (sprite->readyToPick == true && item % 2 == 0)
                        {
                            int& newItem = item;
                            newItem = newItem - 1;
                            freeSlotFound = true;
                            itemMenu->Inventory[i] = item;
                            std::cout << "Inside for loop" << std::endl;
                            break;
                        }
                        else
                        {
                            freeSlotFound = true;
                            itemMenu->Inventory[i] = item;
                            std::cout << "Inside for loop" << std::endl;
                            break;
                        }

                    }
                
                }

                sprite->~SpriteComponent();
            }
        }
    }
};


#endif

