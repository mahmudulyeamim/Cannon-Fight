#include "Sprite.hpp"
#include "TextureManager.hpp"
#include "Menu.hpp"


Sprite:: Sprite(const char* filename, int w, int h, int spriteW, int spriteH, int flag)
{
    no = flag;
    sprite[no] = TextureManager:: loadTexture(filename);

    width = w;
    height = h;
    spriteWidth = spriteW;
    spriteHeight = spriteH;
    
    if(flag == 0)
    {
        defaultSrc[0] = {width/2, 0, width/2, height};
        defaultSrc[1] = {0, 0, width/2, height};
        
    }
    else if(flag == 1 || flag == 2)
    {
        walkSrc[0] = {width/12*11, 0, width/12, height};
        walkSrc[1] = {width/12*10, 0, width/12, height};
        walkSrc[2] = {width/12*9, 0, width/12, height};
        walkSrc[3] = {width/12*8, 0, width/12, height};
        walkSrc[4] = {width/12*7, 0, width/12, height};
        walkSrc[5] = {width/12*6, 0, width/12, height};
        walkSrc[6] = {width/12*5, 0, width/12, height};
        walkSrc[7] = {width/12*4, 0, width/12, height};
        walkSrc[8] = {width/12*3, 0, width/12, height};
        walkSrc[9] = {width/12*2, 0, width/12, height};
        walkSrc[10] = {width/12, 0, width/12, height};
        walkSrc[11] = {0, 0, width/12, height};
    }
    else if(flag == 3 || flag == 4)
    {
        ladderSrc[0] = {0, 0, width/9, height};
        ladderSrc[1] = {width/9, 0, width/9, height};
        ladderSrc[2] = {width/9*2, 0, width/9, height};
        ladderSrc[3] = {width/9*3, 0, width/9, height};
        ladderSrc[4] = {width/9*4, 0, width/9, height};
        ladderSrc[5] = {width/9*5, 0, width/9, height};
        ladderSrc[6] = {width/9*6, 0, width/9, height};
        ladderSrc[7] = {width/9*7, 0, width/9, height};
        ladderSrc[8] = {width/9*8, 0, width/9, height};
    }
}

void Sprite:: update(int frame, int flag, int x, int y, bool left)
{
    if(flag == 0)
    {
        if(left)
            currentSrc = defaultSrc[frame];
        else
            currentSrc = defaultSrc[1-frame];
        defaultDest = {x, y, spriteWidth, spriteHeight};
    }
    else if(flag == 1)
    {
        currentSrc = walkSrc[11-frame];
        defaultDest = {x, y, spriteWidth, spriteHeight};
    }
    else if(flag == 2)
    {
        currentSrc = walkSrc[frame];
        defaultDest = {x, y, spriteWidth, spriteHeight};
    }
    else if(flag == 3 || flag == 4)
    {
        currentSrc = ladderSrc[frame];
        defaultDest = {x, y, spriteWidth, spriteHeight};
    }
    
    currentDest = defaultDest;
}

void Sprite:: render()
{
    SDL_RenderCopy(Menu:: renderer, sprite[no], &currentSrc, &currentDest);
}
