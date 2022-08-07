#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS.h"
#include "Components.h"
#include "LoadScreen.h"
#include "Vector.h"
#include "Collision.h"
#include <iostream>
#include "ItemManager.h"
#include <iostream>
#include "PlayerCharacter.h"
#include "PlayerComponent.h"
#include "Item.h"
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include "InfoBox.h"
#include "ItemMenu.h"
#include "InventoryButton.h"

Map* map;
Map* mapTile;
Map* mapGrass;
Manager manager;
//Inventory* inventory;
InfoBox* infobox;
Item* seed;
//Item* seed2;

SDL_Renderer* Game::renderer = { nullptr };
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, 1600, 880 };

auto& player(manager.addEntity());
auto& seeds(manager.addEntity());
auto& crop(manager.addEntity());

bool Game::isRunning = true;

InventoryButton inventoryButton;
ItemMenu itemMenu;

// Items array: 0 = no item and 1 = seed:
auto& playerItems = itemMenu.Inventory;



Game::~Game()
/* Destructor that destroys the game */
{

}


Game::Game()
/* Constructor that creates the game */
{
    
}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
/* 
    Function that initializes game with game name, position of game on monitor by x and y axis,
    sets game width and height, and shows if game is fullscreen or not.
*/
{
    // Set flag to fullscreen if fullscreen is true:
    int flag = 0;
    if (fullscreen)
    {
        flag = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    /* If SDL initializes without any issues then goes through the series of if/else statements */
    {
        std::cout << "Subsystem Initialized" << std::endl;

        // Image allows you to deal with other image types other than BMP:
        if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            std::cout << "SDL Image Initialization Error: " << IMG_GetError() << std::endl;
            SDL_Quit();
            system("pause");
        }

        // TTF allows you to place text to font for rendering on screen:
        if (TTF_Init() != 0)
        {
            std::cout << "SDL TTF Initialization Error: " << TTF_GetError() << std::endl;
            SDL_Quit();
            system("pause");
        }

        // Mixer allows sound and music:
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        {
            std::cout << "SDL Mixer Initialization Error: " << Mix_GetError() << std::endl;
            SDL_Quit();
            system("pause");
        }

        // Creates window and prints out success message if completed or error if not: 
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);
        if (window)
        {
            std::cout << "Window has been created!" << std::endl;
        } 
        else
        {
            std::cout << "SDL Window Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            system("pause");
        }

        // Creates renderer and prints out success message if completed or error if not: 
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer)
        {
            LoadScreen::loadScreen("assets/farmviewOpen.bmp", 3000);
            std::cout << "Renderer has been created!" << std::endl;
        }
        else
        {
            std::cout << "SDL Renderer Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            system("pause");
        }
    } 
    else
    {
        // If SDL initializes incorrectly then isRunning is set to false:
        isRunning = false;

        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        system("pause");
    }

    map = new Map("assets/farmviewStartingMapTileSet.png", 2, 16);

    //ECS Implementation:
    map->loadMap("assets/farmviewStartingMapTileMap.map", 100, 55);    

    mapTile = new Map("assets/seed.png", 1, 16);

    mapGrass = new Map("assets/grass.png", 1, 16);

    // Setup info box:
    infobox = new InfoBox();
    infobox->setup(renderer);
    infobox->setText("Welcome to Farmview!");
    infobox->draw();


    for (int i = 0; i <= 9; i++)
    {
        playerItems[i] = 0;
    }

    playerItems[0] = 1;


    itemMenu.setup(renderer, playerItems, 0, 0);
    inventoryButton.setup(renderer, {0, 750, 400, 125}, "Inventory");
    inventoryButton.selected = true;

    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("assets/farmer_animations2.png", true, 64, 64);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);
    player.addComponent<PlayerComponent>();

    crop.addComponent<TransformComponent>(500, 500, 16, 16, 1);
    crop.addComponent<SpriteComponent>("assets/seed1.png");
    crop.addGroup(groupItems);

    player.addComponent<ItemManager>();

    std::cout << "Player: " << std::endl;

    Item* wateringcan = ItemManager::createTool("Watering Can", ToolSlot::RIGHTHAND);
    Item* hoe = ItemManager::createTool("Hoe", ToolSlot::LEFTHAND);
    Item* upgradedWateringcan = ItemManager::createTool("Upgrade Watering Can", ToolSlot::RIGHTHAND);

    ItemManager::equip(wateringcan, &player);
    ItemManager::equip(hoe, &player);
    ItemManager::equip(upgradedWateringcan, &player);

    std::cout << "Tool: " << std::endl;
    for (int i = 0; i < (int)ToolSlot::NUM_SLOTS; i++)
    {
        const Tool* tmp = dynamic_cast<Tool*>(player.getComponent<PlayerComponent>().getEquippedTool(i));
        if (tmp)
        {
            std::cout << tmp->name << std::endl;
        }
    }

    seed = ItemManager::createCrop("Seed", 0, 0, "assets/seed1.png");

    //seed2 = ItemManager::createItem("Seed2", 0, 0, "assets/seed1.png");

 
    ItemManager::moveToInventory(seed, &player);
    //ItemManager::moveToInventory(seed2, &player);
    //ItemManager::moveToInventory(ItemManager::createItem("Seed", 0, 0, "assets/seed1.png"), &player);

   /*
    for (auto& i : playerInventory)
    {
        std::cout << i->getData()->name << std::endl;
        std::cout << i->getData() << std::endl;
    }
    */
    std::cout << "Are there seeds? " << ItemManager::checkItem(seed, &player) << std::endl;

}

