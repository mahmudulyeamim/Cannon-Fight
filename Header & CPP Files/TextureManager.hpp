//
//  TextureManager.hpp
//  Game_Project
//
//  Created by Mahmudul Hasan Yeamim on 7/10/22.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "Game.hpp"

class TextureManager {
  
public:
    static SDL_Texture* loadTexture(const char* filename);
    
};


#endif /* TextureManager_hpp */
