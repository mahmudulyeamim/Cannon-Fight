#include "ProgressBar.hpp"
#include "Menu.hpp"


float ProgressBar:: timeW = 80;
float ProgressBar:: timeH = 7;
int ProgressBar:: healthW = 400;
int ProgressBar:: healthH = 20;
int ProgressBar:: velocityW = 350;
int ProgressBar:: velocityH = 10;
int ProgressBar:: windDir;
int ProgressBar:: windSpeed = 0;
bool ProgressBar:: pressedLeft;
bool ProgressBar:: pressedSpace = false;
SDL_Rect ProgressBar:: timeLeft;
SDL_Rect ProgressBar:: timeBG = {0, 0, (int)timeW, (int)timeH};
SDL_Rect ProgressBar:: timeOutline = {0, 0, (int)timeW, (int)timeH};
SDL_Rect ProgressBar:: healthLeft = {20, 11, healthW, healthH};
SDL_Rect ProgressBar:: healthBGLeft = {20, 11, healthW, healthH};
SDL_Rect ProgressBar:: healthOutlineLeft = {20, 11, healthW, healthH};
SDL_Rect ProgressBar:: healthRight = {Game::screenWidth-20-healthW, 11, healthW, healthH};
SDL_Rect ProgressBar:: healthBGRight = {Game::screenWidth-20-healthW, 11, healthW, healthH};
SDL_Rect ProgressBar:: healthOutlineRight = {Game::screenWidth-20-healthW, 11, healthW, healthH};
SDL_Rect ProgressBar:: velocity = {10, 35 + 12, 0, velocityH};
SDL_Rect ProgressBar:: velocityBG = {10, 35 + 12, velocityW, velocityH};
SDL_Rect ProgressBar:: velocityOutline = {10, 32 + 12, velocityW+7, velocityH+7};
SDL_Rect ProgressBar:: velocityOutlineLeft = {10 + 6, 32 + 12, velocityW+7, velocityH+7};
SDL_Rect ProgressBar:: velocityOutlineRight = {Game::screenWidth - (velocityW+7) - 17, 32 + 12, velocityW+7, velocityH+7};
SDL_Rect ProgressBar:: windTTF = {Game::screenWidth/2 - 70, 7, 140, 20};
SDL_Rect ProgressBar:: windBar1 = {Game::screenWidth/2 - 60, 22, 120, 30};
SDL_Rect ProgressBar:: windBar2 = {Game::screenWidth/2 - 50, 38, 100, 1};
SDL_Rect ProgressBar:: windBar3 = {Game::screenWidth/2 - 45, 33, 90, 12};
SDL_Rect ProgressBar:: windRight = {Game::screenWidth/2, 34, 0, 10};
SDL_Rect ProgressBar:: windLeft = {Game::screenWidth/2, 34, 0, 10};

void ProgressBar:: init()
{
    pressedSpace = false;
    windSpeed = 0;
    windSpeed = 15;
    timeLeft.w = timeW;
    healthLeft.w = healthW;
    healthRight.w = healthW;
    velocity.w = 0;
    windRight.w = 0;
    windLeft.w = 0;
}

void ProgressBar:: update(int t, int spriteX, int spriteY)
{
    float remTime;
    remTime = (t > SDL_GetTicks()/1000)? t - SDL_GetTicks()/1000 : 0;
    
    timeLeft = {spriteX-15, spriteY-10, (int) (remTime * 4), (int)timeH};

    timeBG.x = timeOutline.x = spriteX - 15;
    timeBG.y = timeOutline.y = spriteY - 10;
        
    if(pressedSpace)
    {
        if(velocity.w < velocityW)
        {
            velocity.w += 5;
        }
        
        if(pressedLeft)
        {
            velocity.x = velocityBG.x = 20;
            
        }
        else
        {
            velocity.x = velocityBG.x = Game:: screenWidth - 20 - velocityW;
        }
        velocityOutline.x = velocity.x -4;
    }
    else
    {
        velocity.w = 0;
    }
    if(windDir == 0) // right direction
    {
        windRight.w = windSpeed;
    }
    else // left direction
    {
        windLeft.x = Game::screenWidth/2 - windSpeed;
        windLeft.w = windSpeed;
    }
}

