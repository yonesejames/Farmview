#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <SDL.h>

class TileComponent : public Component
{
public:
    TransformComponent* transform;
    SpriteComponent* sprite;

    SDL_Rect tileRectangle;
    int tileID;
    const char* filePath;

    TileComponent() = default;

    TileComponent(int x, int y, int w, int h, int id)
    {
        tileRectangle.x = x;
        tileRectangle.y = y;
        tileRectangle.w = w;
        tileRectangle.h = h;
        tileID = id;

        switch (tileID)
        {
        case 0:
            filePath = "assets/grass.png";
            break;
        case 1:
            filePath = "assets/dirt.png";
            break;
        case 2:
            filePath = "assets/water.png";
            break;
        case 3:
            filePath = "assets/tree1.png";
            break;
        case 4:
            filePath = "assets/tree2.png";
            break;
        case 5:
            filePath = "assets/tree3.png";
            break;
        default:
            break;
        }

    }

    void init() override
    {
        entity->addComponent<TransformComponent>(static_cast<float>(tileRectangle.x), static_cast<float>(tileRectangle.y), tileRectangle.w, tileRectangle.h, 1);
        transform = &entity->getComponent<TransformComponent>();

        entity->addComponent<SpriteComponent>(filePath);
        sprite = &entity->getComponent<SpriteComponent>();
    }
};


#endif

