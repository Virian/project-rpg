#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <Windows.h>

int main()
{
	Game game; /*utworzenie obiektu gry*/
	if (game.checkFiles()) /*sprawdzenie czy s¹ wszystkie potrzebne pliki*/
	{
		srand(time(NULL)); /*seed do generowania losowych liczb*/
		game.start(); /*start gry*/
	}
	else MessageBox(NULL, "You are missing some game files!", "ERROR", NULL); /*wyrzucenie komunikatu o bledzie*/
	return 0;
}