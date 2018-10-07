#include "state_gameplay.h"
#include "state_gameover.h"
#include <ctime>

int State_GamePlay::score = NULL;

bool State_GamePlay::init(Game* game)
{	
	this->game = game;
	sm = new SpriteManager(game);
	
	font = TTF_OpenFont("assets/Capture_it.ttf",15);

	sounds = new SoundEffect("assets/sound/smw_fireball.wav");
	Jetplane = new Player(game , sm);

	sm->loadTexture("assets/background/space3.png");
	background = sm->getTexture("assets/background/space3.png");

	score = 0;
	slowcounter = 0;
	old_fortune = 2;

	Projectile::init(game,sm);

	generate_enemies();

	PowerUp* powers = new PowerUp(20 + 25 * (rand() %20),
		20 + (rand() % 10) * 20 ,rand() % 4,game,sm);

	powerups.push_back(powers);

	damage = 8;
	
	scrollingOffset = 0;

	offSetX = 0;
	offSetY = 0;

	srand(time(NULL));

	cheat = false;

	return true;
}

bool State_GamePlay::Collision(GameObject* a, GameObject* b)
{
	SDL_Rect rectA = a->getColRect();
	SDL_Rect rectB = b->getColRect();

	if(rectA.x + rectA.w < rectB.x)return false;
	if(rectB.x + rectB.w < rectA.x)return false;
	if(rectA.y + rectA.h < rectB.y)return false;
	if(rectB.y + rectB.h < rectA.y)return false;

	return true;
}

void State_GamePlay::draw_text()
{
	sprintf(text_info,"Score: %d   Health: %d",score,Jetplane->getHealth());

	SDL_Rect des;
	des.x = 10;
	des.y = 10;
	des.w = 400;
	des.h = 25;

	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	text = TTF_RenderUTF8_Solid(font,text_info,color);
	textFont = SDL_CreateTextureFromSurface(game->getRenderer(),text);
	SDL_SetTextureAlphaMod(textFont,146);
	SDL_RenderCopy(game->getRenderer(),textFont,NULL,&des);
}

void State_GamePlay::generate_enemies()
{
	int fortune = 0;
	do
	{
		if(score <= 11)
			fortune = rand() % 2;
		if((score > 12) && (score <= 22))
			fortune = rand() % 3;
		if((score > 22) && (score <= 62))
			fortune = rand() % 4;
		if(score > 62)
			fortune = rand() % 6;
	}
	while(fortune == old_fortune);

	if((score > 22) && (fortune < 5) && (rand() % 3 == 1))
	{
		add_enemy = 
			new Enemy(320,50,rand() % 3,game,sm);
		enemies.push_back(add_enemy);
	}

	if((score > 50) && (fortune < 5) && (rand()% 3 == 1))
	{
		second_enemy = new Enemy(320,50,rand() % 4,game,sm);
		enemies.push_back(second_enemy);

		third_enemy = new Enemy(370,80,rand() % 3,game,sm);
		enemies.push_back(third_enemy);
	}

	if((score > 100) && (fortune < 5) && (rand()% 3 == 1))
	{
		fourth_enemy = new Enemy(320,50,rand() %4,game,sm);
		fifth_enemy = new Enemy(370,80,rand()%4,game,sm);
		sixth_enemy= new Enemy(400,50,rand()%5,game,sm);

		enemies.push_back(fourth_enemy);
		enemies.push_back(fifth_enemy);
		enemies.push_back(sixth_enemy);
	}

	if((score > 200) && (fortune < 5) && (rand()%3 == 1))
	{
		seventh_enemy = new Enemy(320,50,5,game,sm);
		eight_enemy = new Enemy(370,50,5,game,sm);
		ninth_enemy = new Enemy(400,80,5,game,sm);
		tenth_enemy = new Enemy(430,70,5,game,sm);

		enemies.push_back(seventh_enemy);
		enemies.push_back(eight_enemy);
		enemies.push_back(ninth_enemy);
		enemies.push_back(tenth_enemy);
	}

	if((score > 500) && (fortune < 5) && (rand() % 3 == 1))
	{
		eleven_enemy = new Enemy(320,50,20,game,sm);
		twelve_enemy = new Enemy(400,50,20,game,sm);

		enemies.push_back(eleven_enemy);
		enemies.push_back(twelve_enemy);
	}

	enemy = 
		new Enemy(70 + fortune * 100 , 20,fortune,game,sm);
	enemies.push_back(enemy);
}

