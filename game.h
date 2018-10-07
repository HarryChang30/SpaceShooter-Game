#ifndef game_h
#define game_h

#include <SDL.h>
#include <vector>
#include "sound.h"
#include <SDL_ttf.h>

using namespace std;

const int BACKGROUND_WIDTH = 1024;
const int BACKGROUND_HEIGHT = 576;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class GameState;

class Game
{
private : 
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;



	bool Quit;

	vector<GameState*>states;

	Uint32 newTime;
	Uint32 oldTime;

	Uint32 nextTime;
	Uint32 time_left();

	void update();
	void render();
	void quit();

	Sound* music;

public : 

	Game();
	~Game();
	bool init(GameState* state);
	void thread();
	void pushstate(GameState* state);
	void popstate();
	void setquit();

	SDL_Renderer* getRenderer();
};

#endif