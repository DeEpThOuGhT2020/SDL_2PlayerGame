#include "Player.h"
#include "Constants.h"


Player::Player(int posX, int posY){
    //Initialize the offsets
    mPosX = posX;
    mPosY = posY;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    //Initialize the score and mental health

    mScore = 0;
    mMentalHealth = 1800;
}

void Player::handleEvent( SDL_Event& e ){
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
        //Adjust the velocity
        switch( e.key.keysym.sym ){
            case SDLK_UP: mVelY -= PLAYER_VEL; break;
            case SDLK_DOWN: mVelY += PLAYER_VEL; break;
            case SDLK_LEFT: mVelX -= PLAYER_VEL; break;
            case SDLK_RIGHT: mVelX += PLAYER_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ){
        //Adjust the velocity
        switch( e.key.keysym.sym ){
            case SDLK_UP: mVelY += PLAYER_VEL; break;
            case SDLK_DOWN: mVelY -= PLAYER_VEL; break;
            case SDLK_LEFT: mVelX += PLAYER_VEL; break;
            case SDLK_RIGHT: mVelX -= PLAYER_VEL; break;
        }
    }
}

void Player::movePlayer(int map[70][100]){
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

    if (map[mPosY/TILE_SIZE][mPosX/TILE_SIZE] != 1){
		mPosX -= mVelX;
		mPosY -= mVelY;

	}

	if (map[(mPosY+PLAYER_HEIGHT)/TILE_SIZE][(mPosX+PLAYER_WIDTH)/TILE_SIZE] != 1){
		mPosX -= mVelX;
		mPosY -= mVelY;

	}

    if (map[(mPosY+PLAYER_HEIGHT)/TILE_SIZE][mPosX/TILE_SIZE]!= 1){
		mPosX -= mVelX;
		mPosY -= mVelY;

	}
    
    if (map[mPosY/TILE_SIZE][(mPosX+PLAYER_WIDTH)/TILE_SIZE] != 1){
		mPosX -= mVelX;
		mPosY -= mVelY;

	}
}

void Player::renderPlayer(SDL_Renderer* renderer, WTexture &playerTexture){
    //Show the player
	playerTexture.render( renderer, mPosX, mPosY, PLAYER_WIDTH, PLAYER_HEIGHT );
}

void Player::transport(){
        mPosX = 796;
        mPosY = 496;
        mVelX = 0;
        mVelY = 0;
    
}

bool Player::isDead(){
    if (mMentalHealth <= 0){
        return true;
    }
    return false;
}

bool Player::reachedDestination(int x , int y){
    if ( mPosX >= x && x <=  (mPosX + PLAYER_WIDTH) &&  mPosY >= y && y <= (mPosY + PLAYER_HEIGHT)){
        return true;
    }
    else
        return false;
}