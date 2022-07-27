#ifndef LOADSCREEN_H
#define LOADSCREEN_H

#include <SDL.h>
#include "Game.h"

class LoadScreen
{
public:
    static int* loadScreen(const char* fileName, int time);
};

#endif


