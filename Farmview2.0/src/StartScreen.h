#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <SDL.h>

class StartScreen {
public:
    StartScreen();
    ~StartScreen();

    void update();
    void draw();

private:
    SDL_Texture* farmviewTitle;
    SDL_Texture* loadGame;
    SDL_Texture* newGame;
    SDL_Texture* settings;
    SDL_Texture* quitGame;

};


#endif 

