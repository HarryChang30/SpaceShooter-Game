#ifndef gameobject_h
#define gameobject_h
#include <SDL.h>
#include "game.h"
#include "spritemanager.h"

class GameObject
{
protected : 
	int mX;
	int mY;
	int mDirection;

	int mWidth;
	int mHeight;

	bool mAlive;

	SDL_Texture* objectTexture;
public : 
	GameObject(int x , int y , int width , int height);
	virtual ~GameObject();

	void DrawObject(Game* game , SpriteManager* sm);
	void Destroy();

	bool isAlive();
	SDL_Rect getColRect();

	int getX();
	int getY();
};

#endif