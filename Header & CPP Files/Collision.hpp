#ifndef Collision_hpp
#define Collision_hpp

#include "Game.hpp"

class Collision {
  
public:
    
    Collision(int radius, int w, int h);
    bool checkCollision(bool leftPlayer);
    
    static pair <int,int> leftBombCentre, rightBombCentre;
    static pair <int,int> leftCollider;
    static pair <int,int> rightCollider;
    static int explosionX, explosionY;
    static bool collidedLeft;
    
private:
    int bombRadius;
    int w, h;
};

#endif /* Collision_hpp */
