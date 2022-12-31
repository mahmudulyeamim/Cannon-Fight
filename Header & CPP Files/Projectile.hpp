#ifndef Projectile_hpp
#define Projectile_hpp

#include "Game.hpp"
#include <cmath>

class Projectile {
  
public:
    
    Projectile(const char* filename, int x, int y, int w, int h, bool left);
    ~Projectile();
    
    void update(double angle, double vel, double time, bool left);
    void render(bool left);
    
    static int xpos, ypos;
    static int Lx0, Ly0, Rx0, Ry0;
    
private:
    
    //int Lx0, Ly0, Rx0, Ry0;
    int bombW, bombH;
    double bombDegree = 0;
    
    SDL_Texture* bombRight;
    SDL_Texture* bombLeft;
    SDL_Rect destR;
    
};


#endif /* Projectile_hpp */
