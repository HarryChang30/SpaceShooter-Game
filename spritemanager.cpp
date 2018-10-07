#include "spritemanager.h"
#include "game.h"

SpriteManager::SpriteManager(Game* game)
{	
	this->game = game;
}

void SpriteManager::loadTexture(std::string filename)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(game->getRenderer(),filename.c_str());

	textures.insert(std::pair<std::string , SDL_Texture*>(filename,texture));
}

SDL_Texture* SpriteManager::getTexture(std::string filename)
{
	SDL_Texture* texture = NULL;
	std::map<std::string , SDL_Texture*>::iterator i;

	i= textures.find(filename);
	texture = i->second;

	return texture;
}

SpriteManager::~SpriteManager()
{
	std::map<std::string, SDL_Texture*>::iterator i;
	for(i = textures.begin(); i != textures.end(); i++)
	{
		SDL_DestroyTexture(i->second);
	}
	textures.clear();
}