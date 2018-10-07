#ifndef projectile_h
#define projectile_h

#include <SDL.h>
#include <iostream>
#include "gameobject.h"

class Projectile:public GameObject
{
private : 
	static SDL_Texture* blueBullet;
	static SDL_Texture* redBullet;
	static SDL_Texture* rocket;
	static SDL_Texture* magic;
	static SDL_Texture* bazooka;
	static SDL_Texture* star;

public : 
	static void init(Game* game , SpriteManager* sm);

	Projectile(int x , int y, int dir);
	~Projectile();

	void update();
};

#endif