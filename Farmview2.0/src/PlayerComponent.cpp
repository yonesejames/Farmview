#include "PlayerComponent.h"


PlayerComponent::~PlayerComponent()
{
    for (auto i = 0; i < static_cast<unsigned long long>(ToolSlot::NUM_SLOTS); i++)
    {
        if (EquippedTools[i])
        {
            delete EquippedTools[i];
            EquippedTools[i] = { nullptr };
        }

    }
}

PlayerComponent::PlayerComponent()
{
    for (auto i = 0; i < static_cast<unsigned long long>(ToolSlot::NUM_SLOTS); i++)
    {
        EquippedTools[i] = nullptr;
    }
}

const std::vector<Item*> PlayerComponent::getInventory()
{
    return Inventory;
}

void PlayerComponent::cleanupInventory()
{
    const auto toRemove = std::stable_partition(Inventory.begin(), Inventory.end(),
        [](const Item* i) -> bool { return !i->getMarkedForDeletion(); }
    );

    std::for_each(toRemove, Inventory.end(), [](Item* i) { delete i; });

    Inventory.erase(toRemove, Inventory.end());

}

EquipmentDelegate* PlayerComponent::getEquippedTool(unsigned long long index)
{
    if (!EquippedTools[index])
    {
        return nullptr;
    }

    return (dynamic_cast<Tool*>(EquippedTools[index]->data));
}