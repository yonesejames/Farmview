#include "Pointwell.h"


PointWell::PointWell()
/* Default constructor that sets current and max hp to 1 */
{
    current = static_cast<int16>(1u);
    max = static_cast<int16>(1u);
}

PointWell::PointWell(int16 c, int16 m)
/*
    Overload constructor that takes in arguments to set
    current and max hp.
*/
{
    current = c;
    max = m;

    if (current > max)
    {
        current = max;
    }
}

bool PointWell::setMax(int16 newMaxHP)
/* Function that returns true if hp has been set successfully. */
{
    if (newMaxHP < 1)
    {
        return false;
    }

    max = newMaxHP;

    if (current > max)
    {
        current = max;
    }

    return true;
}

void PointWell::reduceCurrent(int16 damage)
/*
    Function that decreases current hp as long as damage is
    less than otherwise will set current hp to 0.
*/
{
    if (damage > current)
    {
        current = 0;
        return;
    }

    current -= damage;

}

void PointWell::increaseCurrent(int16 heal)
/*
    Function that increases current hp as long as the heal
    amount combined with current hp is less than max hp
    otherwise will set current hp to max hp.
*/
{
    if (heal + current > max)
    {
        current = max;
        return;
    }

    current += heal;
}

int16 PointWell::getMax()
/* Returns max hp */
{
    return max;
}

int16 PointWell::getCurrent()
/* Returns current hp */
{
    return current;
}

