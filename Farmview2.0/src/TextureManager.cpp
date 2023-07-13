#include "TextureManager.h"
#include <SDL2_image/SDL_image.h>

SDL_Texture* TextureManager::loadTexture(const char* filePath)
/* Function that returns a texture when given a filepath. */
{
    SDL_Surface* temporarySurface = IMG_Load(filePath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, temporarySurface);

    SDL_FreeSurface(temporarySurface);

    return texture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect destination, SDL_RendererFlip flip)
/*
    Function that copies a portion of the texture to the current rendering, 
    with optional rotation and flipping.
*/
{
    SDL_RenderCopyEx(Game::renderer, texture, &source, &destination, NULL, NULL, flip);
}

