#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include <string>
#include "WTexture.h"
#include <iostream>

class Popup{
    public:
        int mPosX;
        int mPosY;
        int mWidth;
        int mHeight;
        void pop(SDL_Renderer* renderer, WTexture &popupTexture);

};