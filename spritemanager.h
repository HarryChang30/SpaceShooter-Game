#ifndef spritemanager_h
#define spritemanager_h

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <iterator>
#include <string>

class Game;

class SpriteManager
{
private : 
	std::map<std::string , SDL_Texture*> textures;
	Game* game;

public :
	SpriteManager(Game* game);
	~SpriteManager();

	void loadTexture(std::string filename);

	SDL_Texture* getTexture(std::string filename);
};

#endif