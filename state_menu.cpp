#include "state_menu.h"
#include "state_menutwo.h"

bool State_Menu::init(Game* game)
{
	this->game = game;

	sm = new SpriteManager(game);

	sm->loadTexture("assets/background/classic space.png");
	menuBackground = sm->getTexture("assets/background/classic space.png");

	TitleFont = TTF_OpenFont("assets/Capture_it.ttf",30);

	fading = 0.0f;

	return true;
}

void State_Menu::handleevents(SDL_Event* event)
{
	if(event->type == SDL_QUIT)
		game->setquit();
}

void State_Menu::renderBackground()
{
	SDL_Rect des;
	des.x = 0;
	des.y = 0;
	des.w = SCREEN_WIDTH;
	des.h = SCREEN_HEIGHT;
	SDL_RenderCopy(game->getRenderer(),menuBackground,NULL,&des);
}

void State_Menu::renderTextOne()
{
	char text[100];
	sprintf(text,"S P A C E    S H O O T E R");

	SDL_Rect fontdes;
	fontdes.x = 130;
	fontdes.y = 170;
	fontdes.w = 400;
	fontdes.h = 50;

	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	title = TTF_RenderText_Solid(TitleFont,text,color);
	titleFont = SDL_CreateTextureFromSurface(game->getRenderer(),title);

	SDL_SetTextureAlphaMod(titleFont,146);
	SDL_RenderCopy(game->getRenderer(),titleFont,NULL,&fontdes);


}

void State_Menu::renderTextTwo()
{
	char infotext[100];
	sprintf(infotext,"PRESS ENTER TO PLAY THE GAME");

	SDL_Rect infodes;
	infodes.x = 150;
	infodes.y = 270;
	infodes.w = 350;
	infodes.h = 40;

	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	info = TTF_RenderText_Solid(TitleFont,infotext,color);
	infoFont = SDL_CreateTextureFromSurface(game->getRenderer(),info);

	SDL_SetTextureAlphaMod(infoFont,146);

	if((int)fading > 0)
		SDL_RenderCopy(game->getRenderer(),infoFont,NULL,&infodes);


}

void State_Menu::renderTextThree()
{
	char textinfo[100];
	sprintf(textinfo,"HOW TO PLAY F1");

	SDL_Rect rect;
	rect.x = 190;
	rect.y = 350;
	rect.w = 250;
	rect.h = 30;

	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	infotwo = TTF_RenderText_Solid(TitleFont,textinfo,color);
	infotwoFont = SDL_CreateTextureFromSurface(game->getRenderer(),infotwo);

	SDL_SetTextureAlphaMod(infotwoFont,146);

	SDL_RenderCopy(game->getRenderer(),infotwoFont,NULL,&rect);
}

void State_Menu::render()
{
	renderBackground();
	renderTextOne();
	renderTextTwo();
	renderTextThree();
}

void State_Menu::update(float deltaTime)
{
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);

	if(keyboard[SDL_SCANCODE_RETURN])
		game->pushstate(new State_GamePlay());
	if(keyboard[SDL_SCANCODE_F1])
		game->pushstate(new State_MenuTwo());

	fading += 2 * deltaTime;
	if(fading >= 2.0f)
		fading = 0.0f;
}

void State_Menu::quit()
{	
	delete sm;
}

State_Menu::~State_Menu()
{	
	TTF_CloseFont(TitleFont);
	SDL_DestroyTexture(titleFont);
	SDL_DestroyTexture(infoFont);
	SDL_DestroyTexture(menuBackground);
	SDL_FreeSurface(title);
	SDL_FreeSurface(info);
}