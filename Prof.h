#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include <string>
#include "Player.h"
#pragma once

class Prof{
    public:
        //The dimensions of the Prof (a square)
        static const int PROF_WIDTH = 18;  
        static const int PROF_HEIGHT = 18;

        //Maximum axis velocity of the Prof
        static const int PROF_VEL = 2;

        //Initializes the variables
        Prof(int posX, int posY);

        void moveProf(Player p1 , Player p2, int map[70][100]);
        void renderProf(SDL_Renderer* renderer, WTexture &ProfTexture);
        bool collided(Player p);


    private:  

        //The X and Y offsets of the Prof
        int mPosX, mPosY;

        int iPosX , iPosY;
        
        //The velocity of the Prof
        int mVelX, mVelY;

        //The Prof's direction
        int mDirection;
};