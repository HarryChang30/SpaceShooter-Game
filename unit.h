#ifndef unit_h
#define unit_h

#include <SDL.h>
#include <string>
#include "gameobject.h"
#include "projectile.h"

class Unit:public GameObject
{
protected : 
	int mTopY;
	int mBottomY;

	std::string mName;

	int mHealth;
	int mShoots;
	float mSpeed;

	bool mAI;

public : 
	static const int LEFT , RIGHT , UP , DOWN;

	Unit(int x , int y , SpriteManager* sm);
	virtual ~Unit();

	void load_image(Game* game , SpriteManager* sm);
	void move();

	virtual bool isAI();
	virtual void move(int direction);
	//Projectile
	Projectile* fire();

	void hit(int damage , Game* game , SpriteManager* sm);

	int getHealth();
	void allow_shooting();
	virtual bool can_shoot();

};

#endif