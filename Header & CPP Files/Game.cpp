#include "Game.hpp"
#include "TextureManager.hpp"
#include "Projectile.hpp"
#include "Cannon.hpp"
#include "Sprite.hpp"
#include "Collision.hpp"
#include "ProgressBar.hpp"
#include "TTF.hpp"
#include "GameEngine.hpp"
#include "GiftBox.hpp"
#include "Menu.hpp"


//SDL_Renderer* Game:: renderer = NULL;
int Game:: screenWidth = 1200;
int Game:: screenHeight = 600;
double Game:: minVel = 30;
bool Game:: isRunning;
Projectile* rightBomb;
Projectile* leftBomb;
Cannon* cannonLeft;
Cannon* cannonRight;
Sprite* spriteLeft[5];
Sprite* spriteRight[5];
Collision* colliders;
TTF* trueTypeFont;
GameEngine* engine;
GiftBox* leftBox;
GiftBox* rightBox;

Game:: Game()
{
    isRunning = false;
    
    // music
    bgm = Mix_LoadMUS("bgm-2.mp3");
    //Mix_PlayMusic(bgm, -1);
    ThrowMusic = Mix_LoadWAV("Throw.wav");
    HitMusic = Mix_LoadWAV("hit.wav");
    GiftMusic = Mix_LoadWAV("Gift.wav");
    CanonMusic = Mix_LoadWAV("canon.wav");
    click = Mix_LoadWAV("click.wav");
    winEffect = Mix_LoadWAV("you win.wav");
    loseEffect = Mix_LoadWAV("you lose.wav");
    
    background = TextureManager:: loadTexture("Asset 3.png");
    ladder = TextureManager:: loadTexture("ladder.png");
    spriteExplosion = TextureManager:: loadTexture("explosion.png");
    spriteExplosionSrc[0] = {40, 0, 120, 223};
    spriteExplosionSrc[1] = {160, 0, 140, 223};
    spriteExplosionSrc[2] = {300, 0, 140, 223};
    spriteExplosionSrc[3] = {440, 0, 160, 223};
    spriteExplosionSrc[4] = {610, 0, 140, 223};
    spriteExplosionSrc[5] = {780, 0, 130, 223};
    spriteExplosionSrc[6] = {930, 0, 120, 223};
    
    
    smoke = TextureManager:: loadTexture("smoke.png");
    smokeSrc[0] = {0, 0, 290, 246};
    smokeSrc[1] = {290, 0, 290, 246};
    smokeSrc[2] = {290*2, 0, 290, 246};
    smokeSrc[3] = {290*3, 0, 290, 246};
    smokeSrc[4] = {290*4, 0, 290, 246};
    
    
    ladderDestLeft = {50, 340, 318, 159};
    ladderDestRight = {840, 270, 318, 159};
    leftBomb = new Projectile("bomb.png", 212, 272, 300 * 0.1, 327 * 0.1, true);
    rightBomb = new Projectile("bomb1.png", 1200-255, 200, 300 * 0.1, 327 * 0.1, false);
    cannonLeft = new Cannon("cannon.png", 170, 260);
    cannonRight = new Cannon("cannon1.png", 1200-265, 185);
    
    spriteLeft[0] = new Sprite("defaultSprite.png", 220, 266, 44, 106, 0);
    spriteLeft[1] = new Sprite("walkBack.png", 1442, 266, 44, 106, 1);
    spriteLeft[2] = new Sprite("walkFront.png", 1442, 262, 44, 106, 2);
    spriteLeft[3] = new Sprite("ladderup.png", 1008, 247, 44, 106, 3);
    spriteLeft[4] = new Sprite("ladderup.png", 1008, 247, 44, 106, 4);
    spritePositionLeft = {150, 245};
    spriteRight[0] = new Sprite("defaultSprite2.png", 220, 266, 44, 106, 0);
    spriteRight[1] = new Sprite("walkBack1.png", 1442, 266, 44, 106, 1);
    spriteRight[2] = new Sprite("walkFront1.png", 1442, 262, 44, 106, 2);
    spriteRight[3] = new Sprite("ladderup1.png", 1008, 247, 44, 106, 3);
    spriteRight[4] = new Sprite("ladderup1.png", 1008, 247, 44, 106, 4);
    spritePositionRight = {990, 158};
    
    colliders = new Collision(12, 30, 80);
    
    clock = TextureManager:: loadTexture("clock.png");
    clockDst.w = clockDst.h = 20;
    
    heart = TextureManager:: loadTexture("heart.png");
    heartDstLeft = {0, 0, 38, 38};
    heartDstRight = {screenWidth-38, 0, 38, 38};
    
    thunder = TextureManager:: loadTexture("speed.png");
    thunderDstLeft = {-2, 35, 40, 40};
    thunderDstRight = {1200 - 40 - 2, 35, 40 ,40};
    
    trueTypeFont = new TTF("Roboto-Regular.ttf");
    
    ProgressBar:: windDir = 0;
    ProgressBar:: windSpeed = 15;
    
    arrowLeft = TextureManager:: loadTexture("arrowLeft.png");
    arrowRight = TextureManager:: loadTexture("arrowRight.png");
    arrowLeftX = screenWidth/2 - 62;
    arrowRightX = screenWidth/2 + 15;
    arrowLeftDest = {screenWidth/2 - 62 - 10, 6, 36 + 10, 27 - 5};
    arrowRightDest = {screenWidth/2 + 15 + 10, 6, 36 + 10, 27 - 5};
    
    engine = new GameEngine(44, 106, 1200-255, 200);
    
    leftBox = new GiftBox("gift.png", 2, 65, 70, "health.png", "damage.png", "turn.png", screenWidth / 2 - 70 / 2, 50);
    rightBox = new GiftBox("gift.png", 1200 - 70 + 2, 65, 70, "health.png", "damage.png", "turn.png", screenWidth / 2 - 70 / 2, 50);
    
    pause = TextureManager:: loadTexture("pause.png");
    pauseDest = {5, screenHeight - 70, 70, 70};
    pauseX = 5 + 15;
    pauseY = screenHeight-70 + 15;
    pauseWidth = 50;
    
    youwin = TextureManager:: loadTexture("youWin.png");
    youlose = TextureManager:: loadTexture("youLose.png");
    leftwin = TextureManager:: loadTexture("leftWin.png");
    rightwin = TextureManager:: loadTexture("rightWin.png");
}

