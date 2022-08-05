#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H


#include "Item.h"
#include "PlayerCharacter.h"
#include "PlayerComponent.h"
#include <SDL.h>
#include <string>

class Inventory;

Inventory itemInventory;

class ItemManager : public Component
{
public:


    static Item* createTool(std::string name, ToolSlot slot)
    {
        Item* tempItem = new Item(new Tool(name, slot));
        return tempItem;
    };

    static Item* createCrop(std::string n, int x, int y, const char* filePath, int16 quantity = 1u)
    {
        Item* tempItem = new Item(new Crop(n, x, y, filePath, (quantity == 0) ? 1 : quantity));
        return tempItem;
    }

    static Item* createItem(std::string n, int x, int y, const char* filePath, int16 quantity = 1u)
    {
        Item* tempItem = new Item(n, x, y, filePath, (quantity == 0) ? 1 : quantity);
        return tempItem;
    }


    static bool equip(Item* itemToEquip, PlayerCharacter* pCharacter)
    {
        if (!itemToEquip->getData() || !itemToEquip || !pCharacter)
        {
            return false;
        }

        Tool* tool = dynamic_cast<Tool*>(itemToEquip->data);

        if (tool)
        {
            unsigned long long slotNum = (unsigned long long)tool->Slot;
            if (pCharacter->EquippedTool[slotNum])
            {
                // Move old item to backpack:
                moveToBackpack(pCharacter->EquippedTool[slotNum], pCharacter);
                pCharacter->EquippedTool[slotNum] = itemToEquip;
            }
            else
            {
                pCharacter->EquippedTool[slotNum] = itemToEquip;
            }

            return true;
        }

        return false;
    }

    static bool equip(Item* itemToEquip, Entity* player)
    {
        if (!itemToEquip->getData() || !itemToEquip || !player)
        {
            return false;
        }

        Tool* tool = dynamic_cast<Tool*>(itemToEquip->data);

        if (tool)
        {
            unsigned long long slotNum = (unsigned long long)tool->Slot;
            if (player->getComponent<PlayerComponent>().EquippedTools[slotNum])
            {
                // Move old item to backpack:
                moveToInventory(player->getComponent<PlayerComponent>().EquippedTools[slotNum], player);
                player->getComponent<PlayerComponent>().EquippedTools[slotNum] = itemToEquip;
            }
            else
            {
                player->getComponent<PlayerComponent>().EquippedTools[slotNum] = itemToEquip;
            }

            return true;
        }

        return false;
    }


    static bool use(Item* itemToUse, PlayerCharacter* pCharacter)
    {
        if (!itemToUse->getData() || !itemToUse || !pCharacter)
        {
            return false;
        }

        Crop* crop = dynamic_cast<Crop*>(itemToUse->data);
        if (crop)
        {
            // Plant crop first then decrease quantity:
            crop->quantity--;

            std::cout << "Plant crop: " << crop->name << std::endl;

            if (crop->quantity == 0)
            {
                itemToUse->markedForDeletion = true;
                pCharacter->cleanupBackpack();
            }

            return true;
        }


        return false;

    }

    static bool use(Item* itemToUse, Entity* player)
    {
        if (!itemToUse->getData() || !itemToUse || !player)
        {
            return false;
        }

        Crop* crop = dynamic_cast<Crop*>(itemToUse->data);
        if (crop)
        {
            // Plant crop first then decrease quantity:
            crop->quantity--;

            std::cout << "Plant crop: " << crop->name << std::endl;

            if (crop->quantity == 0)
            {
                itemToUse->markedForDeletion = true;
                player->getComponent<PlayerComponent>().cleanupInventory();
            }

            return true;
        }


        return false;

    }


    static bool moveToBackpack(Item* itemToMove, PlayerCharacter* pCharacter)
    {
        if (!itemToMove->getData() || !itemToMove || !pCharacter)
        {
            return false;
        }

        pCharacter->Backpack.push_back(itemToMove);
        return true;
    }

    static bool moveToInventory(Item* itemToMove, Entity* player)
    {

        if (!itemToMove->getData() || !itemToMove || !player)
        {
            return false;
        }

        player->getComponent<PlayerComponent>().Inventory.push_back(itemToMove);


        //SDL_Texture* texture = TextureManager::loadTexture("assets/seed1.png");

        //itemInventory.movedToInventory(itemToMove, texture);


        return true;
    }


    static bool checkItem(Item* item, Entity* player)
    {
        auto inventory = player->getComponent<PlayerComponent>().getInventory();
        for (int i = 0; i < inventory.size(); i++)
        {
            if (!"Seed")
            {
                return false;
            }
            else
            {
                return true;
            }
        }

    }
};


#endif

