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

SDL_Rect Game::camera = { 0, 0, 1600, 880 };

auto& player(manager.addEntity());

bool Game::isRunning = false;

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
            LoadScreen::loadScreen("assets/farmviewOpen.bmp", 3000);
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

    map = new Map("assets/farmviewStartingMapTileSet.png", 2, 16);

    //ECS Implementation:
    map->loadMap("assets/farmviewStartingMapTileMap.map", 100, 55);

    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("assets/farmer_animations2.png", true);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& players(manager.getGroup(Game::groupPlayers));


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

    SDL_Rect playerCollider = player.getComponent<ColliderComponent>().collider;
    Vector playerPosition = player.getComponent<TransformComponent>().position;

    // ECS delete dead entities and updates them:
    manager.refresh();
    manager.update();

    for (auto& c : colliders)
    {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if (Collision::AABB(cCol, playerCollider))
        {
            player.getComponent<TransformComponent>().position = playerPosition;
        }
    }

    camera.x = player.getComponent<TransformComponent>().position.x - 800;
    camera.y = player.getComponent<TransformComponent>().position.y - 440;

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

}

void Game::render()
/* Function that renders objects on the screen */
{
    // Clear what is currently in the renderer's buffer:
    SDL_RenderClear(renderer);

    for (auto& tile : tiles)
    {
        tile->draw();
    }

    for (auto& collider : colliders)
    {
        collider->draw();
    }

    for (auto& player : players)
    {
        player->draw();
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

