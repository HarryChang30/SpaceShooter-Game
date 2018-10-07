#include "unit.h"
#include <SDL.h>
#include <SDL_image.h>

const int Unit::UP = 1;
const int Unit::DOWN = 2;
const int Unit::LEFT = 3;
const int Unit::RIGHT = 4;

Unit::Unit(int x , int y , SpriteManager* sm):GameObject(x,y,50,50),
	mShoots(0),mSpeed(7)
{
	
}

Unit::~Unit()
{
	
}

void Unit::load_image(Game* game , SpriteManager* sm)
{
	std::string filename = "assets/sprite/" + mName +".png";

	sm->loadTexture(filename.c_str());
	objectTexture = sm->getTexture(filename.c_str());
}

void Unit::move()
{
	move(mDirection);
}

Projectile* Unit::fire()
{
	int xShift = 21 / 2;
	int yShift = (isAI() ? 21 : 0);
	mShoots++;

	Projectile* p = 
		new Projectile(mX + xShift , 
		mY + yShift , (isAI() ? -1 : 1));

	return p;
}

void Unit::move(int direction)
{
	switch(direction)
	{
	case Unit::UP : 
		if(mY > mTopY)
			mY -= mSpeed;
		else
			mDirection = DOWN;
		break;
	case Unit::DOWN : 
		if(mY < mBottomY)
			mY += mSpeed;
		else
			mDirection = UP;
		break;
	case Unit::LEFT : 
		if(mX > 3)
			mX -= mSpeed;
		else
			mDirection = RIGHT;
		break;
	case Unit::RIGHT : 
		if(mX < 600)
			mX += mSpeed;
		else
			mDirection = LEFT;
		break;
	default : 
		break;
	}
}

void Unit::hit(int damage , Game* game , SpriteManager* sm)
{
	mHealth -= damage;
	if(mHealth < 0)
	{
		mAlive = false;

		SDL_Rect src;
		src.x = 0;
		src.w = 0;
		src.w = mWidth;
		src.h = mHeight;

		SDL_Rect des;
		des.x = mX;
		des.y = mY;
		des.w = mWidth;
		des.h = mHeight;

		sm->loadTexture("assets/sprite/explosion.png");		
		objectTexture = sm->getTexture("assets/sprite/explosion.png");
	}
}

int Unit::getHealth()
{
	return mHealth;
}

bool Unit::isAI()
{
	return true;
}

bool Unit::can_shoot()
{
	return false;
}

void Unit::allow_shooting()
{
	mShoots = 0;
}