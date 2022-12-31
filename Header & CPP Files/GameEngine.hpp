#ifndef GameEngine_hpp
#define GameEngine_hpp

#include "Game.hpp"

class GameEngine {
    
public:
    GameEngine(int width, int height, int rightX, int rightY);
    pair <int,int> getInfo(int leftSpritePositionX, int leftSpritePositionY);
    pair <int,int> getPosition(int y1, int y2, int maxy1, int miny1, int maxy2, int miny2);
    
private:
    const double pi = 3.14159265359;
    int spriteWidth, spriteHeight;
    int rightBombX, rightBombY;
};


#endif /* GameEngine_hpp */
