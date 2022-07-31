#ifndef ITEM_H
#define ITEM_H


#include <string>
#include <typeinfo>
#include "datatypes.h"

class ItemDelegate
{
public:
    std::string name;
    virtual const char* getType() = 0;

protected:
    ItemDelegate(std::string n) : name(n) {};
};


class Crop final : public ItemDelegate
{
public:
    int16 quantity;
    const char* getType() override;
    ~Crop() {}

private:
    Crop(std::string name, int16 q = 1) : ItemDelegate(name), quantity(q) {}
    friend class ItemManager;
    friend class PlayerComponent;
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
class Tool final : public EquipmentDelegate
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

