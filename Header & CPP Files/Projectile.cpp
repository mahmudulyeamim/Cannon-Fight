#include "Projectile.hpp"
#include "TextureManager.hpp"
#include "ProgressBar.hpp"
#include "Menu.hpp"

int Projectile:: Lx0;
int Projectile:: Ly0;
int Projectile:: Rx0;
int Projectile:: Ry0;
int Projectile:: xpos;
int Projectile:: ypos;

Projectile:: Projectile(const char* filename, int x, int y, int w, int h, bool left)
{
    if(left)
        bombLeft = TextureManager:: loadTexture(filename);
    else
        bombRight = TextureManager:: loadTexture(filename);
    
    if(left)
    {
        Lx0 = x;
        Ly0 = y;
    }
    else
    {
        Rx0 = x;
        Ry0 = y;
    }
    
    bombW = w;
    bombH = h;
}

void Projectile:: update(double angle, double vel, double time, bool left)
{
    double Vx = vel * cos(angle);
    double Vy = vel * sin(angle);
    double t = time * 0.18;
    
    if(left)
    {
        if(ProgressBar:: windDir == 0)
        {
            Vx = Vx + ProgressBar:: windSpeed;
        }
        else
        {
            Vx = (Vx - ProgressBar:: windSpeed >= 30)? Vx - ProgressBar:: windSpeed : 30;
        }
        xpos = Lx0 + Vx * t;
        ypos = Ly0 - (Vy * t - 5 * t * t);
        
        destR = {xpos, ypos, bombW, bombH};
        
        bombDegree = time * 15;
        
    }
    else
    {
        if(ProgressBar:: windDir == 0)
        {
            Vx = (Vx - ProgressBar:: windSpeed >= 30)? Vx - ProgressBar:: windSpeed : 30;
        }
        else
        {
            Vx = Vx + ProgressBar:: windSpeed;
        }
        xpos = Rx0 - Vx * t;
        ypos = Ry0 - (Vy * t - 5 * t * t);
        
        destR = {xpos, ypos, bombW, bombH};
        
        bombDegree = time * 15 * -1;
        
    }
}

void Projectile:: render(bool left)
{
    if(left)
        SDL_RenderCopyEx(Menu::renderer, bombLeft, NULL, &destR, bombDegree, NULL, SDL_FLIP_NONE);
    else
        SDL_RenderCopyEx(Menu::renderer, bombRight, NULL, &destR, bombDegree, NULL, SDL_FLIP_NONE);
}
