#include "state_menutwo.h"
#include "state_menu.h"

bool State_MenuTwo::init(Game* game)
{	
	this->game = game;

	sm = new SpriteManager(game);

	sm->loadTexture("assets/background/keyboard.png");
	sm->loadTexture("assets/background/credits.png");

	font = TTF_OpenFont("assets/Capture_it.ttf",15);

	controler = sm->getTexture("assets/background/keyboard.png");
	credits = sm->getTexture("assets/background/credits.png");

	fading = 0.0f;

	return true;
}

void State_MenuTwo::handleevents(SDL_Event* event)
{
	if(event->type == SDL_QUIT)
		game->setquit();
}

void State_MenuTwo::update(float deltaTime)
{
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);

	if(keyboard[SDL_SCANCODE_ESCAPE])
		game->pushstate(new State_Menu());

	fading += 2 * deltaTime;
	if(fading >= 2.0f)
		fading = 0.0f;
}

void State_MenuTwo::renderControler()
{
	SDL_Rect rect;
	rect.x = 80;
	rect.y = 240;
	rect.w = 500;
	rect.h = 240;

	SDL_RenderCopy(game->getRenderer(),controler,NULL,&rect);
}

void State_MenuTwo::renderCredits()
{
	SDL_Rect rect;
	rect.x = 370;
	rect.y = 20;
	rect.w = 200;
	rect.h = 200;

	SDL_RenderCopy(game->getRenderer(),credits,NULL,&rect);
}

void State_MenuTwo::renderText()
{
	char text[100];
	sprintf(text,"ESC");

	SDL_Color color = {255,255,255};

	escfont = TTF_RenderText_Solid(font,text,color);
	escFont = SDL_CreateTextureFromSurface(game->getRenderer(),escfont);

	SDL_Rect rect = {0,0,70,40};

	SDL_RenderCopy(game->getRenderer(),escFont,NULL,&rect);

	SDL_FreeSurface(escfont);
}

void State_MenuTwo::renderTextTwo()
{
	char text[100];
	sprintf(text,"SPECIAL THANKS TO LECTURER : KO ALEXANDER");

	SDL_Color color = {255,255,255};

	onefont = TTF_RenderText_Solid(font,text,color);
	oneFont = SDL_CreateTextureFromSurface(game->getRenderer(),onefont);

	SDL_Rect rect = {10,100,350,35};

	if((int)fading > 0)
		SDL_RenderCopy(game->getRenderer(),oneFont,NULL,&rect);

	SDL_FreeSurface(onefont);
}

void State_MenuTwo::render()
{
	renderControler();
	renderCredits();
	renderText();
	renderTextTwo();
}

void State_MenuTwo::quit()
{
	
}

State_MenuTwo::~State_MenuTwo()
{	
	TTF_CloseFont(font);
	SDL_DestroyTexture(controler);
	SDL_DestroyTexture(credits);
	SDL_DestroyTexture(escFont);
	SDL_DestroyTexture(oneFont);
}