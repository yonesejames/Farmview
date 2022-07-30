#include "statblock.h"

StatBlock::StatBlock()
/* Default constructor that sets strength to 1 */
{
    Strength = static_cast<int16>(1);
    //Endurance = static_cast<stattype>(1);
}

StatBlock::StatBlock(int16 s)
/*
    Overload constructor that takes in arguments to set
    strength.
*/
{
    Strength = s;
    //Endurance = e;
}

int16 StatBlock::getStrength()
/* Returns strength */
{
    return Strength;
}

void StatBlock::increaseStats(int16 s)
{
    Strength += s;
}