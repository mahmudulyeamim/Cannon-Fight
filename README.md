
# Cannon Fight



![CSE1211 Cannon Fight](https://user-images.githubusercontent.com/121728514/210173557-539af942-3e68-40c2-9b1b-b02162c73f51.png)


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

    - Delete these parts from above of Game.hpp

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

Now run the game using below command
```bash
  g++ main.cpp Cannon.cpp Collision.cpp Game.cpp Projectile.cpp Sprite.cpp GameEngine.cpp TextureManager.cpp TTF.cpp ProgressBar.cpp GiftBox.cpp Menu.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx -lSDL2_mixer && ./a.out
```

**Operating System: MacOS**
- Follow this <a href = "https://lazyfoo.net/tutorials/SDL/01_hello_SDL/mac/index.php"> link </a> to setup SDL2 on XCode.
- Then setup image library using this <a href = "https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/mac/index.php"> link </a>.
- Similar to image library, you can set up other libraries such as : TTF, Mixer.
- Then set up gfx extension library using this <a href = "https://www.youtube.com/watch?v=A7Th6kDdNdM&list=PLJ-vQubfi2yEfPCqb1lr9GX2Kc1NhU4du&index=3"> video </a>
- After you have succesfully linked the library files, download the "Assets" folder and "Header & CPP files" folder from above.
- Create a new folder named "Cannon Fight" on your computer.
- Here, move the contents of the downloaded folders to this newly created file.
- Open this folder on XCode and run it.

## Video
- You can watch the demo video of the game on <a href = "https://youtu.be/vELsUzH9Quc"> YouTube </a>
