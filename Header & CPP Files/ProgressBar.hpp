#ifndef ProgressBar_hpp
#define ProgressBar_hpp

#include "Game.hpp"

class ProgressBar {
  
public:
    
    ProgressBar();
    static void init();
    static void update(int t, int spriteX, int spriteY);
    static void render();
    
    static float timeW;
    static float timeH;
    static int healthW;
    static int healthH;
    static int velocityW;
    static int velocityH;
    static bool pressedSpace;;
    static bool pressedLeft;
    static int windDir, windSpeed;
    static SDL_Rect timeLeft;
    static SDL_Rect timeBG;
    static SDL_Rect timeOutline;
    static SDL_Rect healthLeft;
    static SDL_Rect healthBGLeft;
    static SDL_Rect healthOutlineLeft;
    static SDL_Rect healthRight;
    static SDL_Rect healthBGRight;
    static SDL_Rect healthOutlineRight;
    static SDL_Rect velocity;
    static SDL_Rect velocityBG;
    static SDL_Rect velocityOutline, velocityOutlineLeft, velocityOutlineRight;
    static SDL_Rect windTTF;
    static SDL_Rect windBar1, windBar2, windBar3, windLeft, windRight;
    
};

#endif /* ProgressBar_hpp */
