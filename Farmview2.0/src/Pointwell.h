#ifndef HP_H
#define HP_H

#include "Datatypes.h"

class PointWell
{
public:
    bool setMax(int16 newMaxHP);
    void reduceCurrent(int16 damage);
    void increaseCurrent(int16 heal);
    int16 getMax();
    int16 getCurrent();

    // Default constructor:
    PointWell();

    // Overload constructor:
    explicit PointWell(int16 c, int16 m);

private:
    int16 current;
    int16 max;

};

#endif
