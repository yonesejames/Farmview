#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

class ColliderComponent;

class Game 
{
public:
    Game();
    ~Game();

    bool running() { return isRunning; };

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void close();

    static void addTile(int id, int x, int y);

    static SDL_Renderer* renderer;
    static SDL_Event event;

    static std::vector<ColliderComponent*> colliders;

private:
    int count = 0;
    bool isRunning;
    SDL_Window* window;
};

#endif
