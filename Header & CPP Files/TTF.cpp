#include "TTF.hpp"
#include "Menu.hpp"

SDL_Rect TTF:: turnDest;
SDL_Rect TTF:: timerDest;

SDL_Texture* loadTTF(const char* text, const char* fontName, int fontSize, SDL_Color textColor, int flag)
{
    TTF_Font* font = TTF_OpenFont(fontName, fontSize);
    
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* ttfTexture = NULL;
    if(textSurface == NULL)
    {
        printf("Unable to load text surface : %s", TTF_GetError());
    }
    else
    {
        ttfTexture = SDL_CreateTextureFromSurface(Menu:: renderer, textSurface);
        if(ttfTexture == NULL)
        {
            printf("Unable to create ttf texture : %s", SDL_GetError());
        }
        if(flag == 0)
        {
            TTF:: turnDest = {(1200-textSurface->w)/2, 0, textSurface->w, textSurface->h};
        }
        if(flag == 1)
        {
            TTF:: timerDest = {(1200-textSurface->w)/2, 20, textSurface->w, textSurface->h};
        }
    }
    SDL_FreeSurface(textSurface);
    return ttfTexture;
}

TTF:: TTF(const char* fontName)
{
//    font = fontName;
//    leftPlayer = loadTTF("TURN: LEFT PLAYER", fontName, 20, {255, 255, 255, 255}, 0);
//    rightPlayer = loadTTF("TURN: RIGHT PLAYER", fontName, 20, {255, 255, 255, 255}, 0);
    
    SDL_Color textColor = {0, 0, 0, 255};
    
    TTF_Font* font = TTF_OpenFont(fontName, 20);
    
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "WIND", textColor);
    SDL_Texture* ttfTexture = NULL;
    if(textSurface == NULL)
    {
        printf("Unable to load text surface : %s", TTF_GetError());
    }
    else
    {
        ttfTexture = SDL_CreateTextureFromSurface(Menu:: renderer, textSurface);
        if(ttfTexture == NULL)
        {
            printf("Unable to create ttf texture : %s", SDL_GetError());
        }
        windDest = {(Game::screenWidth-textSurface->w)/2, 5, textSurface->w, textSurface->h};
    }
    SDL_FreeSurface(textSurface);
    wind = ttfTexture;
    
}

void TTF:: update(bool leftPlay, int startTime)
{
//    if(leftPlay)
//    {
//        currentPlayer = leftPlayer;
//    }
//    else
//    {
//        currentPlayer = rightPlayer;
//    }
//    timeText.str("");
//    timeText << "Time remaining: " << startTime - SDL_GetTicks()/1000;
//    timer = loadTTF(timeText.str().c_str(), font, 20, {255, 255, 255, 255}, 1);
}

void TTF:: render()
{
//    SDL_RenderCopy(Game:: renderer, currentPlayer, NULL, &turnDest);
//    SDL_RenderCopy(Game:: renderer, timer, NULL, &timerDest);
    SDL_RenderCopy(Menu:: renderer, wind, NULL, &windDest);
}

