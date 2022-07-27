#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS.h"
#include "Components.h"
#include "LoadScreen.h"
#include "Vector.h"
#include "Collision.h"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = { nullptr };
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupVillagers,
    groupColliders
};

Game::Game()
/* Game constructor: Creates Game */
{
    
}

Game::~Game()
/* Game destructor: Destroys Game */
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
    {
        std::cout << "Subsystem Initialized" << std::endl;

        // Creates window and prints out success message if completed or error if not: 
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);
        if (window)
        {
            //LoadScreen::loadScreen("assets/farmviewOpen.bmp", 3000);

            std::cout << "Window has been created!" << std::endl;
        } 
        else
        {
            std::cout << "Window could not be created due to: " << SDL_GetError() << std::endl;
        }

        // Creates renderer and prints out success message if completed or error if not: 
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {

            LoadScreen::loadScreen("assets/farmview.bmp", 3000);
            std::cout << "Renderer has been created!" << std::endl;
        }
        else
        {
            std::cout << "Renderer could not be created due to: " << SDL_GetError() << std::endl;
        }

        // If SDL initializes correctly then isRunning is set to true:
        isRunning = true;


    } 
    else
    {
        // If SDL initializes incorrectly then isRunning is set to false:
        isRunning = false;

        std::cout << "SDL could not initialize due to: " << SDL_GetError() << std::endl;
        
    }

    //ECS Implementation:
    Map::loadMap("assets/farmviewMap_2000x1000.map", 20, 10);

    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("assets/farmer_animations.png", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

    wall.addComponent<TransformComponent>(500.0f, 500.0f, 300, 20, 1);
    wall.addComponent<SpriteComponent>("assets/dirt.png");
    wall.addComponent<ColliderComponent>("wall");
    wall.addGroup(groupMap);

}

void Game::handleEvents()
/* Function that handle keyboard events */
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
    
   
    /*
    // While loop that handles events in the queue, so if there are events in queue:
    while (SDL_PollEvent(&event) != 0)
    {
        // User requests to quit:
        if (event.type == SDL_QUIT)
        {
            LoadScreen::loadScreen("assets/farmviewExit.bmp", window, 1000);

            isRunning = false;
        }
    }
    */
    
}

void Game::update()
/* Function that updates */
{
    // ECS delete dead entities and updates them:
    manager.refresh();
    manager.update();

    for (auto collider : colliders) 
    {
        Collision::AABB(player.getComponent<ColliderComponent>(), *collider);
    }

}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& villagers(manager.getGroup(groupVillagers));

void Game::render()
/* Function that renders objects on the screen */
{
    // Clear what is currently in the renderer's buffer:
    SDL_RenderClear(renderer);

    for (auto& tile : tiles)
    {
        tile->draw();
    }

    for (auto& player : players)
    {
        player->draw();
    }

    for (auto& villager : villagers)
    {
        villager->draw();
    }


    // Add items to render:
    SDL_RenderPresent(renderer);
}

void Game::close()
/* Function that cleans up any pointers by returning it to memory and quits game */
{
    // Deallocate and destroys window and renderer because they were allocated memory:
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();

    std::cout << "Game has been cleaned and closed!" << std::endl;
}


void Game::addTile(int id, int x, int y)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 100, 100, id);
    tile.addGroup(groupMap);
}
