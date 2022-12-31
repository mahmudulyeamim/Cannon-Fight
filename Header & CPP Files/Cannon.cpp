#include "Cannon.hpp"
#include "TextureManager.hpp"
#include "Menu.hpp"

Cannon:: Cannon(const char* filename, int x, int y)
{
    cann = TextureManager:: loadTexture(filename);
    destR = {x, y, 80, 80};
    centre = {208/5, 305/5};
}

void Cannon:: update()
{
}

void Cannon:: render(double degree)
{
    SDL_RenderCopyEx(Menu:: renderer, cann, NULL, &destR, degree, &centre, SDL_FLIP_NONE);
}
