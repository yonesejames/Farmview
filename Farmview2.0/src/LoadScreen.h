#ifndef LOADSCREEN_H
#define LOADSCREEN_H


#include <SDL2/SDL.h>
#include "Game.h"

class LoadScreen
/* Loadscreen creates the title and endscreen for game */
{
public:
    static int* loadScreen(const char* fileName, int time);
};


#endif

