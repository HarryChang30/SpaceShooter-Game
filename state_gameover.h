#ifndef state_gameover_h
#define state_gameover_h

#include "gamestate.h"
#include "spritemanager.h"
#include "state_gameplay.h"

class State_GameOver:public GameState
{
private : 
	SpriteManager* sm;

	float fading;

	SDL_Texture* gameoverBackground;
	SDL_Surface* gameover;
	SDL_Texture* gameoverFont;

	SDL_Surface* button;
	SDL_Texture* buttonFont;

	SDL_Surface* scoresSurface;
	SDL_Texture* scores;

	TTF_Font* font;

	int scrollingOffset;
	int offSetX , offSetY;

	void renderBackground();
	void scrollBackground();
	void renderTextOne();
	void renderTextTwo();
	void renderTextThree();

	SDL_Rect destination;

public : 
	~State_GameOver();
	bool init(Game* game);
	void handleevents(SDL_Event* event);
	void update(float deltaTime);
	void render();
	void quit();
};

#endif