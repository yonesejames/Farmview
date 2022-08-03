#ifndef PLAYERCOMPONENT_H
#define PLAYERCOMPONENT_H


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



    void init() override
    {

    }

    void update() override
    {        

    }

    void draw() override
    {

    }


private:
    friend class ItemManager;

};

 


#endif

