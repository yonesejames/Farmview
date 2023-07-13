#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS.h"
#include "Components.h"
#include "LoadScreen.h"
#include "Vector.h"
#include "Collision.h"
#include <iostream>
#include <iostream>
#include "PlayerCharacter.h"
#include "PlayerComponent.h"
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <cstdlib>
#include "InfoBox.h"
#include "ItemMenu.h"
#include "InventoryButton.h"
#include "Clock.h"
#include <sstream>
#include <iomanip>
#include <stdlib.h> 
#include <time.h> 
#include "LifeBar.h"
#include <fstream>
#include <array>
#include <chrono>

Map* map;
Map* mapTile;
Map* mapGrass;
Manager manager;
InfoBox* infobox;
Clock* clockTime;
Clock* day;

LifeBar farmerLifeBar;

SDL_Renderer* Game::renderer = { nullptr };
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, 1600, 880 };

auto& player(manager.addEntity());
auto& crop(manager.addEntity());

bool Game::isRunning = true;

InventoryButton inventoryButton;
InventoryButton sleepButton;
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


SDL_TimerID Game::addTimer(Uint32 delay, SDL_TimerCallback callback, void* param)
{
    SDL_TimerID id = SDL_AddTimer(delay, callback, param);
    timers.insert(id);
    return id;
}


SDL_TimerID Game::addRecurringTimer(Uint32 interval, SDL_TimerCallback callback, void* param)
{
    SDL_TimerID id = SDL_AddTimer(interval, callback, param);
    timers.insert(id);
    

    SDL_Event event;
    SDL_UserEvent userEvent;

    userEvent.type = SDL_USEREVENT;
    userEvent.code = 0;
    userEvent.data1 = NULL;
    userEvent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userEvent;

    SDL_PushEvent(&event);
    return(interval);

}


std::string Game::timer()
{
    SDL_Color textColor = { 255, 255, 255, 255 };

    std::stringstream ss;

    int time = SDL_GetTicks() / 500;
    const int seconds = time % 60;               
    const int minutes = (time / 60) % 60;
    const int hours = (time / (60 * 60)) % 24;   
    const int days = (time / (60 * 60 * 24));
    int tempHour = 0;
    int firstHour = 0;
    std::array<int, 24> hour = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23 };


    ss.str("");
    ss << std::setfill('0');
    ss << std::setw(2) << hours << ':'
        << std::setw(2) << minutes << ':'
        << std::setw(2) << seconds;


    clockTime->setup(renderer);
    clockTime->setText(ss.str());
    clockTime->draw();

    std::stringstream ss2;

    ss2.str("");

    ss2 << "Day " << days + 1;

    day->setup(renderer);
    day->setText(ss2.str());
    day->draw(); 

    /*
    for (int i = 0; i < hour.size(); i++)
    {
        if (hour[i] == tempHour)
        {
            player.getComponent<PlayerComponent>().takeDamageHunger(5);
            player.getComponent<PlayerComponent>().takeDamageSleepy(5);
        }
    }
    */
    return ss.str();

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

    farmerLifeBar.setup(renderer, 300, 810, 700, 810);

    clockTime = new Clock(1400, 50);
    day = new Clock(1400, 115);

    for (int i = 0; i < 10; i++)
    {
        playerItems[i] = 0;
    }

    playerItems[0] = 2;
    playerItems[1] = 4;
    playerItems[2] = 5;
    playerItems[3] = 7;


    itemMenu.setup(renderer, playerItems, 0, 0);
    inventoryButton.setup(renderer, {0, 800, 200, 75}, "Inventory");
    inventoryButton.selected = true;
    sleepButton.setup(renderer, { 0, 710, 200, 75 }, "Sleep");
    sleepButton.selected = false;

    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("assets/farmerAnimations3.png", true, 64, 64);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);
    player.addComponent<PlayerComponent>();

    
    crop.addComponent<TransformComponent>(500, 500, 16, 16, 1);
    crop.addComponent<SpriteComponent>("assets/tomatoGrowth.png", true, 4);
    crop.addComponent<PlantKeyboardController>(4, &itemMenu);
    crop.addGroup(groupItems);

    player.getComponent<PlayerComponent>().takeDamageHunger(5);
    player.getComponent<PlayerComponent>().takeDamageSleepy(5);
}


