#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include <set>


// Forward declaration of "ColliderComponent" component:
class ColliderComponent;

class Game 
/* Game creates the overall game of Farmview with contributions from all files */
{
public:
    // Destructor destroys the game:
    ~Game();

    // Constructor creates the game:
    Game();

    // Returns value based on isRunning:
    bool running() { return isRunning; };

    // Initializes the SDL for game:
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    
    // Handle keyboard and mouse events in the game:
    void handleEvents();

    // Updates the game when a change has been made:
    void update();

    // Displays update to screen:
    void render();

    // Cleans the game of any memory and exits the game:
    void close();

    static SDL_Renderer* renderer;
    static SDL_Event event;
    static bool isRunning;
    static SDL_Rect camera;

    enum groupLabels : std::size_t
    {
        groupMap,
        groupPlayers,
        groupItems,
        groupColliders,
        groupChests
    };

    enum groupItemLabels : std::size_t
    {
        groupCrops,
    };

    SDL_Texture* inventoryTexture;

    void useItem();

    void itemFound();

    SDL_TimerID addTimer(Uint32 delay, SDL_TimerCallback callback, void* param);
    SDL_TimerID addRecurringTimer(Uint32 interval, SDL_TimerCallback callback, void* param);
    void removeTimer(SDL_TimerID id);
    std::set<SDL_TimerID> timers;

    std::string timer();

    void eatCrop(int item);


private:
    SDL_Window* window;
};



#endif

