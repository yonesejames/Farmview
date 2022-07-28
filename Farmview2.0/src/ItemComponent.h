#ifndef ITEMCOMPONENT_H
#define ITEMCOMPONENT_H

#include <SDL.h>
#include "Components.h"


/*

Added this component and inventory component and must decide if one will stay or both.

*/

class Item : public Component
{
public:
    std::string Name;
    const int id;
    const int type;

    const char* getType();    

private:
    static int tick;

};

#endif
