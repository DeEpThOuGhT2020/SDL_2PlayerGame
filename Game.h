//Using SDL, SDL_image, standard IO, and strings
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include <string>
#include "WTexture.h"
#include "Constants.h"
#pragma once


//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

extern TTF_Font* gFont;

//Scene textures
extern WTexture gPlayer1Texture;
extern WTexture gPlayer2Texture;
extern WTexture gBackgroundTexture;
extern WTexture gRoadTexture;
extern WTexture gProfTexture;
extern WTexture gBuildingTexture;
extern WTexture gGrassTexture;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Map
extern int map[70][100];