void Game:: init(int flag)
{
    if(flag == 1) againstComputer = true;
    else againstComputer = false;
    
    isRunning = true;
    leftPlayer = true;
    rightPlayer = false;
    lock = false;
    pressed = false;
    frame = 0;
    
    time = 0;
    vel = 30;
    speed = 100;
    
    degreeLeft = 0; degreeRight = 0;
    
    spritePositionLeft = {150, 245};
    spritePositionRight = {990, 158};
    spriteMotion[0] = 1;
    spriteMotion[1] = spriteMotion[2] = spriteMotion[3] = spriteMotion[4] = 0;
    
    
    twice = 0;
    
    collidedSprite = 0;
    
    ProgressBar:: init();
    pressedLeft = false; pressedRight = false;
    
    arrowFrame = 0;
    
    leftBox->init("gift.png");
    rightBox->init("gift.png");
    
    computerFrame = 1e8;
    currentAngle = -1; currentVel = -1;
    computerSpeedBar = false;
    frameDelayCount = 0;
    destX = -1; destY = -1;
    goDown = false; goUp = false;
    goRight = false; goLeft = false;
    dontMove = false;

    mouseX = 0; mouseY = 0;

    featureFlag = -1;
    twiceTurnCount = 0;
    
    pickUpGiftBox = 4;
    pickedUpGiftBox = false;
    
    startTime = 20 + SDL_GetTicks()/1000;
}

void Game:: resume()
{
    startTime = remTime + SDL_GetTicks()/1000;
}

void Game:: playMusic()
{
    Mix_PlayMusic(bgm, -1);
}

void Game:: stopMusic()
{
    Mix_HaltMusic();
}

