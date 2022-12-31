#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_gfx/SDL2_gfxPrimitives.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>


using namespace std;


class Game {
  
public:
    
    Game();
    ~Game();
    
    //void init(const char* title, int x, int y, int w, int h, bool onePlayer);
    void init(int flag);
    void resume();
    
    void playMusic();
    void stopMusic();
    void handleEvents();
    void update();
    void render();
    bool checkFinishGame();
    
    void clean();
    
    bool running() { return isRunning; }
    
    //static SDL_Renderer* renderer;
    static int screenWidth, screenHeight;
    static double minVel;
    static bool isRunning;
    
private:
    
    SDL_Rect ladderDestLeft, ladderDestRight, spriteExplosionDest, spriteExplosionSrc[7];
    
    const double pi = 3.14159265359;
    double angle = 0;
    
    double degreeLeft = 0, degreeRight = 0;
    
    bool leftPlayer = true, rightPlayer = false;
    
    bool lock = false;
    
    int startTime;
    double maxVel = 140;
    double vel = 30;
    double time = 0;
    int speed = 100;
    
    bool pressed = false;
    
    int frame = 0;
    bool spriteMotion[5] = {1, 0, 0, 0, 0};
    
    //bool isRunning;
    SDL_Window* window = NULL;
    
    pair <int,int> spritePositionLeft, spritePositionRight;
    
    int explosionTime;
    
    bool twice = 0;
    
    bool collidedSprite = 0;
    
    SDL_Texture* background = NULL;
    SDL_Texture* ladder = NULL;
    SDL_Texture* spriteExplosion = NULL;
    SDL_Texture* smoke = NULL;
    SDL_Rect smokeSrc[5];
    SDL_Rect smokeDst;
    int smokeFrame, explosionFrame;
    
    SDL_Texture *clock, *heart;
    SDL_Rect clockDst, heartDstLeft, heartDstRight;
    
    bool pressedLeft = false, pressedRight = false;
    
    int decreaseLife = 50;
    
    SDL_Texture *arrowLeft, *arrowRight;
    SDL_Rect arrowLeftDest, arrowRightDest;
    int arrowFrame = 0;
    int arrowLeftX, arrowRightX;
    
    SDL_Texture *thunder;
    SDL_Rect thunderDstLeft, thunderDstRight;
    
    // AI variables
    bool againstComputer;
    int computerFrame = 1e8;
    int currentAngle = -1, currentVel = -1;
    bool computerSpeedBar = false;
    int frameDelayCount = 0;
    int destX = -1, destY = -1;
    bool goDown = false, goUp = false;
    bool goRight = false, goLeft = false;
    bool dontMove = false;
    
    int mouseX = 0, mouseY = 0;
    
    // giftbox variables
    int featureFlag = -1;
    int twiceTurnCount = 0;
    
    int pickUpGiftBox = 4;
    bool pickedUpGiftBox = false;
    
    // music part
    Mix_Music* bgm = NULL;
    Mix_Chunk* ThrowMusic = NULL;
    Mix_Chunk* HitMusic = NULL;
    Mix_Chunk* GiftMusic = NULL;
    Mix_Chunk* CanonMusic = NULL;
    Mix_Chunk* click = NULL;
    Mix_Chunk* winEffect = NULL;
    Mix_Chunk* loseEffect = NULL;
    
    SDL_Texture* pause = NULL;
    SDL_Rect pauseDest;
    int pauseX, pauseY, pauseWidth;
    
    SDL_Texture *youwin, *youlose, *leftwin, *rightwin;
    
    int remTime = 20;
};


#endif /* Game_hpp */
