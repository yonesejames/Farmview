#include "ECS.h"


void Entity::addGroup(Group mGroup)
/* Add entity to group */
{
    groupBitSet[mGroup] = true;
    manager.addToGroup(this, mGroup);
}

