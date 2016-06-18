#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <Windows.h>

int main()
{
	Game game;
	if (game.checkFiles())
	{
		srand(time(NULL));
		game.start();
	}
	else MessageBox(NULL, "You are missing some game files!", "ERROR", NULL);
	return 0;
}