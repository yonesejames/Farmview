#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <fstream>
#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "KeyboardController.h"

class Map
/* Map creates a tiled system for game */
{
public:
    // Destructor destroys map:
    ~Map();

    // Constructor creates the map:
    Map(const char* mFP, int mS, int tSize);

    // Load map by taking in file path and how many tiles on the x and y axis:
    void loadMap(std::string filePath, int sizeX, int sizeY);

    // Add tiles on map by taking in the source of the tiles and positioning 
    // them on the x and y axis:
    void addTile(int sourceX, int sourceY, int xpos, int ypos);

    void loadTile(std::string filePath, int xpos, int ypos);

private:
    const char* mapFilePath;
    int mapScale;
    int tileSize;
    int scaledSize;
};


#endif