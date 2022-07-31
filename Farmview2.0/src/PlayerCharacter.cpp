#include "playercharacter.h"
#include <iostream>
#include <algorithm>


PlayerCharacterDelegate::PlayerCharacterDelegate() : StatBlock(0u)
/* Default constructor that sets current level to 1 and current experience to 0 */
{
    currentLevel = 1u;
    currentEXP = 0;
    expToNextLevel = levelTwo;
    HP = std::make_unique<PointWell>();
}

void PlayerCharacterDelegate::gainEXP(int64 gainedEXP)
/* Function that levels character */
{
    currentEXP += gainedEXP;
    while (checkLevel()) {}
}

int16 PlayerCharacterDelegate::getLevel()
/* Returns current level */
{
    return currentLevel;
}

int64 PlayerCharacterDelegate::getCurrentEXP()
/* Returns current experience */
{
    return currentEXP;
}

int64 PlayerCharacterDelegate::getEXPToNextLevel()
/* Returns current experience amount until next level */
{
    return expToNextLevel;
}

bool PlayerCharacterDelegate::checkLevel()
/* Function that checks if c */
{
    // How much experience needed to gain a level 
    // (exponential growth of 2):
    static const int16 levelScale = static_cast<int16>(2);

    if (currentEXP >= expToNextLevel)
    {
        currentLevel++;
        LevelUp();
        expToNextLevel *= levelScale;
        return true;
    }
    return false;
}

Farmer::Farmer() : PlayerCharacterDelegate()
/* Default constructor */
{
    HP->setMax(BASEHP);
    HP->increaseCurrent(BASEHP);
    increaseStats(BASESTR);
}

std::string Farmer::getClassName()
{
    return std::string("Farmer");
}

void Farmer::LevelUp()
/* Function that levels up character */
{
    HP->setMax(static_cast<int16>((BASEHP) / 2.f) + HP->getMax());
    HP->increaseCurrent(static_cast<int16>((BASEHP) / 2.f));
    increaseStats(static_cast<int16>((BASESTR + 1u) / 2.f));
}


PlayerCharacter::~PlayerCharacter()
{
    delete playerCharacterClass;
    playerCharacterClass = { nullptr };

    auto i = 0;
    for (i = 0; i < static_cast<unsigned long long>(ToolSlot::NUM_SLOTS); i++)
    {
        if (EquippedTool[i])
        {
            delete EquippedTool[i];
            EquippedTool[i] = { nullptr };
        }

    }
}

PlayerCharacter::PlayerCharacter(PlayerCharacterDelegate* playerCharacterDelegate) :
    playerCharacterClass(playerCharacterDelegate)
{
    auto i = 0;
    for (i = 0; i < static_cast<unsigned long long>(ToolSlot::NUM_SLOTS); i++)
    {
        EquippedTool[i] = nullptr;
    }
}

std::string PlayerCharacter::getClassName()
{
    return playerCharacterClass->getClassName();
}

int16 PlayerCharacter::getLevel()
{
    return playerCharacterClass->getLevel();
}

int64 PlayerCharacter::getCurrentEXP()
{
    return playerCharacterClass->getCurrentEXP();
}

int64 PlayerCharacter::getEXPToNextLevel()
{
    return playerCharacterClass->getEXPToNextLevel();
}

int16 PlayerCharacter::getCurrentHP()
{
    return playerCharacterClass->HP->getCurrent();
}

int16 PlayerCharacter::getMaxHP()
{
    return playerCharacterClass->HP->getMax();
}

int16 PlayerCharacter::getStrength()
{
    return playerCharacterClass->getStrength();
}

EquipmentDelegate* PlayerCharacter::getEquippedToolAt(unsigned long long i) const
{
    if (!EquippedTool[i])
    {
        return nullptr;
    }

    return (dynamic_cast<Tool*>(EquippedTool[i]->data));
}

void PlayerCharacter::gainEXP(int64 amount)
{
    playerCharacterClass->gainEXP(amount);
}

void PlayerCharacter::takeDamage(int16 amount)
{
    playerCharacterClass->HP->reduceCurrent(amount);
}

void PlayerCharacter::heal(int16 amount)
{
    playerCharacterClass->HP->increaseCurrent(amount);
}

void PlayerCharacter::cleanupBackpack()
{
    const auto toRemove = std::stable_partition(Backpack.begin(), Backpack.end(),
        [](const Item* i) -> bool { return !i->getMarkedForDeletion(); }
    );

    std::for_each(toRemove, Backpack.end(), [](Item* i) { delete i; });

    Backpack.erase(toRemove, Backpack.end());

}