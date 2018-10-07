#include "gameobject.h"

GameObject::GameObject(int x , int y ,
	int width , int height):mX(x),mY(y),
	mWidth(width),mHeight(height),mAlive(true)
{
	
}

GameObject::~GameObject()
{
	
}

void GameObject::DrawObject(Game* game , SpriteManager* sm)
{	
	SDL_Rect des;
	des.x = mX;
	des.y = mY;
	des.w = mWidth;
	des.h = mHeight;

	SDL_RenderCopy(game->getRenderer(),objectTexture,NULL,&des);
}

SDL_Rect GameObject::getColRect()
{
	SDL_Rect rect;
	rect.x = mX;
	rect.y = mY;
	rect.w = mWidth;
	rect.h = mHeight;

	return rect;
}

bool GameObject::isAlive()
{
	return mAlive;
}

void GameObject::Destroy()
{
	mAlive = false;
}

int GameObject::getX()
{
	return mX;
}

int GameObject::getY()
{
	return mY;
}