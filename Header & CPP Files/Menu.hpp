#ifndef Menu_hpp
#define Menu_hpp

#include "Game.hpp"

class Menu {
  
public:
    Menu(const char* title, int x, int y, int w, int h);
    void playMusic();
    void stopMusic();
    int handleEvents(int flag);
    void render(int flag);
    bool running() { return isRunning; }
    void clean();
    static SDL_Renderer* renderer;
    static bool isRunning;
    static bool modeChoiceRunning;
    static bool guideRunning;
    static bool alertRunning;
private:
    //bool isRunning;
    SDL_Window* window;
    //SDL_Renderer* renderer = NULL;
    
    SDL_Texture *menubg;
    SDL_Texture *header, *newgameButton, *loadgameButton, *guideButton, *exitButton;
    SDL_Texture *newgameButton1, *loadgameButton1, *guideButton1, *exitButton1;
    SDL_Rect headerTex, newgameButtonTex, loadgameButtonTex, guideButtonTex, exitButtonTex;
    SDL_Rect newgameButton1Tex, loadgameButton1Tex, guideButton1Tex, exitButton1Tex;
    
    SDL_Texture *onePlayerButton, *twoPlayerButton, *backButton;
    SDL_Texture *onePlayerButton1, *twoPlayerButton1, *backButton1;
    SDL_Rect onePlayerButtonTex, twoPlayerButtonTex, backButtonTex;
    SDL_Rect onePlayerButton1Tex, twoPlayerButton1Tex, backButton1Tex;
    
    SDL_Texture *alertButton, *yesButton, *yesButton1, *noButton, *noButton1;
    SDL_Rect alertButtonTex, yesButtonTex, yesButton1Tex, noButtonTex, noButton1Tex;
    
    SDL_Texture *guideline1Button, *guideline2Button, *guideline3Button;
    //SDL_Rect guidelineButtonTex;
    int guidePageNumber = 1;
    
    
    int mouseX, mouseY;
    int firstScreenFlag = 0, exitScreenFlag = 0, modeScreenFlag = 0;
    int buttonWidth, buttonHeight;
    int buttonX, buttonY1, buttonY2, buttonY3, buttonY4;
    int yesNoX, yesY, noY, yesNoWidth, yesNoHeight;
    
    Mix_Chunk* click = NULL;
    Mix_Music* menubgm = NULL;
};

#endif /* Menu_hpp */
