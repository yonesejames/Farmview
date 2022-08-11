#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H


#include "Game.h"
#include <SDL.h>
#include "Components.h"
#include "Datatypes.h"
#include "Statblock.h"
#include "Pointwell.h"
#include "Item.h"
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class PlayerComponent : public Component

{
public:
    std::vector<Item*> Inventory;
    const std::vector<Item*> getInventory();
    Item* EquippedTools[static_cast<unsigned long long>(ToolSlot::NUM_SLOTS)];
    void cleanupInventory();

    EquipmentDelegate* getEquippedTool(unsigned long long index);

    PlayerComponent();
    ~PlayerComponent();

    std::string name;

    int hunger = 100;
    int hungerMax = 100;
    int sleepy = 100;
    int sleepyMax = 100;

    void init() override
    {

    }

    void update() override
    {        

    }

    void draw() override
    {

    }

    void setName(std::string n)
    {
        name = n;
    }

    std::string getName()
    {
        return name;
    }
    
    int getHunger()
    {
        return hunger;
    }

    int getSleep()
    {
        return sleepy;
    }

    int takeDamageHunger(int damage)
    {
        return hunger = hunger - damage;
    }

    int takeDamageSleepy(int damage)
    {
        return sleepy = sleepy - damage;
    }

    void eat(int amount)
    {
        hunger += amount;
        if (hunger > hungerMax)
        {
            hunger = hungerMax;
        }
    }

    void sleep(int amount)
    {
        sleepy += amount;
        if (sleepy > sleepyMax)
        {
            sleepy = sleepyMax;
        }
    }


private:
    friend class ItemManager;

};

 


#endif

