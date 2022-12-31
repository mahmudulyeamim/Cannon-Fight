#include "Menu.hpp"
#include "TextureManager.hpp"


SDL_Renderer* Menu:: renderer = NULL;
bool Menu:: isRunning = false;
bool Menu:: modeChoiceRunning = false;
bool Menu:: guideRunning = false;
bool Menu:: alertRunning = false;

Menu:: Menu(const char* title, int x, int y, int w, int h)
{
    int flags = 0;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Could not initialize SDL %s\n", SDL_GetError());
        isRunning = false;
    }
    else
    {
        window = SDL_CreateWindow(title, x, y, w, h, flags);
        if(window == NULL)
        {
            printf("Could not create window %s\n", SDL_GetError());
            isRunning = false;
        }
        else
        {
            printf("Window created\n");
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(renderer == NULL)
            {
                printf("Could not create renderer %s\n", SDL_GetError());
                isRunning = false;
            }
            else
            {
                printf("Created renderer\n");
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            }
            if(TTF_Init() == -1)
            {
                printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
            }
        }

        isRunning = true;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    
    click = Mix_LoadWAV("click.wav");
    menubgm = Mix_LoadMUS("menubgm.mp3");
    
    // start menu
    menubg = TextureManager:: loadTexture("menubg.png");
    header = TextureManager:: loadTexture("header.png");
    newgameButton = TextureManager:: loadTexture("newgamebutton.png");
    loadgameButton = TextureManager:: loadTexture("loadgamebutton.png");
    guideButton = TextureManager:: loadTexture("guidebutton.png");
    exitButton = TextureManager:: loadTexture("exitbutton.png");
    
    newgameButton1 = TextureManager:: loadTexture("newgamebutton1.png");
    loadgameButton1 = TextureManager:: loadTexture("loadgamebutton1.png");
    guideButton1 = TextureManager:: loadTexture("guidebutton1.png");
    exitButton1 = TextureManager:: loadTexture("exitbutton1.png");
    
    headerTex = {Game:: screenWidth/2 - 180, 10, 336, 133};
    newgameButtonTex = {Game:: screenWidth/2 - 139, 10 + 110, 277, 156};
    loadgameButtonTex = {Game:: screenWidth/2 - 139, 10 + 110 + 100, 277, 156};
    guideButtonTex = {Game:: screenWidth/2 - 139, 10 + 110 + 100*2, 277, 156};
    exitButtonTex = {Game:: screenWidth/2 - 139, 10 + 110 + 100*3, 277, 156};
    
    newgameButton1Tex = {Game:: screenWidth/2 - 140, 10 + 110, 277, 156};
    loadgameButton1Tex = {Game:: screenWidth/2 - 139, 10 + 110 + 100, 277, 156};
    guideButton1Tex = {Game:: screenWidth/2 - 139, 10 + 110 + 100*2, 277, 156};
    exitButton1Tex = {Game:: screenWidth/2 - 139, 10 + 110 + 100*3, 277, 156};
    
    buttonWidth = 250;
    buttonHeight = 75;
    buttonX =  Game:: screenWidth/2 - 139;
    buttonY1 = 10 + 110 + 40;
    buttonY2 = 10 + 110 + 100 + 40;
    buttonY3 = 10 + 110 + 100*2 + 40;
    buttonY4 = 10 + 110 + 100*3 + 40;
    
    //new game menu
    onePlayerButton = TextureManager:: loadTexture("oneplayer.png");
    twoPlayerButton = TextureManager:: loadTexture("twoplayer.png");
    backButton = TextureManager:: loadTexture("back.png");
    
    onePlayerButton1 = TextureManager:: loadTexture("oneplayer1.png");
    twoPlayerButton1 = TextureManager:: loadTexture("twoplayer1.png");
    backButton1 = TextureManager:: loadTexture("back1.png");
    
    onePlayerButtonTex = {Game:: screenWidth/2 - 139, 10 + 110, 277, 156};
    twoPlayerButtonTex = {Game:: screenWidth/2 - 139, 10 + 110 + 100, 277, 156};
    backButtonTex = {Game:: screenWidth/2 - 139, 10 + 110 + 100*2, 277, 156};
    
    onePlayerButton1Tex = {Game:: screenWidth/2 - 140, 10 + 110, 277, 156};
    twoPlayerButton1Tex = {Game:: screenWidth/2 - 140, 10 + 110 + 100, 277, 156};
    backButton1Tex = {Game:: screenWidth/2 - 141, 10 + 110 + 100*2, 277, 156};
    
    //exit menu
    alertButton = TextureManager:: loadTexture("alertbutton.png");
    yesButton = TextureManager:: loadTexture("yesbutton.png");
    noButton = TextureManager:: loadTexture("nobutton.png");
    
    yesButton1 = TextureManager:: loadTexture("yesbutton1.png");
    noButton1 = TextureManager:: loadTexture("nobutton1.png");
    
    alertButtonTex = {Game:: screenWidth/2 - 339, 10, 677, 229};
    yesButtonTex = {Game:: screenWidth/2 - 120, 10 + 200, 264, 124};
    noButtonTex = {Game:: screenWidth/2 - 120, 10 + 200 + 100, 264, 116};
    
    yesButton1Tex = {Game:: screenWidth/2 - 121, 10 + 200, 264, 117};
    noButton1Tex = {Game:: screenWidth/2 - 121, 10 + 200 + 100, 264, 116};
    
    yesNoX = Game:: screenWidth/2 - 120;
    yesY = 10 + 200 + 40;
    noY = 10 + 200 + 40 + 100;
    yesNoWidth = 220;
    yesNoHeight = 70;
    
    guideline1Button = TextureManager:: loadTexture("guide1.png");
    guideline2Button = TextureManager:: loadTexture("guide2.png");
    guideline3Button = TextureManager:: loadTexture("guide3.png");
    
}

