#ifndef state_menutwo_h
#define state_menutwo_h

#include "gamestate.h"
#include "spritemanager.h"

class State_MenuTwo:public GameState
{
private : 
	SpriteManager* sm;
	SDL_Texture* controler;
	SDL_Texture* credits;

	TTF_Font* font;
	SDL_Surface* escfont;
	SDL_Texture* escFont;

	SDL_Surface* onefont;
	SDL_Texture* oneFont;

	void renderControler();
	void renderCredits();
	void renderText();
	void renderTextTwo();

	float fading;

public : 
	~State_MenuTwo();
	bool init(Game* game);
	void handleevents(SDL_Event* event);
	void update(float deltaTime);
	void render();
	void quit();
};

#endif