void Game:: handleEvents()
{
    SDL_Event e;
    SDL_PollEvent(&e);
    if(e.type == SDL_QUIT)
    {
        isRunning = false;
        Menu:: isRunning = false;
    }
    else if(e.type == SDL_KEYDOWN)
    {
        switch(e.key.keysym.sym)
        {
                
            case SDLK_SPACE:
                if(!lock && startTime - SDL_GetTicks()/1000 >= 0)
                {
                    if(!pressedLeft && !pressedRight)
                    {
                        if(leftPlayer || (!leftPlayer && !againstComputer))
                        {
                            pressedLeft = leftPlayer;
                            pressedRight = !leftPlayer;
                            ProgressBar:: pressedSpace = true;
                            ProgressBar:: pressedLeft = leftPlayer;
                        }
                    }
                    if((pressedLeft && leftPlayer) || (pressedRight && !leftPlayer && !againstComputer))
                    {
                        if(vel < maxVel)
                            vel += 10;
                    }
                    else
                    {
                        if(leftPlayer || (!leftPlayer && !againstComputer))
                        {
                            ProgressBar:: pressedSpace = false;
                        }
                    }
                }
                break;
            case SDLK_UP:
                if(!lock && ProgressBar:: pressedSpace == false && startTime > SDL_GetTicks()/1000)
                {
                    if(leftPlayer)
                    {
                        if(degreeLeft > -30)
                        {
                            degreeLeft -= 5;
                            leftBomb->Lx0 = leftBomb->Lx0 - 3;
                            leftBomb->Ly0 = leftBomb->Ly0 - 1;
                            Mix_PlayChannel(-1, CanonMusic, 0);
                        }
                    }
                    else
                    {
                        if(!againstComputer)
                        {
                            if(degreeRight < 20)
                            {
                                degreeRight += 5;
                                rightBomb->Rx0 = rightBomb->Rx0 + 3;
                                rightBomb->Ry0 = rightBomb->Ry0 - 2;
                                Mix_PlayChannel(-1, CanonMusic, 0);
                            }
                        }
                    }
                }
                break;
            case SDLK_DOWN:
                if(!lock && ProgressBar:: pressedSpace == false && startTime > SDL_GetTicks()/1000)
                {
                    if(leftPlayer)
                    {
                        if(degreeLeft < 10)
                        {
                            degreeLeft += 5;
                            leftBomb->Lx0 = leftBomb->Lx0 + 3;
                            leftBomb->Ly0 = leftBomb->Ly0 + 1;
                            Mix_PlayChannel(-1, CanonMusic, 0);
                        }
                    }
                    else
                    {
                        if(!againstComputer)
                        {
                            if(degreeRight > -20)
                            {
                                degreeRight -= 5;
                                rightBomb->Rx0 = rightBomb->Rx0 - 3;
                                rightBomb->Ry0 = rightBomb->Ry0 + 2;
                                Mix_PlayChannel(-1, CanonMusic, 0);
                            }
                        }
                    }
                }
                break;
                
            case SDLK_a:
                if(!lock && spriteMotion[0] && !spriteMotion[1] && !spriteMotion[2] && !spriteMotion[3] && !spriteMotion[4])
                {
                    if(leftPlayer || (!leftPlayer && !againstComputer))
                    {
                        spriteMotion[0] = false;
                        spriteMotion[1] = true;
                        spriteMotion[2] = false;
                        spriteMotion[3] = false;
                        spriteMotion[4] = false;
                    }
                }
                break;
                
            case SDLK_d:
                if(!lock && spriteMotion[0] && !spriteMotion[1] && !spriteMotion[2] && !spriteMotion[3] && !spriteMotion[4])
                {
                    if(leftPlayer || (!leftPlayer && !againstComputer))
                    {
                        spriteMotion[0] = false;
                        spriteMotion[1] = false;
                        spriteMotion[2] = true;
                        spriteMotion[3] = false;
                        spriteMotion[4] = false;
                    }
                }
                break;
                
            case SDLK_s:
                if(!lock && spriteMotion[0] && !spriteMotion[1] && !spriteMotion[2] && !spriteMotion[3] && !spriteMotion[4])
                {
                    if(leftPlayer || (!leftPlayer && !againstComputer))
                    {
                        if((leftPlayer && spritePositionLeft.first >= 168 && spritePositionLeft.second == 245) || (!leftPlayer && spritePositionRight.first <= 990 && spritePositionRight.second == 158))
                        {
                            frame = 0;
                            if(leftPlayer)
                            {
                                spritePositionLeft.second += 60;
                                spritePositionLeft.first = 183;
                            }
                            else
                            {
                                spritePositionRight.first = 976;
                                spritePositionRight.second = 220;
                            }
                            spriteMotion[0] = false;
                            spriteMotion[1] = false;
                            spriteMotion[2] = false;
                            spriteMotion[3] = true;
                            spriteMotion[4] = false;
                        }
                    }
                }
                break;
                
            case SDLK_w:
                if(!lock && spriteMotion[0] && !spriteMotion[1] && !spriteMotion[2] && !spriteMotion[3] && !spriteMotion[4])
                {
                    if(leftPlayer || (!leftPlayer && !againstComputer))
                    {
                        if((leftPlayer && spritePositionLeft.first <= 230 && spritePositionLeft.second == 356) || (!leftPlayer && spritePositionRight.first >= 955 && spritePositionRight.second == 350))
                        {
                            frame = 0;
                            if(leftPlayer)
                            {
                                spritePositionLeft.second -= 15;
                                spritePositionLeft.first = 183;
                            }
                            else
                            {
                                spritePositionRight.first = 976;
                                spritePositionRight.second = 320;
                            }
                            spriteMotion[0] = false;
                            spriteMotion[1] = false;
                            spriteMotion[2] = false;
                            spriteMotion[3] = false;
                            spriteMotion[4] = true;
                        }
                    }
                }
                break;
            case SDLK_g:
                cout << "hi\n";
                if(leftPlayer)
                {
                    int tempFlag = leftBox->checkMouseClick(40, 100, false);
                    if(tempFlag != -1)
                    {
                        featureFlag = tempFlag;
                        if(featureFlag == 0)
                        {
                            if(ProgressBar:: healthLeft.w < 400)
                            {
                                ProgressBar:: healthLeft.w += decreaseLife;
                            }
                        }
                        Mix_PlayChannel(-1, GiftMusic, 0);
                    }
                }
                else if(!leftPlayer && !againstComputer)
                {
                    int tempFlag = rightBox->checkMouseClick(1200-40, 100, false);
                    if(tempFlag != -1)
                    {
                        featureFlag = tempFlag;
                        if(featureFlag == 0)
                        {
                            if(ProgressBar:: healthRight.w < 400)
                            {
                                ProgressBar:: healthRight.w += decreaseLife;
                            }
                        }
                        Mix_PlayChannel(-1, GiftMusic, 0);
                    }
                }
                break;
            case SDLK_p:
                Mix_PlayChannel(-1, click, 0);
                remTime = startTime - SDL_GetTicks()/1000;
                isRunning = false;
                break;
                
        }
    }
    else if(e.type == SDL_KEYUP)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_SPACE:
                if((pressedLeft && leftPlayer) || (pressedRight && !leftPlayer && !againstComputer))
                {
                    //cout << lock << ' ';
                    if(!lock)
                    {
                        if(leftPlayer || (!leftPlayer && !againstComputer))
                        {
                            pressed = true;
                            Mix_PlayChannel(-1, ThrowMusic, 0);
                        }
                        
                        if(leftPlayer)
                            angle = (35 - degreeLeft) * pi / 180;
                        else
                            angle = (35 + degreeRight) * pi / 180;
                        
                        time = 0;
                        lock = true;
                        pressedLeft = pressedRight = false;
                    }
                }
                else
                {
                    //cout << lock << '\n';
                    if(!lock)
                    {
                        vel = minVel;
                        time = 0;
                        pressedLeft = pressedRight = false;
                    }
                }
                if(leftPlayer || (!leftPlayer && !againstComputer))
                {
                    ProgressBar:: pressedSpace = false;
                }

                break;
                
            case SDLK_a:
                if(spriteMotion[1])
                {
                    spriteMotion[0] = true;
                    spriteMotion[1] = false;
                }
                break;
            case SDLK_d:
                if(spriteMotion[2])
                {
                    spriteMotion[0] = true;
                    spriteMotion[2] = false;
                }
                break;
        }
    }
    else if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_GetMouseState(&mouseX, &mouseY);
        cout << mouseX << ' ' << mouseY << '\n';
        
        if(mouseX > pauseX && mouseX < pauseX+pauseWidth && mouseY > pauseY && mouseY < pauseY+pauseWidth)
        {
            Mix_PlayChannel(-1, click, 0);
            remTime = startTime - SDL_GetTicks()/1000;
            isRunning = false;
        }
        
        if(leftPlayer)
        {
            int tempFlag = leftBox->checkMouseClick(mouseX, mouseY, false);
            if(tempFlag != -1)
            {
                featureFlag = tempFlag;
                if(featureFlag == 0)
                {
                    if(ProgressBar:: healthLeft.w < 400)
                    {
                        ProgressBar:: healthLeft.w += decreaseLife;
                    }
                }
                Mix_PlayChannel(-1, GiftMusic, 0);
            }
        }
        else if(!leftPlayer && !againstComputer)
        {
            int tempFlag = rightBox->checkMouseClick(mouseX, mouseY, false);
            if(tempFlag != -1)
            {
                featureFlag = tempFlag;
                if(featureFlag == 0)
                {
                    if(ProgressBar:: healthRight.w < 400)
                    {
                        ProgressBar:: healthRight.w += decreaseLife;
                    }
                }
                Mix_PlayChannel(-1, GiftMusic, 0);
            }
        }
    }
    
    if(!leftPlayer && againstComputer)
    {
        if(ProgressBar:: healthRight.w <= pickUpGiftBox * 50 && pickedUpGiftBox == false)
        {
            if(startTime - SDL_GetTicks()/1000 < 19)
            {
                featureFlag = rightBox->checkMouseClick(-1, -1, true);
                if(featureFlag == 0)
                {
                    if(ProgressBar:: healthRight.w < 400)
                    {
                        ProgressBar:: healthRight.w += decreaseLife;
                    }
                }
                pickedUpGiftBox = true;
                Mix_PlayChannel(-1, GiftMusic, 0);
                pickUpGiftBox = 10;
            }
        }
        else if(dontMove == false)
        {
            if(destX == -1 && destY == -1)
            {
                auto pos = engine->getPosition(158, 350, 1118, 923, 962, screenWidth/2 + 50);
                destX = pos.first;
                destY = pos.second;
                
                if(spritePositionRight.second != destY)
                {
                    if(destY < spritePositionRight.second)
                    {
                        goUp = true;
                    }
                    else
                    {
                        goDown = true;
                    }
                }
            }
            else
            {
                if(goUp)
                {
                    if(spritePositionRight.first < 955)
                    {
                        spriteMotion[0] = false;
                        spriteMotion[1] = false;
                        spriteMotion[2] = true;
                        spriteMotion[3] = false;
                        spriteMotion[4] = false;
                    }
                    else
                    {
                        frame = 0;
                        
                        spritePositionRight.first = 976;
                        spritePositionRight.second = 320;
                        
                        spriteMotion[0] = false;
                        spriteMotion[1] = false;
                        spriteMotion[2] = false;
                        spriteMotion[3] = false;
                        spriteMotion[4] = true;
                        
                        goUp = false;
                    }
                }
                else if(goDown)
                {
                    if(spritePositionRight.first > 990)
                    {
                        spriteMotion[0] = false;
                        spriteMotion[1] = true;
                        spriteMotion[2] = false;
                        spriteMotion[3] = false;
                        spriteMotion[4] = false;
                    }
                    else
                    {
                        frame = 0;
                        
                        spritePositionRight.first = 976;
                        spritePositionRight.second = 220;
                        
                        spriteMotion[0] = false;
                        spriteMotion[1] = false;
                        spriteMotion[2] = false;
                        spriteMotion[3] = true;
                        spriteMotion[4] = false;
                        
                        goDown = false;
                    }
                }
                else
                {
                    if(goRight == false && goLeft == false)
                    {
                        if(destX < spritePositionRight.first)
                        {
                            goLeft = true;
                        }
                        if(destX > spritePositionRight.first)
                        {
                            goRight = true;
                        }
                    }
                    
                    if(goLeft)
                    {
                        if(destX >= spritePositionRight.first)
                        {
                            spriteMotion[0] = true;
                            spriteMotion[1] = false;
                            spriteMotion[2] = false;
                            spriteMotion[3] = false;
                            spriteMotion[4] = false;
                            dontMove = true;
                        }
                        else
                        {
                            if(spriteMotion[0] && !spriteMotion[1] && !spriteMotion[2] && !spriteMotion[3] && !spriteMotion[4])
                            {
                                spriteMotion[0] = false;
                                spriteMotion[1] = true;
                                spriteMotion[2] = false;
                                spriteMotion[3] = false;
                                spriteMotion[4] = false;
                            }
                        }
                    }
                    else if(goRight)
                    {
                        if(destX <= spritePositionRight.first)
                        {
                            spriteMotion[0] = true;
                            spriteMotion[1] = false;
                            spriteMotion[2] = false;
                            spriteMotion[3] = false;
                            spriteMotion[4] = false;
                            dontMove = true;
                        }
                        else
                        {
                            if(spriteMotion[0] && !spriteMotion[1] && !spriteMotion[2] && !spriteMotion[3] && !spriteMotion[4])
                            {
                                spriteMotion[0] = false;
                                spriteMotion[1] = false;
                                spriteMotion[2] = true;
                                spriteMotion[3] = false;
                                spriteMotion[4] = false;
                            }
                        }
                    }
                    else
                    {
                        dontMove = true;
                    }
                }
            }
        }
        else if(pressed == false && dontMove == true)
        {
            if(computerFrame == 1e8)
            {
                computerFrame = 0;
            }
            if(currentVel == -1 && currentAngle == -1)
            {
                auto info = engine->getInfo(spritePositionLeft.first, spritePositionLeft.second);
                currentVel = max(info.first, 30);
                currentAngle = info.second;
            }
            
            computerFrame++;
            if(degreeRight < currentAngle - 35 && computerFrame % 50 == 0)
            {
                degreeRight += 5;
                rightBomb->Rx0 = rightBomb->Rx0 + 3;
                rightBomb->Ry0 = rightBomb->Ry0 - 2;
                Mix_PlayChannel(-1, CanonMusic, 0);
            }
            if(degreeRight > currentAngle - 35 && computerFrame % 50 == 0)
            {
                degreeRight -= 5;
                rightBomb->Rx0 = rightBomb->Rx0 - 3;
                rightBomb->Ry0 = rightBomb->Ry0 + 2;
                Mix_PlayChannel(-1, CanonMusic, 0);
            }
            if(degreeRight == currentAngle - 35 && computerFrame % 50 == 0)
            {
                if(computerSpeedBar == false)
                {
                    //ProgressBar:: pressedSpace = true;
                    ProgressBar:: pressedLeft = leftPlayer;
                    computerSpeedBar = true;
                    computerFrame++;
                }
            }
            
            if(computerSpeedBar == true && vel < currentVel && degreeRight == currentAngle - 35 && computerFrame % 7 == 0 && frameDelayCount++ >= 5)
            {
                if(ProgressBar:: pressedSpace == false)
                {
                    ProgressBar:: pressedSpace = true;
                }
                vel += 10;
            }
            else if(computerSpeedBar == true && vel == currentVel && computerFrame % 10 == 0 && frameDelayCount++ >= 5)
            {
                if(ProgressBar:: pressedSpace == false)
                {
                    ProgressBar:: pressedSpace = true;
                }
                else
                {
                    pressed = true;
                    
                    Mix_PlayChannel(-1, ThrowMusic, 0);
                    
                    angle = currentAngle * pi / 180;
                    time = 0;
                    lock = true;
                    pressedLeft = pressedRight = false;
                    computerFrame = 1e8;
                    currentVel = -1;
                    currentAngle = -1;
                    computerSpeedBar = false;
                    ProgressBar:: pressedSpace = false;
                    frameDelayCount = 0;
                    destX = -1;
                    destY = -1;
                    goLeft = false;
                    goRight = false;
                }
            }
        }
    }
}