void Menu:: playMusic()
{
    Mix_PlayMusic(menubgm, -1);
}

void Menu:: stopMusic()
{
    Mix_HaltMusic();
}

int Menu:: handleEvents(int flag)
{
    if(flag == 0)
    {
        SDL_Event e;
        SDL_PollEvent(&e);
        if(e.type == SDL_QUIT)
        {
            isRunning = false;
        }
        if(e.type == SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&mouseX, &mouseY);
            if(mouseX > buttonX && mouseX < buttonX+buttonWidth && mouseY > buttonY1 && mouseY < buttonY1+buttonHeight)
            {
                firstScreenFlag = 1;
            }
            else if(mouseX > buttonX && mouseX < buttonX+buttonWidth && mouseY > buttonY2 && mouseY < buttonY2+buttonHeight)
            {
                firstScreenFlag = 2;
            }
            else if(mouseX > buttonX && mouseX < buttonX+buttonWidth && mouseY > buttonY3 && mouseY < buttonY3+buttonHeight)
            {
                firstScreenFlag = 3;
            }
            else if(mouseX > buttonX && mouseX < buttonX+buttonWidth && mouseY > buttonY4 && mouseY < buttonY4+buttonHeight)
            {
                firstScreenFlag = 4;
            }
            else
            {
                firstScreenFlag = -1;
            }
        }
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_GetMouseState(&mouseX, &mouseY);
            if(mouseX > buttonX && mouseX < buttonX+buttonWidth && mouseY > buttonY1 && mouseY < buttonY1+buttonHeight)
            {
                Mix_PlayChannel(-1, click, 0);
                return 1;
            }
            else if(mouseX > buttonX && mouseX < buttonX+buttonWidth && mouseY > buttonY2 && mouseY < buttonY2+buttonHeight)
            {
                Mix_PlayChannel(-1, click, 0);
                return 2;
            }
            else if(mouseX > buttonX && mouseX < buttonX+buttonWidth && mouseY > buttonY3 && mouseY < buttonY3+buttonHeight)
            {
                Mix_PlayChannel(-1, click, 0);
                return 3;
            }
            else if(mouseX > buttonX && mouseX < buttonX+buttonWidth && mouseY > buttonY4 && mouseY < buttonY4+buttonHeight)
            {
                Mix_PlayChannel(-1, click, 0);
                return 4;
            }
        }
    }
    else if(flag == 1)
    {
        SDL_Event e;
        SDL_PollEvent(&e);
        if(e.type == SDL_QUIT)
        {
            isRunning = false;
            modeChoiceRunning = false;
        }
        if(e.type == SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&mouseX, &mouseY);
            if(mouseX > buttonX && mouseX < buttonX+buttonWidth && mouseY > buttonY1 && mouseY < buttonY1+buttonHeight)
            {
                modeScreenFlag = 1;
            }
            else if(mouseX > buttonX && mouseX < buttonX+buttonWidth && mouseY > buttonY2 && mouseY < buttonY2+buttonHeight)
            {
                modeScreenFlag = 2;
            }
            else if(mouseX > buttonX && mouseX < buttonX+buttonWidth && mouseY > buttonY3 && mouseY < buttonY3+buttonHeight)
            {
                modeScreenFlag = 3;
            }
            else
            {
                modeScreenFlag = -1;
            }
        }
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_GetMouseState(&mouseX, &mouseY);
            if(mouseX > buttonX && mouseX < buttonX+buttonWidth && mouseY > buttonY1 && mouseY < buttonY1+buttonHeight)
            {
                Mix_PlayChannel(-1, click, 0);
                return 1;
            }
            else if(mouseX > buttonX && mouseX < buttonX+buttonWidth && mouseY > buttonY2 && mouseY < buttonY2+buttonHeight)
            {
                Mix_PlayChannel(-1, click, 0);
                return 2;
            }
            else if(mouseX > buttonX && mouseX < buttonX+buttonWidth && mouseY > buttonY3 && mouseY < buttonY3+buttonHeight)
            {
                Mix_PlayChannel(-1, click, 0);
                return 0;
            }
        }
        
    }
    else if(flag == 3)
    {
        SDL_Event e;
        SDL_PollEvent(&e);
        if(e.type == SDL_QUIT)
        {
            isRunning = false;
            guideRunning = false;
        }
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_GetMouseState(&mouseX, &mouseY);
            cout << mouseX << ' ' << mouseY << '\n';
            if(guidePageNumber == 1)
            {
                if(mouseX > 13 && mouseX < 160 && mouseY > 505 && mouseY < 540)
                {
                    Mix_PlayChannel(-1, click, 0);
                    return 0;
                }
                if(mouseX > 1040 && mouseX < 1185 && mouseY > 505 && mouseY < 540)
                {
                    Mix_PlayChannel(-1, click, 0);
                    guidePageNumber = 2;
                    return 1;
                }
            }
            else if(guidePageNumber == 2)
            {
                if(mouseX > 13 && mouseX < 160 && mouseY > 505 && mouseY < 540)
                {
                    Mix_PlayChannel(-1, click, 0);
                    guidePageNumber = 1;
                    return 1;
                }
                if(mouseX > 1040 && mouseX < 1185 && mouseY > 505 && mouseY < 540)
                {
                    Mix_PlayChannel(-1, click, 0);
                    guidePageNumber = 3;
                    return 2;
                }
            }
            else if(guidePageNumber == 3)
            {
                if(mouseX > 13 && mouseX < 165 && mouseY > 497 && mouseY < 540)
                {
                    Mix_PlayChannel(-1, click, 0);
                    guidePageNumber = 2;
                    return 2;
                }
            }
        }
    }
    else if(flag == 4)
    {
        SDL_Event e;
        SDL_PollEvent(&e);
        if(e.type == SDL_QUIT)
        {
            isRunning = false;
            alertRunning = false;
        }
        if(e.type == SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&mouseX, &mouseY);
            if(mouseX > yesNoX && mouseX < yesNoX+yesNoWidth && mouseY > yesY && mouseY < yesY+yesNoHeight)
            {
                exitScreenFlag = 1;
            }
            else if(mouseX > yesNoX && mouseX < yesNoX+yesNoWidth && mouseY > noY && mouseY < noY+yesNoHeight)
            {
                exitScreenFlag = 2;
            }
            else
            {
                exitScreenFlag = -1;
            }
        }
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            SDL_GetMouseState(&mouseX, &mouseY);
            if(mouseX > yesNoX && mouseX < yesNoX+yesNoWidth && mouseY > yesY && mouseY < yesY+yesNoHeight)
            {
                Mix_PlayChannel(-1, click, 0);
                for(int i = 0; i < 2e8+1e7; i++);
                isRunning = false;
                return 1;
            }
            else if(mouseX > yesNoX && mouseX < yesNoX+yesNoWidth && mouseY > noY && mouseY < noY+yesNoHeight)
            {
                Mix_PlayChannel(-1, click, 0);
                return 2;
            }
        }
    }
    return -1;
}

