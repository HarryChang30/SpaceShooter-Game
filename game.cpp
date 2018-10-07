#include "game.h"
#include "gamestate.h"
#include <iostream>
#include <time.h>

Game::Game()
{
	window = NULL;
	renderer = NULL;

	music = new Sound("assets/sound/Cold_stone.mp3");

	oldTime = 0;

	Quit = false;
}

bool Game::init(GameState* state)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	window = SDL_CreateWindow("Space Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	srand(time(NULL));
	pushstate(state);
	return true;
}

void Game::thread()
{	
	music->PlayMusic(50);

	static int time_interval = 1000/25;
	nextTime = SDL_GetTicks() + time_interval;

	while (!Quit)
	{
		update();
		render();
		SDL_Delay(time_left());
		nextTime += time_interval;
	}

	quit();
}

Uint32 Game:: time_left()
{
	Uint32 now = SDL_GetTicks();
	return (nextTime <= now) ? 0 : nextTime - now;
}

void Game::update()
{
	while(SDL_PollEvent(&event))
	{
		if(states.size() > 0)
			states.back()->handleevents(&event);
	}

	if(states.size() > 0)
	{
		oldTime = newTime;
		newTime = SDL_GetTicks();

		if(newTime > oldTime)
		{
			float deltaTime = (float)(newTime - oldTime) / 1000.0f;
			states.back()->update(deltaTime);
		}
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	if(states.size() > 0)
		states.back()->render();

	SDL_RenderPresent(renderer);
}

void Game::quit()
{
	while(states.size() > 0)
	{
		states.back()->quit();
		delete states.back();
		states.pop_back();
	}
	states.clear();

	delete music;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_Quit();
}

void Game::setquit()
{
	Quit = true;
}

SDL_Renderer* Game::getRenderer()
{
	return renderer;
}

void Game::pushstate(GameState* state)
{
	states.push_back(state);
	if(state->init(this) == false)
	{
		Quit = true;
	}
}

void Game::popstate()
{
	states.back()->quit();
	delete states.back();
	states.pop_back();

	if(states.size() == 0)
	{
		Quit = true;
	}
}

Game::~Game()
{	

}