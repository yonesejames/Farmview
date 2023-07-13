#ifndef COLLISION_H
#define COLLISION_H


#include <SDL2/SDL.h>
#include <iostream>

// Forward declaration of "ColliderComponent" component:
class ColliderComponent;

class Collision
/* 
    Collision creates a detection system to block an objects path using rectangles and
    "ColliderComponent" component colliders.
*/
{
public: 
    static bool AABB(const SDL_Rect& rectangleA, const SDL_Rect& rectangleB);

    static bool AABB(const ColliderComponent& colliderA, const ColliderComponent& colliderB);
};


#endif