void Game::itemFound()
{
    bool freeSlotFound = false;

    int item = 1;

    for (int i = 0; i < 10; i++)
    {
        if (playerItems[i] == 0)
        {
            freeSlotFound = true;
            playerItems[i] = item;
            break;
        }
    }

    if (freeSlotFound)
    {
        if (item == 1)
        {
            infobox->setup(renderer);
            infobox->setText("Found Seed!");
            infobox->draw();
        }
    }
    else
    {
        infobox->setup(renderer);
        infobox->setText("Your bag is full!");
        infobox->draw();
    }

    infobox->visible = true;
}

void Game::useItem()
{
    if (playerItems[itemMenu.selectedItemIndex] == 1)
    {
        auto playerPosition = player.getComponent<TransformComponent>().position;
        seeds.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        seeds.addComponent<SpriteComponent>("assets/seed.png");
        seeds.addGroup(groupItems);

        //infobox->setup(renderer);
        //infobox->setText("Seed has been planted!");
        //infobox->draw();
        //SDL_RenderPresent(renderer);
    }

    playerItems[itemMenu.selectedItemIndex] = 0;

}


// Grop creation for tiles, colliders, and players:
auto& tiles(manager.getGroup(Game::groupMap));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& players(manager.getGroup(Game::groupPlayers));
auto& items(manager.getGroup(Game::groupItems));
auto& chests(manager.getGroup(Game::groupChests));



void Game::handleEvents()
/* Function that handles keyboard and mouse events */
{
    
    SDL_PollEvent(&event);

    // Switch statement to poll events while game is running
    switch (event.type)
    {
    // User requests to quit:
    case SDL_QUIT:
        LoadScreen::loadScreen("assets/farmviewExit.bmp", 1000);
        isRunning = false;
        break;
    default:
        break;
    }

    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.scancode)
        {
        case SDL_SCANCODE_ESCAPE:
            infobox->visible = false;
            break;
        case SDL_SCANCODE_SPACE:
            itemMenu.visible = true;
        default:
            break;
        }

    }

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        int x = event.button.x;
        int y = event.button.y;
        auto inventoryRect = inventoryButton.buttonRect;
        auto cancelTexture = itemMenu.cancel;

        if (x >= inventoryRect.x && x <= inventoryRect.x + inventoryRect.w && y >= inventoryRect.y && inventoryRect.y + inventoryRect.h)
        {
            itemMenu.visible = true;
        }

        for (auto& chest : chests)
        {
                bool active = true;
                if (active)
                {
                    auto& chestRect = chest->getComponent<SpriteComponent>().destinationRectangle;
                    int j = event.button.x;
                    int k = event.button.y;

                    if (j >= chestRect.x && j <= chestRect.x + chestRect.w && k >= chestRect.y && k <= chestRect.y + chestRect.h)
                    {
                        active = false;
                        itemFound();
                        //std::cout << "Seed found!" << std::endl;
                    }
                }
                else
                {
                    auto& chestRect = chest->getComponent<SpriteComponent>().destinationRectangle;
                    int j = event.button.x;
                    int k = event.button.y;

                    if (j >= chestRect.x && j <= chestRect.x + chestRect.w && k >= chestRect.y && k <= chestRect.y + chestRect.h)
                    {
                        std::cout << "Chest is not active!" << std::endl;
                    }

                }

        }
    }

    if (itemMenu.visible)
    {
        switch (event.key.keysym.scancode)
        {
        case SDL_SCANCODE_UP:
            itemMenu.moveUp();
            break;
        case SDL_SCANCODE_DOWN:
            itemMenu.moveDown();
            break;
        case SDL_SCANCODE_ESCAPE:
            itemMenu.visible = false;
            break;
        default:
            break;
        }

        if (itemMenu.selectedItemIndex == 10 && event.type == SDL_KEYDOWN)
        {
            itemMenu.visible = false;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_RETURN:
                useItem();
                break;
            default:
                break;
            }
        }
    }


    

}


