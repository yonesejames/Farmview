#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H


#include "Components.h"
#include "Vector.h"

class TransformComponent : public Component
/*
    TransformComponent has inherited Component class public parts and creates placements
    with Vectors position and velocity and variables speed, height, width, and scale.
*/
{
public:
    // Create vectors for position and velocity:
    Vector position;
    Vector velocity;
    
    // Default settings for variables, 
    // but can be modified depending on constructor used:
    int speed = 3;
    int height = 64;
    int width = 64;
    int scale = 1;

    TransformComponent()
    /*
        Constructor without any arguments and place an object at
        position to x = 0 and y = 0:
    */
    {
        position.Zero();
    }

    TransformComponent(int s)
    /*
        Constructor that takes one argument to scale an object
        and place the object at position x = 0 and y = 0:
    */
    {
        position.Zero();
        scale = s;
    }


    TransformComponent(float x, float y)
    /*
        Constructor that takes two float arguments: x and y 
        and position of the object at x = 0 and y = 0:
    */
    {
        position.Zero();
    }

    TransformComponent(float x, float y, int w, int h, int s)
    /*
        Constructor that takes float arguments: x and y,
        int arguments w for width, h for height, and s for scale. 
        Places position of the object at the floats x and y.
    */

    {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = s;
    }

    void init() override
    /*
        Function that initializes 
    */
    {
        velocity.Zero();
    }

    void update() override
    /*
        Function that updates 
    */
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

};


#endif

