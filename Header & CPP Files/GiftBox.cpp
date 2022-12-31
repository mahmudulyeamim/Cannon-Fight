#include "GiftBox.hpp"
#include "TextureManager.hpp"
#include "Menu.hpp"

GiftBox:: GiftBox(const char *filename, int posX, int posY, int dim, const char *filename1, const char *filename2, const char *filename3, int featureX, int featureY)
{
    box = TextureManager:: loadTexture(filename);
    boxDestRect = {posX, posY, dim, dim};
    x = posX + 13;
    y = posY + 13;
    dimension = dim - 26;
    
    healthIncrease = TextureManager:: loadTexture(filename1);
    doubleDamage = TextureManager:: loadTexture(filename2);
    twiceTurn = TextureManager:: loadTexture(filename3);
    featureDestRect = {featureX, featureY, dim, dim};
    midx = featureX + 13;
    midy = featureY + 13;
    
}

void GiftBox:: init(const char* filename)
{
    box = TextureManager:: loadTexture(filename);
    boxUsed = false;
}

int GiftBox:: checkMouseClick(int mouseX, int mouseY, int againstComputer)
{
    if(againstComputer == true)
    {
        box = TextureManager:: loadTexture("gift1.png");
        boxUsed = true;
        return rand() % 3;
    }
    bool inside = true;
    if(mouseX < x)
    {
        inside = false;
    }
    else if(mouseX > x + dimension)
    {
        inside = false;
    }
    else if(mouseY < y)
    {
        inside = false;
    }
    else if(mouseY > y + dimension)
    {
        inside = false;
    }
    
    if(inside == true && boxUsed == false)
    {
        box = TextureManager:: loadTexture("gift1.png");
        boxUsed = true;
        return rand() % 3;
    }
    return -1;
}

void GiftBox:: renderFeature(int flag)
{
    if(flag == 0)
    {
        SDL_RenderCopy(Menu:: renderer, healthIncrease, NULL, &featureDestRect);
    }
    else if(flag == 1)
    {
        SDL_RenderCopy(Menu:: renderer, doubleDamage, NULL, &featureDestRect);
    }
    else if(flag == 2)
    {
        SDL_RenderCopy(Menu:: renderer, twiceTurn, NULL, &featureDestRect);
    }
}

void GiftBox::render()
{
    SDL_RenderCopy(Menu:: renderer, box, NULL, &boxDestRect);
}
