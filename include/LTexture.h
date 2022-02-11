#ifndef LTEXTURE_H
#define LTEXTURE_H
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <cstdio>
#include <ostream>
using namespace std;

class LTexture
{
	public:
		LTexture();
        ~LTexture();
		bool loadFromFile( string path );
		bool loadFromRenderedText( string textureText, SDL_Color textColor );

		void free();
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
        int getWidth();
        int getHeight();
        friend ostream& operator << ( ostream& myout, SDL_Surface* );
        friend ostream& operator << ( ostream& myout, SDL_Texture* );
	private:
		SDL_Texture* mTexture;
		int mWidth;	int mHeight;
};

#endif // LTEXTURE_H
