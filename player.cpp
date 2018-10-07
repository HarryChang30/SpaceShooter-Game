#include "player.h"

Player::Player(Game* game , SpriteManager* sm):Unit(300,400,sm)
{	
	mTopY = 0 + 300;
	mBottomY = 430;
	mName = "jetplane";
	mHealth = 100;
	load_image(game,sm);
}

Player::~Player()
{
	
}

void Player::repair(int points)
{
	mHealth += points;
	static int maximum_health = 125;
	if(mHealth > maximum_health)
		mHealth = maximum_health;
}

bool Player::can_shoot()
{
	return mShoots < 3;
}

bool Player::isAI()
{
	return false;
}
