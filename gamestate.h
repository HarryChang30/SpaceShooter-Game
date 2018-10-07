#ifndef gamestate_h
#define gamestate_h

#include <SDL.h>
#include "game.h"

class GameState
{
protected : 
	Game* game;
public : 
	virtual ~GameState(){}
	virtual bool init(Game* game) = 0;
	virtual void handleevents(SDL_Event* event) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
	virtual void quit() = 0;
};

#endif