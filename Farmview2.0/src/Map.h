#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>

class Map
{
public:
    // Constructor that takes in -
    // mFP = map file path
    // mS = map scale
    // tSize = tile size:
    Map(const char* mFP, int mS, int tSize);
    ~Map();

    void loadMap(std::string filePath, int sizeX, int sizeY);
    void addTile(int sourceX, int sourceY, int xpos, int ypos);

private:
    const char* mapFilePath;
    int mapScale;
    int tileSize;
    int scaledSize;
};

#endif