# Cannon-Fight

“Cannon Fight” is a game that can be played in both single-player and multiplayer modes. Here, the player has to hit his opponent with a cannon by pressing the spacebar. The bomb is thrown in projectile motion, and the player has the opportunity to set the direction of the cannon and throw the bomb so that he can increase the probability of hitting his opponent, while the player also has the ability to move down the aisle by a ladder and walk to and fro so that he can protect himself during his own turn only. The player is given specific timing for fixing the angle of the cannon and throwing the bomb at his opponent. There is also a special gift box of  which the player can choose during the game, the gift box provides any of three features: health increase, double damage, twice turns. The player who gets hit will lose life, and if it loses several turns and the life bar is empty, the player is defeated in the game. If the player manages to hit more and defeat his opponent, he wins. 

Installing Process:
* Library Pre-requisites : 
  * ```Linux```:
    * Debian Based Distributions : 
       ```build-essential``` ```libsdl2-2.0```  ```libsdl2-dev``` ```libsdl2-image-dev``` ```libsdl2-ttf-dev``` ```libsdl2-mixer-dev```
    * Install equaivalent packages of the above mentioned by following these command:
      
      Install C++
      ``` 
        sudo apt-get install g++
      ```
      Install libsdl2-2.0
      ``` 
        sudo apt-get install libsdl2-2.0
      ```
      Install libsdl2-dev
      ``` 
        sudo apt-get install libsdl2-dev
      ```
      Install libsdl2-image-dev
      ``` 
        sudo apt-get install libsdl2-image-dev
      ```
      Install libsdl2-ttf-dev
      ``` 
        sudo apt-get install libsdl2-mixer-dev
      ```
      Install libsdl2-ttf-dev
      ``` 
        sudo apt-get install libsdl2-ttf-dev
      ```

    * Alternatively you can run ```setup.sh```
  * Compile with:
      ```
       make 
      ``` 
* In case of playing with mouse make sure to put your mouse's  ```CURSOR``` inside the window.