void Game:: update()
{
    
    if(pressed)
    {
        if(!collidedSprite)
            time++;
        
        if(!collidedSprite && colliders->checkCollision(leftPlayer))
        {
            spriteExplosionDest = {colliders->explosionX-40, colliders->explosionY-60, 80, 120};
            smokeDst = {colliders->explosionX-30, colliders->explosionY-60, 60, 60};
            smokeFrame = 0;
            explosionFrame = 0;
            
            collidedSprite = true;
            explosionTime = 2 + SDL_GetTicks()/1000;
            time = 0;
            vel = minVel;
            
            Mix_PlayChannel(-1, HitMusic, 0);
        }
        
        else if(!collidedSprite && (leftBomb->xpos > screenWidth || leftBomb->ypos > screenHeight))
        {
            lock = false;
            pressed = false;
            if(featureFlag == 2)
            {
                if(twiceTurnCount == 0)
                {
                    twiceTurnCount++;
                }
                else
                {
                    twiceTurnCount = 0;
                    featureFlag = -1;
                }
            }
            else
            {
                featureFlag = -1;
            }
            if(featureFlag != 2)
            {
                leftPlayer ^= true;
                rightPlayer ^= true;
            }
            startTime = 20 + SDL_GetTicks()/1000;
            time = 0;
            ProgressBar:: windDir = rand() % 2;
            ProgressBar:: windSpeed = (rand() % 4) * 15;
            vel = minVel;
            dontMove = false;
        }
        else if(!collidedSprite && rightPlayer && (rightBomb->xpos < -100 || rightBomb->ypos > screenHeight))
        {
            lock = false;
            pressed = false;
            if(featureFlag == 2)
            {
                if(twiceTurnCount == 0)
                {
                    twiceTurnCount++;
                }
                else
                {
                    twiceTurnCount = 0;
                    featureFlag = -1;
                }
            }
            else
            {
                featureFlag = -1;
            }
            if(featureFlag != 2)
            {
                leftPlayer ^= true;
                rightPlayer ^= true;
            }
            startTime = 20 + SDL_GetTicks()/1000;
            time = 0;
            ProgressBar:: windDir = rand() % 2;
            ProgressBar:: windSpeed = (rand() % 4) * 15;
            vel = minVel;
            dontMove = false;
        }
        
    }
    
    if(!collidedSprite && !pressed && startTime < SDL_GetTicks()/1000)
    {
        if(spriteMotion[0] && !spriteMotion[1] && !spriteMotion[2] && !spriteMotion[3] && !spriteMotion[4])
        {
            lock = false;
            pressed = false;
            if(featureFlag == 2)
            {
                if(twiceTurnCount == 0)
                {
                    twiceTurnCount++;
                }
                else
                {
                    twiceTurnCount = 0;
                    featureFlag = -1;
                }
            }
            else
            {
                featureFlag = -1;
            }
            if(featureFlag != 2)
            {
                leftPlayer ^= true;
                rightPlayer ^= true;
            }
            startTime = 20 + SDL_GetTicks()/1000;
            ProgressBar:: windDir = rand() % 2;
            ProgressBar:: windSpeed = (rand() % 4) * 15;
            vel = minVel;
            dontMove = false;
        }
    }
        
    
    cannonLeft->update();
    cannonRight->update();
    
    if(leftPlayer)
    {
        leftBomb->update(angle, vel, time, leftPlayer);
        colliders->leftBombCentre = {leftBomb->xpos + 14, leftBomb->ypos + 14};
        ProgressBar:: update(startTime, spritePositionLeft.first, spritePositionLeft.second);
        clockDst.x = spritePositionLeft.first-35;
        clockDst.y = spritePositionLeft.second-15;
    }
    else
    {
        rightBomb->update(angle, vel, time, leftPlayer);
        colliders->rightBombCentre = {rightBomb->xpos + 14, rightBomb->ypos + 14};
        ProgressBar:: update(startTime, spritePositionRight.first, spritePositionRight.second);
        clockDst.x = spritePositionRight.first-35;
        clockDst.y = spritePositionRight.second-15;
    }
    
    
    if(spriteMotion[0])
    {
        if(frame/35 >= 2)
        {
            frame = 0;
        }
        if(leftPlayer)
        {
            spriteLeft[0]->update(frame/35, 0, spritePositionLeft.first, spritePositionLeft.second, leftPlayer);
            spriteRight[0]->update(1, 0, spritePositionRight.first, spritePositionRight.second, leftPlayer);
        }
        else
        {
            spriteLeft[0]->update(1, 0, spritePositionLeft.first, spritePositionLeft.second, leftPlayer);
            spriteRight[0]->update(frame/35, 0, spritePositionRight.first, spritePositionRight.second, leftPlayer);
        }
        frame++;
    }
    else if(spriteMotion[1])
    {
        if(frame/3 >= 12){
            frame = 0;
        }
        if(leftPlayer)
        {
            if(spritePositionLeft.second == 245 && spritePositionLeft.first > 41)
                spritePositionLeft.first -= frame/8;
            else if(spritePositionLeft.second == 245 && spritePositionLeft.first <= 41)
                spritePositionLeft.first = 41;
            
            if(spritePositionLeft.second == 356 && spritePositionLeft.first > 223)
                spritePositionLeft.first -= frame/8;
            else if(spritePositionLeft.second == 356 && spritePositionLeft.first <= 223)
                spritePositionLeft.first = 223;
            
            spriteLeft[1]->update(frame/3, 1, spritePositionLeft.first, spritePositionLeft.second, leftPlayer);
        }
        else
        {
            if(spritePositionRight.second == 158 && spritePositionRight.first > 923)
                spritePositionRight.first -= frame/8;
            else if(spritePositionRight.second == 158 && spritePositionRight.first <= 923)
                spritePositionRight.first = 923;
            
            if(spritePositionRight.second == 350 && spritePositionRight.first > screenWidth/2 + 50)
                spritePositionRight.first -= frame/8;
            else if(spritePositionRight.second == 350 && spritePositionRight.first <= screenWidth/2 + 50)
                spritePositionRight.first = screenWidth/2 + 50;
            
            spriteRight[1]->update(frame/3, 1, spritePositionRight.first, spritePositionRight.second, leftPlayer);
        }
        frame++;
    }
    else if(spriteMotion[2])
    {
        if(frame/3 >= 12){
            frame = 0;
        }
        if(leftPlayer)
        {
            if(spritePositionLeft.second == 245 && spritePositionLeft.first < 180)
                spritePositionLeft.first += frame/8;
            else if(spritePositionLeft.second == 245 && spritePositionLeft.first >= 180)
                spritePositionLeft.first = 180;
            
            if(spritePositionLeft.second == 356 && spritePositionLeft.first < screenWidth/2 - 50)
                spritePositionLeft.first += frame/8;
            else if(spritePositionLeft.second == 356 && spritePositionLeft.first >= screenWidth/2 - 50)
                spritePositionLeft.first = screenWidth/2 - 50;
            
            spriteLeft[2]->update(frame/3, 2, spritePositionLeft.first, spritePositionLeft.second, leftPlayer);
        }
        else
        {
            if(spritePositionRight.second == 158 && spritePositionRight.first < 1118)
                spritePositionRight.first += frame/8;
            else if(spritePositionRight.second == 158 && spritePositionRight.first >= 1118)
                spritePositionRight.first = 1118;
            
            if(spritePositionRight.second == 350 && spritePositionRight.first < 962)
                spritePositionRight.first += frame/8;
            else if(spritePositionRight.second == 350 && spritePositionRight.first >= 962)
                spritePositionRight.first = 962;
            
            spriteRight[2]->update(frame/3, 2, spritePositionRight.first, spritePositionRight.second, leftPlayer);
        }
        frame++;
    }
    else if(spriteMotion[3])
    {
        if(leftPlayer)
        {
            spritePositionLeft.second += frame/14;
            spriteLeft[3]->update(frame/5, 3, spritePositionLeft.first, spritePositionLeft.second, leftPlayer);
        }
        else
        {
            spritePositionRight.second += frame/14;
            spriteRight[3]->update(frame/5, 3, spritePositionRight.first, spritePositionRight.second, leftPlayer);
        }
        frame++;
        if(frame/5 >= 9)
        {
            if(leftPlayer)
            {
                spritePositionLeft.first += 40;
                
                spriteMotion[0] = true;
                spriteMotion[1] = false;
                spriteMotion[2] = false;
                spriteMotion[3] = false;
                
                spriteLeft[0]->update(0, 0, spritePositionLeft.first, spritePositionLeft.second, leftPlayer);
            }
            else
            {
                if(twice == 0)
                {
                    twice = 1;
                    frame = 0;
                }
                else
                {
                    twice = 0;
                    
                    spritePositionRight.first -= 10;
                    spritePositionRight.second = 350;
                    
                    spriteMotion[0] = true;
                    spriteMotion[1] = false;
                    spriteMotion[2] = false;
                    spriteMotion[3] = false;
                    
                    spriteRight[0]->update(0, 0, spritePositionRight.first, spritePositionRight.second, leftPlayer);
                }
            }
        }
    }
    else if(spriteMotion[4])
    {
        if(leftPlayer)
        {
            spritePositionLeft.second -= frame/14;
            spriteLeft[4]->update(frame/5, 4, spritePositionLeft.first, spritePositionLeft.second, leftPlayer);
        }
        else
        {
            spritePositionRight.second -= frame/14;
            spriteRight[4]->update(frame/5, 4, spritePositionRight.first, spritePositionRight.second, leftPlayer);
        }
        frame++;
        if(frame/5 >= 9)
        {
            if(leftPlayer)
            {
                spritePositionLeft.first -= 15;
                spritePositionLeft.second = 245;
                
                spriteMotion[0] = true;
                spriteMotion[1] = false;
                spriteMotion[2] = false;
                spriteMotion[4] = false;
                
                spriteLeft[0]->update(0, 0, spritePositionLeft.first, spritePositionLeft.second, leftPlayer);
            }
            else
            {
                if(twice == 0)
                {
                    twice = 1;
                    frame = 0;
                }
                else
                {
                    twice = 0;
                    
                    spritePositionRight.first = 990;
                    spritePositionRight.second = 158;
                    
                    spriteMotion[0] = true;
                    spriteMotion[1] = false;
                    spriteMotion[2] = false;
                    spriteMotion[4] = false;
                    spriteRight[0]->update(0, 0, spritePositionRight.first, spritePositionRight.second, leftPlayer);
                }
            }
        }
    }
    
    colliders->leftCollider = {spritePositionLeft.first+5, spritePositionLeft.second+5};
    colliders->rightCollider = {spritePositionRight.first+5, spritePositionRight.second+5};
    
    
//    trueTypeFont->update(leftPlayer, startTime);
        
}

