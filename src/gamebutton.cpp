#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "gamebutton.h"
#include "LTimer.h"
enum Game_Mode
{
    MAINSCREEN = 0,
    PLAYING = 1,
    TEACHING =2,
    END=3
};
extern int playmode;
extern int mode;
GameButton::GameButton()
{
    mPosition.x = 0;
    mPosition.y = 0;
}
void GameButton::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}
void GameButton::loadFromFile()
{
    button.loadFromFile(path0.c_str());
}
void GameButton::handleEvent( SDL_Event* e )
{
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		int x, y;
		SDL_GetMouseState( &x, &y );

		bool inside = true;

		if( x < mPosition.x )
		{
			inside = false;
		}

		else if( x > mPosition.x + button.getWidth() )
		{
			inside = false;
		}

		else if( y < mPosition.y )
		{
			inside = false;
		}

		else if( y > mPosition.y + button.getHeight() )
		{
			inside = false;
		}


		if( !inside )
		{
            path0=path1;

        }

		else
		{

			switch( e->type )
			{
				case SDL_MOUSEMOTION:
                {
				   path0=path2;
				   break;
                }



				case SDL_MOUSEBUTTONDOWN:
                {
                   path0=path2;
                   break;
                }



				case SDL_MOUSEBUTTONUP:
                {
                    playmode=mode;
                    break;
                }
            }
        }
    }
}

void GameButton::render()
{
    button.render( mPosition.x, mPosition.y,NULL,0,NULL,SDL_FLIP_NONE);
}
void GameButton::SetMediaPath(std::string path)
{
    path1=path;
    path0=path1;
}
void GameButton::SetMediaPathClick(std::string path)
{
    path2=path;
}

void GameButton::SetMode(int m)
{
    mode = m;
}