void ProgressBar:: render()
{
    SDL_SetRenderDrawColor(Menu:: renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(Menu:: renderer, &timeBG);
    
    SDL_SetRenderDrawColor(Menu:: renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(Menu:: renderer, &timeLeft);
    
    SDL_SetRenderDrawColor(Menu:: renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(Menu:: renderer, &timeOutline);
    
    
    roundedBoxRGBA(Menu:: renderer, healthBGLeft.x + healthBGLeft.w + 4, healthBGLeft.y - 4, healthBGLeft.x - 4, healthBGLeft.y + healthBGLeft.h + 4, 10, 0xFF, 0xA5, 0x00, 255);
    roundedRectangleRGBA(Menu:: renderer, healthBGLeft.x + healthBGLeft.w + 4, healthBGLeft.y - 4, healthBGLeft.x - 4, healthBGLeft.y + healthBGLeft.h + 4, 10, 0xDF, 0x36, 0x2D, 255);
    roundedBoxRGBA(Menu:: renderer, healthBGLeft.x + healthBGLeft.w, healthBGLeft.y, healthBGLeft.x, healthBGLeft.y + healthBGLeft.h, 8, 255, 255, 255, 255);
    roundedBoxRGBA(Menu:: renderer, healthLeft.x + healthLeft.w, healthLeft.y, healthLeft.x, healthLeft.y + healthLeft.h, 8, 255, 0, 0, 255);
    roundedRectangleRGBA(Menu:: renderer, healthOutlineLeft.x + healthOutlineLeft.w, healthOutlineLeft.y, healthOutlineLeft.x, healthOutlineLeft.y + healthOutlineLeft.h, 8, 0, 0, 0, 255);
    
    
    roundedBoxRGBA(Menu:: renderer, healthBGRight.x + healthBGRight.w + 4, healthBGRight.y - 4, healthBGRight.x - 4, healthBGRight.y + healthBGRight.h + 4, 10, 0xFF, 0xA5, 0x00, 255);
    roundedRectangleRGBA(Menu:: renderer, healthBGRight.x + healthBGRight.w + 4, healthBGRight.y - 4, healthBGRight.x - 4, healthBGRight.y + healthBGRight.h + 4, 10, 0xDF, 0x36, 0x2D, 255);
    roundedBoxRGBA(Menu:: renderer, healthBGRight.x + healthBGRight.w, healthBGRight.y, healthBGRight.x, healthBGRight.y + healthBGRight.h, 8, 255, 255, 255, 255);
    roundedBoxRGBA(Menu:: renderer, healthRight.x + healthW, healthRight.y, healthRight.x + (healthW - healthRight.w), healthRight.y + healthRight.h, 8, 255, 0, 0, 255);
    roundedRectangleRGBA(Menu:: renderer, healthOutlineRight.x + healthOutlineRight.w, healthOutlineRight.y, healthOutlineRight.x, healthOutlineRight.y + healthOutlineRight.h, 8, 0, 0, 0, 255);
    
    
    // Bar1
    roundedBoxRGBA(Menu:: renderer, windBar1.x + windBar1.w, windBar1.y, windBar1.x, windBar1.y + windBar1.h, 10, 0xFF, 0xA5, 0x00, 255);
    roundedRectangleRGBA(Menu:: renderer, windBar1.x + windBar1.w, windBar1.y, windBar1.x, windBar1.y + windBar1.h, 10, 0xDF, 0x36, 0x2D, 255);
    // Bar2
    roundedBoxRGBA(Menu:: renderer, windBar2.x + windBar2.w, windBar2.y, windBar2.x, windBar2.y + windBar2.h, 8, 0xDF, 0x36, 0x2D, 255);
    // Bar3
    SDL_SetRenderDrawColor(Menu:: renderer, 0xFF, 0xA5, 0x00, 255);
    SDL_RenderFillRect(Menu:: renderer, &windBar3);
    // windSpeed
    if(windDir == 0)
    {
        SDL_SetRenderDrawColor(Menu:: renderer, 0xFF, 0xFF, 0x00, 255);
        SDL_RenderFillRect(Menu:: renderer, &windRight);
    }
    else
    {
        SDL_SetRenderDrawColor(Menu:: renderer, 0xFF, 0xFF, 0x00, 255);
        SDL_RenderFillRect(Menu:: renderer, &windLeft);
    }
    
    //windTTF
    roundedBoxRGBA(Menu:: renderer, windTTF.x + windTTF.w, windTTF.y, windTTF.x, windTTF.y + windTTF.h, 8, 0xFF, 0xA5, 0x00, 255);
    roundedRectangleRGBA(Menu:: renderer, windTTF.x + windTTF.w, windTTF.y, windTTF.x, windTTF.y + windTTF.h, 8, 0xDF, 0x36, 0x2D, 255);
    
    if(pressedSpace)
    {
        if(pressedLeft)
        {
            //roundedBoxRGBA(Game:: renderer, velocityBG.x + velocityW, velocityBG.y, velocityBG.x, velocityBG.y + velocityH, 6, 255, 255, 255, 255);
            roundedBoxRGBA(Menu:: renderer, velocity.x + velocity.w, velocity.y, velocity.x, velocity.y + velocityH, 8, 0, 255, 0, 255);
            roundedRectangleRGBA(Menu:: renderer, velocityOutline.x + velocityOutline.w, velocityOutline.y, velocityOutline.x, velocityOutline.y + velocityOutline.h, 8, 0, 0, 0, 255);
        }
        else
        {
            //roundedBoxRGBA(Game:: renderer, velocityBG.x + velocityW, velocityBG.y, velocityBG.x, velocityBG.y + velocityH, 6, 255, 255, 255, 255);
            roundedBoxRGBA(Menu:: renderer, velocity.x + velocityW, velocity.y, velocity.x + (velocityW - velocity.w), velocity.y + velocityH, 8, 0, 255, 0, 255);
            roundedRectangleRGBA(Menu:: renderer, velocityOutline.x + velocityOutline.w, velocityOutline.y, velocityOutline.x, velocityOutline.y + velocityOutline.h, 8, 0, 0, 0, 255);
        }
    }
    
    if(!pressedLeft || !pressedSpace)
    {
        roundedRectangleRGBA(Menu:: renderer, velocityOutlineLeft.x + velocityOutlineLeft.w, velocityOutlineLeft.y, velocityOutlineLeft.x, velocityOutlineLeft.y + velocityOutlineLeft.h, 8, 0, 0, 0, 255);
    }

    if(pressedLeft || !pressedSpace)
    {
        roundedRectangleRGBA(Menu:: renderer, velocityOutlineRight.x + velocityOutlineRight.w, velocityOutlineRight.y, velocityOutlineRight.x, velocityOutlineRight.y + velocityOutlineRight.h, 8, 0, 0, 0, 255);
    }
}
