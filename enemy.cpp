#include "enemy.h"
#include <time.h>

Enemy::Enemy(int x , int y , int power , Game* game , SpriteManager* sm):
Unit(x,y,sm),mMoves(0),mPower(power)
{
	srand(time(NULL));

	mDirection = rand() % 4 + 1;
	mTopY = 0;
	mBottomY = 360;
	mHealth = power * 25 + 20;
	mChaoticLevel = 1;

	switch(mPower)
	{
	case 0 :
		mName = "smallplane";
		mSpeed = 5;
		break;
	case 1 : 
		mName = "orangeplane";
		mChaoticLevel = 2;
		break;
	case 2 : 
		mName = "greyplane";
		break;
	case 3 : 
		mName = "darkplane";
		mSpeed = 3;
		break;
	case 4 : 
		mName = "redplane";
		mChaoticLevel = 2;
		break;
	case 5 : 
		mName = "unknownplane";
		mSpeed = 3;
		break;
	case 20 : 
		mName = "miniboss";
		mChaoticLevel = 5;
		break;
	default : 
		break;
	}

	load_image(game,sm);
}

Enemy::~Enemy()
{
	
}

void Enemy::change_direction()
{
	mDirection = rand() % 4 + 1;
}

void Enemy::random_move()
{
	mMoves++;
	move();

	if(mMoves >= ( 30 - 10 * mChaoticLevel))
	{
		mMoves = 0;
		if ( rand() % mChaoticLevel == 0)
			change_direction();
	}
}

int Enemy::getPower()
{
	return mPower;
}

bool Enemy::can_shoot()
{
	return (mPower >= 1) && (mShoots < mPower);
}

bool Enemy::isAI()
{
	return true;
}