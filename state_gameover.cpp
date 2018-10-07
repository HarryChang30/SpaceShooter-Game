#include "state_gameover.h"
#include "state_menu.h"
#include "state_gameplay.h"

bool State_GameOver::init(Game* game)
{
	this->game = game;

	sm = new SpriteManager(game);

	sm->loadTexture("assets/background/space.png");
	gameoverBackground = sm->getTexture("assets/background/space.png");

	font = TTF_OpenFont("assets/Capture_it.ttf",15);

	fading = 0.0f;

	scrollingOffset = 0;
	offSetX = 0;
	offSetY = 0;

	return true;
}

void State_GameOver::handleevents(SDL_Event* event)
{
	if(event->type == SDL_QUIT)
		game->setquit();
}

void State_GameOver::scrollBackground()
{
	scrollingOffset += 2;
	if(scrollingOffset > BACKGROUND_HEIGHT)
		scrollingOffset = 0;

	destination.x = offSetX;
	destination.y = scrollingOffset - BACKGROUND_HEIGHT;
	destination.w = BACKGROUND_WIDTH;
	destination.h = BACKGROUND_HEIGHT;

}

void State_GameOver::update(float deltaTime)
{
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);

	if(keyboard[SDL_SCANCODE_F2])
		game->pushstate(new State_Menu());


	scrollBackground();


	fading += 2*deltaTime;
	if(fading >= 2.0f)
		fading = 0.0f;
}

void State_GameOver::renderBackground()
{
	SDL_Rect vertical;
	vertical.x = offSetX;
	vertical.y = offSetY + scrollingOffset;
	vertical.w = BACKGROUND_WIDTH;
	vertical.h = BACKGROUND_HEIGHT;

	SDL_RenderCopy(game->getRenderer(),gameoverBackground,NULL,&destination);
	SDL_RenderCopy(game->getRenderer(),gameoverBackground,NULL,&vertical);
}

void State_GameOver::renderTextOne()
{
	SDL_Rect over;
	over.x = 125;
	over.y = 180;
	over.w = 400;
	over.h = 25;

	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	char text[100];
	sprintf(text,"G  A  M  E       O  V  E  R");

	gameover = TTF_RenderUTF8_Solid(font,text,color);
	gameoverFont = SDL_CreateTextureFromSurface(game->getRenderer(),
		gameover);

	SDL_RenderCopy(game->getRenderer(),gameoverFont,NULL,&over);

	SDL_FreeSurface(gameover);
}

void State_GameOver::renderTextTwo()
{
	SDL_Rect scorefont;
	scorefont.x = 200;
	scorefont.y = 240;
	scorefont.w = 250;
	scorefont.h = 25;

	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	char textScore[100];
	sprintf(textScore,"YOUR SCORE : %d",State_GamePlay::getScore());

	scoresSurface = TTF_RenderUTF8_Solid(font,textScore,color);
	scores = SDL_CreateTextureFromSurface(game->getRenderer(),scoresSurface);

	SDL_RenderCopy(game->getRenderer(),scores,NULL,&scorefont);

	SDL_FreeSurface(scoresSurface);
}

void State_GameOver::renderTextThree()
{
	SDL_Rect secondWord;
	secondWord.x = 225;
	secondWord.y = 285;
	secondWord.w = 200;
	secondWord.h = 20;

	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;


	char textTwo[100];
	sprintf(textTwo , "PRESS F2 BACK TO MENU");

	button = TTF_RenderUTF8_Solid(font,textTwo,color);
	buttonFont = SDL_CreateTextureFromSurface(game->getRenderer(),
		button);

	if((int)fading > 0)
		SDL_RenderCopy(game->getRenderer(),buttonFont,
		NULL,&secondWord);

	SDL_FreeSurface(button);
}

void State_GameOver::render()
{
	renderBackground();
	renderTextOne();
	renderTextTwo();
	renderTextThree();
}

void State_GameOver::quit()
{	
	TTF_CloseFont(font);
	SDL_DestroyTexture(gameoverBackground);
	SDL_DestroyTexture(gameoverFont);
	SDL_DestroyTexture(scores);

	SDL_DestroyTexture(buttonFont);
	delete sm;
}

State_GameOver::~State_GameOver()
{	

}