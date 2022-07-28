#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS.h"
#include "Components.h"

// Manager object that is defined elsewhere:
extern Manager manager;

Map::Map(const char* mFP, int mS, int tS) : mapFilePath(mFP), mapScale(mS), tileSize(tS)
{
    scaledSize = mS * tS;
}

Map::~Map()
{

}

void Map::loadMap(std::string filePath, int sizeX, int sizeY)
{
    char c;
    std::fstream mapFile;
    mapFile.open(filePath);

    int sourceX;
    int sourceY;

    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            // 16 px:
            mapFile.get(c);
            sourceY = atoi(&c) * tileSize;

            // 16 px:
            mapFile.get(c);
            sourceX = atoi(&c) * tileSize;

            // 32 px:
            addTile(sourceX, sourceY, x * scaledSize, y * scaledSize);
            mapFile.ignore();
        }
    }

    // Ignore empty line
    mapFile.ignore();

    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(c);
            if (c == '1')
            {
                auto& tileCollider(manager.addEntity());
                tileCollider.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
                tileCollider.addGroup(Game::groupColliders);
            }

            mapFile.ignore();
        }
    }

    mapFile.close();
    
}

void Map::addTile(int sourceX, int sourceY, int xpos, int ypos)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(sourceX, sourceY, xpos, ypos, tileSize, mapScale, mapFilePath);
    tile.addGroup(Game::groupMap);
}
