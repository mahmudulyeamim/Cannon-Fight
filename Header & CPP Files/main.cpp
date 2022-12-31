#include "Menu.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"


Menu* menu;
Game *game;
int main(int argc, const char * argv[]) {
    
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    
    bool gameHasEnded = true;

    Uint32 frameStart;
    int frameTime;
    
    menu = new Menu("Cannon Fight", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 600);
    game = new Game();
    
    menu->playMusic();
    
    while(menu->running())
    {
        int flag = menu->handleEvents(0);
        if(flag == 1)
        {
            menu->modeChoiceRunning = true;
            while(menu->modeChoiceRunning)
            {
                int flag1 = menu->handleEvents(1);
                if(flag1 == 1 || flag1 == 2)
                {
                    menu->playMusic();
                    gameHasEnded = false;
                    game->init(flag1);
                    if(game->running())
                    {
                        game->playMusic();
                    }
                    while(game->running())
                    {
                        frameStart = SDL_GetTicks();

                        game->handleEvents();
                        game->update();
                        game->render();
                        gameHasEnded = game->checkFinishGame();

                        frameTime = SDL_GetTicks() - frameStart;
                        if(frameDelay > frameTime)
                        {
                            SDL_Delay(frameDelay - frameTime);
                        }
                    }
                    game->stopMusic();
                    menu->modeChoiceRunning = false;
                    menu->playMusic();
                    //menu->render(0);
                    flag = 0;
                }
                else if(flag1 == 0)
                {
                    menu->modeChoiceRunning = false;
                }
                else
                {
                    menu->render(1);
                }
            }
        }
        else if(flag == 2)
        {
            if(gameHasEnded == false)
            {
                menu->stopMusic();
                game->resume();
                game->isRunning = true;
                if(game->running())
                {
                    game->playMusic();
                }
                while(game->running())
                {
                    frameStart = SDL_GetTicks();

                    game->handleEvents();
                    game->update();
                    game->render();
                    gameHasEnded = game->checkFinishGame();

                    frameTime = SDL_GetTicks() - frameStart;
                    if(frameDelay > frameTime)
                    {
                        SDL_Delay(frameDelay - frameTime);
                    }
                }
                game->stopMusic();
                menu->playMusic();
                //menu->render(0);
                flag = 0;
            }
        }
        else if(flag == 3)
        {
            menu->guideRunning = true;
            while(menu->guideRunning)
            {
                int flag1 = menu->handleEvents(3);
                if(flag1 == 0)
                {
                    menu->guideRunning = false;
                }
                else
                {
                    menu->render(3);
                }
            }
        }
        else if(flag == 4)
        {
            menu->alertRunning = true;
            while(menu->alertRunning)
            {
                int flag1 = menu->handleEvents(4);
                if(flag1 == 1 || flag1 == 2)
                {
                    menu->alertRunning = false;
                }
                else
                {
                    menu->render(4);
                }
            }
        }
        else
        {
            menu->render(0);
        }
    }
    
    menu->stopMusic();
    game->clean();
    menu->clean();
}

