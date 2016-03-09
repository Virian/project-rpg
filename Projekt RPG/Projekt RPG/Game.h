#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Game
{
private:
	RenderWindow window;
	Font font;
	void menu();
protected:
	enum GameState {MENU, GAME, GAME_OVER, END};
	GameState state;
public:
	Game();
	~Game();
	void start();
};