#ifndef INFORMATIONCOMPONENT_H
#define INFORMATIONCOMPONENT_H

#include <SDL.h>
#include <string>
#include <iostream>
#include "Components.h"
#include <vector>


class InformationComponent : public Component
{
public:
    std::string name;
    int id;

    static int ID;

    InformationComponent()
    {
        id = ID++;
    }

    int getID()
    {
        return id;
    }


private:


};


#endif

