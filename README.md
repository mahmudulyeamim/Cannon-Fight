
# Cannon Fight



![CSE1211-Cannon Fight](https://user-images.githubusercontent.com/121728514/210166898-c9aa812e-70e6-4d56-acae-fd8dbdf64a83.png)


## About
“Cannon Fight” is a game that can be played in both single-player and multiplayer modes. Here, the player has to hit his opponent with a cannon by pressing the spacebar. The bomb is thrown in projectile motion, and the player has the opportunity to set the direction of the cannon and throw the bomb so that he can increase the probability of hitting his opponent, while the player also has the ability to move down the aisle by a ladder and walk to and fro so that he can protect himself during his own turn only. The player is given specific timing for fixing the angle of the cannon and throwing the bomb at his opponent. There is also a special gift box of which the player can choose during the game, the gift box provides any of three features: health increase, double damage, twice turns. The player who gets hit will lose life, and if it loses several turns and the life bar is empty, the player is defeated in the game. If the player manages to hit more and defeat his opponent, he wins.

The game is implemented using only **C/C++** language and **SDL2 (Simple DirectMedia Layer)** library. We developed this game for the **"CSE-1211 Project"**.
## Installation

**Operating System: Linux**

- First open your terminal and run the given commands to install required packages.

Install C++ compiler
```bash
  sudo apt-get install g++
```
Install libsdl2-2.0
```bash
  sudo apt-get install libsdl2-2.0
```
Install libsdl2-dev
```bash
  sudo apt-get install libsdl2-dev
```
Install libsdl2-image-dev
```bash
  sudo apt-get install libsdl2-image-dev
```
Install libsdl2-ttf-dev
```bash
  sudo apt-get install libsdl2-ttf-dev
```
Install libsdl2-mixer-dev
```bash
  sudo apt-get install libsdl2-mixer-dev
```
- After you have succesfully installed the packages, download the "Assets" folder and "Header & CPP files" folder from above.  
- Create a folder named "Cannon Fight" on your computer and move the contents of the downloaded folders to this newly created file.
- Open up "Cannon Fight" on your terminal.
- Open Game.hpp file and do the following:

    - Delete these parts form above of Game.hpp

            #include <SDL2/SDL.h>
            #include <SDL2_image/SDL_image.h>
            #include <SDL2_ttf/SDL_ttf.h>
            #include <SDL2_gfx/SDL2_gfxPrimitives.h>
            #include <SDL2_mixer/SDL_mixer.h>
    - Now paste these parts there

            #include <SDL2/SDL.h>
            #include <SDL2/SDL_image.h>
            #include <SDL2/SDL_ttf.h>
            #include <SDL2/SDL2_gfxPrimitives.h>
            #include <SDL2/SDL_mixer.h>

- Close Game.hpp
- Now run the game using below command
```bash
  g++ main.cpp Cannon.cpp Collision.cpp Game.cpp Projectile.cpp Sprite.cpp GameEngine.cpp TextureManager.cpp TTF.cpp ProgressBar.cpp GiftBox.cpp Menu.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx -lSDL2_mixer && ./a.out
```