void Game::itemFound()
{
    bool freeSlotFound = false;
    srand(time(NULL));

    int item = rand() % 22 + 1;    

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
        if (item % 2 == 0)
        {
            infobox->setup(renderer);
            infobox->setText("Found Seed!");
            infobox->draw();
        }
        if (item % 2 != 0)
        {
            infobox->setup(renderer);
            infobox->setText("Found Crop!");
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
        auto& carrot(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        carrot.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        carrot.addComponent<SpriteComponent>("assets/carrot.png");
        carrot.addComponent<PlantKeyboardController>(1, &itemMenu);
        carrot.addGroup(groupItems);

        carrot.update();
        carrot.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 2)
    {
        auto& carrotSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        carrotSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        carrotSeed.addComponent<SpriteComponent>("assets/carrotGrowth.png", true, 2);
        carrotSeed.addComponent<PlantKeyboardController>(2, &itemMenu);
        carrotSeed.addGroup(groupItems);

        carrotSeed.update();
        carrotSeed.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 3)
    {
        auto& tomato(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        tomato.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        tomato.addComponent<SpriteComponent>("assets/tomato.png");
        tomato.addComponent<PlantKeyboardController>(3, &itemMenu);
        tomato.addGroup(groupItems);

        tomato.update();
        tomato.draw();
        SDL_RenderPresent(renderer);

    }
    if (playerItems[itemMenu.selectedItemIndex] == 4)
    {
        auto& tomatoSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        tomatoSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        tomatoSeed.addComponent<SpriteComponent>("assets/tomatoGrowth.png", true, 2);
        tomatoSeed.addComponent<PlantKeyboardController>(4, &itemMenu);
        tomatoSeed.addGroup(groupItems);

        tomatoSeed.update();
        tomatoSeed.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 5)
    {
        auto& strawberry(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        strawberry.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        strawberry.addComponent<SpriteComponent>("assets/strawberry.png");
        strawberry.addComponent<PlantKeyboardController>(5, &itemMenu);
        strawberry.addGroup(groupItems);

        strawberry.update();
        strawberry.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 6)
    {
        auto& strawberrySeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        strawberrySeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        strawberrySeed.addComponent<SpriteComponent>("assets/strawberryGrowth.png", true, 2);
        strawberrySeed.addComponent<PlantKeyboardController>(6, &itemMenu);
        strawberrySeed.addGroup(groupItems);

        strawberrySeed.update();
        strawberrySeed.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 7)
    {
        auto& pumpkin(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        pumpkin.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        pumpkin.addComponent<SpriteComponent>("assets/pumpkin.png");
        pumpkin.addComponent<PlantKeyboardController>(7, &itemMenu);
        pumpkin.addGroup(groupItems);

        pumpkin.update();
        pumpkin.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 8)
    {
        auto& pumpkinSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        pumpkinSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        pumpkinSeed.addComponent<SpriteComponent>("assets/pumpkinGrowth.png", true, 2);
        pumpkinSeed.addComponent<PlantKeyboardController>(8, &itemMenu);
        pumpkinSeed.addGroup(groupItems);

        pumpkinSeed.update();
        pumpkinSeed.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 9)
    {
        auto& corn(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        corn.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        corn.addComponent<SpriteComponent>("assets/corn.png");
        corn.addComponent<PlantKeyboardController>(9, &itemMenu);
        corn.addGroup(groupItems);

        corn.update();
        corn.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 10)
    {
        auto& cornSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        cornSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        cornSeed.addComponent<SpriteComponent>("assets/cornGrowth.png", true, 2);
        cornSeed.addComponent<PlantKeyboardController>(10, &itemMenu);
        cornSeed.addGroup(groupItems);

        cornSeed.update();
        cornSeed.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 11)
    {
        auto& potato(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        potato.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        potato.addComponent<SpriteComponent>("assets/potato.png");
        potato.addComponent<PlantKeyboardController>(11, &itemMenu);
        potato.addGroup(groupItems);

        potato.update();
        potato.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 12)
    {
        auto& potatoSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        potatoSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        potatoSeed.addComponent<SpriteComponent>("assets/potatoGrowth.png", true, 2);
        potatoSeed.addComponent<PlantKeyboardController>(12, &itemMenu);
        potatoSeed.addGroup(groupItems);

        potatoSeed.update();
        potatoSeed.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 13)
    {
        auto& watermelon(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        watermelon.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        watermelon.addComponent<SpriteComponent>("assets/watermelon.png");
        watermelon.addComponent<PlantKeyboardController>(13, &itemMenu);
        watermelon.addGroup(groupItems);

        watermelon.update();
        watermelon.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 14)
    {
        auto& watermelonSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        watermelonSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        watermelonSeed.addComponent<SpriteComponent>("assets/watermelonGrowth.png", true, 2);
        watermelonSeed.addComponent<PlantKeyboardController>(14, &itemMenu);
        watermelonSeed.addGroup(groupItems);

        watermelonSeed.update();
        watermelonSeed.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 15)
    {
        auto& radish(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        radish.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        radish.addComponent<SpriteComponent>("assets/radish.png");
        radish.addComponent<PlantKeyboardController>(15, &itemMenu);
        radish.addGroup(groupItems);

        radish.update();
        radish.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 16)
    {
        auto& radishSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        radishSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        radishSeed.addComponent<SpriteComponent>("assets/radishGrowth.png", true, 2);
        radishSeed.addComponent<PlantKeyboardController>(16, &itemMenu);
        radishSeed.addGroup(groupItems);

        radishSeed.update();
        radishSeed.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 17)
    {
        auto& lettuce(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        lettuce.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        lettuce.addComponent<SpriteComponent>("assets/lettuce.png");
        lettuce.addComponent<PlantKeyboardController>(17, &itemMenu);
        lettuce.addGroup(groupItems);

        lettuce.update();
        lettuce.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 18)
    {
        auto& lettuceSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        lettuceSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        lettuceSeed.addComponent<SpriteComponent>("assets/lettuceGrowth.png", true, 2);
        lettuceSeed.addComponent<PlantKeyboardController>(18, &itemMenu);
        lettuceSeed.addGroup(groupItems);

        lettuceSeed.update();
        lettuceSeed.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 19)
    {
        auto& wheat(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        wheat.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        wheat.addComponent<SpriteComponent>("assets/wheat.png");
        wheat.addComponent<PlantKeyboardController>(19, &itemMenu);
        wheat.addGroup(groupItems);

        wheat.update();
        wheat.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 20)
    {
        auto& wheatSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        wheatSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        wheatSeed.addComponent<SpriteComponent>("assets/wheatGrowth.png", true, 2);
        wheatSeed.addComponent<PlantKeyboardController>(20, &itemMenu);
        wheatSeed.addGroup(groupItems);

        wheatSeed.update();
        wheatSeed.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 21)
    {
        auto& plum(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        plum.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        plum.addComponent<SpriteComponent>("assets/plum.png");
        plum.addComponent<PlantKeyboardController>(21, &itemMenu);
        plum.addGroup(groupItems);

        plum.update();
        plum.draw();
        SDL_RenderPresent(renderer);
    }
    if (playerItems[itemMenu.selectedItemIndex] == 22)
    {
        auto& plumSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        plumSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        plumSeed.addComponent<SpriteComponent>("assets/plumGrowth.png", true, 2);
        plumSeed.addComponent<PlantKeyboardController>(22, &itemMenu);
        plumSeed.addGroup(groupItems);

        plumSeed.update();
        plumSeed.draw();
        SDL_RenderPresent(renderer);
    }

    playerItems[itemMenu.selectedItemIndex] = 0;

}


void Game::eatCrop(int item)
{
    int hunger = player.getComponent<PlayerComponent>().getHunger();
    bool freeSlotFound = false;

    if (hunger < 100)
    {
        player.getComponent<PlayerComponent>().eat(10);
        
    }
    else
    {
        infobox->setup(renderer);
        infobox->setText("You're Full!");
        infobox->draw();
    }
    
}


void Game::dropItem()
{
    if (playerItems[itemMenu.selectedItemIndex] == 1)
    {
        auto& carrot(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        carrot.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        carrot.addComponent<SpriteComponent>("assets/carrot.png");
        carrot.addComponent<PlantKeyboardController>(1, &itemMenu);
        carrot.addGroup(groupItems);

        carrot.update();
        carrot.draw();
        SDL_RenderPresent(renderer);
        carrot.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 2)
    {
        auto& carrotSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        carrotSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        carrotSeed.addComponent<SpriteComponent>("assets/carrotGrowth.png", true, 2);
        carrotSeed.addComponent<PlantKeyboardController>(2, &itemMenu);
        carrotSeed.addGroup(groupItems);

        carrotSeed.update();
        carrotSeed.draw();
        SDL_RenderPresent(renderer);

        carrotSeed.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 3)
    {
        auto& tomato(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        tomato.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        tomato.addComponent<SpriteComponent>("assets/tomato.png");
        tomato.addComponent<PlantKeyboardController>(3, &itemMenu);
        tomato.addGroup(groupItems);

        tomato.update();
        tomato.draw();
        SDL_RenderPresent(renderer);

        tomato.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 4)
    {
        auto& tomatoSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        tomatoSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        tomatoSeed.addComponent<SpriteComponent>("assets/tomatoGrowth.png", true, 2);
        tomatoSeed.addComponent<PlantKeyboardController>(4, &itemMenu);
        tomatoSeed.addGroup(groupItems);

        tomatoSeed.update();
        tomatoSeed.draw();
        SDL_RenderPresent(renderer);

        tomatoSeed.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 5)
    {
        auto& strawberry(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        strawberry.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        strawberry.addComponent<SpriteComponent>("assets/strawberry.png");
        strawberry.addComponent<PlantKeyboardController>(5, &itemMenu);
        strawberry.addGroup(groupItems);

        strawberry.update();
        strawberry.draw();
        SDL_RenderPresent(renderer);

        strawberry.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 6)
    {
        auto& strawberrySeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        strawberrySeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        strawberrySeed.addComponent<SpriteComponent>("assets/strawberryGrowth.png", true, 2);
        strawberrySeed.addComponent<PlantKeyboardController>(6, &itemMenu);
        strawberrySeed.addGroup(groupItems);

        strawberrySeed.update();
        strawberrySeed.draw();
        SDL_RenderPresent(renderer);

        strawberrySeed.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 7)
    {
        auto& pumpkin(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        pumpkin.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        pumpkin.addComponent<SpriteComponent>("assets/pumpkin.png");
        pumpkin.addComponent<PlantKeyboardController>(7, &itemMenu);
        pumpkin.addGroup(groupItems);

        pumpkin.update();
        pumpkin.draw();
        SDL_RenderPresent(renderer);

        pumpkin.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 8)
    {
        auto& pumpkinSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        pumpkinSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        pumpkinSeed.addComponent<SpriteComponent>("assets/pumpkinGrowth.png", true, 2);
        pumpkinSeed.addComponent<PlantKeyboardController>(8, &itemMenu);
        pumpkinSeed.addGroup(groupItems);

        pumpkinSeed.update();
        pumpkinSeed.draw();
        SDL_RenderPresent(renderer);

        pumpkinSeed.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 9)
    {
        auto& corn(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        corn.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        corn.addComponent<SpriteComponent>("assets/corn.png");
        corn.addComponent<PlantKeyboardController>(9, &itemMenu);
        corn.addGroup(groupItems);

        corn.update();
        corn.draw();
        SDL_RenderPresent(renderer);

        corn.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 10)
    {
        auto& cornSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        cornSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        cornSeed.addComponent<SpriteComponent>("assets/cornGrowth.png", true, 2);
        cornSeed.addComponent<PlantKeyboardController>(10, &itemMenu);
        cornSeed.addGroup(groupItems);

        cornSeed.update();
        cornSeed.draw();
        SDL_RenderPresent(renderer);

        cornSeed.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 11)
    {
        auto& potato(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        potato.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        potato.addComponent<SpriteComponent>("assets/potato.png");
        potato.addComponent<PlantKeyboardController>(11, &itemMenu);
        potato.addGroup(groupItems);

        potato.update();
        potato.draw();
        SDL_RenderPresent(renderer);

        potato.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 12)
    {
        auto& potatoSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        potatoSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        potatoSeed.addComponent<SpriteComponent>("assets/potatoGrowth.png", true, 2);
        potatoSeed.addComponent<PlantKeyboardController>(12, &itemMenu);
        potatoSeed.addGroup(groupItems);

        potatoSeed.update();
        potatoSeed.draw();
        SDL_RenderPresent(renderer);

        potatoSeed.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 13)
    {
        auto& watermelon(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        watermelon.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        watermelon.addComponent<SpriteComponent>("assets/watermelon.png");
        watermelon.addComponent<PlantKeyboardController>(13, &itemMenu);
        watermelon.addGroup(groupItems);

        watermelon.update();
        watermelon.draw();
        SDL_RenderPresent(renderer);

        watermelon.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 14)
    {
        auto& watermelonSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        watermelonSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        watermelonSeed.addComponent<SpriteComponent>("assets/watermelonGrowth.png", true, 2);
        watermelonSeed.addComponent<PlantKeyboardController>(14, &itemMenu);
        watermelonSeed.addGroup(groupItems);

        watermelonSeed.update();
        watermelonSeed.draw();
        SDL_RenderPresent(renderer);

        watermelonSeed.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 15)
    {
        auto& radish(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        radish.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        radish.addComponent<SpriteComponent>("assets/radish.png");
        radish.addComponent<PlantKeyboardController>(15, &itemMenu);
        radish.addGroup(groupItems);

        radish.update();
        radish.draw();
        SDL_RenderPresent(renderer);

        radish.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 16)
    {
        auto& radishSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        radishSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        radishSeed.addComponent<SpriteComponent>("assets/radishGrowth.png", true, 2);
        radishSeed.addComponent<PlantKeyboardController>(16, &itemMenu);
        radishSeed.addGroup(groupItems);

        radishSeed.update();
        radishSeed.draw();
        SDL_RenderPresent(renderer);

        radishSeed.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 17)
    {
        auto& lettuce(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        lettuce.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        lettuce.addComponent<SpriteComponent>("assets/lettuce.png");
        lettuce.addComponent<PlantKeyboardController>(17, &itemMenu);
        lettuce.addGroup(groupItems);

        lettuce.update();
        lettuce.draw();
        SDL_RenderPresent(renderer);

        lettuce.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 18)
    {
        auto& lettuceSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        lettuceSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        lettuceSeed.addComponent<SpriteComponent>("assets/lettuceGrowth.png", true, 2);
        lettuceSeed.addComponent<PlantKeyboardController>(18, &itemMenu);
        lettuceSeed.addGroup(groupItems);

        lettuceSeed.update();
        lettuceSeed.draw();
        SDL_RenderPresent(renderer);

        lettuceSeed.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 19)
    {
        auto& wheat(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        wheat.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        wheat.addComponent<SpriteComponent>("assets/wheat.png");
        wheat.addComponent<PlantKeyboardController>(19, &itemMenu);
        wheat.addGroup(groupItems);

        wheat.update();
        wheat.draw();
        SDL_RenderPresent(renderer);

        wheat.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 20)
    {
        auto& wheatSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        wheatSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        wheatSeed.addComponent<SpriteComponent>("assets/wheatGrowth.png", true, 2);
        wheatSeed.addComponent<PlantKeyboardController>(20, &itemMenu);
        wheatSeed.addGroup(groupItems);

        wheatSeed.update();
        wheatSeed.draw();
        SDL_RenderPresent(renderer);

        wheatSeed.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 21)
    {
        auto& plum(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        plum.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        plum.addComponent<SpriteComponent>("assets/plum.png");
        plum.addComponent<PlantKeyboardController>(21, &itemMenu);
        plum.addGroup(groupItems);

        plum.update();
        plum.draw();
        SDL_RenderPresent(renderer);

        plum.getComponent<SpriteComponent>().~SpriteComponent();
    }
    if (playerItems[itemMenu.selectedItemIndex] == 22)
    {
        auto& plumSeed(manager.addEntity());

        auto playerPosition = player.getComponent<TransformComponent>().position;

        plumSeed.addComponent<TransformComponent>(playerPosition.x, playerPosition.y, 16, 16, 1);
        plumSeed.addComponent<SpriteComponent>("assets/plumGrowth.png", true, 2);
        plumSeed.addComponent<PlantKeyboardController>(22, &itemMenu);
        plumSeed.addGroup(groupItems);

        plumSeed.update();
        plumSeed.draw();
        SDL_RenderPresent(renderer);

        plumSeed.getComponent<SpriteComponent>().~SpriteComponent();
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
            break;
        case SDL_SCANCODE_1:
            itemMenu.buttonVisible = true;
            break;
        case SDL_SCANCODE_TAB: 
            itemMenu.buttonVisible = false;
            break;
        default:
            break;
        }
    }

    if (event.key.keysym.scancode == SDL_SCANCODE_UP)
    {
        sleepButton.selected = true;
        inventoryButton.selected = false;
    }

    if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
    {
        sleepButton.selected = false;
        inventoryButton.selected = true;
    } 

    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        int x = event.button.x;
        int y = event.button.y;
        auto inventoryRect = inventoryButton.buttonRect;
        auto sleepRect = sleepButton.buttonRect;
        auto cancelTexture = itemMenu.cancel;

        if (sleepButton.selected == true)
        {
            if (x > sleepRect.x && x < sleepRect.x + sleepRect.w && y > sleepRect.y && sleepRect.y + sleepRect.h)
            {
                LoadScreen::loadScreen("assets/sleep.bmp", 3000);
                player.getComponent<PlayerComponent>().sleep(100);
                infobox->setup(renderer);
                infobox->setText("You are now well rested!");
                infobox->draw();
            }
        }

        if (inventoryButton.selected == true)
        {
            if (x > inventoryRect.x && x < inventoryRect.x + inventoryRect.w && y > inventoryRect.y && inventoryRect.y + inventoryRect.h)
            {
                itemMenu.visible = true;
            }
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
                        chest->getComponent<SpriteComponent>().~SpriteComponent();
                    }
                }
        } 

    }

    if (itemMenu.visible)
    {
        if (event.type == SDL_KEYDOWN)
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
        }

        if (itemMenu.selectedItemIndex == 10 && event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_RETURN:
                itemMenu.visible = false;
                break;
            default:
                break;
            }
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

    crop.update();

    farmerLifeBar.hunger = player.getComponent<PlayerComponent>().getHunger();
    farmerLifeBar.sleepy = player.getComponent<PlayerComponent>().getSleep();
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

    clockTime->setup(renderer);
    clockTime->draw();

    day->setup(renderer);
    day->draw();

    inventoryButton.draw();
    sleepButton.draw();
    itemMenu.draw();

    farmerLifeBar.draw();

    // Add items to render:
    SDL_RenderPresent(renderer);
}


void Game::removeTimer(SDL_TimerID id)
{
    if (SDL_RemoveTimer(id) == SDL_FALSE)
    {
        std::cout << "Error, timer not removed" << std::endl;
    }
    else
    {
        timers.erase(id);
    }
}


void Game::saveGame()
{
         

}


void Game::loadGame()
{
    

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

