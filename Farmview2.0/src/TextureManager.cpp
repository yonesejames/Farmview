#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* filePath)
{
    SDL_Surface* temporarySurface = IMG_Load(filePath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, temporarySurface);

    SDL_FreeSurface(temporarySurface);

    return texture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect destination, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer, texture, &source, &destination, NULL, NULL, flip);
}