void Game:: render()
{
    SDL_RenderClear(Menu:: renderer);
    SDL_RenderCopy(Menu:: renderer, background, NULL, NULL);
    
    if(!collidedSprite && pressed)
    {
        if(leftPlayer)
            leftBomb->render(leftPlayer);
        else
            rightBomb->render(leftPlayer);
    }
    
    cannonLeft->render(degreeLeft);
    cannonRight->render(degreeRight);
    
    
    SDL_RenderCopy(Menu:: renderer, ladder, NULL, &ladderDestLeft);
    SDL_RenderCopy(Menu:: renderer, ladder, NULL, &ladderDestRight);
    
    if(leftPlayer)
    {
        spriteRight[0]->render();
        if(spriteMotion[0])
            spriteLeft[0]->render();
        else if(spriteMotion[1])
            spriteLeft[1]->render();
        else if(spriteMotion[2])
            spriteLeft[2]->render();
        else if(spriteMotion[3])
            spriteLeft[3]->render();
        else if(spriteMotion[4])
            spriteLeft[4]->render();
    }
    else
    {
        spriteLeft[0]->render();
        if(spriteMotion[0])
            spriteRight[0]->render();
        else if(spriteMotion[1])
            spriteRight[1]->render();
        else if(spriteMotion[2])
            spriteRight[2]->render();
        else if(spriteMotion[3])
            spriteRight[3]->render();
        else if(spriteMotion[4])
            spriteRight[4]->render();
    }
    
    //ProgressBar:: render();
//    SDL_RenderCopy(Menu:: renderer, clock, NULL, &clockDst);
//    SDL_RenderCopy(Menu:: renderer, heart, NULL, &heartDstLeft);
//    SDL_RenderCopy(Menu:: renderer, heart, NULL, &heartDstRight);
//    SDL_RenderCopy(Menu:: renderer, thunder, NULL, &thunderDstLeft);
//    SDL_RenderCopy(Menu:: renderer, thunder, NULL, &thunderDstRight);
    
    if(ProgressBar:: windSpeed != 0)
    {
        if(ProgressBar:: windDir == 0)
        {
            arrowRightDest.x = arrowRightX + arrowFrame/16 * 2;
            SDL_RenderCopy(Menu:: renderer, arrowRight, NULL, &arrowRightDest);
            arrowFrame++;
            if(arrowFrame > 80)
            {
                arrowFrame = 0;
            }
        }
        else
        {
            arrowLeftDest.x = arrowLeftX - arrowFrame/16 * 2;
            SDL_RenderCopy(Menu:: renderer, arrowLeft, NULL, &arrowLeftDest);
            arrowFrame++;
            if(arrowFrame > 80)
            {
                arrowFrame = 0;
            }
        }
    }
    
    if(collidedSprite)
    {
        if(explosionTime > SDL_GetTicks()/1000)
        {
            if(smokeFrame/10 < 5 && explosionFrame/7 > 2)
            {
                SDL_RenderCopy(Menu:: renderer, smoke, &smokeSrc[smokeFrame/10], &smokeDst);
                smokeFrame++;
            }

            if(explosionFrame/7 < 7)
            {
                SDL_RenderCopy(Menu:: renderer, spriteExplosion, &spriteExplosionSrc[explosionFrame/7], &spriteExplosionDest);
                explosionFrame++;
            }
        }
        else
        {
            if(Collision:: collidedLeft == true)
            {
                if(ProgressBar:: healthLeft.w > 0)
                {
                    ProgressBar:: healthLeft.w -= decreaseLife;
                    if(featureFlag == 1 && ProgressBar:: healthLeft.w > 0)
                    {
                        ProgressBar:: healthLeft.w -= decreaseLife;
                        featureFlag = -1;
                    }
                        
                }
            }
            else
            {
                if(ProgressBar:: healthRight.w > 0)
                {
                    ProgressBar:: healthRight.w -= decreaseLife;
                    if(featureFlag == 1 && ProgressBar:: healthRight.w > 0)
                    {
                        ProgressBar:: healthRight.w -= decreaseLife;
                        featureFlag = -1;
                    }
                }
            }
            collidedSprite = false;
            lock = false;
            pressed = false;
            if(featureFlag == 2)
            {
                if(twiceTurnCount == 0)
                {
                    twiceTurnCount++;
                }
                else
                {
                    twiceTurnCount = 0;
                    featureFlag = -1;
                }
            }
            else
            {
                featureFlag = -1;
            }
            if(featureFlag != 2)
            {
                leftPlayer ^= true;
                rightPlayer ^= true;
            }
            startTime = 20 + SDL_GetTicks()/1000;
            ProgressBar:: windDir = rand() % 2;
            ProgressBar:: windSpeed = (rand() % 4) * 15;
            vel = minVel;
            dontMove = false;
        }
    }
    
    ProgressBar:: render();
    SDL_RenderCopy(Menu:: renderer, clock, NULL, &clockDst);
    SDL_RenderCopy(Menu:: renderer, heart, NULL, &heartDstLeft);
    SDL_RenderCopy(Menu:: renderer, heart, NULL, &heartDstRight);
    SDL_RenderCopy(Menu:: renderer, thunder, NULL, &thunderDstLeft);
    SDL_RenderCopy(Menu:: renderer, thunder, NULL, &thunderDstRight);
    
    trueTypeFont->render();
    
    leftBox->render();
    rightBox->render();
    leftBox->renderFeature(featureFlag);
    rightBox->renderFeature(featureFlag);
    
    SDL_RenderCopy(Menu:: renderer, pause, NULL, &pauseDest);
    
//    for checking the colliders position
//    SDL_Rect fillRect1 = {spritePositionLeft.first+5, spritePositionLeft.second+5, 30, 80};
//    SDL_Rect fillRect2 = {spritePositionRight.first+5, spritePositionRight.second+5, 30, 80};
//    SDL_Rect fillRect3 = {leftBomb->xpos, leftBomb->ypos, 30, 32};
//    SDL_Rect fillRect4 = {rightBomb->xpos, rightBomb->ypos, 30, 32};
//    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
//    SDL_RenderFillRect(renderer, &fillRect1);
//    SDL_RenderFillRect(renderer, &fillRect2);
//    SDL_RenderFillRect(renderer, &fillRect3);
//    SDL_RenderFillRect(renderer, &fillRect4);
    
    SDL_RenderPresent(Menu:: renderer);
}

