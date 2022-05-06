#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include <string>
#include "Player.h"
#pragma once

class Guard{
    public:
        //The dimensions of the guard (a square)
        static const int GUARD_WIDTH = 19;  
        static const int GUARD_HEIGHT = 19;

        //Maximum axis velocity of the guard
        static const int GUARD_VEL = 5;

        //Initializes the variables
        Guard(int posX, int posY);

        void moveGuard(Player p1 , Player p2, int map[70][100]);
        void renderGuard(SDL_Renderer* renderer, WTexture &guardTexture);

         //The X and Y offsets of the guard
        int mPosX, mPosY;

    private:  

        //The velocity of the guard
        int mVelX, mVelY;

        //The guard's direction
        int mDirection;
};

        