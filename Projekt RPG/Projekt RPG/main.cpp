#include "Game.h"
#include <ctime>
#include <cstdlib>

/*Reminder - usunac using namespace z plikow .h*/

int main()
{
	Game game;
	srand(time(NULL));
	game.start();
	return 0;
}