#include "Guard.h"
#include "Constants.h"


Guard::Guard(int posX, int posY){
    mPosX=posX;
    mPosY=posY;
    
    mVelX = 0;
    mVelY = 0;
}

void Guard::moveGuard(Player p1 ,Player p2, int map[60][100]){    
    if(mPosX < p1.mPosX && mPosX < p2.mPosX){
        mVelX = GUARD_VEL;
    }
    else if(mPosX > p1.mPosX && mPosX < p2.mPosX && mPosX - p1.mPosX > p2.mPosX -mPosX ){
        mVelX = GUARD_VEL;
    }
    else if(mPosX > p1.mPosX && mPosX < p2.mPosX && mPosX - p1.mPosX < p2.mPosX -mPosX ){
        mVelX = -1*GUARD_VEL;
    }
    else if(mPosX < p1.mPosX && mPosX > p2.mPosX && p1.mPosX - mPosX < mPosX - p2.mPosX ){
        mVelX = GUARD_VEL;
    }
    else if(mPosX < p1.mPosX && mPosX > p2.mPosX && p1.mPosX - mPosX > mPosX - p2.mPosX ){
        mVelX = -1* GUARD_VEL;
    }
    else if(mPosX > p1.mPosX && mPosX > p2.mPosX){
        mVelX = -1*GUARD_VEL;
    }

    if(mPosY < p1.mPosY && mPosY < p2.mPosY){
        mVelY = GUARD_VEL;
    }
    else if(mPosY > p1.mPosY && mPosY < p2.mPosY && mPosY - p1.mPosY > p2.mPosY -mPosY ){
        mVelY = GUARD_VEL;
    }
    else if(mPosY > p1.mPosY && mPosY < p2.mPosY && mPosY - p1.mPosY < p2.mPosY -mPosY ){
        mVelY = -1 * GUARD_VEL;
    }
    else if(mPosY < p1.mPosY && mPosY > p2.mPosY && p1.mPosY - mPosY < mPosY - p2.mPosY ){
        mVelY = GUARD_VEL;
    }
    else if(mPosY < p1.mPosY && mPosY > p2.mPosY && p1.mPosY - mPosY > mPosY - p2.mPosY ){
        mVelY = -1 * GUARD_VEL;
    }
    else if(mPosY > p1.mPosY && mPosY > p2.mPosY){
        mVelY = -1 * GUARD_VEL;
    }

  
    //Move the guard left or right
     mPosX += mVelX;
    //If the guard went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + GUARD_WIDTH > SCREEN_WIDTH ) ){
        //Move back
        mPosX -= mVelX;
    }

    //Move the guard up or down
    mPosY += mVelY;
    //If the guard went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + GUARD_HEIGHT > SCREEN_HEIGHT ) ){
        //Move back
        mPosY -= mVelY;
    }

    if (map[mPosY/TILE_SIZE][mPosX/TILE_SIZE] == 0){
        mPosX -= mVelX;
        mPosY -= mVelY;
    }
    if (map[(mPosY+GUARD_HEIGHT)/TILE_SIZE][(mPosX+GUARD_WIDTH)/TILE_SIZE] == 0){
        mPosX -= mVelX;
        mPosY -= mVelY;
    }
    if (map[(mPosY+GUARD_HEIGHT)/TILE_SIZE][mPosX/TILE_SIZE] == 0){
        mPosX -= mVelX;
        mPosY -= mVelY;
    }
    if (map[mPosY/TILE_SIZE][(mPosX+GUARD_WIDTH)/TILE_SIZE] == 0){
        mPosX -= mVelX;
        mPosY -= mVelY;
    }
}    

void Guard::renderGuard(SDL_Renderer* renderer, WTexture &guardTexture){
    guardTexture.render(renderer, mPosX, mPosY);
}