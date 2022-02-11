#include "LTexture.h"
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cstdio>
#include <iostream>
using namespace std;
extern SDL_Renderer* gRenderer;
extern TTF_Font* font;

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

void LTexture::free()
{
	if( mTexture != NULL ){
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

ostream& operator<<(ostream& myout, SDL_Surface* a)
{
    myout << "Unable to load image! SDL_image Error: \n";
    return myout;
}

ostream& operator<<(ostream& myout, SDL_Texture* a)
{
    myout << "Unable to create texture! SDL Error: \n";
    return myout;
}

bool LTexture::loadFromFile( string path ){
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ) cout << loadedSurface << path.c_str() << IMG_GetError();
		else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL ) cout << newTexture <<  path.c_str() << SDL_GetError();
		else{ mWidth = loadedSurface->w; mHeight = loadedSurface->h;	}
		SDL_FreeSurface( loadedSurface );
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText( string textureText, SDL_Color textColor )
{
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL ) cout << mTexture;
		else{ mWidth = textSurface->w; mHeight = textSurface->h; }

		SDL_FreeSurface( textSurface );
	}
	else{ printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );}

	return mTexture != NULL;
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if( clip != NULL )	{ renderQuad.w = clip->w;	renderQuad.h = clip->h;	}
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight(){
    return mHeight;
}