void State_GamePlay::draw_enemies()
{
	std::list<Enemy*>::iterator s;
	for(s = enemies.begin(); s != enemies.end(); s++)
	{
		(*s)->DrawObject(game,sm);
	}
}

void State_GamePlay::update_enemies()
{
	std::list<Enemy*>::iterator s;
	for(s = enemies.begin(); s != enemies.end();)
	{
		(*s)->random_move();

		if((*s)->can_shoot())
		{
			Projectile* p = (*s)->fire();
			enemy_shoots.push_back(p);
		}

		if(!(*s)->isAlive())
		{
			score += (5 + (*s)->getPower());
			old_fortune = (*s)->getPower();
			delete *s;
			s = enemies.erase(s++);

			//Bonus
			if(rand() % 3 == 1 )
			{
				 PowerUp* powers = new PowerUp(20 + 25 * (rand() % 20),
					20 + (rand() % 5) * 20,
					rand() % 4 , game,sm);
				powerups.push_back(powers);
			}


		}
		else
			s++;
	}
}

void State_GamePlay::handleevents(SDL_Event* event)
{	
	if(event->type == SDL_QUIT)
		game->setquit();
}

void State_GamePlay::update(float deltaTime)
{
	events();
	update_projectile();
	update_slowcounter();
	update_enemies();
	scrollBackground();

    if(!Jetplane->isAlive())
	{
		game->pushstate(new State_GameOver());
	}

}

bool object_not_alive(GameObject* a)
{
	bool res = !a->isAlive();
	if(res)
		delete a;

	return res;
}

void State_GamePlay::events()
{
		keyboard = SDL_GetKeyboardState(NULL);
		
		if(keyboard[SDL_SCANCODE_LEFT])
			Jetplane->move(Unit::LEFT);
		if(keyboard[SDL_SCANCODE_RIGHT])
			Jetplane->move(Unit::RIGHT);
		if(keyboard[SDL_SCANCODE_UP])
			Jetplane->move(Unit::UP);
		if(keyboard[SDL_SCANCODE_DOWN])
			Jetplane->move(Unit::DOWN);
		if(keyboard[SDL_SCANCODE_SPACE])
		{	
			slowcounter++;
			if(Jetplane->can_shoot())
			{	
				Projectile* p = Jetplane->fire();
				player_shoots.push_back(p);
				sounds->PlaySoundEffect(30);
			}
		}

		if(keyboard[SDL_SCANCODE_F10])
		{	
			cheat = true;
			damage = 30000;
		}
		if(keyboard[SDL_SCANCODE_F11])
		{	
			cheat = false;
			damage = 8;
		}
}

void State_GamePlay::render()
{	
	renderbackground();
	Jetplane->DrawObject(game,sm);
	draw_projectile();
	draw_enemies();
	draw_text();
}

void State_GamePlay::draw_projectile()
{
	std::list<Projectile*>::iterator it;
	std::list<Enemy*>::iterator en;
	
	for(it = player_shoots.begin();
		it != player_shoots.end();
		it++)
	{
		(*it)->DrawObject(game,sm);

		for(en = enemies.begin(); en != enemies.end();
			en++)
		{
			if(Collision(*it,*en))
			{	
				//(*en)->hit(damage,game,sm);
				if(score > 50)
					(*en)->hit(damage + 5,game,sm);
				if(score > 100)
					(*en)->hit(damage + 10,game,sm);
				if(score > 200)
					(*en)->hit(damage + 15,game,sm);
				if(score > 500)
					(*en)->hit(damage + 40,game,sm);
				else
					(*en)->hit(damage,game,sm);

				(*it)->Destroy();
			}
		}

	}
	player_shoots.remove_if(object_not_alive);

	for(it = enemy_shoots.begin();
		it != enemy_shoots.end();
		it++)
	{
		if(Collision(*it,Jetplane))
		{	
			if(cheat)
				Jetplane->hit(0,game,sm);
			else
				Jetplane->hit(2,game,sm);

			(*it)->Destroy();
		}
		else
		{
			(*it)->DrawObject(game,sm);
		}
	}
	enemy_shoots.remove_if(object_not_alive);

	std::list<PowerUp*>::iterator power;
	for(power = powerups.begin();
		power != powerups.end();
		++power)
	{
		if(Collision(*power,Jetplane))
		{
			int type = (*power)->getType();

			if(type == PowerUp::ROCKET)
			{
				Jetplane->hit(20,game,sm);
			}
			if(type == PowerUp::MONEY)
			{
				score += 20;
			}
			if(type == PowerUp::REPAIR)
			{
				Jetplane->repair(20);
			}
			if(type == PowerUp::SHIELD)
			{
				int randomRepair = rand() % 10+1;
				Jetplane->repair(randomRepair);
			}
			(*power)->Destroy();
		}
		else
		{
			(*power)->DrawObject(game,sm);
		}
	}
	powerups.remove_if(object_not_alive);
}

