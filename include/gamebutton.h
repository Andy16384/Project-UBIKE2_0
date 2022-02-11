#ifndef GAMEBUTTON_H_INCLUDED
#define GAMEBUTTON_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "LTexture.h"

class GameButton
{
    public:
        GameButton();
        void setPosition(int x,int y);
        void loadFromFile();
        void handleEvent( SDL_Event* e );
        void render();
        void SetMediaPath(std::string path);
        void SetMediaPathClick(std::string path);
        void SetMode(int m);

    private:
		SDL_Point mPosition;
        LTexture button;
        std::string path0;
        std::string path1;
        std::string path2;
        int mode;
};
#endif // GAMEBUTTON_H_INCLUDED
