#ifndef state_menu_h
#define state_menu_h

#include "gamestate.h"
#include "spritemanager.h"
#include "state_gameplay.h"


class State_Menu:public GameState
{
private : 
	SpriteManager* sm;
	SDL_Texture* menuBackground;
	SDL_Surface* title;
	SDL_Texture* titleFont;
	

	SDL_Surface* info;
	SDL_Texture* infoFont;

	SDL_Surface* infotwo;
	SDL_Texture* infotwoFont;

	TTF_Font* TitleFont;

	float fading;

	void renderBackground();
	void renderTextOne();
	void renderTextTwo();
	void renderTextThree();


public : 
	~State_Menu();
	bool init(Game* game);
	void handleevents(SDL_Event* event);
	void update(float deltaTime);
	void render();
	void quit();
};

#endif