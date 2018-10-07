#include "projectile.h"
#include "state_gameplay.h"
#include <SDL.h>
#include <SDL_image.h>

SDL_Texture* Projectile::blueBullet = NULL;
SDL_Texture* Projectile::redBullet = NULL;
SDL_Texture* Projectile::rocket = NULL;
SDL_Texture* Projectile::magic = NULL;
SDL_Texture* Projectile::bazooka = NULL;
SDL_Texture* Projectile::star = NULL;

void Projectile::init(Game* game , SpriteManager* sm)
{
	sm->loadTexture("assets/sprite/blue_ball.png");
	sm->loadTexture("assets/sprite/red_ball.png");
	sm->loadTexture("assets/sprite/planerocket.png");
	sm->loadTexture("assets/sprite/magic.png");
	sm->loadTexture("assets/sprite/bazooka.png");
	sm->loadTexture("assets/sprite/star.png");

	Projectile::blueBullet = sm->getTexture("assets/sprite/blue_ball.png");
	Projectile::redBullet = sm->getTexture("assets/sprite/red_ball.png");
	Projectile::rocket = sm->getTexture("assets/sprite/planerocket.png");
	Projectile::magic = sm->getTexture("assets/sprite/magic.png");
	Projectile::bazooka = sm->getTexture("assets/sprite/bazooka.png");
	Projectile::star = sm->getTexture("assets/sprite/star.png");
}

Projectile::Projectile(int x , int y , int dir):
GameObject(x,y,12,12)
{
	mDirection = dir;

	if(mDirection == 1)
	{
		Projectile::objectTexture = Projectile::blueBullet;

		if(State_GamePlay::getScore() > 50)
			Projectile::objectTexture = Projectile::magic;
		if(State_GamePlay::getScore() > 100)
			Projectile::objectTexture = Projectile::rocket;
		if(State_GamePlay::getScore() > 200)
			Projectile::objectTexture = Projectile::bazooka;
		if(State_GamePlay::getScore() > 500)
			Projectile::objectTexture = Projectile::star;
	}
	else
	{
		Projectile::objectTexture = Projectile::redBullet;
	}

	mX -= mWidth / 2 - 14;
}

Projectile::~Projectile()
{
	
}

void Projectile::update()
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