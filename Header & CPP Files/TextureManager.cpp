#include "TextureManager.hpp"
#include "Menu.hpp"

SDL_Texture* TextureManager:: loadTexture(const char* filename)
{
    SDL_Surface *tempSurface = NULL;
    tempSurface = IMG_Load(filename);
    SDL_Texture *tempTex = NULL;
    if(tempSurface == NULL)
    {
        printf("Could not load image %s\n", IMG_GetError());
    }
    else
    {
        printf("Loaded image %s\n", filename);
        tempTex = SDL_CreateTextureFromSurface(Menu::renderer, tempSurface);
    }
    SDL_FreeSurface(tempSurface);
    return tempTex;
}