bool Game:: checkFinishGame()
{
    if(ProgressBar:: healthLeft.w == 0)
    {
        isRunning = false;
        Mix_HaltMusic();
        if(againstComputer == false)
        {
            Mix_PlayChannel(-1, winEffect, 0);
            for(int i = 0; i < 2e2; i++)
            {
                SDL_RenderClear(Menu:: renderer);
                SDL_RenderCopy(Menu:: renderer, rightwin, NULL, NULL);
                SDL_RenderPresent(Menu:: renderer);
            }
        }
        else
        {
            Mix_PlayChannel(-1, loseEffect, 0);
            for(int i = 0; i < 2e2; i++)
            {
                SDL_RenderClear(Menu:: renderer);
                SDL_RenderCopy(Menu:: renderer, youlose, NULL, NULL);
                SDL_RenderPresent(Menu:: renderer);
            }
        }
        return true;
    }
    else if(ProgressBar:: healthRight.w == 0)
    {
        isRunning = false;
        Mix_HaltMusic();
        if(againstComputer == false)
        {
            Mix_PlayChannel(-1, winEffect, 0);
            for(int i = 0; i < 2e2; i++)
            {
                SDL_RenderClear(Menu:: renderer);
                SDL_RenderCopy(Menu:: renderer, leftwin, NULL, NULL);
                SDL_RenderPresent(Menu:: renderer);
            }
        }
        else
        {
            Mix_PlayChannel(-1, winEffect, 0);
            for(int i = 0; i < 2e2; i++)
            {
                SDL_RenderClear(Menu:: renderer);
                SDL_RenderCopy(Menu:: renderer, youwin, NULL, NULL);
                SDL_RenderPresent(Menu:: renderer);
            }
        }
        return true;
    }
    return false;
}

void Game:: clean()
{
//    SDL_DestroyWindow(window);
//    SDL_DestroyRenderer(renderer);
    
    Mix_FreeMusic(bgm);
    Mix_FreeChunk(ThrowMusic);
    Mix_FreeChunk(HitMusic);
    Mix_FreeChunk(GiftMusic);
    Mix_FreeChunk(CanonMusic);
    bgm = NULL;
    ThrowMusic = NULL;
    HitMusic = NULL;
    GiftMusic = NULL;
    CanonMusic = NULL;
    
//    window = NULL;
//    renderer = NULL;
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
    printf("SDL cleaned\n");
}
