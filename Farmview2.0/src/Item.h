#ifndef ITEM_H
#define ITEM_H


#include <SDL.h>
#include <string>
#include <typeinfo>
#include "datatypes.h"
#include "Vector.h"
#include "TextureManager.h"

class ItemDelegate
{
public:
    std::string name;
    virtual const char* getType() = 0;

protected:
    ItemDelegate(std::string n) : name(n) {};
};


class Crop : public ItemDelegate
{
public:
    Vector position;
    Vector velocity;
    int height = 16;
    int width = 16;
    int scale = 1;
    int16 quantity;
    const char* getType() override;
    ~Crop() 
    {
        SDL_DestroyTexture(texture);
    }

    void setTexture(const char* filePath)
        /* Function that creates a texture from filePath */
    {
        texture = TextureManager::loadTexture(filePath);
    }

private:
    Crop(std::string name, float x, float y, int w, int h, int s, const char* filePath, int16 q = 1) : ItemDelegate(name), quantity(q)
    {
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = s;

        velocity.Zero();
    }
    friend class ItemManager;
    friend class PlayerComponent;
    SDL_Texture* texture;
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

private:
    ItemDelegate* data;
    Item(ItemDelegate* item) : data(item) {};

    friend class ItemManager;
    friend class PlayerCharacter;
    friend class PlayerComponent;

    bool markedForDeletion = false;
};

#endif

