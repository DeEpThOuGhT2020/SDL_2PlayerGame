//Using SDL, SDL_image, standard IO, and strings
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "stdio.h"
#include "string"
#pragma once

// SDL_Texture wrapper class
class WTexture{
	public:
		//Initializes variables
		WTexture();
        
		//Deallocates memory
		~WTexture();

		//Loads image at specified path
		bool loadFromFile( SDL_Renderer* renderer, std::string path );
		
		/*#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from font string
		bool loadFromRenderedText( SDL_Renderer* renderer, std::string textureText, SDL_Color textColor );
		#endif*/

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( SDL_Renderer* renderer, int x, int y, int l, int b);
		static void renderText( SDL_Renderer* renderer, TTF_Font* font, char *text, int x, int y, int l, int b );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};