#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>
#include <iostream>

class ColliderComponent;

class Collision
{
public: 
    static bool AABB(const SDL_Rect& rectangleA, const SDL_Rect& rectangleB);

    static bool AABB(const ColliderComponent& colliderA, const ColliderComponent& colliderB);
};


#endif
