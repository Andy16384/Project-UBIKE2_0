#include "Ubike2_0.h"
#include "LTexture.h"

extern LTexture gUbike2_0Texture;
extern LTexture PLAYER;
extern const int SCREEN_WIDTH = 640;

Ubike2_0::Ubike2_0()
{
    mPosX = 0;
    mVelX = -3;
    mPosY = 0;
    mVelY = 0;
}

void Ubike2_0::operator--()
{
    --mVelX;
}

void Ubike2_0::operator= ( int a[3] )
{
    mPosX = a[0];
    mPosY = a[1];
    mVelX = a[2];
}

void Ubike2_0::moveout()
{
    mPosX += mVelX;
    mPosY += mVelY;
}

void Ubike2_0::move()
{
    mPosX += mVelX;
    if( mPosX + 1500 < 0 ) mPosX = SCREEN_WIDTH;
    mPosY += mVelY;
    if(  mPosY < 175 || mPosY > 275 || mVelX < 0 ) mPosY -= mVelY;
}

void Ubike2_0::render() const
{
    gUbike2_0Texture.render( mPosX, mPosY );
}

Player::Player()
{
    mPosX = 50;
    mVelX =  0;
    mPosY = 240;
    mVelY =  0;
}

void Player::handleEvent( SDL_Event& e ){
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_w : mVelY -= Player_VEL; break;
            case SDLK_UP: mVelY -= Player_VEL; break;
            case SDLK_s : mVelY += Player_VEL; break;
            case SDLK_DOWN : mVelY += Player_VEL; break;
            case SDLK_a : mVelX -= 1; break;
            case SDLK_LEFT : mVelX -= 1; break;
            case SDLK_d : mVelX += Player_VEL; break;
            case SDLK_RIGHT : mVelX += Player_VEL; break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        if( 175 < mPosY && mPosY < 225 && mVelY < 0 ) mPosY = 175;
        if( 175 < mPosY && mPosY < 225 && mVelY > 0 ) mPosY = 225;
        if( 225 < mPosY && mPosY < 275 && mVelY < 0 ) mPosY = 225;
        if( 225 < mPosY && mPosY < 275 && mVelY > 0 ) mPosY = 275;
        switch( e.key.keysym.sym )
        {
            case SDLK_w : mVelY += Player_VEL; break;
            case SDLK_UP: mVelY += Player_VEL; break;
            case SDLK_s : mVelY -= Player_VEL; break;
            case SDLK_DOWN : mVelY -= Player_VEL; break;
            case SDLK_a : mVelX += 1; break;
            case SDLK_LEFT : mVelX += 1; break;
            case SDLK_d : mVelX -= Player_VEL; break;
            case SDLK_RIGHT : mVelX -= Player_VEL; break;
        }
    }
}
void Player::move()
{
    mPosX += mVelX;
    if ( mVelX < 0 && mPosX > 20 ) PLAYER.loadFromFile( "images/Players/Player_01.png" );
    if(  mPosX < 20 || mPosX + Player_WIDTH > SCREEN_WIDTH ) mPosX -= mVelX;
    mPosY += mVelY;
    if(  mPosY < 175 || mPosY > 275 || mVelX < 0 ) mPosY -= mVelY;
    if(  mVelX < 0 && mPosX == 20 ) mPosY += mVelY;
    if( (mPosY < 175 || mPosY > 275) && mVelX < 0 ) mPosY -= mVelY;
}

void Player::moveout()
{
    mPosX += mVelX;
    mPosY += mVelY;
}

void Player::render() const
{
    PLAYER.render( mPosX, mPosY );
}
