#include "Map.h"
#include "Game.h"
#include <fstream>

Map::Map()
{

}

Map::~Map()
{

}

void Map::loadMap(std::string filePath, int sizeX, int sizeY)
{
    char tile;
    std::fstream mapFile;
    mapFile.open(filePath);

    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(tile);
            Game::addTile(atoi(&tile), x * 100, y * 100);
            mapFile.ignore();
        }
        mapFile.ignore();
    }

    mapFile.close();
    
}

