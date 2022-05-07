#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include <string>
#include "WTexture.h"
#include <iostream>

#pragma once


//The player that will move around on the screen
class Player{
    public:
		//The dimensions of the player (a square)
		static const int PLAYER_WIDTH = 13;
		static const int PLAYER_HEIGHT = 13;

		//Maximum axis velocity of the player
		static const int PLAYER_VEL = 6;

		//Initializes the variables
		Player(int posX, int posY);

		//Takes key presses and adjusts the player's velocity
		void handleEvent( SDL_Event& e );

		//Moves the player
		void movePlayer(int map[70][100]);

		//Shows the player on the screen
		void renderPlayer(SDL_Renderer* renderer, WTexture &playerTexture);

		void transport();

		bool reachedDestination(int x , int y);
		bool isDead();
		//The X and Y offsets of the player
		int mPosX, mPosY;

		int mScore;
		int mMentalHealth;


    private:
		
		//The velocity of the player
		int mVelX, mVelY;

};