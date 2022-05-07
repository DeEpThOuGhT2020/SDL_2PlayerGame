#include "Prof.h"
#include "Constants.h"


Prof::Prof(int posX, int posY){

    mPosX=posX;
    mPosY=posY;
    iPosX = posX;
    iPosY = posY;
    mVelX = 0;
    mVelY = 0;
}

float dist(int x1, int y1, int x2, int y2){
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
void Prof::moveProf(Player p1 ,Player p2, int map[70][100]){    
   
    if (dist(mPosX,mPosY,p1.mPosX,p1.mPosY) < dist(mPosX,mPosY,p2.mPosX,p2.mPosY)){
        if(mPosX < p1.mPosX){
            mVelX = PROF_VEL;
        }
        else if(mPosX > p1.mPosX){
            mVelX = -1*PROF_VEL;
        }
        if(mPosY < p1.mPosY){
            mVelY = PROF_VEL;
        }
        else if(mPosY > p1.mPosY){
            mVelY = -1*PROF_VEL;
        }
    }else{
        if(mPosX < p2.mPosX){
            mVelX = PROF_VEL;
        }
        else if(mPosX > p2.mPosX){
            mVelX = -1*PROF_VEL;
        }
        if(mPosY < p2.mPosY){
            mVelY = PROF_VEL;
        }
        else if(mPosY > p2.mPosY){
            mVelY = -1*PROF_VEL;
        }
    }
    //Move the Prof left or right
     mPosX += mVelX;
    //If the Prof went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + PROF_WIDTH > SCREEN_WIDTH ) ){
        //Move back
        mPosX -= mVelX;
    }

    //Move the Prof up or down
    mPosY += mVelY;
    //If the Prof went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + PROF_HEIGHT > SCREEN_HEIGHT ) ){
        //Move back
        mPosY -= mVelY;
    }
    
    if(mPosX > iPosX + 300 || mPosX < iPosX - 300){
        mPosX -= mVelX;
    }
    if(mPosY > iPosY + 300 || mPosY < iPosY - 300){
        mPosY -= mVelY;
    }
   
}    

void Prof::renderProf(SDL_Renderer* renderer, WTexture &ProfTexture){
    ProfTexture.render(renderer, mPosX, mPosY);
}

bool Prof::collided(Player p){
    if(mPosX == p.mPosX && mPosY == p.mPosY){
        p.transport();
        return true;
    }else{
        return false;
    }
}