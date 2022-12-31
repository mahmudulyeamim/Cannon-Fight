#include "GameEngine.hpp"
#include "ProgressBar.hpp"

GameEngine:: GameEngine(int width, int height, int rightX, int rightY)
{
    spriteWidth = width;
    spriteHeight = height;
    rightBombX = rightX;
    rightBombY = rightY;
}

pair <int,int> GameEngine:: getInfo(int leftSpritePositionX, int leftSpritePositionY)
{
    int destX = rightBombX - leftSpritePositionX + spriteWidth / 2;
    int destY = rightBombY - leftSpritePositionY - spriteHeight / 2;
    
    
    int bestAngle = 35, bestVel = 0;
    int closestDist = 100000000;
    
    for(int vel = 10; vel <= 140; vel += 10)
    {
        for(int angle = 15; angle <= 55; angle += 5)
        {
            double alpha = angle * pi / 180;
            double Vx = vel * cos(alpha);
            double Vy = vel * sin(alpha);
            
            if(ProgressBar:: windDir == 0)
            {
                Vx = (Vx - ProgressBar:: windSpeed >= 30)? Vx - ProgressBar:: windSpeed : 30;
            }
            else
            {
                Vx = Vx + ProgressBar:: windSpeed;
            }
            
            double a = 5 / (Vx * Vx);
            double b = - Vy / Vx;
            double c = destY;
            
            int x = (-b + sqrt(b*b - 4*a*c)) / (2*a);
            
            
            if(abs(destX - x) < closestDist)
            {
                bestVel = vel;
                bestAngle = angle;
                closestDist = abs(destX - x);
            }
        }
    }
    
    if(bestAngle == 55)
    {
        bestAngle = bestAngle - (rand() % 2) * 5;
    }
    else
    {
        bestAngle = bestAngle + pow(-1, rand()%2) * (rand() % 2) * 5;
    }
    
    if(bestVel == 140)
    {
        bestVel = bestVel - (rand() % 2) * 10;
    }
    else
    {
        bestVel = bestVel + pow(-1, rand()%2) * (rand() % 2) * 10;
    }
    
    return {bestVel, bestAngle};
}

pair <int,int> GameEngine:: getPosition(int y1, int y2, int maxy1, int miny1, int maxy2, int miny2)
{
    int x, y;
    int flag = rand() % 2;
    if(flag == 0) // y1
    {
        y = y1;
        x = miny1 + rand() % (maxy1 - miny1);
    }
    else // y2
    {
        y = y2;
        x = miny2 + rand() % (maxy2 - miny2);
    }
    return {x, y};
}
