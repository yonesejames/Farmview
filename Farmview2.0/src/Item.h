#ifndef ITEM_H
#define ITEM_H


#include <SDL.h>
#include <string>
#include <typeinfo>
#include "datatypes.h"
#include "Vector.h"
#include "TextureManager.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Item;

class ItemDelegate
{
public:
    std::string name;
    virtual const char* getType() = 0;
    ItemDelegate(){}

protected:
    ItemDelegate(std::string n) : name(n) {};
};


class Crop : public ItemDelegate
{
public:
    using Group = std::size_t;
    Vector position;
    Vector velocity;
    int height = 16;
    int width = 16;
    int scale = 1;
    int16 quantity;
    const char* getType() override;

    int xpos;
    int ypos;
  

    ~Crop() 
    {

    }


    Crop(){}

    Crop(std::string n, int x, int y, const char* filePath, int16 q = 1) : ItemDelegate(name), quantity(q)
    {
        itemTexture = TextureManager::loadTexture(filePath);

        name = n;

        xpos = x;
        ypos = y;
    }

    void update()
    {
        sourceRect.h = 16;
        sourceRect.w = 16;
        sourceRect.x = 0;
        sourceRect.y = 0;

        destinationRect.h = sourceRect.h;
        destinationRect.w = sourceRect.w;
        destinationRect.x = xpos;
        destinationRect.y = ypos;

    }

    void render()
    {
        SDL_RenderCopy(Game::renderer, itemTexture, &sourceRect, &destinationRect);
    }

private:
    friend class ItemManager;
    friend class PlayerComponent;

    SDL_Texture* itemTexture;
    SDL_Rect sourceRect, destinationRect;
};



class EquipmentDelegate : public ItemDelegate
{
public:
    const int32 uniqueID;

protected:
    EquipmentDelegate(std::string n);

private:
};

// NUM_SLOTS for making arrays of tool slots
enum class ToolSlot { RIGHTHAND, LEFTHAND, NUM_SLOTS };
class Tool : public EquipmentDelegate
{
public:
    ToolSlot Slot;

    const char* getType() override;

private:
    Tool() = delete;
    Tool(const Tool&) = delete;
    Tool(const Tool&&) = delete;

    Tool(std::string name, ToolSlot slot) : EquipmentDelegate(name), Slot(slot) {}

    friend class ItemManager;
    friend class PlayerComponent;
};

class Item
{
public:
    const ItemDelegate* getData() { return data; }
    ~Item();
    bool getMarkedForDeletion() const;
    ItemDelegate* data;
    Item(ItemDelegate* item) : data(item) {};
    int xpos;
    int ypos;
    std::string name;

    Item() {}

    Item(std::string n, int x, int y, const char* filePath, int16 q = 1) 
    {
        itemTexture = TextureManager::loadTexture(filePath);

        name = n;

        xpos = x;
        ypos = y;
    }


    void update()
    {
        sourceRect.h = 16;
        sourceRect.w = 16;
        sourceRect.x = 0;
        sourceRect.y = 0;

        destinationRect.h = sourceRect.h;
        destinationRect.w = sourceRect.w;
        destinationRect.x = xpos;
        destinationRect.y = ypos;

    }

    void render()
    {
        SDL_RenderCopy(Game::renderer, itemTexture, &sourceRect, &destinationRect);
    }

private:
    friend class ItemManager;
    friend class PlayerCharacter;
    friend class PlayerComponent;

    bool markedForDeletion = false;

    SDL_Texture* itemTexture;
    SDL_Rect sourceRect, destinationRect;
};

class Inventory
{
public:
    int screenWidth = 800;
    int screenHeight = 440;

    ~Inventory(){}

    //Inventory(){}

    Inventory(const char* texture)
    {
        inventoryTexture = TextureManager::loadTexture(texture);
    }

    void update()
    {
        sourceRect.h = 100;
        sourceRect.w = 100;
        sourceRect.x = 0;
        sourceRect.y = 0;

        destinationRect.w = screenWidth / 2;
        destinationRect.h = screenHeight / 2;
        destinationRect.x = 0;
        destinationRect.y = 0;
    }

    void render()
    {
        SDL_RenderCopy(Game::renderer, inventoryTexture, &sourceRect, &destinationRect);
    }

    void all()
    {
        sourceRect.h = 100;
        sourceRect.w = 100;
        sourceRect.x = 0;
        sourceRect.y = 0;

        destinationRect.w = screenWidth / 2;
        destinationRect.h = screenHeight / 2;
        destinationRect.x = 0;
        destinationRect.y = 0;

        SDL_RenderCopy(Game::renderer, inventoryTexture, &sourceRect, &destinationRect);

        SDL_RenderPresent(Game::renderer);
    }

private:
    SDL_Texture* inventoryTexture;
    SDL_Rect inventoryViewport;
    SDL_Rect sourceRect, destinationRect;
};

#endif

