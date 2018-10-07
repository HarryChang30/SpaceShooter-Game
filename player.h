#ifndef player_h
#define player_h

#include "unit.h"

class Player:public Unit
{
public : 
	Player(Game* game , SpriteManager* sm);
	~Player();
	void repair(int bonus);
	bool can_shoot();
	bool isAI();

};

#endif