#ifndef powerup_h
#define powerup_h

#include <SDL.h>
#include "gameobject.h"

class PowerUp:public GameObject
{
private : 
	int mType;

public : 
	static const int ROCKET , REPAIR , SHIELD , MONEY;

	PowerUp(int x , int y , int type , Game* game , SpriteManager* sm);
	~PowerUp();

	void update();
	int getType();
};

#endif