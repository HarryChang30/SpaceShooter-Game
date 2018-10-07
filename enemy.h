#ifndef enemy_h
#define enemy_h

#include "unit.h"

class Enemy:public Unit
{
private : 
	int mMoves;
	int mPower;
	int mChaoticLevel;

public : 
	Enemy(int x , int y , int power , Game* game ,
		SpriteManager* sm);
	~Enemy();
	bool can_shoot();
	bool isAI();
	void random_move();
	void change_direction();
	int getPower();
};

#endif