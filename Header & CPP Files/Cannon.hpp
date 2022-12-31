#ifndef Cannon_hpp
#define Cannon_hpp

#include "Game.hpp"

class Cannon {
  
public:
    Cannon(const char* filename, int x, int y);
    ~Cannon();
    
    void update();
    void render(double degree);
    
private:
    
    SDL_Rect destR;
    SDL_Texture* cann;
    SDL_Point centre;
    
};


#endif /* Cannon_hpp */
