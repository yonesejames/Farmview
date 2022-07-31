#include "Item.h"
#include <typeinfo>

const char* Crop::getType()
{
    return typeid(*this).name();
}

static int32 equipmentUniqueIDIterator = 0u;


EquipmentDelegate::EquipmentDelegate(std::string n)
    : ItemDelegate(n), uniqueID(++equipmentUniqueIDIterator) {}


const char* Tool::getType()
{
    return typeid(*this).name();
}

Item::~Item()
{
    if (data)
    {
        delete data;
        data = { nullptr };
    }
}

bool Item::getMarkedForDeletion() const
{
    return markedForDeletion;
}