#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>

class Menu
{
public:
    Menu(){}

    int showMenu(SDL_Surface* screen, TTF_Font* font)
    {
        Uint32 time;
        int x;
        int y;
        const int NUMMENU = 4;
        const char* labels[NUMMENU] = { "Load Game", "Play New Game", "Settings", "Quit Game" };
        SDL_Surface* menus[NUMMENU];
        bool selected[NUMMENU] = { 0,0 };
        SDL_Color color[2] = { {255,255,255}, {255,0,0} };
        
        menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
        menus[1] = TTF_RenderText_Solid(font, labels[1], color[0]);
        menus[2] = TTF_RenderText_Solid(font, labels[2], color[0]);
        menus[3] = TTF_RenderText_Solid(font, labels[3], color[0]);

        SDL_Rect position[NUMMENU];

        position[0].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
        position[0].y = screen->clip_rect.h / 4 - menus[0]->clip_rect.h;

        position[1].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
        position[1].y = screen->clip_rect.h / 4 + menus[0]->clip_rect.h;


        position[2].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
        position[2].y = screen->clip_rect.h / 4 + menus[0]->clip_rect.h;


        position[3].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
        position[3].y = screen->clip_rect.h / 4 + menus[0]->clip_rect.h;

        SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
        
        SDL_Event event;
        while (1)
        {
            time = SDL_GetTicks();
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    for (int i = 0; i < NUMMENU; i++)
                    {
                        SDL_FreeSurface(menus[i]);
                    }
                    return 1;
                    break;
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;

                    for (int i = 0; i < NUMMENU; i++)
                    {
                        if (x >= position[i].x && x <= position[i].x + position[i].w &&
                            y >= position[i].y && y <= position[i].h)
                        {
                            if (!selected[i])
                            {
                                selected[i] = 1;
                                SDL_FreeSurface(menus[i]);
                                menus[i] = TTF_RenderText_Solid(font, menus[i], color[1]);
                            }
                            else
                            {
                                if (selected[i] = 0)
                                {
                                    selected[i] = 0;
                                    SDL_FreeSurface(menus[i]);
                                    menus[i] = TTF_RenderText_Solid(font, menus[i], color[0]);
                                }
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;

                    for (int i = 0; i < NUMMENU; i++)
                    {
                        if (x >= position[i].x && x <= position[i].x + position[i].w &&
                            y >= position[i].y && y <= position[i].h)
                        {
                            return i;
                        }

                    }
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        return 0;
                    }
                }                
            }
        }
    }



};

#endif
