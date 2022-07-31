#ifndef STATBLOCK_H
#define STATBLOCK_H


#include "Datatypes.h"

class StatBlock
{
public:
    // Size of 0xFF;
    int16 Strength;
    //stattype Endurance; 

    StatBlock();
    explicit StatBlock(int16 s);

    int16 getStrength();

protected:
    void increaseStats(int16 s);
};



#endif

