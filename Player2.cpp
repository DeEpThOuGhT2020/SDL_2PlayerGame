#include "Player2.h"
#include "Constants.h"


Player2::Player2(){
    //Initialize the offsets
    mPosX = 50;
    mPosY = 350;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Player2::handleEvent( SDL_Event& e ){
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
        //Adjust the velocity
        switch( e.key.keysym.sym ){
            case SDLK_w: mVelY -= PLAYER_VEL; break;
            case SDLK_s: mVelY += PLAYER_VEL; break;
            case SDLK_a: mVelX -= PLAYER_VEL; break;
            case SDLK_d: mVelX += PLAYER_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ){
        //Adjust the velocity
        switch( e.key.keysym.sym ){
            case SDLK_w: mVelY += PLAYER_VEL; break;
            case SDLK_s: mVelY -= PLAYER_VEL; break;
            case SDLK_a: mVelX += PLAYER_VEL; break;
            case SDLK_d: mVelX -= PLAYER_VEL; break;
        }
    }
}

void Player2::movePlayer(int map[60][100]){
    //Move the player left or right
    mPosX += mVelX;
    //If the player went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + PLAYER_WIDTH > SCREEN_WIDTH ) ){
        //Move back
        mPosX -= mVelX;
    }

    //Move the player up or down
    mPosY += mVelY;
    //If the player went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + PLAYER_HEIGHT > SCREEN_HEIGHT ) ){
        //Move back
        mPosY -= mVelY;
    }

    if (map[mPosY/TILE_SIZE][mPosX/TILE_SIZE] == 0){
		mPosX -= mVelX;
		mPosY -= mVelY;

	}

	if (map[(mPosY+PLAYER_HEIGHT)/TILE_SIZE][(mPosX+PLAYER_WIDTH)/TILE_SIZE] == 0){
		mPosX -= mVelX;
		mPosY -= mVelY;

	}

    if (map[(mPosY+PLAYER_HEIGHT)/TILE_SIZE][mPosX/TILE_SIZE] == 0){
		mPosX -= mVelX;
		mPosY -= mVelY;

	}
    
    if (map[mPosY/TILE_SIZE][(mPosX+PLAYER_WIDTH)/TILE_SIZE] == 0){
		mPosX -= mVelX;
		mPosY -= mVelY;

	}
}

void Player2::renderPlayer(SDL_Renderer* renderer, WTexture &playerTexture){
    //Show the player
	playerTexture.render( renderer, mPosX, mPosY );
}