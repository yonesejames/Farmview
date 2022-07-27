#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>

class Map
{
public:
    Map();
    ~Map();

    static void loadMap(std::string filePath, int sizeX, int sizeY);

};

#endif