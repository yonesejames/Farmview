#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Components.h"
#include "Vector.h"

class TransformComponent : public Component
{
public:
    Vector position;
    Vector velocity;
    
    int speed = 3;

    int height = 100;
    int width = 100;
    int scale = 1;

    TransformComponent()
    {
        position.Zero();
    }

    TransformComponent(int s)
    {
        position.Zero();
        scale = s;
    }


    TransformComponent(float x, float y)
    {
        position.Zero();
    }

    TransformComponent(float x, float y, int w, int h, int s)
    {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = s;
    }

    void init() override
    {
        velocity.Zero();
    }

    void update() override
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

};

#endif

