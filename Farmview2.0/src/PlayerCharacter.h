#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H


#include <memory>
#include <string>
#include "datatypes.h"
#include "statblock.h"
#include "pointwell.h"
#include "item.h"
#include <vector>

class PlayerCharacterDelegate : public StatBlock
{
public:
    static const int64 levelTwo = static_cast<int64>(100u);

    PlayerCharacterDelegate();
    std::unique_ptr <PointWell> HP;

    void gainEXP(int64 gainedEXP);

    int16 getLevel();
    int64 getCurrentEXP();
    int64 getEXPToNextLevel();

    virtual void LevelUp() = 0;

    virtual std::string getClassName() = 0;

protected:
    int16 currentLevel;
    int64 currentEXP;
    int64 expToNextLevel;

    bool checkLevel();
};

class Farmer : public PlayerCharacterDelegate
{
public:
    static const int16 BASEHP = static_cast<int16>(20u);
    static const int16 BASESTR = static_cast<int16>(5u);

    static const int16 HPGROWTH = static_cast<int16>(5u);
    static const int16 STRGROWTH = static_cast<int16>(1u);

    Farmer();

    std::string getClassName() override;

private:
    void LevelUp() override;
};

class PlayerCharacter
{
public:
    ~PlayerCharacter();

    PlayerCharacter() = delete;
    PlayerCharacter(const PlayerCharacter&) = delete;
    PlayerCharacter(const PlayerCharacter&&) = delete;

    PlayerCharacter(PlayerCharacterDelegate* playerCharacterDelegate);

    std::string getClassName();
    int16 getLevel();
    int64 getCurrentEXP();
    int64 getEXPToNextLevel();
    int16 getCurrentHP();
    int16 getMaxHP();
    int16 getStrength();

    const std::vector<Item*> getBackpackList() { return Backpack; }

    EquipmentDelegate* getEquippedToolAt(unsigned long long i) const;

    void gainEXP(int64 amount);
    void takeDamage(int16 amount);
    void heal(int16 amount);

private:
    PlayerCharacterDelegate* playerCharacterClass;
    Item* EquippedTool[static_cast<unsigned long long>(ToolSlot::NUM_SLOTS)];
    std::vector<Item*> Backpack;
    void cleanupBackpack();
    friend class ItemManager;
};

#endif
