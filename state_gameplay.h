#ifndef state_gameplay_h
#define state_gameplay_h

#include "gamestate.h"
#include "spritemanager.h"
#include "sound.h"
#include "soundeffect.h"
#include "player.h"
#include "enemy.h"
#include "powerup.h"
#include <list>


class State_GamePlay:public GameState
{
private : 
	SpriteManager* sm;

	SoundEffect* sounds;

	//Player
	Player* Jetplane;

	//background
	SDL_Texture* background; 

	//Font
	SDL_Surface* text;
	SDL_Texture* textFont;
	TTF_Font* font;

	//Enemy container
	std::list<Enemy*> enemies;
	Enemy* add_enemy;
	Enemy* second_enemy;
	Enemy* third_enemy;
	Enemy* fourth_enemy;
	Enemy* fifth_enemy;
	Enemy* sixth_enemy;
	Enemy* seventh_enemy;
	Enemy* eight_enemy;
	Enemy* ninth_enemy;
	Enemy* tenth_enemy;
	Enemy* eleven_enemy;
	Enemy* twelve_enemy;
	Enemy* enemy;

	//Enemy* enemy[13];

	//Powerup container
	std::list<PowerUp*> powerups;
	

	//private methods
	void renderbackground();

	//projectiles enemy and player
	std::list<Projectile*> player_shoots;
	std::list<Projectile*> enemy_shoots;

	//generate enemy
	void generate_enemies();
	
	//events input
	void events();

	//collision
	bool Collision(GameObject* a, GameObject* b);

	//draw enemy and player projectile
	void draw_projectile();
	void draw_enemies();
	void draw_text();

	//update enemy and player projectile
	void update_projectile();
	void update_slowcounter();
	void update_enemies();

	//gameplay variables
	static int score;
	int slowcounter;
	int enemycounter;
	int old_fortune;
	char text_info[100];

	//damage
	int damage;

	//scroll background
	int offSetX;
	int offSetY;
	SDL_Rect source;
	SDL_Rect destination;
	int scrollingOffset;
	void scrollBackground();

	const Uint8* keyboard;
	bool cheat;

public : 
	~State_GamePlay();
	bool init(Game* game);
	void handleevents(SDL_Event* event);
	void update(float deltaTime);
	void render();
	
	void quit();

	static int getScore();
};

#endif