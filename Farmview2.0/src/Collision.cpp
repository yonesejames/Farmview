#include "Collision.h"
#include "ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& rectangleA, const SDL_Rect& rectangleB)
{
    if (
        rectangleA.x + rectangleA.w >= rectangleB.x &&
        rectangleB.x + rectangleB.w >= rectangleA.x &&
        rectangleA.y + rectangleA.h >= rectangleB.y &&
        rectangleB.y + rectangleB.h >= rectangleA.y
        )
    {
        return true;
    }

    return false;
}

bool Collision::AABB(const ColliderComponent& colliderA, const ColliderComponent& colliderB)
{
    if (AABB(colliderA.collider, colliderB.collider))
    {
        //std::cout << colliderA.tag << " hit: " << colliderB.tag << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}