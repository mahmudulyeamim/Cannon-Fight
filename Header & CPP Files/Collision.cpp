#include "Collision.hpp"

pair <int,int> Collision:: leftBombCentre;
pair <int,int> Collision:: rightBombCentre;
pair <int,int> Collision:: leftCollider;
pair <int,int> Collision:: rightCollider;
int Collision:: explosionX;
int Collision:: explosionY;
bool Collision:: collidedLeft;

int getDistance(int x1, int y1, int x2, int y2)
{
    int x = x1 - x2;
    int y = y1 - y2;
    
    return x*x + y*y;
}

Collision:: Collision(int radius, int width, int height)
{
    bombRadius = radius;
    w = width;
    h = height;
    
}

bool Collision:: checkCollision(bool leftPlayer)
{
    int closestX, closestY;
    if(leftPlayer)
    {
        
        if(leftBombCentre.first < leftCollider.first)
        {
            closestX = leftCollider.first;
        }
        else if(leftBombCentre.first > leftCollider.first + w)
        {
            closestX = leftCollider.first + w;
        }
        else
        {
            closestX = leftBombCentre.first;
        }
        
        if(leftBombCentre.second < leftCollider.second)
        {
            closestY = leftCollider.second;
        }
        else if(leftBombCentre.second > leftCollider.second + h)
        {
            closestY = leftCollider.second + h;
        }
        else
        {
            closestY = leftBombCentre.second;
        }
        
        if(getDistance(leftBombCentre.first, leftBombCentre.second, closestX, closestY) < bombRadius * bombRadius && closestY > 330)
        {
            explosionX = closestX;
            explosionY = closestY;
            collidedLeft = true;
            return true;
        }
        
        if(leftBombCentre.first < rightCollider.first)
        {
            closestX = rightCollider.first;
        }
        else if(leftBombCentre.first > rightCollider.first + w)
        {
            closestX = rightCollider.first + w;
        }
        else
        {
            closestX = leftBombCentre.first;
        }
        
        if(leftBombCentre.second < rightCollider.second)
        {
            closestY = rightCollider.second;
        }
        else if(leftBombCentre.second > rightCollider.second + h)
        {
            closestY = rightCollider.second + h;
        }
        else
        {
            closestY = leftBombCentre.second;
        }
        
        if(getDistance(leftBombCentre.first, leftBombCentre.second, closestX, closestY) < bombRadius * bombRadius)
        {
            explosionX = closestX;
            explosionY = closestY;
            collidedLeft = false;
            return true;
        }
        
        return false;
    }
    else
    {
        if(rightBombCentre.first < rightCollider.first)
        {
            closestX = rightCollider.first;
        }
        else if(rightBombCentre.first > rightCollider.first + w)
        {
            closestX = rightCollider.first + w;
        }
        else
        {
            closestX = rightBombCentre.first;
        }
        
        if(rightBombCentre.second < rightCollider.second)
        {
            closestY = rightCollider.second;
        }
        else if(rightBombCentre.second > rightCollider.second + h)
        {
            closestY = rightCollider.second + h;
        }
        else
        {
            closestY = rightBombCentre.second;
        }
        if(getDistance(rightBombCentre.first, rightBombCentre.second, closestX, closestY) < bombRadius * bombRadius && closestY > 245)
        {
            explosionX = closestX;
            explosionY = closestY;
            collidedLeft = false;
            return true;
        }
        
        
        if(rightBombCentre.first < leftCollider.first)
        {
            closestX = leftCollider.first;
        }
        else if(rightBombCentre.first > leftCollider.first + w)
        {
            closestX = leftCollider.first + w;
        }
        else
        {
            closestX = rightBombCentre.first;
        }
        
        if(rightBombCentre.second < leftCollider.second)
        {
            closestY = leftCollider.second;
        }
        else if(rightBombCentre.second > leftCollider.second + h)
        {
            closestY = leftCollider.second + h;
        }
        else
        {
            closestY = rightBombCentre.second;
        }
        if(getDistance(rightBombCentre.first, rightBombCentre.second, closestX, closestY) < bombRadius * bombRadius)
        {
            explosionX = closestX;
            explosionY = closestY;
            collidedLeft = true;
            return true;
        }
        
        return false;
    }
    
}
