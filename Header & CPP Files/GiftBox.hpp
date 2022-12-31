#ifndef GiftBox_hpp
#define GiftBox_hpp

#include "Game.hpp"

class GiftBox {
  
public:
    GiftBox(const char *filename, int posX, int posY, int dim, const char *filename1, const char *filename2, const char *filename3, int featureX, int featureY);
    void init(const char* filename);
    int checkMouseClick(int mouseX, int mouseY, int againstComputer);
    void renderFeature(int flag);
    void render();
private:
    SDL_Texture* box = NULL;
    SDL_Texture* healthIncrease = NULL;
    SDL_Texture* doubleDamage = NULL;
    SDL_Texture* twiceTurn = NULL;
    SDL_Rect boxDestRect;
    SDL_Rect featureDestRect;
    int x, y, dimension;
    int midx, midy;
    bool boxUsed;
};

#endif /* GiftBox_hpp */