void Menu:: render(int flag)
{
    SDL_RenderClear(renderer);
    //SDL_RenderCopy(renderer, menubg, NULL, NULL);
    if(flag == 0)
    {
        SDL_RenderCopy(renderer, menubg, NULL, NULL);
        SDL_RenderCopy(renderer, header, NULL, &headerTex);
        if(firstScreenFlag == 1)
            SDL_RenderCopy(renderer, newgameButton1, NULL, &newgameButton1Tex);
        else
            SDL_RenderCopy(renderer, newgameButton, NULL, &newgameButtonTex);
        if(firstScreenFlag == 2)
            SDL_RenderCopy(renderer, loadgameButton1, NULL, &loadgameButton1Tex);
        else
            SDL_RenderCopy(renderer, loadgameButton, NULL, &loadgameButtonTex);
        if(firstScreenFlag == 3)
            SDL_RenderCopy(renderer, guideButton1, NULL, &guideButton1Tex);
        else
            SDL_RenderCopy(renderer, guideButton, NULL, &guideButtonTex);
        if(firstScreenFlag == 4)
            SDL_RenderCopy(renderer, exitButton1, NULL, &exitButton1Tex);
        else
            SDL_RenderCopy(renderer, exitButton, NULL, &exitButtonTex);
    }
    else if(flag == 1)
    {
        SDL_RenderCopy(renderer, menubg, NULL, NULL);
        SDL_RenderCopy(renderer, header, NULL, &headerTex);
        if(modeScreenFlag == 1)
            SDL_RenderCopy(renderer, onePlayerButton1, NULL, &onePlayerButton1Tex);
        else
            SDL_RenderCopy(renderer, onePlayerButton, NULL, &onePlayerButtonTex);
        if(modeScreenFlag == 2)
            SDL_RenderCopy(renderer, twoPlayerButton1, NULL, &twoPlayerButton1Tex);
        else
            SDL_RenderCopy(renderer, twoPlayerButton, NULL, &twoPlayerButtonTex);
        if(modeScreenFlag == 3)
            SDL_RenderCopy(renderer, backButton1, NULL, &backButton1Tex);
        else
            SDL_RenderCopy(renderer, backButton, NULL, &backButtonTex);
    }
    else if(flag == 3)
    {
        if(guidePageNumber == 1)
        {
            SDL_RenderCopy(renderer, guideline1Button, NULL, NULL);
        }
        else if(guidePageNumber == 2)
        {
            SDL_RenderCopy(renderer, guideline2Button, NULL, NULL);
        }
        else if(guidePageNumber == 3)
        {
            SDL_RenderCopy(renderer, guideline3Button, NULL, NULL);
        }
    }
    else if(flag == 4)
    {
        SDL_RenderCopy(renderer, menubg, NULL, NULL);
        SDL_RenderCopy(renderer, alertButton, NULL, &alertButtonTex);
        if(exitScreenFlag == 1)
            SDL_RenderCopy(renderer, yesButton1, NULL, &yesButton1Tex);
        else
            SDL_RenderCopy(renderer, yesButton, NULL, &yesButtonTex);
        if(exitScreenFlag == 2)
            SDL_RenderCopy(renderer, noButton1, NULL, &noButton1Tex);
        else
            SDL_RenderCopy(renderer, noButton, NULL, &noButtonTex);
    }
    SDL_RenderPresent(renderer);
}

void Menu:: clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    
    window = NULL;
    renderer = NULL;
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
