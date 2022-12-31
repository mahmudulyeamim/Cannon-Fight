#ifndef Sprite_hpp
#define Sprite_hpp

#include "Game.hpp"

class Sprite {
  
public:
    
    Sprite(const char* filaname, int x, int h, int spriteW, int spriteH, int flag);
    ~Sprite();
    
    void update(int frame, int flag, int x, int y, bool left);
    void render();
    
private:
    
    int width;
    int height;
    int spriteWidth;
    int spriteHeight;
    int no = 0;
    
    SDL_Texture* sprite[5];
    SDL_Rect defaultSrc[2], walkSrc[12], ladderSrc[9];
    SDL_Rect defaultDest;
    SDL_Rect currentSrc, currentDest;
    
};

#endif /* Sprite_hpp */
