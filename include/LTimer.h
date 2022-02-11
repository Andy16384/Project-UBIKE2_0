#ifndef LTIMER_H
#define LTIMER_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <cstdio>
#include <string>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include "LTexture.h"
#include "LTimer.h"

class LTimer
{
    public:
		LTimer();
		void start();
        void stop();
        void pause();
        void unpause();

		Uint32 getTicks();
		bool isStarted() const;
        bool isPaused() const;
    private:
		Uint32 mStartTicks;
        Uint32 mPausedTicks;
		bool mPaused;
        bool mStarted;
};

#endif // LTIMER_H
