#include "Collision.h"
#include "ColliderComponent.h"


bool Collision::AABB(const SDL_Rect& rectangleA, const SDL_Rect& rectangleB)
/* 
    Function that checks if rectangle A and B intercepts and returns true or false by
    checking width and height location when adding x coordinate with width and 
    y coordinate with height to get precise location of both rectangles.
*/
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
/* 
    Function that calls AABB function to check if colliderA and colliderB had a collision
    returns true if they did or false otherwise.
*/
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

