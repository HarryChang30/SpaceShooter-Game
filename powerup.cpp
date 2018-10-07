#include "powerup.h"
#include <SDL.h>
#include <SDL_image.h>

const int PowerUp::ROCKET = 0;
const int PowerUp::REPAIR = 1;
const int PowerUp::SHIELD = 2;
const int PowerUp::MONEY = 3;

PowerUp::PowerUp(int x , int y , int type , Game* game ,
	SpriteManager* sm):GameObject(x,y,24,24)
{
	mDirection = -1;
	mType = type;

	sm->loadTexture("assets/sprite/rocket.png");
	sm->loadTexture("assets/sprite/repair.png");
	sm->loadTexture("assets/sprite/shield.png");
	sm->loadTexture("assets/sprite/money.png");

	switch(type)
	{
	case ROCKET :
		objectTexture = sm->getTexture("assets/sprite/rocket.png");
		break;
	case REPAIR : 
		objectTexture = sm->getTexture("assets/sprite/repair.png");
		break;
	case SHIELD : 
		objectTexture = sm->getTexture("assets/sprite/shield.png");
		break;
	case MONEY : 
		objectTexture = sm->getTexture("assets/sprite/money.png");
		break;
	}


	mX -= mWidth / 2;
}

PowerUp::~PowerUp()
{
	SDL_DestroyTexture(objectTexture);
}

void PowerUp::update()
{
	if(mY > -100 && mY < 500)
	{
		mY -= 13 * mDirection;
	}
	else
	{
		mAlive = false;
	}
}

int PowerUp::getType()
{
	return mType;
}