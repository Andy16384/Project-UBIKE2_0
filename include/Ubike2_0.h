#ifndef UBIKE2_0_H
#define UBIKE2_0_H
#include "SDL2/SDL.h"
#include <string>
using namespace std;

class bike
{
    virtual void move();
    void render() const;
    void moveout();
};
class Ubike2_0: public bike
{
    public:
		static const int Ubike2_0_WIDTH = 60, Ubike2_0_HEIGHT = 45, Ubike2_0_VEL = 5;
		Ubike2_0();
		void move();
		void render() const;
		void moveout();
		int mPosX, mPosY, mVelX, mVelY;
		void operator= ( int a[] );
		void operator--();
};
class Player: public bike
{
    friend Ubike2_0;
    public:
		static const int Player_WIDTH = 83, Player_HEIGHT = 45, Player_VEL = 3;
		Player();
		void handleEvent( SDL_Event& e );
		void move();
		void moveout();
		void render()const;
		int mPosX, mPosY, mVelX, mVelY;
};
#endif // UBIKE2_0_H
