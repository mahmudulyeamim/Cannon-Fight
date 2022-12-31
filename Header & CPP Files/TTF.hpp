#ifndef TTF_hpp
#define TTF_hpp

#include "Game.hpp"

class TTF {
  
public:
    TTF(const char* fontname);
    void update(bool leftPlay, int startTime);
    void render();
    static SDL_Rect turnDest, timerDest;
    
private:
    
    const char* font;
    SDL_Texture* leftPlayer;
    SDL_Texture* rightPlayer;
    SDL_Texture* timer;
    SDL_Texture* currentPlayer;
    SDL_Texture* wind;
    SDL_Texture* warning;
    SDL_Rect windDest;
    stringstream timeText;
};

#endif /* TTF_hpp */
