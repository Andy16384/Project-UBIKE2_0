#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <string>
#include <sstream>
#include "LTexture.h"
#include "LTimer.h"
#include "LTexture.h"
#include "Ubike2_0.h"
#include "Player.h"
#include "music.h"
#include "gamebutton.h"
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;
const int TOTAL_BUTTONS = 4;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
int frameTicks1 = 0;
int frameTicks2 = 0;
enum Game_Mode
{
    MAINSCREEN = 0,
    PLAYING = 1,
    TEACHING = 2,
    PAUSED = 3,
    END = 4
};
int playmode=0;
enum Botton_Type
{
    STARTED = 0,
    TEACH = 1,
    PAUSE = 2,
    BEGIN = 3
};
bool init();
bool loadMedia();
void close();

TTF_Font* font = NULL;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

LTexture TIME;
LTexture Pause;
LTexture START;
LTexture PLAYER;
LTexture _123GO_;
LTexture gUbike2_0Texture;
LTexture BG;
LTexture boom;
LTexture wasd;
LTexture mode_picture[3] ;
GameButton gButtons[TOTAL_BUTTONS];

bool init(){
	bool success = true;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow( "Do you like Youbike 2.0, only because it looks like bicycles?", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ){
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia()
{
        gButtons[STARTED].SetMediaPath("images/others/buttonstart.png");
        gButtons[STARTED].SetMediaPathClick("images/others/buttonstart.click.png");
        gButtons[TEACH].SetMediaPath("images/others/buttonteaching.png");
        gButtons[TEACH].SetMediaPathClick("images/others/buttonteaching.click.png");
        gButtons[PAUSE].SetMediaPath("images/others/buttonpause.png");
        gButtons[PAUSE].SetMediaPathClick("images/others/buttonpause.click.png");
        gButtons[BEGIN].SetMediaPath("images/others/buttonbegin.png");
        gButtons[BEGIN].SetMediaPathClick("images/others/buttonbegin.click.png");
        gButtons[STARTED].SetMode(PLAYING);
        gButtons[TEACH].SetMode(TEACHING);
        gButtons[PAUSE].SetMode(PAUSED);
        gButtons[BEGIN].SetMode(PLAYING);
        gButtons[STARTED].setPosition( 540, 360 );
        gButtons[TEACH].setPosition( 270, 350 );
        gButtons[PAUSE].setPosition( 0, 0 );
        gButtons[BEGIN].setPosition( 0, 0 );
        return true;
}

void close(){
	TIME.free();
	START.free();
	Pause.free();

	TTF_CloseFont( font );
	font = NULL;

	PLAYER.free();
	BG.free();

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] ){
//========================================================================================================================
	if( init() ){
        if(loadMedia()){
        bool quit = false, death = false;
        int t = -1, s1 = 0, s2 = 0;
        SDL_Event e;
        SDL_Color KURO = { 0, 0, 0, 255 }, SHIRO = { 255, 255, 255, 0 } ;
        LTimer timer;                           Player Player;

        Ubike2_0 Ubike2_0[6];
        MusicSound op = MusicSound("mp3/op.mp3");
        EffectSound dead = EffectSound("mp3/dead.mp3");

        int dx = 0;
        std::stringstream timeText;
//===================================================================================
        Ubike2_0[0].mPosX = 400; Ubike2_0[0].mPosY = 100; Ubike2_0[1].mPosX = 600; Ubike2_0[1].mPosY = 100;
        Ubike2_0[2].mPosX = 600; Ubike2_0[2].mPosY = 250; Ubike2_0[3].mPosX =   0; Ubike2_0[3].mPosY =  30;
        Ubike2_0[4].mPosX = 300; Ubike2_0[4].mPosY = 150; Ubike2_0[5].mPosX = 800; Ubike2_0[5].mPosY = 200;
        op.play();
        while( !quit && timer.getTicks() == 0 && playmode == MAINSCREEN)
        {
            BG.loadFromFile( "images/backgrounds/main.png" );
            if((SDL_GetTicks()/ 300)%2 == 0 )gUbike2_0Texture.loadFromFile( "images/others/ubike2_0_01.png" );
            if((SDL_GetTicks()/ 300)%2 == 1 )gUbike2_0Texture.loadFromFile( "images/others/ubike2_0_02.png" );

            font = TTF_OpenFont( "fonts/GenJyuuGothic-Monospace-Bold.ttf", 30 );
            START.loadFromRenderedText( "Press Enter to Start", KURO );
            for( int i = 0 ; i < 6 ; i++ ) Ubike2_0[i].move();

            timeText.str( "" ); timeText << timer.getTicks()/1000.f ;
            TIME.loadFromRenderedText( timeText.str().c_str(), KURO );

            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );
            for( int i = 0 ; i < 6 &&  SDL_GetTicks() < 7000 ; i++) Ubike2_0[i].render();
            dx -= 2;
            if( dx > -220 ){
                BG.render( dx, -30 );
                BG.render( dx + BG.getWidth(), -30 );
            }
            else BG.render( -220 , -30 );
            if( (SDL_GetTicks() / 500 ) % 2 != 0 ) START.render((SCREEN_WIDTH-START.getWidth())/2,300);

            while( SDL_PollEvent( &e ) != 0 )
            {
                if( e.type == SDL_QUIT ) quit = true;
                else if( e.key.keysym.sym == SDLK_RETURN ) timer.start();
                gButtons[TEACH].handleEvent( &e );

            }
                gButtons[TEACH].loadFromFile();
                gButtons[TEACH].render();
                SDL_RenderPresent( gRenderer );

        }
        while( !quit && timer.getTicks() == 0 && playmode == TEACHING )
        {
            BG.loadFromFile("images/backgrounds/teaching.png");
            BG.render(0,0);
            while( SDL_PollEvent( &e ) != 0 )
            {
                if( e.type == SDL_QUIT ) quit = true;

                gButtons[STARTED].handleEvent( &e );
                if( playmode == PLAYING )
                {
                    timer.start();
                }
            }
            gButtons[STARTED].loadFromFile();
            gButtons[STARTED].render();
            SDL_RenderPresent( gRenderer );
        }
//===============================================================================================================================
        while( !quit ){
            if( timer.getTicks() != 0 )
            {
                Mix_ResumeMusic();
                dx = 0;
                PLAYER.loadFromFile( "images/Players/Player_01.png" );
                BG.loadFromFile( "images/backgrounds/play.png" );
                timer.start(); Player.mPosX = 50; Player.mVelX =  0; Player.mPosY = 225; Player.mVelY =  0;
                Ubike2_0[0].mPosX = -1000; Ubike2_0[0].mPosY = 185; Ubike2_0[1].mPosX = 1200; Ubike2_0[1].mPosY = 190;
                Ubike2_0[2].mPosX =  1000; Ubike2_0[2].mPosY = 235; Ubike2_0[3].mPosX = -100; Ubike2_0[3].mPosY = 240;
                Ubike2_0[4].mPosX = -1700; Ubike2_0[4].mPosY = 285; Ubike2_0[5].mPosX = 1400; Ubike2_0[5].mPosY = 290;
            }
            while(  timer.getTicks() > 0  && !death )
            {
                int frameTicks = frameTicks2-frameTicks1;
                if( frameTicks < SCREEN_TICK_PER_FRAME )
                {
					SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
                }
                frameTicks1 = timer.getTicks();

                if( timer.getTicks() >= 3000){
                    timeText.str( "" );
                    timeText <<  timer.getTicks() / 1000.f - 3 ;
                    if( ( timer.getTicks()/ 300) % 2 == 0 )PLAYER.loadFromFile( "images/Players/Player_01.png" );
                    if( ( timer.getTicks()/ 300) % 2 == 1 )PLAYER.loadFromFile( "images/Players/Player_02.png" );

                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        if( e.type == SDL_QUIT ) quit = true;
                        if( playmode != PAUSED )
                        {
                            gButtons[PAUSE].handleEvent(&e);
                        }
                        else
                        {
                            gButtons[BEGIN].handleEvent(&e);
                        }
                        if( playmode != PAUSED ) {timer.unpause();Mix_ResumeMusic();}
                        else {timer.pause();Mix_PauseMusic();}

                    Player.handleEvent( e );
                    }
                    s1 = Player.mPosX; s2 = Player.mPosY;
                    if( Player.mPosX < Ubike2_0[0].mPosX && Player.mPosX + Player.Player_WIDTH > Ubike2_0[0].mPosX && Player.mPosY < 200 ) {death = true; t = 1;}
                    if( Player.mPosX < Ubike2_0[1].mPosX && Player.mPosX + Player.Player_WIDTH > Ubike2_0[1].mPosX && Player.mPosY < 200 ) {death = true; t = 2;}
                    if( Player.mPosX < Ubike2_0[2].mPosX && Player.mPosX + Player.Player_WIDTH > Ubike2_0[2].mPosX && Player.mPosY >= 200 && Player.mPosY <= 250 ) {death = true; t = 3;}
                    if( Player.mPosX < Ubike2_0[3].mPosX && Player.mPosX + Player.Player_WIDTH > Ubike2_0[3].mPosX && Player.mPosY >= 200 && Player.mPosY <= 250 ) {death = true; t = 4;}
                    if( Player.mPosX < Ubike2_0[4].mPosX && Player.mPosX + Player.Player_WIDTH > Ubike2_0[4].mPosX && Player.mPosY > 250 ) {death = true; t = 5;}
                    if( Player.mPosX < Ubike2_0[5].mPosX && Player.mPosX + Player.Player_WIDTH > Ubike2_0[5].mPosX && Player.mPosY > 250 ) {death = true; t = 6;}

                    if( Player.mPosX < Ubike2_0[0].mPosX + Ubike2_0[0].Ubike2_0_WIDTH && Player.mPosX > Ubike2_0[0].mPosX && Player.mPosY < 200 ) {death = true; t =  7;}
                    if( Player.mPosX < Ubike2_0[1].mPosX + Ubike2_0[1].Ubike2_0_WIDTH && Player.mPosX > Ubike2_0[1].mPosX && Player.mPosY < 200 ) {death = true; t =  8;}
                    if( Player.mPosX < Ubike2_0[2].mPosX + Ubike2_0[2].Ubike2_0_WIDTH && Player.mPosX > Ubike2_0[2].mPosX && Player.mPosY >= 200 && Player.mPosY <= 250 ) {death = true; t =  9;}
                    if( Player.mPosX < Ubike2_0[3].mPosX + Ubike2_0[3].Ubike2_0_WIDTH && Player.mPosX > Ubike2_0[3].mPosX && Player.mPosY >= 200 && Player.mPosY <= 250 ) {death = true; t = 10;}
                    if( Player.mPosX < Ubike2_0[4].mPosX + Ubike2_0[4].Ubike2_0_WIDTH && Player.mPosX > Ubike2_0[4].mPosX && Player.mPosY > 250 ) {death = true; t = 11;}
                    if( Player.mPosX < Ubike2_0[5].mPosX + Ubike2_0[5].Ubike2_0_WIDTH && Player.mPosX > Ubike2_0[5].mPosX && Player.mPosY > 250 ) {death = true; t = 12;}

                    if( dx < -BG.getWidth() ) dx = 0;

                    if( !timer.isPaused() ){
                        Player.move();
                        for( int i = 0 ; i < 6 ; i++ ) Ubike2_0[i].move();
                        --dx;
                    }
                }
                TIME.loadFromRenderedText( timeText.str().c_str(), KURO ) ;

                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                gButtons[PAUSE].loadFromFile();
                gButtons[BEGIN].loadFromFile();
                BG.render( dx, 0 );

                BG.render( dx + BG.getWidth(), 0 );
                wasd.loadFromFile( "images/others/wasd.png" );
                if( timer.getTicks() < 1000 ){
                    timeText.str( " " );
                    _123GO_.loadFromFile( "images/others/3.png" );
                    _123GO_.render( ( SCREEN_WIDTH - _123GO_.getWidth() ) / 2, ( SCREEN_HEIGHT - _123GO_.getHeight() ) / 2);
                    wasd.render(50,110);
                }
                if( timer.getTicks() > 1000 && timer.getTicks() < 2000 ){
                    timeText.str( " " );
                    _123GO_.loadFromFile( "images/others/2.png" );
                    _123GO_.render( ( SCREEN_WIDTH - _123GO_.getWidth() ) / 2, ( SCREEN_HEIGHT - _123GO_.getHeight() ) / 2);
                    wasd.render(50,110);
                }
                if( timer.getTicks() > 2000 && timer.getTicks() < 3000 ){
                    timeText.str( " " );
                    _123GO_.loadFromFile( "images/others/1.png" );
                    _123GO_.render( ( SCREEN_WIDTH - _123GO_.getWidth() ) / 2, ( SCREEN_HEIGHT - _123GO_.getHeight() ) / 2);
                    wasd.render(50,110);
                }
                if( timer.getTicks() > 3000 && timer.getTicks() < 4000 ){
                    timeText.str( " " );
                    _123GO_.loadFromFile( "images/others/go.png" );
                    _123GO_.render( ( SCREEN_WIDTH - _123GO_.getWidth() ) / 2, ( SCREEN_HEIGHT - _123GO_.getHeight() ) / 2);
                }

                if(timer.getTicks() > 3000)
                {
                    TIME.render( 285 , 0 );

                    if(playmode!=PAUSED)
                    {
                        gButtons[PAUSE].render();
                    }
                    else
                    {
                        gButtons[BEGIN].render();
                    }

                }
                switch((SDL_GetTicks() - timer.getTicks())%3){
                case 0:
                Ubike2_0[0].mVelX = -5 - timer.getTicks()/21000;
                Ubike2_0[1].mVelX = -1 - timer.getTicks()/9900;
                Ubike2_0[2].mVelX = -6 - timer.getTicks()/6000;
                Ubike2_0[3].mVelX = -4 - timer.getTicks()/10000;
                Ubike2_0[4].mVelX = -3 - timer.getTicks()/6200;
                Ubike2_0[5].mVelX = -7 - timer.getTicks()/4100;break;
                case 1:
                Ubike2_0[0].mVelX = -3 - timer.getTicks()/6200;
                Ubike2_0[1].mVelX = -4 - timer.getTicks()/20000;
                Ubike2_0[2].mVelX = -5 - timer.getTicks()/11000;
                Ubike2_0[3].mVelX = -1 - timer.getTicks()/9900;
                Ubike2_0[4].mVelX = -6 - timer.getTicks()/6000;
                Ubike2_0[5].mVelX = -7 - timer.getTicks()/4100;break;
                case 2:
                Ubike2_0[0].mVelX = -5 - timer.getTicks()/11000;
                Ubike2_0[1].mVelX = -4 - timer.getTicks()/20000;
                Ubike2_0[2].mVelX = -5 - timer.getTicks()/11000;
                Ubike2_0[3].mVelX = -1 - timer.getTicks()/16000;
                Ubike2_0[4].mVelX = -3 - timer.getTicks()/6200;
                Ubike2_0[5].mVelX = -7 - timer.getTicks()/4100;break;
                }
                //Render objects
                if((timer.getTicks()/ 300)%2 == 0 )gUbike2_0Texture.loadFromFile( "images/others/ubike2_0_01.png" );
                if((timer.getTicks()/ 300)%2 == 1 )gUbike2_0Texture.loadFromFile( "images/others/ubike2_0_02.png" );
                Ubike2_0[0].render();
                if((timer.getTicks()/ 300)%2 == 0 )gUbike2_0Texture.loadFromFile( "images/others/ubike2_0_03.png" );
                if((timer.getTicks()/ 300)%2 == 1 )gUbike2_0Texture.loadFromFile( "images/others/ubike2_0_04.png" );
                Ubike2_0[1].render();
                Ubike2_0[2].render();
                if((timer.getTicks()/ 300)%2 == 0 )gUbike2_0Texture.loadFromFile( "images/others/ubike2_0_01.png" );
                if((timer.getTicks()/ 300)%2 == 1 )gUbike2_0Texture.loadFromFile( "images/others/ubike2_0_02.png" );
                Ubike2_0[3].render();
                Player.render();
                Ubike2_0[4].render();
                if((timer.getTicks()/ 300)%2 == 0 && (timer.getTicks() < 31000) )gUbike2_0Texture.loadFromFile( "images/others/ubike2_0_03.png" );
                if((timer.getTicks()/ 300)%2 == 1 && (timer.getTicks() < 31000) )gUbike2_0Texture.loadFromFile( "images/others/ubike2_0_04.png" );
                if( timer.getTicks() >= 31000 )gUbike2_0Texture.loadFromFile( "images/others/baiku.png" );
                Ubike2_0[5].render();
                frameTicks2 = timer.getTicks();
                SDL_RenderPresent( gRenderer );
            }
    //==========================================================================================================================
            //op.play();
            if(death) dead.play();
            while( !quit && timer.getTicks() > 0 && death )
            {
                Mix_PauseMusic();

                BG.loadFromFile( "images/backgrounds/death.png" );
                gUbike2_0Texture.loadFromFile( "images/others/ubike2_0_death.png" );
                PLAYER.loadFromFile( "images/Players/Player_death.png" );
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT ) quit = true;
                    else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE ) {quit = true;}
                    else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN ) {death = false;}
                }

                timer.pause();
                timeText.str( "" );
                timeText <<  timer.getTicks() / 1000.f - 3 ;
                if( !TIME.loadFromRenderedText( timeText.str().c_str(), SHIRO ) )
                {
                    printf( "Unable to render time texture!\n" );
                }

                SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xff );
                SDL_RenderClear( gRenderer );

                BG.render( dx, 0 );
                BG.render( dx + BG.getWidth(), 0 );

                TIME.render( 285 , 0 );

                Pause.loadFromRenderedText( "Press Enter to Restart", SHIRO );

                Pause.render( ( SCREEN_WIDTH - Pause.getWidth() ) / 2, 130 );

                switch(t){
                case  1: Player.mVelX = -15; Player.mVelY = -20;Ubike2_0[0].mVelX = 20;Ubike2_0[0].mVelY = -20;Ubike2_0[0].moveout();break;
                case  2: Player.mVelX = -15; Player.mVelY = -20;Ubike2_0[1].mVelX = 20;Ubike2_0[1].mVelY = -20;Ubike2_0[1].moveout();break;
                case  3: Player.mVelX = -15; Player.mVelY = -20;Ubike2_0[2].mVelX = 20;Ubike2_0[2].mVelY = -20;Ubike2_0[2].moveout();break;
                case  4: Player.mVelX = -15; Player.mVelY = -20;Ubike2_0[3].mVelX = 20;Ubike2_0[3].mVelY = -20;Ubike2_0[3].moveout();break;
                case  5: Player.mVelX = -15; Player.mVelY = -20;Ubike2_0[4].mVelX = 20;Ubike2_0[4].mVelY = -20;Ubike2_0[4].moveout();break;
                case  6: Player.mVelX = -15; Player.mVelY = -20;Ubike2_0[5].mVelX = 20;Ubike2_0[5].mVelY = -20;Ubike2_0[5].moveout();break;

                case  7: Player.mVelX = 10; Player.mVelY = -20;Ubike2_0[0].mVelX = -20;Ubike2_0[0].mVelY = 20;Ubike2_0[0].moveout();break;
                case  8: Player.mVelX = 10; Player.mVelY = -20;Ubike2_0[1].mVelX = -20;Ubike2_0[1].mVelY = 20;Ubike2_0[1].moveout();break;
                case  9: Player.mVelX = 10; Player.mVelY = -20;Ubike2_0[2].mVelX = -20;Ubike2_0[2].mVelY = 20;Ubike2_0[2].moveout();break;
                case 10: Player.mVelX = 10; Player.mVelY = -20;Ubike2_0[3].mVelX = -20;Ubike2_0[3].mVelY = 20;Ubike2_0[3].moveout();break;
                case 11: Player.mVelX = 10; Player.mVelY = -20;Ubike2_0[4].mVelX = -20;Ubike2_0[4].mVelY = 20;Ubike2_0[4].moveout();break;
                case 12: Player.mVelX = 10; Player.mVelY = -20;
                if(timer.getTicks() < 31000){Ubike2_0[5].mVelX = -20;Ubike2_0[5].mVelY = 20;Ubike2_0[5].moveout();}break;
                }
                boom.loadFromFile( "images/others/boom.png" );
                boom.render(s1,s2);

                Player.moveout();

                gUbike2_0Texture.loadFromFile( "images/others/ubike2_0_death.png" );
                Ubike2_0[0].render();
                gUbike2_0Texture.loadFromFile( "images/others/ubike2_0_03_death.png" );
                Ubike2_0[1].render();
                Ubike2_0[2].render();
                gUbike2_0Texture.loadFromFile( "images/others/ubike2_0_death.png" );
                Ubike2_0[3].render();
                Player.render();
                Ubike2_0[4].render();
                if( timer.getTicks() <  31000 )gUbike2_0Texture.loadFromFile( "images/others/ubike2_0_03_death.png" );
                if( timer.getTicks() >= 31000 )gUbike2_0Texture.loadFromFile( "images/others/baiku.png" );
                Ubike2_0[5].render();

                SDL_SetRenderDrawColor( gRenderer, 0xff, 0xff, 0xff, 0xff );
                SDL_RenderPresent( gRenderer );
            }
        }
//===============================================================================================================================
	}
}
	close();
    return 0;
}
