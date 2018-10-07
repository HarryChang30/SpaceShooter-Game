#include "game.h"
#include "state_menu.h"
#include "state_gameover.h"
#include "state_menutwo.h"

int main(int argc , char** args)
{	
	Game g;

	if(g.init(new State_Menu()))
		g.thread();

	//if(g.init(new State_MenuTwo()))
	//	g.thread();

	//if(g.init(new State_GameOver()))
	//	g.thread();

	return 0;
}