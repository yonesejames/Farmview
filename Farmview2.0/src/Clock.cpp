#include "Clock.h"

Clock::Clock(int x, int y)
/* Constructor that loads font in 16 size */
{
    font = TTF_OpenFont("assets/Walkway_SemiBold.ttf", 48);
    this->x = x;
    this->y = y;
}

Clock::~Clock()
{
    if (textTexture != NULL)
    {
        SDL_DestroyTexture(textTexture);
    }

    TTF_CloseFont(font);
}

void Clock::setup(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

void Clock::setText(std::string text)
{
    if (this->text != text && text != "")
    {
        // Destroy old text texture before creating a new one:
        if (textTexture != NULL)
        {
            SDL_DestroyTexture(textTexture);
        }

        this->text = text;

        // Build text texture using font and text string:
        SDL_Color textColor = { 255, 255, 255, 255 };
        // Create surface out of our text:
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
        // Convert surface into texture:
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        // Delete surface:
        SDL_FreeSurface(textSurface);

        // Work out width and height of generated texture:
        SDL_QueryTexture(textTexture, NULL, NULL, &textRectangle.w, &textRectangle.h);

        // Work out how to center the text on the screen:
        textRectangle.x = x - textRectangle.w / 2; // Half screen - half width
        textRectangle.y = y  - textRectangle.h / 2; // Half screen - half height

        // Work out box rectangle with some padding:
        boxRectangle.x = textRectangle.x - 4; // Add 4 pixels of padding
        boxRectangle.y = textRectangle.y - 4; // Add 4 pixels of padding
        boxRectangle.w = textRectangle.w + 8; // Add 8 pixels of padding
        boxRectangle.h = textRectangle.h + 8; // Add 8 pixels of padding
    }
}

void Clock::draw()
{
    if (visible && textTexture != NULL && text != "")
    {
        // Draw box:
        SDL_SetRenderDrawColor(renderer, 8, 43, 20, 255);
        SDL_RenderFillRect(renderer, &boxRectangle);

        // Draw border:
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &boxRectangle);

        // Draw text on box:
        SDL_RenderCopy(renderer, textTexture, NULL, &textRectangle);
    }

}
