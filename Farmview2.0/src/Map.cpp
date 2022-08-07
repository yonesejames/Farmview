#include "Map.h"


// Manager object that is defined elsewhere:
extern Manager manager;



Map::~Map()
/* Destructor that destroys the map */
{

}


Map::Map(const char* mFP, int mS, int tS) : mapFilePath(mFP), mapScale(mS), tileSize(tS)
/* 
    Constructor that creates a map that takes in the scaling of the map 
    and the size of pixels of each tile. 
*/
{
    // Depending on the scale of the map, we need to = mapScale * tileSize 
    scaledSize = mS * tS;
}


void Map::loadMap(std::string filePath, int sizeX, int sizeY)
/* Function that takes in file and sizes of the tiles on the x and y axis */
{
    char c;
    // Input/output stream class to operate on files:
    std::fstream mapFile;
    // Open file:
    mapFile.open(filePath);

    int sourceX;
    int sourceY;

    // Nested for loops to go through first paragraph of characters for each line of the file:
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(c);
            // Convert string to integer then * with the size of the tile (16 px) 
            // and grab the information in order to place the tile source on the y axis:
            sourceY = atoi(&c) * tileSize;

            // Convert string to integer then * with the size of the tile (16 px) 
            // and grab the information in order to place the tile source on the x axis:
            mapFile.get(c);
            sourceX = atoi(&c) * tileSize;

            // Calls the addTile function: 
            addTile(sourceX, sourceY, x * scaledSize, y * scaledSize);
            mapFile.ignore(); 

        }
    }

    // Ignore empty line:
    mapFile.ignore();

    // Nested for loops to go through second paragraph of characters for each line of the file:
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


    // Ignore empty line:
    mapFile.ignore();

    // Nested for loops to go through second paragraph of characters for each line of the file:
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(c);
            if (c == '1')
            {
                auto& chest(manager.addEntity());
                chest.addComponent<TransformComponent>(x * scaledSize, y * scaledSize, 16, 16, 2);
                chest.addComponent<SpriteComponent>("assets/chest.png");
                chest.addGroup(Game::groupChests);              
              
            }

        }
    }

    mapFile.close();

    
}


void Map::addTile(int sourceX, int sourceY, int xpos, int ypos)
/* 
    Function that adds tile on the map which takes in the the sources x and y axis by 
    getting information from file and x and y position to place the tiles.
*/
{
    // Add tile entity:
    auto& tile(manager.addEntity());

    // Add component to tile:
    tile.addComponent<TileComponent>(sourceX, sourceY, xpos, ypos, tileSize, mapScale, mapFilePath);
    
    // Add tile to the groupMap group:
    tile.addGroup(Game::groupMap);

}


void Map::loadTile(std::string filePath, int xpos, int ypos)
/* Function that takes in file and sizes of the tiles on the x and y axis */
{
    addTile(0, 0, xpos, ypos);   

}