void State_GamePlay::update_projectile()
{
	std::list<Projectile*>::iterator it;
	std::list<Enemy*>::iterator en;

	for(it = player_shoots.begin();
		it != player_shoots.end();
		it++)
	{
		(*it)->update();
	}
	player_shoots.remove_if(object_not_alive);

	for(it = enemy_shoots.begin();
		it != enemy_shoots.end();
		it++)
	{		
			(*it)->update();
	}
	enemy_shoots.remove_if(object_not_alive);

	std::list<PowerUp*>::iterator power;
	for(power = powerups.begin();
		power != powerups.end();
		++power)
	{
		if(Collision(*power,Jetplane))
		{
			int type = (*power)->getType();

			if(type == PowerUp::ROCKET)
			{
				Jetplane->hit(20,game,sm);
			}
			if(type == PowerUp::MONEY)
			{
				score += 20;
			}
			if(type == PowerUp::REPAIR)
			{
				Jetplane->repair(20);
			}
			if(type == PowerUp::SHIELD)
			{
				int randomRepair = rand() % 10+1;
				Jetplane->repair(randomRepair);
			}
			(*power)->Destroy();
		}
		else
		{
			(*power)->update();
			(*power)->DrawObject(game,sm);
		}
	}
	powerups.remove_if(object_not_alive);
}

void State_GamePlay::update_slowcounter()
{
	if(slowcounter >= 10)
	{
		slowcounter = 0;
		Jetplane->allow_shooting();
		std::list<Enemy*>::iterator en;

		for(en = enemies.begin(); 
			en != enemies.end();
			++en)
		{
			(*en)->allow_shooting();
		}

		if(enemies.size() < 2)
		{
			generate_enemies();
		}
	}
}

void State_GamePlay::scrollBackground()
{	
	scrollingOffset+=2;
	if(scrollingOffset > BACKGROUND_HEIGHT)
		scrollingOffset = 0;

	destination.x = offSetX;
	destination.y = scrollingOffset - BACKGROUND_HEIGHT;
	destination.w = BACKGROUND_WIDTH;
	destination.h = BACKGROUND_HEIGHT;

}

void State_GamePlay::renderbackground()
{	
	SDL_Rect vertical;
	vertical.x = offSetX;
	vertical.y = offSetY + scrollingOffset;
	vertical.w = BACKGROUND_WIDTH;
	vertical.h = BACKGROUND_HEIGHT;

	SDL_RenderCopy(game->getRenderer(),background,NULL,&destination);
	SDL_RenderCopy(game->getRenderer(),background,NULL,&vertical);
}

void State_GamePlay::quit()
{	
	TTF_CloseFont(font);
	SDL_FreeSurface(text);
	SDL_DestroyTexture(textFont);
	SDL_DestroyTexture(background);
	delete Jetplane;
	delete sounds;
	delete sm;



	for(std::list<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); ++i)
	{
		delete (*i);
	}
	enemies.clear();

	for(std::list<Projectile*>::iterator i = player_shoots.begin(); i != player_shoots.end(); ++i)
	{
		delete (*i);
	}
	player_shoots.clear();

	for(std::list<Projectile*>::iterator i = enemy_shoots.begin(); i != enemy_shoots.end(); ++i)
	{
		delete (*i);
	}
	enemy_shoots.clear();

	for(std::list<PowerUp*>::iterator i = powerups.begin(); i != powerups.end(); ++i)
	{
		delete (*i);
	}
	powerups.clear();
}

int State_GamePlay::getScore()
{
	return score;
}

State_GamePlay::~State_GamePlay()
{
	
}