void Game::update()
/* Function that updates based on any changes (updates continously) */
{
    // Retrives components for player:
    SDL_Rect playerCollider = player.getComponent<ColliderComponent>().collider;
    Vector playerPosition = player.getComponent<TransformComponent>().position;
    //Vector itemPosition = item.getComponent<TransformComponent>().position;

    // ECS delete dead entities and updates them:
    manager.refresh();
    manager.update();

    for (auto& c : colliders)
    /* Checks if colliders and player has collision and if so then player gets blocked */
    {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCollider))
        {
            player.getComponent<TransformComponent>().position = playerPosition;
        }
    }

    // Camera that moves with player based on half the map size:
    camera.x = player.getComponent<TransformComponent>().position.x - 800;
    camera.y = player.getComponent<TransformComponent>().position.y - 440;

    // If statements to ensure that camera does not keep moving outside of the map:
    if (camera.x < 0)
    {
        camera.x = 0;
    }
    if (camera.y < 0)
    {
        camera.y = 0;
    }
    if (camera.x > camera.w)
    {
        camera.x = camera.w;
    }
    if (camera.y > camera.h)
    {
        camera.y = camera.h;
    }

    seed = new Item("Seed", 100, 100, "assets/seed1.png");
    seed->update();

    //inventory = new Inventory(0, 660,"assets/farmviewInventory.png");
    //inventory->update();

    crop.update();

    auto playerInventory = player.getComponent<PlayerComponent>().getInventory();
    for (auto i : playerInventory)
    {
        if (ItemManager::checkItem(seed, &player) == true)
        {

            for (auto& tile : tiles)
            {
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {

                    int x = event.button.x;
                    int y = event.button.y;
                    auto tileRect = tile->getComponent<TileComponent>().destinationRect;
                    auto tileRectSource = tile->getComponent<TileComponent>().sourceRect;

                    if (x > tileRect.x && x < tileRect.x + tileRect.w && y > tileRect.y && tileRect.y + tileRect.h)
                    {
                        //seeds.addComponent<TransformComponent>(x, y, 16, 16, 1);
                        //seeds.addComponent<SpriteComponent>("assets/seed.png");
                        //crop.addGroup(groupItems);

                        //mapTile->loadTile("assets/seed.png", x, y);
                        //std::cout << "Plant Seed" << std::endl;

                        //ItemManager::use(seed, &player);
                    }
                }
                else if (event.type == SDL_MOUSEBUTTONUP)
                {

                }
            }

        }

        else
        {
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                for (auto& tile : tiles)
                {
                    if (event.type == SDL_MOUSEBUTTONDOWN)
                    {
                        ItemManager::use(seed, &player);
                        int x = event.button.x;
                        int y = event.button.y;
                        auto tileRect = tile->getComponent<TileComponent>().destinationRect;
                        auto tileRectSource = tile->getComponent<TileComponent>().sourceRect;

                        if (x > tileRect.x && x < tileRect.x + tileRect.w && y > tileRect.y && tileRect.y + tileRect.h)
                        {
                            //mapGrass->loadTile("assets/grass.png", x, y);
                            //std::cout << "Cannot plant seed" << std::endl;

                        }
                    }
                }

            }
        }

    }

    seeds.update();

}


void Game::render()
/* Function that renders objects on the screen */
{
    // Clear what is currently in the renderer's buffer:
    SDL_RenderClear(renderer);

    for (auto& tile : tiles)
    /* Loops through tiles and draw each tile on screen first */
    {
        tile->draw();   

    }

    for (auto& collider : colliders)
    /* Loops through colliders and draw each collider on screen next */
    {
        collider->draw();
    }

    seed->draw();

    seeds.draw();

    //inventory->draw();

    for (auto& item : items)
        /* Loops through player and draw each player on screen last */
    {
        item->draw();
    }

    for (auto& chest : chests)
        /* Loops through player and draw each player on screen last */
    {
        chest->draw();
    }

    for (auto& player : players)
    /* Loops through player and draw each player on screen last */
    {
        player->draw();
    }

    infobox->setup(renderer);
    infobox->draw();  

    inventoryButton.draw();
    itemMenu.draw();

    // Add items to render:
    SDL_RenderPresent(renderer);
}


void Game::close()
/* Function that cleans up any pointers by returning it to memory and quits game */
{
    // Deallocate and destroys window and renderer because they were allocated memory:
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    // Game exits:
    SDL_Quit();

    std::cout << "Game has been cleaned and closed!" << std::endl;
}

